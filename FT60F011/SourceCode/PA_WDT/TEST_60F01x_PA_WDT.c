//*********************************************************
/*  文件名：TEST_60F01x_WDT.c
*	功能：  FT60F01x-WDT功能演示
*   IC:    FT60F011A SOP8
*   晶振：  16M/4T                    
*   说明：  程序中开启看门狗并将看门狗时间设置为32ms
*		   a. 主函数先在DemoPortOut脚输出一个高3ms低3ms的信号，
*		   b. 然后循环输出高1ms低1ms，500HZ的信号。
*		   如果不在主程序中清看门狗，则每隔32ms单片机复位后，会重复输出a+b信号；
*		   如果在主函数中清看门狗，则一直输出b信号
*
*                  FT60F011A  SOP8 
*                 ----------------
*  VDD-----------|1(VDD)    (GND)8|------------GND     
*  DemoPortIn----|2(PA2)    (PA4)7|----DemoPortOut 
*  NC------------|3(PA1)    (PA5)6|-------------NC
*  NC------------|4(PA3)    (PA0)5|-------------NC
*			      ----------------
*
*
*                  MG117  SOP8 
*                 ----------------
*  VDD-----------|1(VDD)    (GND)8|------------GND     
*  LED_N---------|2(PA2)    (PA4)7|-----------BTN2 (Normal Adv Data)
*  NC------------|3(PA1)    (PA5)6|-----------BTN3 (Rapid Adv Data)
*  RSTn----------|4(PA3)    (PA0)5|-------------NC
*			      ----------------

*/
//*********************************************************
#include "SYSCFG.h"

//**********************************************************
//***********************宏定义*****************************
#define unchar unsigned char
#define unint unsigned int
#define unlong unsigned long

#define LED_PIN RA2
#define NORMAL_ADV_BTN RA4
#define RAPID_ADV_BTN RA5

/*-------------------------------------------------
 *  函数名：POWER_INITIAL
 *	功能：  上电系统初始化
 *  输入：  无
 *  输出：  无
 --------------------------------------------------*/
void POWER_INITIAL(void)
{
    OSCCON = 0B01110001; //WDT 32KHZ IRCF=111=16MHZ/2=8MHZ,0.125US/T
                         //Bit0=1,系统时钟为内部振荡器(60F01x保留位)
                         //Bit0=0,时钟源由FOSC<2：0>决定即编译选项时选择(60F01x保留位)

    INTCON = 0; //暂禁止所有中断
    PORTA = 0B00000000;
    TRISA = 0B11111111; //PA输入输出 0-输出 1-输入
                        //PA2/PA4/PA5->输出
    TRISA2 = 0;         //没有输入，唯一输入Reset
    TRISA4 = 0;
    TRISA5 = 0;
    WPUA = 0B00000000; //PA端口上拉控制 1-开上拉 0-关上拉，都是OUTPUT无需上拉。

    OPTION = 0B00001000;  //Bit3=1 WDT MODE,PS=000=1:1 WDT RATE
                          //Bit7(PAPU)=0 ENABLED PULL UP PA
    MSCKCON = 0B00000000; //Bit6->0,禁止PA4, PC5稳压输出(60F01x保留位)
                          //Bit5->0,TIMER2时钟为Fosc(60F01x保留位)
                          //Bit4->0,禁止LVR(60F01x O版之前)
                          //Bit4->0, LVREN使能时,开启LVR(60F01x O版及O版后)
                          //Bit4->1, LVREN使能时,工作时开启LVR, 睡眠时自动关闭LVR(60F01x O版及O版之后)
}

/*-------------------------------------------------
 *  函数名称：DelayUs
 *  功能：   短延时函数 --16M-4T--大概快1%左右.
 *  输入参数：Time 延时时间长度 延时时长Time*2Us
 * 	返回参数：无 
 -------------------------------------------------*/
void DelayUs(unsigned char Time)
{
    unsigned char a;
    for (a = 0; a < Time; a++)
    {
        NOP();
    }
}
/*------------------------------------------------- 
 * 	函数名称：DelayMs
 * 	功能：   短延时函数
 * 	输入参数：Time 延时时间长度 延时时长Time ms
 * 	返回参数：无 
 -------------------------------------------------*/
void DelayMs(unsigned char Time)
{
    unsigned char a, b;
    for (a = 0; a < Time; a++)
    {
        for (b = 0; b < 5; b++)
        {
            DelayUs(98); //快1%
        }
    }
}
/*------------------------------------------------- 
 * 	函数名称：DelayS
 * 	功能：   短延时函数
 * 	输入参数：Time 延时时间长度 延时时长Time S
 * 	返回参数：无 
 -------------------------------------------------*/
void DelayS(unsigned char Time)
{
    unsigned char a, b;
    for (a = 0; a < Time; a++)
    {
        for (b = 0; b < 10; b++)
        {
            DelayMs(100);
        }
    }
}

/*-------------------------------------------------
 * 函数名称：WDT_INITIAL
 * 功能：初始化设置看门狗1S时间复位
 * 相关寄存器：
 * 1、INTCON 
 * 2、OPTION
 * 3、WDTCON
 -------------------------------------------------*/
void WDT_INITIAL(void)
{
    CLRWDT();            //清看门狗
    PSA = 1;             //时钟分频分给WDT，Darren修改了
    WDTCON = 0B00001010; //WDTPS=0101=1:1024,PS=000=1:1
                         //定时时间=(1024*1)/32000=32ms
}
/*-------------------------------------------------
 *  函数名: main 
 *	功能：  主函数
 *  输入：  无
 *  输出：  无
 --------------------------------------------------*/
void main()
{
    POWER_INITIAL(); //系统初始化
    WDT_INITIAL();
    DemoPortOut = 1;
    DelayMs(3); //3ms
    DemoPortOut = 0;
    DelayMs(3); //3ms
    while (1)
    {
        //	CLRWDT(); 			//清看门狗
        DemoPortOut = 1;
        DelayMs(1); //1ms
        DemoPortOut = 0;
        DelayMs(1); //1ms
        SLEEP();
    }
}