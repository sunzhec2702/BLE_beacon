//Project: MG117McuBeacon.prj
// Device: FT60F01X
// Memory: Flash 1KX14b, EEPROM 256X8b, SRAM 64X8b
// Author: Darren Sun
//Company:
//Version: 0.1
//   Date: 2019-1-22
//===========================================================
//===========================================================
/*
*                  MG117  SOP8 
*                 ----------------
*  VDD-----------|1(VDD)    (GND)8|------------GND     
*  LED_N---------|2(PA2)    (PA4)7|-----------BTN3 (Rapid Adv Data)
*  NC------------|3(PA1)    (PA5)6|-----------BTN2 (Normal Adv Data)
*  RSTn----------|4(PA3)    (PA0)5|-------------NC
*			      ----------------
*/

#include "SYSCFG.h";
#include "FT60F01X.h";

//===========================================================
//Variable definition
#define unchar unsigned char
#define unint unsigned int
#define unlong unsigned long

#define LED_PIN RA2
#define NORMAL_ADV_BTN RA4
#define RAPID_ADV_BTN RA5

#define RAPID_PERIOD 1500 // 1500ms
#define RAPID_PERIOD_S  1
#define RAPID_PERIOD_MS 500

#define LED_ON_PERIOD 50 // 100ms

#define NORMAL_INTERVAL 2000   // Send Normal Adv every 1s.
#define NORMAL_PRESS_HOLD 1 // 1ms
#define NORMAL_RELEASE_HOLD (10) // 10 ms for release

//===========================================================

void interrupt ISR(void)
{
}

// System init
void POWER_INITIAL(void)
{
    OSCCON = 0B01010001; //WDT 32KHZ IRCF=101=4MHZ.
                         // Change it to 4MHz as default
                         //Bit0=1,ϵͳʱ��Ϊ�ڲ�����(60F01x����λ)
                         //Bit0=0,ʱ��Դ��FOSC<2��0>����������ѡ��ʱѡ��(60F01x����λ)

    INTCON = 0; //�ݽ�ֹ�����ж�
    PORTA = 0B00000000;
    LED_PIN = 1;
    NORMAL_ADV_BTN = 1;
    RAPID_ADV_BTN = 1;

    TRISA = 0B11111111; //PA�������?0-���?1-����
                        //PA2/PA4/PA5->���?

    TRISA2 = 0;         //û�����룬Ψһ����Reset
    TRISA4 = 0;
    TRISA5 = 0;

    LED_PIN = 1;
    NORMAL_ADV_BTN = 1;
    RAPID_ADV_BTN = 1;

    WPUA = 0B00000000; //PA�˿��������� 1-������ 0-������������OUTPUT����������
    OPTION = 0B00001000;  //Bit3=1 WDT MODE,PS=000=1:1 WDT RATE, Bit7(PAPU)=0 ENABLED PULL UP PA

    MSCKCON = 0B00000000; //Bit6->0,��ֹPA4, PC5��ѹ���?60F01x����λ)
                          //Bit5->0,TIMER2ʱ��ΪFosc(60F01x����λ)
                          //Bit4->0,��ֹLVR(60F01x O��֮ǰ)
                          //Bit4->0, LVRENʹ��ʱ,����LVR(60F01x O�漰O���?
                          //Bit4->1, LVRENʹ��ʱ,����ʱ����LVR, ˯��ʱ�Զ��ر�LVR(60F01x O�漰O��֮��)
}

void WDT_INITIAL(void)
{
    CLRWDT();            //�忴�Ź�
    PSA = 1;             //ʱ�ӷ�Ƶ�ָ�WDT��Darren�޸���
    WDTCON = 0B00010110; //WDTPS=1010=1:32768,PS=000=1:1. Watchdot Timeout=(32768*1)/32000=2.048s
    SWDTEN = 0;
}

void DelayUs(unsigned char Time)
{
    unsigned char a;
    for (a = 0; a < Time; a++)
    {
        NOP();
    }
}
void DelayMs(unsigned char Time)
{
    unsigned char a, b;
    for (a = 0; a < Time; a++)
    {
        for (b = 0; b < 5; b++)
        {
            DelayUs(25); //��1%
        }
    }
}
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

//===========================================================
//Funtion name��main
//parameters����
//returned value����
//===========================================================
main()
{
    POWER_INITIAL(); // System Init
    WDT_INITIAL();   // WDT Init. Watchdog Timeout set to 1.024s
	
    // Sleep 

    // Hold RAPID_ADV_BTN for RAPID_PERIOD
    RAPID_ADV_BTN = 0;
    DelayS(RAPID_PERIOD_S);
    DelayMs(RAPID_PERIOD_MS);
    RAPID_ADV_BTN = 1;
     // Blink one time.
    LED_PIN = 0;
    DelayMs(LED_ON_PERIOD);
    LED_PIN = 1;
    DelayMs(10);

    // Enter Normal Status. Doing while(1)
    while (1)
    {
        CLRWDT();   // Clear Watdog
        SWDTEN = 1; // Enable Watchdog

        NORMAL_ADV_BTN = 0; // Press Normal Button.
        DelayMs(NORMAL_PRESS_HOLD);
        NORMAL_ADV_BTN = 1;
        DelayMs(NORMAL_RELEASE_HOLD);
        // Sleep and waiting for the watchdog to wake up.
        SLEEP();
    }
}
//===========================================================
