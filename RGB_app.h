/*RGB ��ɫLED��Ӧ�ú���ͷ�ļ� */
#ifndef __RGB_APP_H_
#define __RGB_APP_H_

#include "RGB_har.h"

/*��˸ѭ������ö�ٶ���*/
typedef enum {
    RGB_SHINGING_DIR_UP = 0,
    RGB_SHINGING_DIR_DOWN 

} RGB_SHINGING_DIR;

/*��˸ģʽö�ٶ���*/
typedef enum {
    RGB_SHINGING_MODE_BREATH = 0,
    RGB_SHINGING_MODE_HEART_BEAT,
    RGB_SHINGING_MODE_CO
} RGB_SHINGING_MODE;

/*���ֳ�����ɫö�ٶ���*/
typedef enum  {
    RGB_RED = 0,
    RGB_BLUE,
    RGB_GREEN,
    RGB_WHITE,
    RGB_PINK,
    RGB_PURPLE,
    RGB_YELLOW
} RGB_COLOR;

/*��ɫ����ṹ�嶨��*/
struct RGB_COLOR_STRUCT {
    f32 red_vector; //����ɫ����, ʵ������Ϊ brightness * vector, Ҫ��֤��0 - 1֮�䣬�޲���������
    f32 green_vector;
    f32 blue_vector;
};

/*������ģʽ����ṹ�嶨��*/
struct RGB_SHINGING_MODE_STRUCT_BREATH {
    BITWIDTH speed; //�ٶȣ�ÿ��ִ�к���ʱ�Ĳ���ȽϼĴ�������
    BITWIDTH brightness; //������ȣ�����ȽϼĴ������ֵ
    BITWIDTH darkness; //��󰵶ȣ�����ȽϼĴ�����Сֵ

    u8 dir; //��ǰ��������
    BITWIDTH count; //��ǰʱ��
};

/*����ģʽ����ṹ�嶨��*/
struct RGB_SHINGING_MODE_STRUCT_CO {
    BITWIDTH brightness;
};

/*������ģʽ����ṹ�嶨��*/
struct RGB_SHINGING_MODE_STRUCT_HEART {
    BITWIDTH brightness;
    BITWIDTH darkness;

    BITWIDTH beatPoint; //��һ����0���������ڶ�����������
    BITWIDTH beatTime; //����������ʱ��

    BITWIDTH count; //��ǰʱ��
    BITWIDTH period; //��������
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