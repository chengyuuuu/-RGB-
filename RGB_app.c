/*RGB 三色LED灯应用函数源文件 */
#include "RGB_app.h"

/*根据输入参数，获得一个颜色对象句柄*/
struct RGB_COLOR_STRUCT* RGB_getColorStruct(f32 red_vector, f32 green_vector, f32 blue_vector) {
    
    struct RGB_COLOR_STRUCT* colorStruct;

    /*获取颜色结构体内存空间*/
    colorStruct = (struct RGB_COLOR_STRUCT*)malloc(sizeof(struct RGB_COLOR_STRUCT));
    if (colorStruct == 0) {
        return (struct RGB_COLOR_STRUCT *)0;
    }

    /*初始化结构体相关参数*/
    colorStruct->red_vector = red_vector;
    colorStruct->green_vector = green_vector;
    colorStruct->blue_vector = blue_vector;

    /*返回颜色句柄结构体*/
    return colorStruct;
}

/*根据输入参数，获得一个呼吸灯模式对象句柄*/
struct RGB_SHINGING_MODE_STRUCT_BREATH* RGB_getShingingModeStruct_breath(BITWIDTH brightness, BITWIDTH darkness, BITWIDTH speed) {

    struct RGB_SHINGING_MODE_STRUCT_BREATH* modeStruct;

    /*获取颜色结构体内存空间*/
    modeStruct = (struct RGB_SHINGING_MODE_STRUCT_BREATH *)malloc(sizeof(struct RGB_SHINGING_MODE_STRUCT_BREATH));
    if (modeStruct == 0) {
        return (struct RGB_SHINGING_MODE_STRUCT_BREATH *)0;
    }

    modeStruct->brightness = brightness;
    modeStruct->darkness = darkness;
    modeStruct->speed = speed;

    return modeStruct;
}

/*根据输入参数，获得一个心跳灯模式对象句柄*/
struct RGB_SHINGING_MODE_STRUCT_HEART* RGB_getShingingModeStruct_heart(BITWIDTH brightness, BITWIDTH darkness, BITWIDTH beatPoint, BITWIDTH beatTime, BITWIDTH period) {

    struct RGB_SHINGING_MODE_STRUCT_HEART* modeStruct;

    /*获取颜色结构体内存空间*/
    modeStruct = (struct RGB_SHINGING_MODE_STRUCT_HEART *)malloc(sizeof(struct RGB_SHINGING_MODE_STRUCT_HEART));
    if (modeStruct == 0) {
        return (struct RGB_SHINGING_MODE_STRUCT_HEART *)0;
    }

    modeStruct->beatPoint = beatPoint;
    modeStruct->beatTime = beatTime;
    modeStruct->brightness = brightness;
    modeStruct->darkness = darkness;
    modeStruct->period = period;

    return modeStruct;
}

/*根据输入参数，获得一个常亮灯模式对象句柄*/
struct RGB_SHINGING_MODE_STRUCT_CO* RGB_getShingingModeStruct_CO(BITWIDTH brightness) {

    struct RGB_SHINGING_MODE_STRUCT_CO* modeStruct;

    /*获取颜色结构体内存空间*/
    modeStruct = (struct RGB_SHINGING_MODE_STRUCT_CO *)malloc(sizeof(struct RGB_SHINGING_MODE_STRUCT_CO));
    if (modeStruct == 0) {
        return (struct RGB_SHINGING_MODE_STRUCT_CO *)0;
    }

    modeStruct->brightness = brightness;

    return modeStruct;
}

/*将所有灯亮度调为0*/
#define RGB_DISABLE_ALL_CCM() \
        RGB_BLUE_CCM_CONFIG(0);\
        RGB_RED_CCM_CONFIG(0);\
        RGB_GREEN_CCM_CONFIG(0)

/*呼吸灯输出公共赋值语句*/
#define RGB_BREATH_OUTPUT_CCM_CONFIG() \
        RGB_BLUE_CCM_CONFIG((BITWIDTH)(colorStruct.blue_vector * modeStruct->count));\
        RGB_RED_CCM_CONFIG((BITWIDTH)(colorStruct.red_vector * modeStruct->count));\
        RGB_GREEN_CCM_CONFIG((BITWIDTH)(colorStruct.green_vector * modeStruct->count))

/*定时执行一次，便能输出呼吸灯*/
void RGB_breath_output(struct RGB_COLOR_STRUCT colorStruct, struct RGB_SHINGING_MODE_STRUCT_BREATH* modeStruct, u8 status) {

    if (status == DISABLE) {
        RGB_DISABLE_ALL_CCM();
        return ;
    }

    /*呼吸灯计时循环*/
    if (modeStruct->dir == RGB_SHINGING_DIR_UP) {

        RGB_BREATH_OUTPUT_CCM_CONFIG();

        modeStruct->count += modeStruct->speed;
        if (modeStruct->count >= modeStruct->brightness) {
            modeStruct->dir = RGB_SHINGING_DIR_DOWN;
        }
    } else {
        
        RGB_BREATH_OUTPUT_CCM_CONFIG();

        modeStruct->count -= modeStruct->speed;
        if (modeStruct->count <= modeStruct->darkness + modeStruct->speed) { //加上speed是为了防止过零
            modeStruct->dir = RGB_SHINGING_DIR_UP;
        }
    }
}

/*定时执行一次，便能输出心跳灯*/
void RGB_heartBeat_output(struct RGB_COLOR_STRUCT colorStruct, struct RGB_SHINGING_MODE_STRUCT_HEART* modeStruct, u8 status) {

    if (status == DISABLE) {
        RGB_DISABLE_ALL_CCM();
        return ;
    }

    /*心跳灯计时循环*/
    if (modeStruct->count == 0 || modeStruct->count == modeStruct->beatPoint) {

        RGB_BLUE_CCM_CONFIG((BITWIDTH)(colorStruct.blue_vector * modeStruct->brightness));
        RGB_RED_CCM_CONFIG((BITWIDTH)(colorStruct.red_vector * modeStruct->brightness));
        RGB_GREEN_CCM_CONFIG((BITWIDTH)(colorStruct.green_vector * modeStruct->brightness));
    }

    if (modeStruct->count == modeStruct->beatTime || modeStruct->count == modeStruct->beatPoint + modeStruct->beatTime) {

        RGB_BLUE_CCM_CONFIG((BITWIDTH)(colorStruct.blue_vector * modeStruct->darkness));
        RGB_RED_CCM_CONFIG((BITWIDTH)(colorStruct.red_vector * modeStruct->darkness));
        RGB_GREEN_CCM_CONFIG((BITWIDTH)(colorStruct.green_vector * modeStruct->darkness));
    }

    if (modeStruct->count++ >= modeStruct->period) {
        modeStruct->count = 0;
    }
}

/*常亮灯*/
void RGB_ConstantOn_output(struct RGB_COLOR_STRUCT colorStruct, struct RGB_SHINGING_MODE_STRUCT_CO* modeStruct, u8 status) {

    if (status == DISABLE) {

        RGB_BLUE_CCM_CONFIG(0);
        RGB_RED_CCM_CONFIG(0);
        RGB_GREEN_CCM_CONFIG(0);
    } else {

        RGB_BLUE_CCM_CONFIG((BITWIDTH)(colorStruct.blue_vector * modeStruct->brightness));
        RGB_RED_CCM_CONFIG((BITWIDTH)(colorStruct.red_vector * modeStruct->brightness));
        RGB_GREEN_CCM_CONFIG((BITWIDTH)(colorStruct.green_vector * modeStruct->brightness));
    }    
}

/*输入颜色和状态，点亮或熄灭三色LED*/
void RGB_quickOutput(RGB_COLOR color, BitStatus status) {

    switch(color) {
        case RGB_RED: 
            status == RESET ? RGB_RED_CCM_CONFIG(0), \
                                RGB_BLUE_CCM_CONFIG(0), \
                                RGB_GREEN_CCM_CONFIG(0) :\
                                RGB_RED_CCM_CONFIG(RGB_TIMER_PERIOD), \
                                RGB_BLUE_CCM_CONFIG(0), \
                                RGB_GREEN_CCM_CONFIG(0);
            break;
        case RGB_BLUE:
            status == RESET ? RGB_RED_CCM_CONFIG(0), \
                                RGB_BLUE_CCM_CONFIG(0), \
                                RGB_GREEN_CCM_CONFIG(0) :\
                                RGB_RED_CCM_CONFIG(0), \
                                RGB_BLUE_CCM_CONFIG(RGB_TIMER_PERIOD), \
                                RGB_GREEN_CCM_CONFIG(0);
            break;
        case RGB_GREEN:
            status == RESET ? RGB_RED_CCM_CONFIG(0), \
                                RGB_BLUE_CCM_CONFIG(0), \
                                RGB_GREEN_CCM_CONFIG(0) :\
                                RGB_RED_CCM_CONFIG(0), \
                                RGB_BLUE_CCM_CONFIG(0), \
                                RGB_GREEN_CCM_CONFIG(RGB_TIMER_PERIOD);
            break;
        case RGB_YELLOW: //红 + 少量绿 = 黄
            status == RESET ? RGB_RED_CCM_CONFIG(0), \
                                RGB_BLUE_CCM_CONFIG(0), \
                                RGB_GREEN_CCM_CONFIG(0) :\
                                RGB_RED_CCM_CONFIG(RGB_TIMER_PERIOD), \
                                RGB_BLUE_CCM_CONFIG(0), \
                                RGB_GREEN_CCM_CONFIG((BITWIDTH)(RGB_TIMER_PERIOD * 0.2));
            break;
        case RGB_WHITE: //红 + 蓝 + 绿 = 白
            status == RESET ? RGB_RED_CCM_CONFIG(0), \
                                RGB_BLUE_CCM_CONFIG(0), \
                                RGB_GREEN_CCM_CONFIG(0) :\
                                RGB_RED_CCM_CONFIG(RGB_TIMER_PERIOD), \
                                RGB_BLUE_CCM_CONFIG(RGB_TIMER_PERIOD), \
                                RGB_GREEN_CCM_CONFIG((RGB_TIMER_PERIOD));
            break;
        case RGB_PINK: //蓝 + 绿 + 少量红 = 粉
            status == RESET ? RGB_RED_CCM_CONFIG(0), \
                                RGB_BLUE_CCM_CONFIG(0), \
                                RGB_GREEN_CCM_CONFIG(0) :\
                                RGB_RED_CCM_CONFIG((BITWIDTH)(RGB_TIMER_PERIOD * 0.5)), \
                                RGB_BLUE_CCM_CONFIG(RGB_TIMER_PERIOD), \
                                RGB_GREEN_CCM_CONFIG((RGB_TIMER_PERIOD));
            break;
        case RGB_PURPLE: //红 + 蓝 = 紫
            status == RESET ? RGB_RED_CCM_CONFIG(0), \
                                RGB_BLUE_CCM_CONFIG(0), \
                                RGB_GREEN_CCM_CONFIG(0) :\
                                RGB_RED_CCM_CONFIG(RGB_TIMER_PERIOD), \
                                RGB_BLUE_CCM_CONFIG(RGB_TIMER_PERIOD), \
                                RGB_GREEN_CCM_CONFIG(0);
            break;
        default:
            break;
    }
}

/*根据三颜色分量点亮三色LED*/
void RGB_mixOutput(f32 red_vector, f32 green_vector, f32 blue_vector) {

    RGB_RED_CCM_CONFIG((BITWIDTH)(red_vector * RGB_TIMER_PERIOD));
    RGB_BLUE_CCM_CONFIG((BITWIDTH)(blue_vector * RGB_TIMER_PERIOD));
    RGB_GREEN_CCM_CONFIG((BITWIDTH)(green_vector * RGB_TIMER_PERIOD));
}