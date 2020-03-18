#include "X9C103.h"


/*³õÊ¼»¯X9C103¹Ü½Å*/
void X9C103_Config(void)
{
  /*¶¨ÒåÒ»¸öGPIO_InitTypeDefÀàĞÍµÄ½á¹¹Ìå*/
  GPIO_InitTypeDef GPIO_InitStructure; 

	/*Ê¹ÄÜx9c103Ê¹ÓÃµÄGPIOÊ±ÖÓ*/
  RCC_APB2PeriphClockCmd(CS_GPIO_CLK, ENABLE); 	//|RCC_APB2Periph_AFIO
  /*PB3 PB4 ¸´Î»ºó£¬×÷ÎªJTAGÏÂÔØ¿ÚÊ¹ÓÃ£¬ÏëÒªÓÃIO¿Ú£¬ĞèÒªÅäÖÃÒÔÏÂ£RCC_APB2Periph_AFIOº*/ 
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = CS_GPIO_PIN|INC_GPIO_PIN|UD_GPIO_PIN; //PB0 PB1 PB5
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //GPIO¹¤×÷ÔÚÍÆÍìÄ£Ê½
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(CS_GPIO_PORT, &GPIO_InitStructure);  /*µ÷ÓÃ¿âº¯Êı£¬³õÊ¼»¯GPIO*/
  GPIO_SetBits(CS_GPIO_PORT,CS_GPIO_PIN|INC_GPIO_PIN|UD_GPIO_PIN);/* ÖÃÎ»ËùÓĞGPIOµÆ	*/
  
//  GPIO_InitStructure.GPIO_Pin = LCD_BRIGHT_UD|LCD_BRIGHT_INC|LCD_BRIGHT_CS; //??PG3~PG5
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //GPIO?????????
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIO_LCDBRIGHT, &GPIO_InitStructure);  //???GPIO????
//  GPIO_SetBits(GPIO_LCDBRIGHT,LCD_BRIGHT_UD|LCD_BRIGHT_INC|LCD_BRIGHT_CS);
}

//ÑÓÊ±us×Ó³ÌĞò 
void Delay(unsigned int t) 
{ 
unsigned int i; 
for(i=0;i<t;i++) ;

} 

//************************************************************************
// Êı×ÖµçÎ»Æ÷ÏòÉÏµ÷Ò»²½
// Êı×ÖµçÎ»Æ÷100¸ö³éÍ·£¬Ïàµ±ÓÚ99²½
//************************************************************************
void X9C103_Inc_N_Step(unsigned char N)
{
   unsigned char i=0; 
          
        CS(0);             // CS  À­µÍ
        UD(1);             // U/D À­¸ß   ÔòÏÂÃæµÄINCÏÂÑØ£¬Ö´ĞĞUP²Ù×÷  
        Delay(3);           // ÑÓÊ±´óÔ¼2us
        for(i = N; i>0; i--)
        {
            INC(0);         // ÒòÎªGPIO³õÊ¼»¯Ê±£¬INCÒÑ¾­À­¸ßÁË¡£INC À­µÍ;  // ²úÉúÒ»¸öÏÂÑØ
            Delay(200);       // ÑÓÊ±2us×óÓÒ
            INC(1);         // À­¸ßINC //±£´æÄ£Ê½
        }
        CS(1);              // Íê±ÏCSÀ­¸ß //store

}
//************************************************************************
// Êı×ÖµçÎ»Æ÷ÏòÏÂµ÷Ò»²½
// Êı×ÖµçÎ»Æ÷100¸ö³éÍ·£¬Ïàµ±ÓÚ99²½
//************************************************************************
void X9C103_Dec_N_Step(unsigned char N)
{
   unsigned char i=0; 
    UD(0);               //CLRB_X9C103_UD;   // U/D Çå0£¬  ÔòÏÂÃæµÄINCÏÂÑØ£¬Ö´ĞĞDown²Ù×÷  
    Delay(3);            // ÑÓÊ±´óÔ¼2us
    CS(0);  
 
   for(i=N;i>0;i--) 
  { 
     INC(1);               // À­¸ßINC    ÒòÎªINCµÄÏÂÑØÓĞĞ§
     Delay(2);              // ÑÓÊ±2us×óÓÒ
     INC(0);                // INC À­µÍ;  // ²úÉúÒ»¸öÏÂÑØ
     Delay(600);            // ÑÓÊ±´óÔ¼500us, RwµÈ´ıÊä³öÎÈ¶¨
  }
     INC(0);//±£´æÄ£Ê½
     CS(1);                 // Íê±ÏCSÀ­¸ß // store 
 

}

void X9C103_Init(void)//³õÊ¼»¯ÖÁÖĞ¼äÎ»ÖÃ
{
 X9C103_Dec_N_Step(99); 
 delay_ms(2000);
 X9C103_Inc_N_Step(49); 
} 

void Init_x109_1_3_6(void)
{
	u8 i;
								/*1*/
									GPIO_ResetBits(GPIOC,GPIO_Pin_12);//UD(0);               //CLRB_X9C103_UD;   // U/D Çå0£¬  ÔòÏÂÃæµÄINCÏÂÑØ£¬Ö´ĞĞDown²Ù×÷  
									Delay(3);            // ÑÓÊ±´óÔ¼2us
									GPIO_ResetBits(GPIOC,GPIO_Pin_10);//CS(0);  
							 
								 for(i=99;i>0;i--) 
								{ 
									 GPIO_SetBits(GPIOC,GPIO_Pin_11);//INC(1);               // À­¸ßINC    ÒòÎªINCµÄÏÂÑØÓĞĞ§
									 Delay(2);              // ÑÓÊ±2us×óÓÒ
									 GPIO_ResetBits(GPIOC,GPIO_Pin_11);//INC(0);                // INC À­µÍ;  // ²úÉúÒ»¸öÏÂÑØ
									 Delay(600);            // ÑÓÊ±´óÔ¼500us, RwµÈ´ıÊä³öÎÈ¶¨
								}
									 GPIO_ResetBits(GPIOC,GPIO_Pin_11);//INC(0);//±£´æÄ£Ê½
									 GPIO_SetBits(GPIOC,GPIO_Pin_10);//CS(1); 
								/*3*/
									GPIO_ResetBits(GPIOA,GPIO_Pin_8);//UD(0);               //CLRB_X9C103_UD;   // U/D Çå0£¬  ÔòÏÂÃæµÄINCÏÂÑØ£¬Ö´ĞĞDown²Ù×÷  
									Delay(3);            // ÑÓÊ±´óÔ¼2us
									GPIO_ResetBits(GPIOA,GPIO_Pin_12);//CS(0);  
							 
								 for(i=99;i>0;i--) 
								{ 
									 GPIO_SetBits(GPIOA,GPIO_Pin_11);//INC(1);               // À­¸ßINC    ÒòÎªINCµÄÏÂÑØÓĞĞ§
									 Delay(2);              // ÑÓÊ±2us×óÓÒ
									 GPIO_ResetBits(GPIOA,GPIO_Pin_11);//INC(0);                // INC À­µÍ;  // ²úÉúÒ»¸öÏÂÑØ
									 Delay(600);            // ÑÓÊ±´óÔ¼500us, RwµÈ´ıÊä³öÎÈ¶¨
								}
									 GPIO_ResetBits(GPIOA,GPIO_Pin_11);//INC(0);//±£´æÄ£Ê½
									 GPIO_SetBits(GPIOA,GPIO_Pin_12);//CS(1); 
								/*6*/
									GPIO_ResetBits(GPIOB,GPIO_Pin_10);//UD(0);               //CLRB_X9C103_UD;   // U/D Çå0£¬  ÔòÏÂÃæµÄINCÏÂÑØ£¬Ö´ĞĞDown²Ù×÷  
									Delay(3);            // ÑÓÊ±´óÔ¼2us
									GPIO_ResetBits(GPIOB,GPIO_Pin_12);//CS(0);  
							 
								 for(i=99;i>0;i--) 
								{ 
									 GPIO_SetBits(GPIOB,GPIO_Pin_11);//INC(1);               // À­¸ßINC    ÒòÎªINCµÄÏÂÑØÓĞĞ§
									 Delay(2);              // ÑÓÊ±2us×óÓÒ
									 GPIO_ResetBits(GPIOB,GPIO_Pin_11);//INC(0);                // INC À­µÍ;  // ²úÉúÒ»¸öÏÂÑØ
									 Delay(600);            // ÑÓÊ±´óÔ¼500us, RwµÈ´ıÊä³öÎÈ¶¨
								}
									 GPIO_ResetBits(GPIOB,GPIO_Pin_11);//INC(0);//±£´æÄ£Ê½
									 GPIO_SetBits(GPIOB,GPIO_Pin_12);//CS(1);                 
}