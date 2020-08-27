
/*移植过程：*/
//  0. 硬件要求：
//        (1) RGB为共阳驱动
//        (2) 定时器捕获比较输出为向上计数，输出极性高电平
//        (3) RGB电流为：red : green : blue = 1 : 2 : 2
//  1. 包含定时器捕获比较模块相关头文件 #include "timer.h"
//  2. 定义定时器捕获比较模块计数周期 #define RGB_TIMER_PERIOD TIMER1_PERIOD
//  3.定义定时器位宽，函数参数传递时以这个位宽传递 #define BITWIDTH u16 / u8
//  3.定义捕获比较模块操作函数, 例如： 
/* 
    #define RGB_RED_CCM_CONFIG(CCM_VALUE) TIM1_SetCompare1((BITWIDTH)CCM_VALUE)
    #define RGB_GREEN_CCM_CONFIG(CCM_VALUE) TIM1_SetCompare2((BITWIDTH)CCM_VALUE)
    #define RGB_BLUE_CCM_CONFIG(CCM_VALUE) TIM1_SetCompare3((BITWIDTH)CCM_VALUE)
/*

// 4.定义捕获比较模块使能函数, 例如：
/* 
    #define RGB_RED_CCM_ENABLE() TIM1_CCxCmd(TIM1_CHANNEL_1, ENABLE)
    #define RGB_RED_CCM_DISABLE() TIM1_CCxCmd(TIM1_CHANNEL_1, DISABLE)
    #define RGB_GREEN_CCM_ENABLE() TIM1_CCxCmd(TIM1_CHANNEL_2, ENABLE)
    #define RGB_GREEN_CCM_DISABLE() TIM1_CCxCmd(TIM1_CHANNEL_2, DISBALE)
    #define RGB_BLUE_CCM_ENABLE() TIM1_CCxCmd(TIM1_CHANNEL_3, ENABLE)
    #define RGB_BLUE_CCM_DISABLE() TIM1_CCxCmd(TIM1_CHANNEL_3, DISABLE)
*/

/*RGB 三色LED灯底层相关函数头文件, 移植时需修改 */
#ifndef __RGB_HAR_H_
#define __RGB_HAR_H_
#include "stdlib.h"

#include "timer1.h"

/*移植时，要保证捕获比较寄存器值为0时输出高电平, 为最大时输出低电平*/

#define RGB_TIMER_PERIOD TIMER1_PERIOD

/*数据类型定义*/
//typedef unsigned long u32;
//typedef unsigned int u16;
//typedef unsigned char u8;
typedef float f32;

/*根据内核或定时器选择合适的位宽，合适的位宽能保证函数传递的效率*/
/*函数传递时会以这个位宽进行参数传递*/
#define BITWIDTH u16


/*定义设置捕获比较寄存器操作函数映射，移植时需要重写*/
#define RGB_RED_CCM_CONFIG(CCM_VALUE) TIM1_SetCompare1((BITWIDTH)CCM_VALUE)
#define RGB_GREEN_CCM_CONFIG(CCM_VALUE) TIM1_SetCompare2((BITWIDTH)CCM_VALUE)
#define RGB_BLUE_CCM_CONFIG(CCM_VALUE) TIM1_SetCompare3((BITWIDTH)CCM_VALUE)

/*使能失能pwm输出函数映射, 移植时需要重写*/
#define RGB_RED_CCM_ENABLE() TIM1_CCxCmd(TIM1_CHANNEL_1, ENABLE)
#define RGB_RED_CCM_DISABLE() TIM1_CCxCmd(TIM1_CHANNEL_1, DISABLE)
#define RGB_GREEN_CCM_ENABLE() TIM1_CCxCmd(TIM1_CHANNEL_2, ENABLE)
#define RGB_GREEN_CCM_DISABLE() TIM1_CCxCmd(TIM1_CHANNEL_2, DISBALE)
#define RGB_BLUE_CCM_ENABLE() TIM1_CCxCmd(TIM1_CHANNEL_3, ENABLE)
#define RGB_BLUE_CCM_DISABLE() TIM1_CCxCmd(TIM1_CHANNEL_3, DISABLE)


#endif

