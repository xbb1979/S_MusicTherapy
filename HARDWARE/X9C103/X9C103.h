#ifndef __X9C103_H
#define __X9C103_H

#include "stm32f10x.h"

/*--------------------------------------------------------------------------
X9C103.H
X9C103 functions.
Copyright (c) 2007 DC. By Delphifx 2007-8-11.
All rights reserved.
--------------------------------------------------------------------------*/

// CS
#define CS_GPIO_PORT    	GPIOB		              /* GPIO端口 */
#define CS_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define CS_GPIO_PIN		    GPIO_Pin_12			        /* 连接到CS时钟线的GPIO */

// INC
#define INC_GPIO_PORT    	GPIOB			              /* GPIO端口 */
#define INC_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define INC_GPIO_PIN		  GPIO_Pin_11			        /* 连接到INC时钟线的GPIO */

// UD
#define UD_GPIO_PORT    	GPIOB		              /* GPIO端口 */
#define UD_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define UD_GPIO_PIN		    GPIO_Pin_10		        /* 连接到UD时钟线的GPIO */

/* 有关电位器的宏定义  使用标准的固件库控制IO*/
#define CS(a)	if (a)\
							GPIO_SetBits(CS_GPIO_PORT,CS_GPIO_PIN);\
							else		\
							GPIO_ResetBits(CS_GPIO_PORT,CS_GPIO_PIN)

#define INC(a)	if (a)	\
								GPIO_SetBits(INC_GPIO_PORT,INC_GPIO_PIN);\
								else		\
								GPIO_ResetBits(INC_GPIO_PORT,INC_GPIO_PIN)

#define UD(a)	if (a)	\
							GPIO_SetBits(UD_GPIO_PORT,UD_GPIO_PIN);\
							else		\
							GPIO_ResetBits(UD_GPIO_PORT,UD_GPIO_PIN)



void X9C103_Inc_N_Step(unsigned char N);
void X9C103_Dec_N_Step(unsigned char N);
void Delay(unsigned int t) ;
void X9C103_Init(void);//初始化至中间位置
void X9C103_Config(void);
void Init_x109_1_3_6(void);
#endif