/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h" 
#include "usart.h"
#include "delay.h" 
#include "X9C103.h"

void NMI_Handler(void)
{
}
 
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
void SVC_Handler(void)
{
}
 
void DebugMon_Handler(void)
{
}
 
void PendSV_Handler(void)
{
}
 
void SysTick_Handler(void)
{
}


u8 flag =0;
void USART1_IRQHandler(void)                	//串口1中断服务程序
	{
	u8 Res;
	u8 i;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
		Res =USART_ReceiveData(USART1);	//读取接收到的数据
		
		if((USART_RX_STA&0x8000)==0)//接收未完成
			{
			if(USART_RX_STA&0x4000)//接收到了0x0d
				{
				if(Res!=0x0a)
					USART_RX_STA=0;//接收错误,重新开始
				else //接收完成了
				{
					USART_RX_STA|=0x8000;	 
				  flag=1;
	        USART_RX_STA = 0;
				}
				}
			else //还没收到0X0D
				{	
				if(Res==0x0d)USART_RX_STA|=0x4000;
				else
					{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据错误,重新开始接收	  
					}		 
				}
			} 
///////////////接收完毕//////////////////
		if(flag)
				 {
					 flag = 0;
					 //cmd = USART_RX_BUF[0];//切歌，上一首，下一首。
					 switch(USART_RX_BUF[0])//判断通道数据
					 {
						case 0x01://1通道；
								{
								 switch(USART_RX_BUF[1])	
								 {
									 case 0x44://音量增加；
										 X9C103_Inc_N_Step(5);
//										 USART_SendData( USART1, 0x01);	
//									 delay_ms(50);
//										 USART_SendData( USART1, 0x44);
									 	GPIO_ResetBits(GPIOC,GPIO_Pin_10);//CS(0);             // CS  拉低
										GPIO_SetBits(GPIOC,GPIO_Pin_12);//UD(1);             // U/D 拉高   则下面的INC下沿，执行UP操作  
										Delay(3);           // 延时大约2us
										for( i = 5; i>0; i--)
										{
												GPIO_ResetBits(GPIOC,GPIO_Pin_11);//INC(0);         // 因为GPIO初始化时，INC已经拉高了。INC 拉低;  // 产生一个下沿
												Delay(200);       // 延时2us左右
												GPIO_SetBits(GPIOC,GPIO_Pin_11);//INC(1);         // 拉高INC //保存模式
										}
										GPIO_SetBits(GPIOC,GPIO_Pin_10);//CS(1);
											break;							 
									 case 0x55://音量减小；
//										 X9C103_Dec_N_Step(5);
//										 USART_SendData( USART1, 0x01);	
//									 delay_ms(50);
//										 USART_SendData( USART1, 0x55);	
									GPIO_ResetBits(GPIOC,GPIO_Pin_12);//UD(0);               //CLRB_X9C103_UD;   // U/D 清0，  则下面的INC下沿，执行Down操作  
									Delay(3);            // 延时大约2us
									GPIO_ResetBits(GPIOC,GPIO_Pin_10);//CS(0);  
							 
								 for(i=5;i>0;i--) 
								{ 
									 GPIO_SetBits(GPIOC,GPIO_Pin_11);//INC(1);               // 拉高INC    因为INC的下沿有效
									 Delay(2);              // 延时2us左右
									 GPIO_ResetBits(GPIOC,GPIO_Pin_11);//INC(0);                // INC 拉低;  // 产生一个下沿
									 Delay(600);            // 延时大约500us, Rw等待输出稳定
								}
									 GPIO_ResetBits(GPIOC,GPIO_Pin_11);//INC(0);//保存模式
									 GPIO_SetBits(GPIOC,GPIO_Pin_10);//CS(1);                 
											break;
									 default:	
											break;		
								 }
								}				 
					 		break;						
						case 0x02://2通道；
					 {
             switch(USART_RX_BUF[1])	
						 {
							 case 0x44://音量增加；
							 X9C103_Inc_N_Step(1);
								 USART_SendData( USART1, 0x02);	
							 delay_ms(50);
							   USART_SendData( USART1, 0x44);
									break;							 
               case 0x55://音量减小；
								 USART_SendData( USART1, 0x02);	
							 delay_ms(50);
							   USART_SendData( USART1, 0x55);	
									break;
               default:	
								  break;	
						 }	
						}
						break;
						case 0x03://3通道；							
					 {
             switch(USART_RX_BUF[1])	
						 { case 0x44://音量增加；
//							   X9C103_Inc_N_Step(1);
//								 USART_SendData( USART1, 0x03);	
//							 delay_ms(50);
//							   USART_SendData( USART1, 0x44);
							 		  GPIO_ResetBits(GPIOA,GPIO_Pin_12);//CS(0);             // CS  拉低
										GPIO_SetBits(GPIOA,GPIO_Pin_8);//UD(1);             // U/D 拉高   则下面的INC下沿，执行UP操作  
										Delay(3);           // 延时大约2us
										for( i = 5; i>0; i--)
										{
												GPIO_ResetBits(GPIOA,GPIO_Pin_11);//INC(0);         // 因为GPIO初始化时，INC已经拉高了。INC 拉低;  // 产生一个下沿
												Delay(200);       // 延时2us左右
												GPIO_SetBits(GPIOA,GPIO_Pin_11);//INC(1);         // 拉高INC //保存模式
										}
										GPIO_SetBits(GPIOA,GPIO_Pin_12);//CS(1);
									break;							 
               case 0x55://音量减小；
//								 X9C103_Dec_N_Step(1); 
//								 USART_SendData( USART1, 0x03);	
//							 delay_ms(50);
//							   USART_SendData( USART1, 0x55);
									GPIO_ResetBits(GPIOA,GPIO_Pin_8);//UD(0);               //CLRB_X9C103_UD;   // U/D 清0，  则下面的INC下沿，执行Down操作  
									Delay(3);            // 延时大约2us
									GPIO_ResetBits(GPIOA,GPIO_Pin_12);//CS(0);  
							 
								 for(i=5;i>0;i--) 
								{ 
									 GPIO_SetBits(GPIOA,GPIO_Pin_11);//INC(1);               // 拉高INC    因为INC的下沿有效
									 Delay(2);              // 延时2us左右
									 GPIO_ResetBits(GPIOA,GPIO_Pin_11);//INC(0);                // INC 拉低;  // 产生一个下沿
									 Delay(600);            // 延时大约500us, Rw等待输出稳定
								}
									 GPIO_ResetBits(GPIOA,GPIO_Pin_11);//INC(0);//保存模式
									 GPIO_SetBits(GPIOA,GPIO_Pin_12);//CS(1);                 							 
									break;
               default:	
								  break;	}	
						}			
            break;						
						case 0x04://4通道；
					 {
             switch(USART_RX_BUF[1])	
						 { case 0x44://音量增加；
							   X9C103_Inc_N_Step(1);
								 USART_SendData( USART1, 0x04);	
							 delay_ms(50);
							   USART_SendData( USART1, 0x44);
									break;							 
               case 0x55://音量减小；
                 X9C103_Dec_N_Step(1);								
							   USART_SendData( USART1, 0x04);	
							 delay_ms(50);
							   USART_SendData( USART1, 0x55);	
									break;
               default:	
								  break;	}	
						}
						break;
						case 0x05://5通道；
					 {
             switch(USART_RX_BUF[1])	
						 {case 0x44://音量增加；						 
									X9C103_Inc_N_Step(1);
									USART_SendData( USART1, 0x05);	
									delay_ms(50);
							    USART_SendData( USART1, 0x44);
									break;							 
               case 0x55://音量减小；
								 X9C103_Dec_N_Step(1); 
						  	 USART_SendData( USART1, 0x05);	
							 delay_ms(50);
							   USART_SendData( USART1, 0x55);	
									break;
               default:	
								  break;		}
						}
						break;
						case 0x06://6通道；
					 {
             switch(USART_RX_BUF[1])	
						 {case 0x44://音量增加；
//							   X9C103_Inc_N_Step(5);
//								 USART_SendData( USART1, 0x06);
//									delay_ms(50);							 
//							   USART_SendData( USART1, 0x44);
							      GPIO_ResetBits(GPIOB,GPIO_Pin_12);//CS(0);             // CS  拉低
										GPIO_SetBits(GPIOB,GPIO_Pin_10);//UD(1);             // U/D 拉高   则下面的INC下沿，执行UP操作  
										Delay(3);           // 延时大约2us
										for( i = 5; i>0; i--)
										{
												GPIO_ResetBits(GPIOB,GPIO_Pin_11);//INC(0);         // 因为GPIO初始化时，INC已经拉高了。INC 拉低;  // 产生一个下沿
												Delay(200);       // 延时2us左右
												GPIO_SetBits(GPIOB,GPIO_Pin_11);//INC(1);         // 拉高INC //保存模式
										}
										GPIO_SetBits(GPIOB,GPIO_Pin_12);//CS(1);              // 完毕CS拉高 //store             
									break;							 
               case 0x55://音量减小；
//                 X9C103_Dec_N_Step(5);
//							   USART_SendData( USART1, 0x06);	
//							 delay_ms(50);  
//							 USART_SendData( USART1, 0x55);	
									GPIO_ResetBits(GPIOB,GPIO_Pin_10);//UD(0);               //CLRB_X9C103_UD;   // U/D 清0，  则下面的INC下沿，执行Down操作  
									Delay(3);            // 延时大约2us
									GPIO_ResetBits(GPIOB,GPIO_Pin_12);//CS(0);  
							 
								 for(i=5;i>0;i--) 
								{ 
									 GPIO_SetBits(GPIOB,GPIO_Pin_11);//INC(1);               // 拉高INC    因为INC的下沿有效
									 Delay(2);              // 延时2us左右
									 GPIO_ResetBits(GPIOB,GPIO_Pin_11);//INC(0);                // INC 拉低;  // 产生一个下沿
									 Delay(600);            // 延时大约500us, Rw等待输出稳定
								}
									 GPIO_ResetBits(GPIOB,GPIO_Pin_11);//INC(0);//保存模式
									 GPIO_SetBits(GPIOB,GPIO_Pin_12);//CS(1);                 // 完毕CS拉高 // store 
									break;
               default:	
								  break;	}	
						}
						break;
						case 0x07://7通道；
				   Init_x109_1_3_6();// X9C103_Dec_N_Step(99);//静音； 
						break;
						
					 }
					 
				 }			
     }
		
	 }
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
