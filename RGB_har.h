
/*��ֲ���̣�*/
//  0. Ӳ��Ҫ��
//        (1) RGBΪ��������
//        (2) ��ʱ������Ƚ����Ϊ���ϼ�����������Ըߵ�ƽ
//        (3) RGB����Ϊ��red : green : blue = 1 : 2 : 2
//  1. ������ʱ������Ƚ�ģ�����ͷ�ļ� #include "timer.h"
//  2. ���嶨ʱ������Ƚ�ģ��������� #define RGB_TIMER_PERIOD TIMER1_PERIOD
//  3.���嶨ʱ��λ��������������ʱ�����λ���� #define BITWIDTH u16 / u8
//  3.���岶��Ƚ�ģ���������, ���磺 
/* 
    #define RGB_RED_CCM_CONFIG(CCM_VALUE) TIM1_SetCompare1((BITWIDTH)CCM_VALUE)
    #define RGB_GREEN_CCM_CONFIG(CCM_VALUE) TIM1_SetCompare2((BITWIDTH)CCM_VALUE)
    #define RGB_BLUE_CCM_CONFIG(CCM_VALUE) TIM1_SetCompare3((BITWIDTH)CCM_VALUE)
/*

// 4.���岶��Ƚ�ģ��ʹ�ܺ���, ���磺
/* 
    #define RGB_RED_CCM_ENABLE() TIM1_CCxCmd(TIM1_CHANNEL_1, ENABLE)
    #define RGB_RED_CCM_DISABLE() TIM1_CCxCmd(TIM1_CHANNEL_1, DISABLE)
    #define RGB_GREEN_CCM_ENABLE() TIM1_CCxCmd(TIM1_CHANNEL_2, ENABLE)
    #define RGB_GREEN_CCM_DISABLE() TIM1_CCxCmd(TIM1_CHANNEL_2, DISBALE)
    #define RGB_BLUE_CCM_ENABLE() TIM1_CCxCmd(TIM1_CHANNEL_3, ENABLE)
    #define RGB_BLUE_CCM_DISABLE() TIM1_CCxCmd(TIM1_CHANNEL_3, DISABLE)
*/

/*RGB ��ɫLED�Ƶײ���غ���ͷ�ļ�, ��ֲʱ���޸� */
#ifndef __RGB_HAR_H_
#define __RGB_HAR_H_
#include "stdlib.h"

#include "timer1.h"

/*��ֲʱ��Ҫ��֤����ȽϼĴ���ֵΪ0ʱ����ߵ�ƽ, Ϊ���ʱ����͵�ƽ*/

#define RGB_TIMER_PERIOD TIMER1_PERIOD

/*�������Ͷ���*/
//typedef unsigned long u32;
//typedef unsigned int u16;
//typedef unsigned char u8;
typedef float f32;

/*�����ں˻�ʱ��ѡ����ʵ�λ�����ʵ�λ���ܱ�֤�������ݵ�Ч��*/
/*��������ʱ�������λ����в�������*/
#define BITWIDTH u16


/*�������ò���ȽϼĴ�����������ӳ�䣬��ֲʱ��Ҫ��д*/
#define RGB_RED_CCM_CONFIG(CCM_VALUE) TIM1_SetCompare1((BITWIDTH)CCM_VALUE)
#define RGB_GREEN_CCM_CONFIG(CCM_VALUE) TIM1_SetCompare2((BITWIDTH)CCM_VALUE)
#define RGB_BLUE_CCM_CONFIG(CCM_VALUE) TIM1_SetCompare3((BITWIDTH)CCM_VALUE)

/*ʹ��ʧ��pwm�������ӳ��, ��ֲʱ��Ҫ��д*/
#define RGB_RED_CCM_ENABLE() TIM1_CCxCmd(TIM1_CHANNEL_1, ENABLE)
#define RGB_RED_CCM_DISABLE() TIM1_CCxCmd(TIM1_CHANNEL_1, DISABLE)
#define RGB_GREEN_CCM_ENABLE() TIM1_CCxCmd(TIM1_CHANNEL_2, ENABLE)
#define RGB_GREEN_CCM_DISABLE() TIM1_CCxCmd(TIM1_CHANNEL_2, DISBALE)
#define RGB_BLUE_CCM_ENABLE() TIM1_CCxCmd(TIM1_CHANNEL_3, ENABLE)
#define RGB_BLUE_CCM_DISABLE() TIM1_CCxCmd(TIM1_CHANNEL_3, DISABLE)


#endif

