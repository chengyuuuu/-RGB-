/*RGB 三色LED灯应用函数头文件 */
#ifndef __RGB_APP_H_
#define __RGB_APP_H_

#include "RGB_har.h"

/*闪烁循环方向枚举定义*/
typedef enum {
    RGB_SHINGING_DIR_UP = 0,
    RGB_SHINGING_DIR_DOWN 

} RGB_SHINGING_DIR;

/*闪烁模式枚举定义*/
typedef enum {
    RGB_SHINGING_MODE_BREATH = 0,
    RGB_SHINGING_MODE_HEART_BEAT,
    RGB_SHINGING_MODE_CO
} RGB_SHINGING_MODE;

/*多种常用颜色枚举定义*/
typedef enum  {
    RGB_RED = 0,
    RGB_BLUE,
    RGB_GREEN,
    RGB_WHITE,
    RGB_PINK,
    RGB_PURPLE,
    RGB_YELLOW
} RGB_COLOR;

/*颜色对象结构体定义*/
struct RGB_COLOR_STRUCT {
    f32 red_vector; //各颜色分量, 实际亮度为 brightness * vector, 要保证在0 - 1之间，无参数检查机制
    f32 green_vector;
    f32 blue_vector;
};

/*呼吸灯模式对象结构体定义*/
struct RGB_SHINGING_MODE_STRUCT_BREATH {
    BITWIDTH speed; //速度，每次执行函数时的捕获比较寄存器增量
    BITWIDTH brightness; //最大亮度，捕获比较寄存器最大值
    BITWIDTH darkness; //最大暗度，捕获比较寄存器最小值

    u8 dir; //当前计数方向
    BITWIDTH count; //当前时间
};

/*常亮模式对象结构体定义*/
struct RGB_SHINGING_MODE_STRUCT_CO {
    BITWIDTH brightness;
};

/*心跳灯模式对象结构体定义*/
struct RGB_SHINGING_MODE_STRUCT_HEART {
    BITWIDTH brightness;
    BITWIDTH darkness;

    BITWIDTH beatPoint; //第一次在0点跳动，第二次在哪跳动
    BITWIDTH beatTime; //从跳起到落下时间

    BITWIDTH count; //当前时间
    BITWIDTH period; //心跳周期
};


struct RGB_COLOR_STRUCT* RGB_getColorStruct(f32 red_vector, f32 green_vector, f32 blue_vector);
struct RGB_SHINGING_MODE_STRUCT_BREATH* RGB_getShingingModeStruct_breath(BITWIDTH brightness, BITWIDTH darkness, BITWIDTH speed); 
struct RGB_SHINGING_MODE_STRUCT_HEART* RGB_getShingingModeStruct_heart(BITWIDTH brightness, BITWIDTH darkness, \
                                                    BITWIDTH beatPoint, BITWIDTH beatTime, BITWIDTH period);
struct RGB_SHINGING_MODE_STRUCT_CO* RGB_getShingingModeStruct_CO(BITWIDTH brightness);
void RGB_breath_output(struct RGB_COLOR_STRUCT colorStruct, struct RGB_SHINGING_MODE_STRUCT_BREATH* modeStruct, u8 status);
void RGB_heartBeat_output(struct RGB_COLOR_STRUCT colorStruct, struct RGB_SHINGING_MODE_STRUCT_HEART* modeStruct, u8 status);
void RGB_ConstantOn_output(struct RGB_COLOR_STRUCT colorStruct, struct RGB_SHINGING_MODE_STRUCT_CO* modeStruct, u8 status);
void RGB_quickOutput(RGB_COLOR color, BitStatus status);
void RGB_mixOutput(f32 red_vector, f32 green_vector, f32 blue_vector);

#endif