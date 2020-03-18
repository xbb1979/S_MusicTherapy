#include "sys.h"
#include "delay.h"
#include "usart.h" 
//#include "led.h" 		 	 
//#include "lcd.h"  
//#include "key.h"     
//#include "usmart.h" 
//#include "malloc.h"
//#include "sdio_sdcard.h"  
//#include "w25qxx.h"    
//#include "ff.h"  
//#include "exfuns.h"   
//#include "text.h" 
//#include "vs10xx.h"
//#include "mp3player.h"	
#include "X9C103.h"
 
/************************************************
 ALIENTEK战舰STM32开发板实验43
 音乐播放器 实验
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

	
void usart_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA,ENABLE);
	USART_DeInit(USART1);//复位USART1;
	//GPIOA端口模式设置；
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;//TX_PA9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//RX_PA10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//串口初始化；
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	USART_Init(USART1,&USART_InitStructure);
	
	#if EN_USART1_RX
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	#endif
	
	
	USART_Cmd(USART1,ENABLE);
	
}
void Test_X9C103_Config(void)
{
  /*定义一个GPIO_InitTypeDef类型的结构体*/
  GPIO_InitTypeDef GPIO_InitStructure; 

	/*使能x9c103使用的GPIO时钟*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE); 	//|RCC_APB2Periph_AFIO

	/*3通道*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_8; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //GPIO工作在推挽模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  /*调用库函数，初始化GPIO*/
  GPIO_SetBits(GPIOA,GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_8);/* 置位所有GPIO*/
  /*6通道*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_10; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //GPIO工作在推挽模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);  /*调用库函数，初始化GPIO*/
  GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_10);/* 置位所有GPIO*/
	/*1通道*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_10; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //GPIO工作在推挽模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);  /*调用库函数，初始化GPIO*/
  GPIO_SetBits(GPIOC,GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_10);/* 置位所有GPIO*/
}
	
 int main(void)
 {	 
 
	delay_init();	    	 //延时函数初始化	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	usart_init(9600);	 	//串口初始化为115200
	USART_RX_STA=0;       //接收状态标记
// 	LED_Init();		  			//初始化与LED连接的硬件接口
//	KEY_Init();					//初始化按键
//	LCD_Init();			   		//初始化LCD     
//	W25QXX_Init();				//初始化W25Q128
	 
	 
// 	VS_Init();	  				//初始化VS1053 			
//	
//	 
//	 
// 	my_mem_init(SRAMIN);		//初始化内部内存池
//	exfuns_init();				//为fatfs相关变量申请内存  
// 	f_mount(fs[0],"0:",1); 		//挂载SD卡 
// 	f_mount(fs[1],"1:",1); 		//挂载FLASH.
//	POINT_COLOR=RED;  
	 
// 	while(font_init()) 				//检查字库
//	{	    
////		LCD_ShowString(30,50,200,16,16,"Font Error!");
////		delay_ms(200);				  
////		LCD_Fill(30,50,240,66,WHITE);//清除显示	     
//	}
// 	Show_Str(30,50,200,16,"战舰 STM32开发板",16,0);				    	 
//	Show_Str(30,70,200,16,"音乐播放器实验",16,0);				    	 
//	Show_Str(30,90,200,16,"正点原子@ALIENTEK",16,0);				    	 
//	Show_Str(30,130,200,16,"KEY0:NEXT   KEY2:PREV",16,0);
//	Show_Str(30,150,200,16,"KEY_UP:VOL+ KEY1:VOL-",16,0);
//	delay_ms(5000);	
    //X9C103_Config();
		Test_X9C103_Config();
		delay_ms(5000);
		Init_x109_1_3_6();//全部置零；
   //delay_ms(5000);
  //X9C103_Dec_N_Step(99); //输出电压为0；
	//X9C103_Inc_N_Step(99); //不分压，与输入信号等值。
    delay_ms(2000);
	while(1)		
	{

		  
//  	LED1=0; 	  
//		Show_Str(30,170,200,16,"存储器测试...",16,0);
//		printf("Ram Test:0X%04X\r\n",VS_Ram_Test());//打印RAM测试结果	    
//		Show_Str(30,170,200,16,"正弦波测试...",16,0); 	 	 
// 		VS_Sine_Test();	   
//		Show_Str(30,170,200,16,"<<音乐播放器>>",16,0); 		 
//		LED1=1;
//		mp3_play();
//	  USART_SendData( USART1, 0x99);
		delay_ms(3000);
	} 	   										    
}



