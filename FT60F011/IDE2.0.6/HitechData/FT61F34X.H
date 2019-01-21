
#ifndef	_HTC_H_
#warning Header file pic16f685.h included directly. Use #include <htc.h> instead.
#endif

/* header file for the MICROCHIP PIC microcontroller
 *  16F685
 */


#ifndef __PIC16F685_H
#define __PIC16F685_H

//
// Configuration mask definitions
//


// Config Register: CONFIG
#define CONFIG               0x2007
// Oscillator Selection bits
// RC oscillator: CLKOUT function on RA4/OSC2/CLKOUT pin, RC on RA5/OSC1/CLKIN
#define FOSC_EXTRCCLK        0xFFFF
// RCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, RC on RA5/OSC1/CLKIN
#define FOSC_EXTRCIO         0xFFFE
// INTOSC oscillator: CLKOUT function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN
#define FOSC_INTRCCLK        0xFFFD
// INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN
#define FOSC_INTRCIO         0xFFFC
// EC: I/O function on RA4/OSC2/CLKOUT pin, CLKIN on RA5/OSC1/CLKIN
#define FOSC_EC              0xFFFB
// HS oscillator: High-speed crystal/resonator on RA4/OSC2/CLKOUT and RA5/OSC1/CLKIN
#define FOSC_HS              0xFFFA
// XT oscillator: Crystal/resonator on RA4/OSC2/CLKOUT and RA5/OSC1/CLKIN
#define FOSC_XT              0xFFF9
// LP oscillator: Low-power crystal on RA4/OSC2/CLKOUT and RA5/OSC1/CLKIN
#define FOSC_LP              0xFFF8
// Watchdog Timer Enable bit
// WDT enabled
#define WDTE_ON              0xFFFF
// WDT disabled and can be enabled by SWDTEN bit of the WDTCON register
#define WDTE_OFF             0xFFF7
// Power-up Timer Enable bit
// PWRT disabled
#define PWRTE_OFF            0xFFFF
// PWRT enabled
#define PWRTE_ON             0xFFEF
// MCLR Pin Function Select bit
// MCLR pin function is MCLR
#define MCLRE_ON             0xFFFF
// MCLR pin function is digital input, MCLR internally tied to VDD
#define MCLRE_OFF            0xFFDF
// Code Protection bit
// Program memory code protection is disabled
#define CP_OFF               0xFFFF
// Program memory code protection is enabled
#define CP_ON                0xFFBF
// Data Code Protection bit
// Data memory code protection is disabled
#define CPD_OFF              0xFFFF
// Data memory code protection is enabled
#define CPD_ON               0xFF7F
// Brown-out Reset Selection bits
// BOR enabled
#define BOREN_ON             0xFFFF
// BOR enabled during operation and disabled in Sleep
#define BOREN_NSLEEP         0xFEFF
// BOR controlled by SBOREN bit of the PCON register
#define BOREN_SBODEN         0xFDFF
// BOR disabled
#define BOREN_OFF            0xFCFF
// Internal External Switchover bit
// Internal External Switchover mode is enabled
#define IESO_ON              0xFFFF
// Internal External Switchover mode is disabled
#define IESO_OFF             0xFBFF
// Fail-Safe Clock Monitor Enabled bit
// Fail-Safe Clock Monitor is enabled
#define FCMEN_ON             0xFFFF
// Fail-Safe Clock Monitor is disabled
#define FCMEN_OFF            0xF7FF


//
// Special function register definitions
//


// Register: INDF
volatile unsigned char           INDF                @ 0x000;
// bit and bitfield definitions

// Register: TMR0
volatile unsigned char           TMR0                @ 0x001;
// bit and bitfield definitions

// Register: PCL
volatile unsigned char           PCL                 @ 0x002;
// bit and bitfield definitions

// Register: STATUS
volatile unsigned char           STATUS              @ 0x003;
// bit and bitfield definitions
volatile bit CARRY               @ ((unsigned)&STATUS*8)+0;
volatile bit DC                  @ ((unsigned)&STATUS*8)+1;
volatile bit ZERO                @ ((unsigned)&STATUS*8)+2;
volatile bit nPD                 @ ((unsigned)&STATUS*8)+3;
volatile bit nTO                 @ ((unsigned)&STATUS*8)+4;
volatile bit RP0                 @ ((unsigned)&STATUS*8)+5;
volatile bit RP1                 @ ((unsigned)&STATUS*8)+6;
volatile bit FSR_B8              @ ((unsigned)&STATUS*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	CARRY               : 1;
        unsigned	DC                  : 1;
        unsigned	ZERO                : 1;
        unsigned	nPD                 : 1;
        unsigned	nTO                 : 1;
        unsigned	RP                  : 2;
        unsigned	FSR_B8              : 1;
    };
    struct{
    		unsigned  C										:1;
    		unsigned HC 									:1;
    		unsigned Z  									:1;
    		unsigned nPF 									:1;
    		unsigned nTF									:1;
    		unsigned PAGE									:2;
    };
    struct{
    		unsigned    									:5;
    		unsigned PAGE0								:1;
    		unsigned PAGE1								:1;
    };
    struct{
    		unsigned    									:5;
    		unsigned RP0								  :1;
    		unsigned RP1								  :1;
    };
} STATUSbits @ 0x003;
#endif

// Register: FSR
volatile unsigned char           FSR                 @ 0x004;
// bit and bitfield definitions

// Register: PORTA
volatile unsigned char           PORTA               @ 0x005;
// bit and bitfield definitions
volatile bit RA0                 @ ((unsigned)&PORTA*8)+0;
volatile bit RA1                 @ ((unsigned)&PORTA*8)+1;
volatile bit RA2                 @ ((unsigned)&PORTA*8)+2;
volatile bit RA3                 @ ((unsigned)&PORTA*8)+3;
volatile bit RA4                 @ ((unsigned)&PORTA*8)+4;
volatile bit RA5                 @ ((unsigned)&PORTA*8)+5;
volatile bit RA6                 @ ((unsigned)&PORTA*8)+6;
volatile bit RA7                 @ ((unsigned)&PORTA*8)+7;

volatile bit PA0                 @ ((unsigned)&PORTA*8)+0;
volatile bit PA1                 @ ((unsigned)&PORTA*8)+1;
volatile bit PA2                 @ ((unsigned)&PORTA*8)+2;
volatile bit PA3                 @ ((unsigned)&PORTA*8)+3;
volatile bit PA4                 @ ((unsigned)&PORTA*8)+4;
volatile bit PA5                 @ ((unsigned)&PORTA*8)+5;
volatile bit PA6                 @ ((unsigned)&PORTA*8)+6;
volatile bit PA7                 @ ((unsigned)&PORTA*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	RA0                 : 1;
        unsigned	RA1                 : 1;
        unsigned	RA2                 : 1;
        unsigned	RA3                 : 1;
        unsigned	RA4                 : 1;
        unsigned	RA5                 : 1;
        unsigned	RA6                 : 1;
        unsigned	RA7                 : 1;
    };
    struct {
        unsigned	RA                  : 8;
    };
	struct {
        unsigned	PA0                 : 1;
        unsigned	PA1                 : 1;
        unsigned	PA2                 : 1;
        unsigned	PA3                 : 1;
        unsigned	PA4                 : 1;
        unsigned	PA5                 : 1;
        unsigned	PA6                 : 1;
        unsigned	PA7                 : 1;
    };
    struct {
        unsigned	PA                  : 8;
    };
} PORTAbits @ 0x005;
#endif

//conrad add
// Register: PORTB
volatile unsigned char           PORTB              @ 0x006;
// bit and bitfield definitions
volatile bit RB0                 @ ((unsigned)&PORTB*8)+0;
volatile bit RB1                 @ ((unsigned)&PORTB*8)+1;
volatile bit RB2                 @ ((unsigned)&PORTB*8)+2;
volatile bit RB3                 @ ((unsigned)&PORTB*8)+3;

volatile bit PB0                 @ ((unsigned)&PORTB*8)+0;
volatile bit PB1                 @ ((unsigned)&PORTB*8)+1;
volatile bit PB2                 @ ((unsigned)&PORTB*8)+2;
volatile bit PB3                 @ ((unsigned)&PORTB*8)+3;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	RB0                 : 1;
        unsigned	RB1                 : 1;
        unsigned	RB2                 : 1;
        unsigned	RB3                 : 1;
    };
    struct {
        unsigned	RB                  : 4;
    };
	struct {
        unsigned	PB0                 : 1;
        unsigned	PB1                 : 1;
        unsigned	PB2                 : 1;
        unsigned	PB3                 : 1;
    };
    struct {
        unsigned	PB                  : 4;
    };
} PORTBbits @ 0x006;
#endif

// Register: PORTC
volatile unsigned char           PORTC               @ 0x007;
// bit and bitfield definitions
volatile bit RC0                 @ ((unsigned)&PORTC*8)+0;
volatile bit RC1                 @ ((unsigned)&PORTC*8)+1;
volatile bit RC2                 @ ((unsigned)&PORTC*8)+2;
volatile bit RC3                 @ ((unsigned)&PORTC*8)+3;
volatile bit RC4                 @ ((unsigned)&PORTC*8)+4;
volatile bit RC5                 @ ((unsigned)&PORTC*8)+5;

volatile bit PC0                 @ ((unsigned)&PORTC*8)+0;
volatile bit PC1                 @ ((unsigned)&PORTC*8)+1;
volatile bit PC2                 @ ((unsigned)&PORTC*8)+2;
volatile bit PC3                 @ ((unsigned)&PORTC*8)+3;
volatile bit PC4                 @ ((unsigned)&PORTC*8)+4;
volatile bit PC5                 @ ((unsigned)&PORTC*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	RC0                 : 1;
        unsigned	RC1                 : 1;
        unsigned	RC2                 : 1;
        unsigned	RC3                 : 1;
        unsigned	RC4                 : 1;
        unsigned	RC5                 : 1;
    };
    struct {
        unsigned	RC                  : 6;
    };
	struct {
        unsigned	PC0                 : 1;
        unsigned	PC1                 : 1;
        unsigned	PC2                 : 1;
        unsigned	PC3                 : 1;
        unsigned	PC4                 : 1;
        unsigned	PC5                 : 1;
    };
    struct {
        unsigned	PC                  : 6;
    };
} PORTCbits @ 0x007;
#endif

// Register: FOSCCAL
volatile unsigned char           FOSCCAL              @ 0x009;
// bit and bitfield definitions
volatile bit FOSCCAL0                @ ((unsigned)&FOSCCAL*8)+0;
volatile bit FOSCCAL1                @ ((unsigned)&FOSCCAL*8)+1;
volatile bit FOSCCAL2                @ ((unsigned)&FOSCCAL*8)+2;
volatile bit FOSCCAL3                @ ((unsigned)&FOSCCAL*8)+3;
volatile bit FOSCCAL4                @ ((unsigned)&FOSCCAL*8)+4;
volatile bit FOSCCAL5                @ ((unsigned)&FOSCCAL*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	FOSCCAL0                : 1;
        unsigned	FOSCCAL1                : 1;
        unsigned	FOSCCAL2                : 1;
        unsigned	FOSCCAL3                : 1;
        unsigned	FOSCCAL4                : 1;
        unsigned	FOSCCAL5                : 1;
    };
    struct {
        unsigned	FOSCCAL                : 6;
    };
} FOSCCALbits @ 0x009;
#endif
// Register: PCLATH
volatile unsigned char           PCLATH              @ 0x00A;
// bit and bitfield definitions
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                    : 5;
    };
} PCLATHbits @ 0x00A;
#endif

// Register: INTCON
volatile unsigned char           INTCON              @ 0x00B;
// bit and bitfield definitions
volatile bit PAIF                @ ((unsigned)&INTCON*8)+0;
volatile bit INTF                @ ((unsigned)&INTCON*8)+1;
volatile bit T0IF                @ ((unsigned)&INTCON*8)+2;
volatile bit PAIE                @ ((unsigned)&INTCON*8)+3;
volatile bit INTE                @ ((unsigned)&INTCON*8)+4;
volatile bit T0IE                @ ((unsigned)&INTCON*8)+5;
volatile bit PEIE                @ ((unsigned)&INTCON*8)+6;
volatile bit GIE                 @ ((unsigned)&INTCON*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PAIF                : 1;
        unsigned	INTF                : 1;
        unsigned	T0IF                : 1;
        unsigned	PAIE                : 1;
        unsigned	INTE                : 1;
        unsigned	T0IE                : 1;
        unsigned	PEIE                : 1;
        unsigned	GIE                 : 1;
    };
} INTCONbits @ 0x00B;
#endif

//conrad change
// Register: PIR1
volatile unsigned char           PIR1                @ 0x00C;
// bit and bitfield definitions
volatile bit TMR1IF              @ ((unsigned)&PIR1*8)+0;
volatile bit TMR2IF              @ ((unsigned)&PIR1*8)+1;
volatile bit OSFIF               @ ((unsigned)&PIR1*8)+2;
volatile bit C4IF                @ ((unsigned)&PIR1*8)+3;
volatile bit C5IF                @ ((unsigned)&PIR1*8)+4;
volatile bit CKMEAIF             @ ((unsigned)&PIR1*8)+6;
volatile bit EEIF                @ ((unsigned)&PIR1*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TMR1IF        			: 1;
        unsigned	TMR2IF              : 1;
        unsigned	OSFIF         			: 1;
        unsigned	C4IF          			: 1;
        unsigned	C5IF          			: 1;
        unsigned	                    : 1;
        unsigned	CKMEAIF             : 1;
        unsigned	EEIF                : 1;
    };
} PIR1bits @ 0x00C;
#endif

// Register: PIR2
volatile unsigned char           PIR2                @ 0x00D;
// bit and bitfield definitions
volatile bit CCP1IF              @ ((unsigned)&PIR2*8)+0;
volatile bit ADIF                @ ((unsigned)&PIR2*8)+1;
volatile bit C0IF                @ ((unsigned)&PIR2*8)+2;
volatile bit C1IF                @ ((unsigned)&PIR2*8)+3;
volatile bit C2IF                @ ((unsigned)&PIR2*8)+4;
volatile bit C3IF                @ ((unsigned)&PIR2*8)+5;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	CCP1IF        		  : 1;
        unsigned	ADIF                : 1;
        unsigned	C0IF                : 1;
        unsigned	C1IF                : 1;
        unsigned	C2IF                : 1;
        unsigned	C3IF                : 1;
    };
} PIR2bits @ 0x00D;
#endif

// Register: TMR1L
volatile unsigned char           TMR1L              @ 0x00E;
// bit and bitfield definitions

// Register: TMR1H
volatile unsigned char           TMR1H              @ 0x00F;
// bit and bitfield definitions

// Register: T1CON
volatile unsigned char           T1CON              @ 0x0010;
// bit and bitfield definitions
volatile bit TMR1ON              @ ((unsigned)&T1CON*8)+0;
volatile bit TMR1CS              @ ((unsigned)&T1CON*8)+1;
volatile bit T1SYNC              @ ((unsigned)&T1CON*8)+2;
volatile bit T1OSCEN             @ ((unsigned)&T1CON*8)+3;
volatile bit T1CKPS0             @ ((unsigned)&T1CON*8)+4;
volatile bit T1CKPS1             @ ((unsigned)&T1CON*8)+5;
volatile bit TMR1GE              @ ((unsigned)&T1CON*8)+6;
volatile bit T1GINV              @ ((unsigned)&T1CON*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TMR1ON        		  : 1;
        unsigned	TMR1CS              : 1;
        unsigned	T1SYNC              : 1;
        unsigned	T1OSCEN             : 1;
        unsigned	T1CKPS              : 2;
        unsigned	TMR1GE              : 1;
        unsigned	T1GINV              : 1;
    };
	    struct {
        unsigned	             		    : 4;
        unsigned	T1CKPS0             : 1;
		    unsigned	T1CKPS1             : 1;
    };
} T1CONbits @0x010;
#endif

// Register: TMR2
volatile unsigned char           TMR2                @ 0x011;
// bit and bitfield definitions

// Register: T2CON
volatile unsigned char           T2CON               @ 0x012;
// bit and bitfield definitions
volatile bit T2CKPS0             @ ((unsigned)&T2CON*8)+0;
volatile bit T2CKPS1             @ ((unsigned)&T2CON*8)+1;
volatile bit TMR2ON              @ ((unsigned)&T2CON*8)+2;
volatile bit TOUTPS0             @ ((unsigned)&T2CON*8)+3;
volatile bit TOUTPS1             @ ((unsigned)&T2CON*8)+4;
volatile bit TOUTPS2             @ ((unsigned)&T2CON*8)+5;
volatile bit TOUTPS3             @ ((unsigned)&T2CON*8)+6;
volatile bit NRPM             	 @ ((unsigned)&T2CON*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T2CKPS              : 2;
        unsigned	TMR2ON              : 1;
        unsigned	TOUTPS              : 4;
				unsigned  NRPM				        : 1;
    };
    struct {
        unsigned	T2CKPS0             : 1;
        unsigned	T2CKPS1             : 1;
        unsigned	                    : 1;
        unsigned	TOUTPS0             : 1;
        unsigned	TOUTPS1             : 1;
        unsigned	TOUTPS2             : 1;
        unsigned	TOUTPS3             : 1;
    };
} T2CONbits @ 0x012;
#endif
// bit and bitfield definitions

// Register: CCPR1L
volatile unsigned char           CCPR1L                @ 0x013;
// bit and bitfield definitions

// Register: CCPR1H
volatile unsigned char           CCPR1H                @ 0x014;
// bit and bitfield definitions

// Register: CCP1CON
volatile unsigned char           CCP1CON               @ 0x015;
// bit and bitfield definitions
volatile bit CCP1M0              @ ((unsigned)&CCP1CON*8)+0;
volatile bit CCP1M1              @ ((unsigned)&CCP1CON*8)+1;
volatile bit CCP1M2              @ ((unsigned)&CCP1CON*8)+2;
volatile bit CCP1M3              @ ((unsigned)&CCP1CON*8)+3;
volatile bit DC1B0               @ ((unsigned)&CCP1CON*8)+4;
volatile bit DC1B1               @ ((unsigned)&CCP1CON*8)+5;
volatile bit P1M0                @ ((unsigned)&CCP1CON*8)+6;
volatile bit P1M1                @ ((unsigned)&CCP1CON*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	CCP1M               : 4;
        unsigned	DC1B                : 2;
        unsigned	P1M                 : 2;
    };
    struct {
        unsigned	CCP1M0              : 1;
        unsigned	CCP1M1              : 1;
        unsigned	CCP1M2              : 1;
        unsigned	CCP1M3              : 1;
        unsigned	DC1B0               : 1;
        unsigned	DC1B1               : 1;
        unsigned	P1M0                : 1;
        unsigned	P1M1                : 1;
    };
} CCP1CONbits @ 0x015;
#endif
// bit and bitfield definitions

// Register: PWM1CON
volatile unsigned char           PWM1CON               @ 0x016;
// bit and bitfield definitions
volatile bit PDC0                 @ ((unsigned)&PWM1CON*8)+0;
volatile bit PDC1                 @ ((unsigned)&PWM1CON*8)+1;
volatile bit PDC2                 @ ((unsigned)&PWM1CON*8)+2;
volatile bit PDC3                 @ ((unsigned)&PWM1CON*8)+3;
volatile bit PDC4                 @ ((unsigned)&PWM1CON*8)+4;
volatile bit PDC5                 @ ((unsigned)&PWM1CON*8)+5;
volatile bit PDC6                 @ ((unsigned)&PWM1CON*8)+6;
volatile bit PRSEN                @ ((unsigned)&PWM1CON*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PDC                 : 7;
        unsigned	PRSEN               : 1;
    };
    struct {
        unsigned	PDC0                : 1;
        unsigned	PDC1                : 1;
        unsigned	PDC2                : 1;
        unsigned	PDC3                : 1;
        unsigned	PDC4                : 1;
        unsigned	PDC5                : 1;
        unsigned	PDC6                : 1;
    };
} PWM1CONbits @ 0x016;
#endif
// bit and bitfield definitions

// Register: ECCPAS
volatile unsigned char           ECCPAS               @ 0x017;
// bit and bitfield definitions
volatile bit PSSBD0                 @ ((unsigned)&ECCPAS*8)+0;
volatile bit PSSBD1                 @ ((unsigned)&ECCPAS*8)+1;
volatile bit PSSAC0                 @ ((unsigned)&ECCPAS*8)+2;
volatile bit PSSAC1                 @ ((unsigned)&ECCPAS*8)+3;
volatile bit ECCPAS0                @ ((unsigned)&ECCPAS*8)+4;
volatile bit ECCPAS1                @ ((unsigned)&ECCPAS*8)+5;
volatile bit ECCPAS2                @ ((unsigned)&ECCPAS*8)+6;
volatile bit ECCPASE                @ ((unsigned)&ECCPAS*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PSSBD               : 2;
        unsigned	PSSAC               : 2;
        unsigned	ECCPAS              : 3;
        unsigned	ECCPASE             : 1;
    };
    struct {
        unsigned	PSSBD0              : 1;
        unsigned	PSSBD1              : 1;
        unsigned	PSSAC0              : 1;
        unsigned	PSSAC1              : 1;
        unsigned	ECCPAS0             : 1;
        unsigned	ECCPAS1             : 1;
        unsigned	ECCPAS2             : 1;
    };
} ECCPASbits @ 0x017;
#endif
// bit and bitfield definitions
// Register: WDTCON
volatile unsigned char           WDTCON             @ 0x018;
// bit and bitfield definitions
volatile bit SWDTEN                @ ((unsigned)&WDTCON*8)+0;
volatile bit WDTPS0                @ ((unsigned)&WDTCON*8)+1;
volatile bit WDTPS1                @ ((unsigned)&WDTCON*8)+2;
volatile bit WDTPS2                @ ((unsigned)&WDTCON*8)+3;
volatile bit WDTPS3                @ ((unsigned)&WDTCON*8)+4;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	SWDTEN              : 1;
        unsigned	WDTPS               : 4;
    };
    struct {
        unsigned	                   : 1;
        unsigned	WDTPS0             : 1;
        unsigned	WDTPS1             : 1;
        unsigned	WDTPS2             : 1;
        unsigned	WDTPS3             : 1;
    };
} WDTCONbits @ 0x018;
#endif

//conrad change 
// Register: CMCON0
volatile unsigned char           CMCON0             @ 0x019;
// bit and bitfield definitions
volatile bit CM0                  @ ((unsigned)&CMCON0*8)+0;
volatile bit CM1                  @ ((unsigned)&CMCON0*8)+1;
volatile bit CM2                  @ ((unsigned)&CMCON0*8)+2;
volatile bit CIS                  @ ((unsigned)&CMCON0*8)+3;
volatile bit C4INV                @ ((unsigned)&CMCON0*8)+4;
volatile bit C5INV                @ ((unsigned)&CMCON0*8)+5;
volatile bit C4OUT                @ ((unsigned)&CMCON0*8)+6;
volatile bit C5OUT                @ ((unsigned)&CMCON0*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	CM                 : 3;
        unsigned	CIS				         : 1;
        unsigned	C4INV              : 1;
        unsigned	C5INV              : 1;
        unsigned	C4OUT              : 1;
        unsigned	C5OUT              : 1;
    };
    struct {
        unsigned	CM0                : 1;
        unsigned	CM1                : 1;
        unsigned	CM2                : 1;
    };
} CMCON0bits @ 0x019;
#endif

// Register: CMCON1
volatile unsigned char           CMCON1             @ 0x01A;
// bit and bitfield definitions
volatile bit C2SYNC                  @ ((unsigned)&CMCON1*8)+0;
volatile bit T1GSS                   @ ((unsigned)&CMCON1*8)+1;
volatile bit HYSEN0                  @ ((unsigned)&CMCON1*8)+4;
volatile bit HYSEN1                  @ ((unsigned)&CMCON1*8)+5;
volatile bit HYSEN2                  @ ((unsigned)&CMCON1*8)+6;
volatile bit HYSEN3                  @ ((unsigned)&CMCON1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	C2SYNC             	: 1;
        unsigned	T1GSS 			 	      : 1;
				unsigned 						          : 1;
				unsigned						          : 1;
				unsigned	HYSEN				        : 4;

    };
	struct{
				unsigned	                    : 4;
				unsigned	HYSEN0				      : 1;
				unsigned	HYSEN1				      : 1;
				unsigned	HYSEN2				      : 1;
				unsigned	HYSEN3				      : 1;
	};
} CMCON1bits @ 0x01a;
#endif

// Register: MSCKCON
volatile unsigned char           MSCKCON         @ 0x01B;
// bit and bitfield definitions
volatile bit CK32MS                   @ ((unsigned)&MSCKCON*8)+0;
volatile bit CKCNTI                   @ ((unsigned)&MSCKCON*8)+1;
volatile bit CKMAVG                   @ ((unsigned)&MSCKCON*8)+2;
volatile bit SLVREN                   @ ((unsigned)&MSCKCON*8)+4;
volatile bit T2CKSRC                  @ ((unsigned)&MSCKCON*8)+5;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	CK32MS               : 1;
        unsigned	CKCNTI               : 1;
        unsigned	CKMAVG               : 1;
        unsigned	                     : 1;
        unsigned	SLVREN               : 1;
        unsigned	T2CKSRC				       : 1;
    };
} MSCKCONbits @ 0x01B;
#endif

// Register: SOSCPRL
volatile unsigned char           SOSCPRL             @ 0x01C;
// bit and bitfield definitions

// Register: SOSCPRH
volatile unsigned char           SOSCPRH              @ 0x01D;
// bit and bitfield definitions
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	SOSCPRH              : 4;
    };
} SOSCPRHbits @ 0x01D;
#endif


// Register: ADRESH
volatile unsigned char           ADRESH              @ 0x01E;
// bit and bitfield definitions
//
// Register: MSCKCON
volatile unsigned char           ADCON0             @ 0x01F;
// bit and bitfield definitions
volatile bit ADON                      @ ((unsigned)&ADCON0*8)+0;
volatile bit GO_DONE                   @ ((unsigned)&ADCON0*8)+1;
volatile bit CHS0                      @ ((unsigned)&ADCON0*8)+2;
volatile bit CHS1                      @ ((unsigned)&ADCON0*8)+3;
volatile bit CHS2                      @ ((unsigned)&ADCON0*8)+4;
volatile bit VCFG0                     @ ((unsigned)&ADCON0*8)+5;
volatile bit VCHG1                     @ ((unsigned)&ADCON0*8)+6;
volatile bit ADFM                      @ ((unsigned)&ADCON0*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	ADON                 : 1;
        unsigned	GO_DONE              : 1;
        unsigned	CHS                  : 3;
        unsigned	VCFG                 : 2;
        unsigned	ADFM                 : 1;
    };
    struct {
        unsigned	                     : 2;
        unsigned	CHS0                 : 1;
        unsigned	CHS1                 : 1;
        unsigned	CHS2                 : 1;
        unsigned	VCFG0                : 1;
        unsigned	VCFG1                : 1;
    };
} ADCON0bits @ 0x01F;
#endif
// Special function register definitions: Bank 1
//

// Register: OPTION_REG
volatile unsigned char           OPTION          @ 0x081;
// bit and bitfield definitions
volatile bit PS0                 @ ((unsigned)&OPTION*8)+0;
volatile bit PS1                 @ ((unsigned)&OPTION*8)+1;
volatile bit PS2                 @ ((unsigned)&OPTION*8)+2;
volatile bit PSA                 @ ((unsigned)&OPTION*8)+3;
volatile bit T0SE                @ ((unsigned)&OPTION*8)+4;
volatile bit T0CS                @ ((unsigned)&OPTION*8)+5;
volatile bit INTEDG              @ ((unsigned)&OPTION*8)+6;
volatile bit nPAPU               @ ((unsigned)&OPTION*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PS                  : 3;
        unsigned	PSA                 : 1;
        unsigned	T0SE                : 1;
        unsigned	T0CS                : 1;
        unsigned	INTEDG              : 1;
        unsigned	nPAPU               : 1;
    };
    struct {
        unsigned	PS0                 : 1;
        unsigned	PS1                 : 1;
        unsigned	PS2                 : 1;
    };
} OPTIONbits @ 0x081;
#endif

// Register: TRISA
volatile unsigned char           TRISA               @ 0x085;
// bit and bitfield definitions
volatile bit TRISA0              @ ((unsigned)&TRISA*8)+0;
volatile bit TRISA1              @ ((unsigned)&TRISA*8)+1;
volatile bit TRISA2              @ ((unsigned)&TRISA*8)+2;
volatile bit TRISA3              @ ((unsigned)&TRISA*8)+3;
volatile bit TRISA4              @ ((unsigned)&TRISA*8)+4;
volatile bit TRISA5              @ ((unsigned)&TRISA*8)+5;
volatile bit TRISA6              @ ((unsigned)&TRISA*8)+6;
volatile bit TRISA7              @ ((unsigned)&TRISA*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TRISA0              : 1;
        unsigned	TRISA1              : 1;
        unsigned	TRISA2              : 1;
        unsigned	TRISA3              : 1;
        unsigned	TRISA4              : 1;
        unsigned	TRISA5              : 1;
        unsigned	TRISA6              : 1;
        unsigned	TRISA7              : 1;
    };
    struct {
        unsigned	TRISA               : 8;
    };
} TRISAbits @ 0x085;
#endif
//conrad add
// Register: TRISA
volatile unsigned char           TRISB               @ 0x086;
// bit and bitfield definitions
volatile bit TRISB0              @ ((unsigned)&TRISB*8)+0;
volatile bit TRISB1              @ ((unsigned)&TRISB*8)+1;
volatile bit TRISB2              @ ((unsigned)&TRISB*8)+2;
volatile bit TRISB3              @ ((unsigned)&TRISB*8)+3;
#ifndef _LIB_BUILD
volatile union {
	struct {
        unsigned	TRISB               : 4;
    };
    struct {
        unsigned	TRISB0              : 1;
        unsigned	TRISB1              : 1;
        unsigned	TRISB2              : 1;
        unsigned	TRISB3              : 1;
    };
} TRISBbits @ 0x086;
#endif
// Register: TRISC
volatile unsigned char           TRISC               @ 0x087;
// bit and bitfield definitions
volatile bit TRISC0              @ ((unsigned)&TRISC*8)+0;
volatile bit TRISC1              @ ((unsigned)&TRISC*8)+1;
volatile bit TRISC2              @ ((unsigned)&TRISC*8)+2;
volatile bit TRISC3              @ ((unsigned)&TRISC*8)+3;
volatile bit TRISC4              @ ((unsigned)&TRISC*8)+4;
volatile bit TRISC5              @ ((unsigned)&TRISC*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TRISC               : 6;
    };
    struct {
        unsigned	TRISC0              : 1;
        unsigned	TRISC1              : 1;
        unsigned	TRISC2              : 1;
        unsigned	TRISC3              : 1;
        unsigned	TRISC4              : 1;
        unsigned	TRISC5              : 1;
    };
} TRISCbits @ 0x087;
#endif

// Register: WPUC
volatile unsigned char           WPUC               @ 0x088;
// bit and bitfield definitions
volatile bit WPUC0              @ ((unsigned)&WPUC*8)+0;
volatile bit WPUC1              @ ((unsigned)&WPUC*8)+1;
volatile bit WPUC2              @ ((unsigned)&WPUC*8)+2;
volatile bit WPUC3              @ ((unsigned)&WPUC*8)+3;
volatile bit WPUC4              @ ((unsigned)&WPUC*8)+4;
volatile bit WPUC5              @ ((unsigned)&WPUC*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	WPUC               : 6;
    };
    struct {
        unsigned	WPUC0              : 1;
        unsigned	WPUC1              : 1;
        unsigned	WPUC2              : 1;
        unsigned	WPUC3              : 1;
        unsigned	WPUC4              : 1;
        unsigned	WPUC5              : 1;
    };
} WPUCbits @ 0x088;
#endif

//conrad change
// Register: WPD
volatile unsigned char           WPD               @ 0x089;
// bit and bitfield definitions
volatile bit WPDC3              @ ((unsigned)&WPD*8)+1;
volatile bit WPDC2              @ ((unsigned)&WPD*8)+2;
volatile bit WPDC1              @ ((unsigned)&WPD*8)+3;
volatile bit WPDA4              @ ((unsigned)&WPD*8)+4;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                   : 1;
        unsigned	WPDC3              : 1;
        unsigned	WPDC2              : 1;
        unsigned	WPDC1              : 1;
        unsigned	WPDA4              : 1;
    };
} WPDbits @ 0x089;
#endif
//conrad change 
// Register: PIE1
volatile unsigned char           PIE1                @ 0x08C;
// bit and bitfield definitions
volatile bit TMR1IE              @ ((unsigned)&PIE1*8)+0;
volatile bit TMR2IE              @ ((unsigned)&PIE1*8)+1;
volatile bit OSFIE               @ ((unsigned)&PIE1*8)+2;
volatile bit C4IE                @ ((unsigned)&PIE1*8)+3;
volatile bit C5IE                @ ((unsigned)&PIE1*8)+4;
volatile bit CKMEAIE             @ ((unsigned)&PIE1*8)+6;
volatile bit EEIE                @ ((unsigned)&PIE1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TMR1IE              : 1;
        unsigned	TMR2IE              : 1;
        unsigned	OSFIE               : 1;
        unsigned	C4IE                : 1;
        unsigned	C5IE                : 1;
        unsigned				              : 1;
        unsigned	CKMEAIE             : 1;
        unsigned	EEIE                : 1;
    };
} PIE1bits @ 0x08C;
#endif


// Register: PIE2
volatile unsigned char           PIE2                @ 0x08D;
// bit and bitfield definitions
volatile bit CCP1IE              @ ((unsigned)&PIE2*8)+0;
volatile bit ADIE                @ ((unsigned)&PIE2*8)+1;
volatile bit C0IE                @ ((unsigned)&PIE2*8)+2;
volatile bit C1IE                @ ((unsigned)&PIE2*8)+3;
volatile bit C2IE                @ ((unsigned)&PIE2*8)+4;
volatile bit C3IE                @ ((unsigned)&PIE2*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	CCP1IE              : 1;
        unsigned	ADIE                : 1;
        unsigned	C0IE                : 1;
        unsigned	C1IE                : 1;
        unsigned	C2IE                : 1;
        unsigned	C3IE                : 1;
    };
} PIE2bits @ 0x08D;
#endif
//conrad change
// Register: PCON
volatile unsigned char           PCON                @ 0x08E;
// bit and bitfield definitions
volatile bit nBOR                @ ((unsigned)&PCON*8)+0;
volatile bit nPOR                @ ((unsigned)&PCON*8)+1;
volatile bit LVDW                @ ((unsigned)&PCON*8)+2;
volatile bit LVDEN               @ ((unsigned)&PCON*8)+3;
volatile bit LVDL0               @ ((unsigned)&PCON*8)+4;
volatile bit LVDL1               @ ((unsigned)&PCON*8)+5;
volatile bit LVDL2               @ ((unsigned)&PCON*8)+6;
volatile bit SYSON               @ ((unsigned)&PCON*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	nBOR                : 1;
        unsigned	nPOR                : 1;
        unsigned	LVDW                : 1;
        unsigned	LVDEN               : 1;
        unsigned	LVDL                : 3;
        unsigned	SYSON               : 1;
        	
    };
    struct {
				unsigned	                    : 4;
        unsigned	LVDL0               : 1;
        unsigned	LVDL1               : 1;
        unsigned	LVDL2               : 1;
    };
} PCONbits @ 0x08E;
#endif

// Register: OSCCON
volatile unsigned char           OSCCON              @ 0x08F;
// bit and bitfield definitions
volatile bit SCS                    @ ((unsigned)&OSCCON*8)+0;
volatile bit LTS                    @ ((unsigned)&OSCCON*8)+1;
volatile bit HTS                    @ ((unsigned)&OSCCON*8)+2;
volatile bit OSTS                   @ ((unsigned)&OSCCON*8)+3;
volatile bit IRCF0                  @ ((unsigned)&OSCCON*8)+4;
volatile bit IRCF1                  @ ((unsigned)&OSCCON*8)+5;
volatile bit IRCF2                  @ ((unsigned)&OSCCON*8)+6;
volatile bit LFOMOD                 @ ((unsigned)&OSCCON*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	SCS                    : 1;
        unsigned	LTS                    : 1;
        unsigned	HTS                    : 1;
        unsigned	OSTS                   : 1;
        unsigned	IRCF                   : 3;
        unsigned	LFOMOD                 : 1;
    };
    struct {
        unsigned	                    : 4;
        unsigned	IRCF0               : 1;
        unsigned	IRCF1               : 1;
        unsigned	IRCF2               : 1;
    };
} OSCCONbits @ 0x08F;
#endif

// Register: PWM1AUX
volatile unsigned char           PWM1AUX              @ 0x090;
// bit and bitfield definitions
volatile bit P1AOE                    @ ((unsigned)&PWM1AUX*8)+0;
volatile bit P1BOE                    @ ((unsigned)&PWM1AUX*8)+1;
volatile bit P1COE                    @ ((unsigned)&PWM1AUX*8)+2;
volatile bit P1DOE                    @ ((unsigned)&PWM1AUX*8)+3;
volatile bit P1EOE                    @ ((unsigned)&PWM1AUX*8)+4;
volatile bit P1FOE                    @ ((unsigned)&PWM1AUX*8)+5;
volatile bit P1OS                     @ ((unsigned)&PWM1AUX*8)+6;
volatile bit AUX1EN                   @ ((unsigned)&PWM1AUX*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	P1AOE                    : 1;
        unsigned	P1BOE                    : 1;
        unsigned	P1COE                    : 1;
        unsigned	P1DOE                    : 1;
        unsigned	P1EOE                	   : 1;
        unsigned	P1FOE                    : 1;
        unsigned	P1OS                	   : 1;
        unsigned	AUX1EN                   : 1;
    };
} PWM1AUXbits @ 0x090;
#endif

// Register: ANSEL
volatile unsigned char           ANSEL              @ 0x091;
// bit and bitfield definitions

// Register: PR2
volatile unsigned char           PR2                 @ 0x092;
// bit and bitfield definitions
volatile bit ANSEL0                    @ ((unsigned)&ANSEL*8)+0;
volatile bit ANSEL1                    @ ((unsigned)&ANSEL*8)+1;
volatile bit ANSEL2                    @ ((unsigned)&ANSEL*8)+2;
volatile bit ANSEL3                    @ ((unsigned)&ANSEL*8)+3;
volatile bit ANSEL4                    @ ((unsigned)&ANSEL*8)+4;
volatile bit ANSEL5                    @ ((unsigned)&ANSEL*8)+5;
volatile bit ANSEL6                    @ ((unsigned)&ANSEL*8)+6;
volatile bit ANSEL7                    @ ((unsigned)&ANSEL*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	ANSEL0                    : 1;
        unsigned	ANSEL1                    : 1;
        unsigned	ANSEL2                    : 1;
        unsigned	ANSEL3                    : 1;
        unsigned	ANSEL4                	  : 1;
        unsigned	ANSEL5                    : 1;
        unsigned	ANSEL6              	    : 1;
        unsigned	ANSEL7                    : 1;
    };
    struct {
        unsigned	ANSEL                     : 8;
    };
} ANSELbits @ 0x091;
#endif
//conrad add
// Register: PR2L
volatile unsigned char           PR2L              @ 0x093;
// bit and bitfield definitions
volatile bit PR2LSB                    @ ((unsigned)&PR2L*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                      	   : 7;
        unsigned	PR2LSB                	   : 1;
    };
} PR2Lbits @ 0x093;
#endif


// Register: WPUA
volatile unsigned char           WPUA                @ 0x095;
volatile unsigned char           WPU                 @ 0x095;
// bit and bitfield definitions
volatile bit WPUA0               @ ((unsigned)&WPUA*8)+0;
volatile bit WPUA1               @ ((unsigned)&WPUA*8)+1;
volatile bit WPUA2               @ ((unsigned)&WPUA*8)+2;
volatile bit WPUA3               @ ((unsigned)&WPUA*8)+3;
volatile bit WPUA4               @ ((unsigned)&WPUA*8)+4;
volatile bit WPUA5               @ ((unsigned)&WPUA*8)+5;
volatile bit WPUA6               @ ((unsigned)&WPUA*8)+6;
volatile bit WPUA7               @ ((unsigned)&WPUA*8)+7;

volatile bit WPU0                @ ((unsigned)&WPUA*8)+0;
volatile bit WPU1                @ ((unsigned)&WPUA*8)+1;
volatile bit WPU2                @ ((unsigned)&WPUA*8)+2;
volatile bit WPU3                @ ((unsigned)&WPUA*8)+3;
volatile bit WPU4                @ ((unsigned)&WPUA*8)+4;
volatile bit WPU5                @ ((unsigned)&WPUA*8)+5;
volatile bit WPU6                @ ((unsigned)&WPUA*8)+6;
volatile bit WPU7                @ ((unsigned)&WPUA*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	WPUA               : 8;
    };
    struct {
        unsigned	WPU                : 8;
    };
} WPUAbits @ 0x095;
#endif

//conrad change
// Register: IOFA
volatile unsigned char           IOFA                @ 0x096;
volatile unsigned char           IOF                 @ 0x096;
// bit and bitfield definitions
volatile bit IOFA0               @ ((unsigned)&IOFA*8)+0;
volatile bit IOFA1               @ ((unsigned)&IOFA*8)+1;
volatile bit IOFA2               @ ((unsigned)&IOFA*8)+2;
volatile bit IOFA3               @ ((unsigned)&IOFA*8)+3;
volatile bit IOFA4               @ ((unsigned)&IOFA*8)+4;
volatile bit IOFA5               @ ((unsigned)&IOFA*8)+5;
volatile bit IOFA6               @ ((unsigned)&IOFA*8)+6;
volatile bit IOFA7               @ ((unsigned)&IOFA*8)+7;

volatile bit IOF0                @ ((unsigned)&IOFA*8)+0;
volatile bit IOF1                @ ((unsigned)&IOFA*8)+1;
volatile bit IOF2                @ ((unsigned)&IOFA*8)+2;
volatile bit IOF3                @ ((unsigned)&IOFA*8)+3;
volatile bit IOF4                @ ((unsigned)&IOFA*8)+4;
volatile bit IOF5                @ ((unsigned)&IOFA*8)+5;
volatile bit IOF6                @ ((unsigned)&IOFA*8)+6;
volatile bit IOF7                @ ((unsigned)&IOFA*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	IOFA               : 8;
    };
    struct {
        unsigned	IOF                : 8;
    };
} IOFAbits @ 0x096;
#endif

// Register: VRCON
volatile unsigned char           VRCON              @ 0x099;
// bit and bitfield definitions
volatile bit VR0              @ ((unsigned)&VRCON*8)+0;
volatile bit VR1              @ ((unsigned)&VRCON*8)+1;
volatile bit VR2              @ ((unsigned)&VRCON*8)+2;
volatile bit VR3              @ ((unsigned)&VRCON*8)+3;
volatile bit VRR              @ ((unsigned)&VRCON*8)+5;
volatile bit VREN             @ ((unsigned)&VRCON*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	VR                  : 4;
        unsigned	                    : 1;
        unsigned	VRR                 : 1;
        unsigned	                    : 1;
        unsigned	VREN                : 1;
    };
    struct {
        unsigned	VR0                 : 1;
        unsigned	VR1                 : 1;
        unsigned	VR2                 : 1;
        unsigned	VR3                 : 1;
    };
} VRCONbits @ 0x099;
#endif

// Register: EEDAT
volatile unsigned char           EEDAT              @ 0x09A;
volatile unsigned char           EEDATA             @ 0x09A;
// bit and bitfield definitions

// Register: EEADR
volatile unsigned char           EEADR              @ 0x09B;
// bit and bitfield definitions


// Register: EECON1
volatile unsigned char           EECON1              @ 0x09C;
// bit and bitfield definitions
volatile bit RD                  @ ((unsigned)&EECON1*8)+0;
volatile bit WREN1               @ ((unsigned)&EECON1*8)+2;
volatile bit WRERR               @ ((unsigned)&EECON1*8)+3;
volatile bit WREN2               @ ((unsigned)&EECON1*8)+4;
volatile bit WREN3               @ ((unsigned)&EECON1*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	RD                  : 1;
        unsigned	                    : 1;
        unsigned	WREN1               : 1;
        unsigned	WRERR               : 1;
        unsigned	WREN2               : 1;
        unsigned	WREN3               : 1;
    };
} EECON1bits @ 0x09C;
#endif

// Register: EECON2
volatile unsigned char           EECON2             @ 0x09D;
// bit and bitfield definitions
volatile bit WR                  @ ((unsigned)&EECON2*8)+0;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	WR                  : 1;
    };
} EECON2bits @ 0x09d;
#endif

// Register: ADRESL
volatile unsigned char           ADRESL             @ 0x09E;
// bit and bitfield definitions

//conrad change
// Register: ADCON1
volatile unsigned char           ADCON1             @ 0x09F;
// bit and bitfield definitions
volatile bit AN0SEL                 @ ((unsigned)&ADCON1*8)+0;
volatile bit ADV1V_SEL              @ ((unsigned)&ADCON1*8)+1;
volatile bit ADCS0                  @ ((unsigned)&ADCON1*8)+4;
volatile bit ADCS1                  @ ((unsigned)&ADCON1*8)+5;
volatile bit ADCS2                  @ ((unsigned)&ADCON1*8)+6;
volatile bit DIVS                   @ ((unsigned)&ADCON1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
				unsigned	AN0SEL                : 1;
				unsigned	ADV1V_SEL             : 1;					
        unsigned	                      : 2;
        unsigned	ADCS                  : 3;
        unsigned	DIVS                  : 1;
    };
    struct {
        unsigned	                      : 4;
        unsigned	ADCS0                 : 1;
        unsigned	ADCS1                 : 1;
        unsigned	ADCS2                 : 1;
				unsigned	                      : 1;
    };
} ADCON1bits @ 0x09F;
#endif

// Special function register definitions: Bank 2
//
//conrad add
// Register: CMCON2
volatile unsigned char           CMCON2          @ 0x0101;
// bit and bitfield definitions
volatile bit VR1C0             	@ ((unsigned)&CMCON2*8)+0;
volatile bit VR1C1             	@ ((unsigned)&CMCON2*8)+1;
volatile bit VR1C2             	@ ((unsigned)&CMCON2*8)+2;
volatile bit VR2C0             	@ ((unsigned)&CMCON2*8)+3;
volatile bit VR2C1             	@ ((unsigned)&CMCON2*8)+4;
volatile bit VR2C2              @ ((unsigned)&CMCON2*8)+5;
volatile bit C0POL              @ ((unsigned)&CMCON2*8)+6;
volatile bit C1POL              @ ((unsigned)&CMCON2*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	VR1C                : 3;
        unsigned	VR2C                : 3;
        unsigned	C0POL               : 1;
        unsigned	C1POL               : 1;
    };
    struct {
        unsigned	VR1C0             : 1;
        unsigned	VR1C1             : 1;
        unsigned	VR1C2             : 1;
        unsigned	VR2C0             : 1;
        unsigned	VR2C1             : 1;
        unsigned	VR2C2             : 1;
    };
} CMCON2bits @ 0x0101;
#endif

//conrad add
// Register: EPWMCR1
volatile unsigned char           EPWMCR1          @ 0x0105;
// bit and bitfield definitions
volatile bit PWMFCKS0             	@ ((unsigned)&EPWMCR1*8)+0;
volatile bit PWMFCKS1             	@ ((unsigned)&EPWMCR1*8)+1;
volatile bit PWMFCKS2             	@ ((unsigned)&EPWMCR1*8)+2;
volatile bit PWMFCKS3             	@ ((unsigned)&EPWMCR1*8)+3;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PWMFCKS             : 4;
    };
    struct {
        unsigned	PWMFCKS0             : 1;
        unsigned	PWMFCKS1             : 1;
        unsigned	PWMFCKS2             : 1;
        unsigned	PWMFCKS3             : 1;
    };
} EPWMCR1bits @ 0x0105;
#endif

//conrad add
// Register: WPUB
volatile unsigned char           WPUB          @ 0x0106;
// bit and bitfield definitions
volatile bit WPUB0             	@ ((unsigned)&WPUB*8)+0;
volatile bit WPUB1             	@ ((unsigned)&WPUB*8)+1;
volatile bit WPUB2             	@ ((unsigned)&WPUB*8)+2;
volatile bit WPUB3             	@ ((unsigned)&WPUB*8)+3;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	WPUB                : 4;
    };
    struct {
        unsigned	WPUB0             : 1;
        unsigned	WPUB1             : 1;
        unsigned	WPUB2             : 1;
        unsigned	WPUB3             : 1;
    };
} WPUBbits @ 0x0106;
#endif

//conrad add
// Register: CMCON3
volatile unsigned char           CMCON3          @ 0x0107;
// bit and bitfield definitions
volatile bit VR3C0             	@ ((unsigned)&CMCON3*8)+0;
volatile bit VR3C1             	@ ((unsigned)&CMCON3*8)+1;
volatile bit VR3C2             	@ ((unsigned)&CMCON3*8)+2;
volatile bit VR4C0            	@ ((unsigned)&CMCON3*8)+3;
volatile bit VR4C1             	@ ((unsigned)&CMCON3*8)+4;
volatile bit VR4C2             	@ ((unsigned)&CMCON3*8)+5;
volatile bit C2POL             	@ ((unsigned)&CMCON3*8)+6;
volatile bit C3POL             	@ ((unsigned)&CMCON3*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	VR3C                : 3;
        unsigned	VR4C                : 3;
        unsigned	C2POL               : 1;
        unsigned	C3POL               : 1;
    };
    struct {
        unsigned	VR3C0             : 1;
        unsigned	VR3C1             : 1;
        unsigned	VR3C2             : 1;
        unsigned	VR4C0             : 1;
        unsigned	VR4C1             : 1;
        unsigned	VR4C2	            : 1;
    };
} CMCON3bits @ 0x0107;
#endif

// Register: POLCON1
volatile unsigned char           POLCON1          @ 0x0108;
// bit and bitfield definitions
volatile bit P1EFPOL             	@ ((unsigned)&POLCON1*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                    : 7;
        unsigned	P1EFPOL             : 1;
    };
} POLCON1bits @ 0x0108;
#endif


// Register: POLCON1
volatile unsigned char           POLCON2          @ 0x0108;
// bit and bitfield definitions
volatile bit P1CDPOL             	@ ((unsigned)&POLCON2*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                    : 7;
        unsigned	P1CDPOL             : 1;
    };
} POLCON2bits @ 0x0108;
#endif

// Register: TMR3L
volatile unsigned char           TMR3L          @ 0x010C;
// bit and bitfield definitions

// Register: TMR3H
volatile unsigned char           TMR3H          @ 0x010D;
// bit and bitfield definitions
volatile bit PR3H0              @ ((unsigned)&TMR3H*8)+0;
volatile bit PR3H1              @ ((unsigned)&TMR3H*8)+1;
volatile bit PR3H2              @ ((unsigned)&TMR3H*8)+2;
volatile bit PR3H3              @ ((unsigned)&TMR3H*8)+3;
volatile bit TMR3H0             @ ((unsigned)&TMR3H*8)+4;
volatile bit TMR3H1             @ ((unsigned)&TMR3H*8)+5;
volatile bit TMR3H2             @ ((unsigned)&TMR3H*8)+6;
volatile bit TMR3H3             @ ((unsigned)&TMR3H*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PR3H                : 4;
        unsigned	TMR3H               : 4;
    };
    struct {
        unsigned	PR3H0             : 1;
        unsigned	PR3H1             : 1;
        unsigned	PR3H2             : 1;
        unsigned	PR3H3             : 1;
        unsigned	TMR3H0            : 1;
        unsigned	TMR3H1            : 1;
        unsigned	TMR3H2            : 1;
        unsigned	TMR3H3            : 1;
    };
} TMR3Hbits @ 0x010D;
#endif

// Register: PR3L
volatile unsigned char           PR3L          @ 0x010E;
// bit and bitfield definitions

// Register: PWM3CR0
volatile unsigned char           PWM3CR0       @ 0x010F;
// bit and bitfield definitions
volatile bit P3BZR              @ ((unsigned)&PWM3CR0*8)+0;
volatile bit P3CKSRC0           @ ((unsigned)&PWM3CR0*8)+1;
volatile bit P3CKSRC1           @ ((unsigned)&PWM3CR0*8)+2;
volatile bit P3CKSRC2           @ ((unsigned)&PWM3CR0*8)+3;
volatile bit P3PER0             @ ((unsigned)&PWM3CR0*8)+4;
volatile bit P3PER1             @ ((unsigned)&PWM3CR0*8)+5;
volatile bit P3PER2             @ ((unsigned)&PWM3CR0*8)+6;
volatile bit P3INTS             @ ((unsigned)&PWM3CR0*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	P3BZR             : 1;
        unsigned	P3CKSRC           : 3;
        unsigned	P3PER             : 3;
        unsigned	P3INTS            : 1;
    };
    struct {
        unsigned	                  : 1;
        unsigned	P3CKSRC0          : 1;
        unsigned	P3CKSRC1          : 1;
        unsigned	P3CKSRC2          : 1;
        unsigned	P3PER0            : 1;
        unsigned	P3PER1            : 1;
        unsigned	P3PER2            : 1;
    };
} PWM3CR0bits @ 0x010F;
#endif

// Register: PWM3CR1
volatile unsigned char           PWM3CR1       @ 0x0110;
// bit and bitfield definitions
volatile bit TMR3IF              @ ((unsigned)&PWM3CR1*8)+0;
volatile bit TMR3IE              @ ((unsigned)&PWM3CR1*8)+1;
volatile bit TMR3ON              @ ((unsigned)&PWM3CR1*8)+2;
volatile bit TMR3PS0             @ ((unsigned)&PWM3CR1*8)+3;
volatile bit TMR3PS1             @ ((unsigned)&PWM3CR1*8)+4;
volatile bit TMR3PS2             @ ((unsigned)&PWM3CR1*8)+5;
volatile bit P3POL               @ ((unsigned)&PWM3CR1*8)+6;
volatile bit P3EN                @ ((unsigned)&PWM3CR1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TMR3IF            : 1;
        unsigned	TMR3IE            : 1;
        unsigned	TMR3ON            : 1;
        unsigned	TMR3PS            : 3;
        unsigned	P3POL             : 1;
        unsigned	P3EN              : 1;
    };
    struct {
				unsigned	                  : 3;
        unsigned	TMR3PS0           : 1;
        unsigned	TMR3PS1           : 1;
        unsigned	TMR3PS2           : 1;
    };
} PWM3CR1bits @ 0x0110;
#endif

// Register: T3CKDIV
volatile unsigned char           T3CKDIV       @ 0x0111;
// bit and bitfield definitions


// Register: TMR4L
volatile unsigned char           TMR4L          @ 0x0112;
// bit and bitfield definitions

// Register: TMR4H
volatile unsigned char           TMR4H          @ 0x0113;
// bit and bitfield definitions
volatile bit PR4H0              @ ((unsigned)&TMR4H*8)+0;
volatile bit PR4H1              @ ((unsigned)&TMR4H*8)+1;
volatile bit PR4H2              @ ((unsigned)&TMR4H*8)+2;
volatile bit PR4H3              @ ((unsigned)&TMR4H*8)+3;
volatile bit TMR4H0             @ ((unsigned)&TMR4H*8)+4;
volatile bit TMR4H1             @ ((unsigned)&TMR4H*8)+5;
volatile bit TMR4H2             @ ((unsigned)&TMR4H*8)+6;
volatile bit TMR4H3             @ ((unsigned)&TMR4H*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PR4H                : 4;
        unsigned	TMR4H               : 4;
    };
    struct {
        unsigned	PR4H0             : 1;
        unsigned	PR4H1             : 1;
        unsigned	PR4H2             : 1;
        unsigned	PR4H3             : 1;
        unsigned	TMR4H0            : 1;
        unsigned	TMR4H1            : 1;
        unsigned	TMR4H2            : 1;
        unsigned	TMR4H3            : 1;
    };
} TMR4Hbits @ 0x0113;
#endif

// Register: PR4L
volatile unsigned char           PR4L          @ 0x0114;
// bit and bitfield definitions

// Register: PWM4CR0
volatile unsigned char           PWM4CR0       @ 0x0115;
// bit and bitfield definitions
volatile bit P4BZR              @ ((unsigned)&PWM4CR0*8)+0;
volatile bit P4CKSRC0           @ ((unsigned)&PWM4CR0*8)+1;
volatile bit P4CKSRC1           @ ((unsigned)&PWM4CR0*8)+2;
volatile bit P4CKSRC2           @ ((unsigned)&PWM4CR0*8)+3;
volatile bit P4PER0             @ ((unsigned)&PWM4CR0*8)+4;
volatile bit P4PER1             @ ((unsigned)&PWM4CR0*8)+5;
volatile bit P4PER2             @ ((unsigned)&PWM4CR0*8)+6;
volatile bit P4INTS             @ ((unsigned)&PWM4CR0*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	P4BZR             : 1;
        unsigned	P4CKSRC           : 3;
        unsigned	P4PER             : 3;
        unsigned	P4INTS            : 1;
    };
    struct {
        unsigned	                  : 1;
        unsigned	P4CKSRC0          : 1;
        unsigned	P4CKSRC1          : 1;
        unsigned	P4CKSRC2          : 1;
        unsigned	P4PER0            : 1;
        unsigned	P4PER1            : 1;
        unsigned	P4PER2            : 1;
    };
} PWM4CR0bits @ 0x0115;
#endif

// Register: PWM4CR1
volatile unsigned char           PWM4CR1       @ 0x0116;
// bit and bitfield definitions
volatile bit TMR4IF              @ ((unsigned)&PWM4CR1*8)+0;
volatile bit TMR4IE              @ ((unsigned)&PWM4CR1*8)+1;
volatile bit TMR4ON              @ ((unsigned)&PWM4CR1*8)+2;
volatile bit TMR4PS0             @ ((unsigned)&PWM4CR1*8)+3;
volatile bit TMR4PS1             @ ((unsigned)&PWM4CR1*8)+4;
volatile bit TMR4PS2             @ ((unsigned)&PWM4CR1*8)+5;
volatile bit P4POL               @ ((unsigned)&PWM4CR1*8)+6;
volatile bit P4EN                @ ((unsigned)&PWM4CR1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TMR4IF            : 1;
        unsigned	TMR4IE            : 1;
        unsigned	TMR4ON            : 1;
        unsigned	TMR4PS            : 3;
        unsigned	P4PER             : 1;
        unsigned	P4INTS            : 1;
    };
    struct {
        unsigned	         		    : 3;
        unsigned	TMR4PS0         : 1;
        unsigned	TMR4PS1         : 1;
        unsigned	TMR4PS2         : 1;
    };
} PWM4CR1bits @ 0x0116;
#endif

// Register: T4CKDIV
volatile unsigned char           T4CKDIV       @ 0x0117;
// bit and bitfield definitions

// Register: TMR5L
volatile unsigned char           TMR5L          @ 0x0118;
// bit and bitfield definitions

// Register: TMR5H
volatile unsigned char           TMR5H          @ 0x0119;
// bit and bitfield definitions
volatile bit PR5H0              @ ((unsigned)&TMR5H*8)+0;
volatile bit PR5H1              @ ((unsigned)&TMR5H*8)+1;
volatile bit PR5H2              @ ((unsigned)&TMR5H*8)+2;
volatile bit PR5H3              @ ((unsigned)&TMR5H*8)+3;
volatile bit TMR5H0             @ ((unsigned)&TMR5H*8)+4;
volatile bit TMR5H1             @ ((unsigned)&TMR5H*8)+5;
volatile bit TMR5H2             @ ((unsigned)&TMR5H*8)+6;
volatile bit TMR5H3             @ ((unsigned)&TMR5H*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PR5H                : 4;
        unsigned	TMR5H               : 4;
    };
    struct {
        unsigned	PR5H0             : 1;
        unsigned	PR5H1             : 1;
        unsigned	PR5H2             : 1;
        unsigned	PR5H3             : 1;
        unsigned	TMR5H0            : 1;
        unsigned	TMR5H1            : 1;
        unsigned	TMR5H2            : 1;
        unsigned	TMR5H3            : 1;
    };
} TMR5Hbits @ 0x0119;
#endif

// Register: PR5L
volatile unsigned char           PR5L          @ 0x011A;
// bit and bitfield definitions

// Register: PWM5CR0
volatile unsigned char           PWM5CR0       @ 0x011B;
// bit and bitfield definitions
volatile bit P5BZR              @ ((unsigned)&PWM5CR0*8)+0;
volatile bit P5CKSRC0           @ ((unsigned)&PWM5CR0*8)+1;
volatile bit P5CKSRC1           @ ((unsigned)&PWM5CR0*8)+2;
volatile bit P5CKSRC2           @ ((unsigned)&PWM5CR0*8)+3;
volatile bit P5PER0             @ ((unsigned)&PWM5CR0*8)+4;
volatile bit P5PER1             @ ((unsigned)&PWM5CR0*8)+5;
volatile bit P5PER2             @ ((unsigned)&PWM5CR0*8)+6;
volatile bit P5INTS             @ ((unsigned)&PWM5CR0*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	P5BZR             : 1;
        unsigned	P5CKSRC           : 3;
        unsigned	P5PER             : 3;
        unsigned	P5INTS            : 1;
    };
    struct {
        unsigned	                  : 1;
        unsigned	P5CKSRC0          : 1;
        unsigned	P5CKSRC1          : 1;
        unsigned	P5CKSRC2          : 1;
        unsigned	P5PER0            : 1;
        unsigned	P5PER1            : 1;
        unsigned	P5PER2            : 1;
    };
} PWM5CR0bits @ 0x011B;
#endif

// Register: PWM5CR1
volatile unsigned char           PWM5CR1       @ 0x011C;
// bit and bitfield definitions
volatile bit TMR5IF              @ ((unsigned)&PWM5CR1*8)+0;
volatile bit TMR5IE              @ ((unsigned)&PWM5CR1*8)+1;
volatile bit TMR5ON              @ ((unsigned)&PWM5CR1*8)+2;
volatile bit TMR5PS0             @ ((unsigned)&PWM5CR1*8)+3;
volatile bit TMR5PS1             @ ((unsigned)&PWM5CR1*8)+4;
volatile bit TMR5PS2             @ ((unsigned)&PWM5CR1*8)+5;
volatile bit P5POL               @ ((unsigned)&PWM5CR1*8)+6;
volatile bit P5EN                @ ((unsigned)&PWM5CR1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TMR5IF            : 1;
        unsigned	TMR5IE            : 1;
        unsigned	TMR5ON            : 1;
        unsigned	TMR5PS0           : 3;
        unsigned	P5POL             : 1;
        unsigned	P5EN              : 1;
    };
    struct {
        unsigned	                  : 3;
        unsigned	P5CKSRC0          : 1;
        unsigned	P5CKSRC1          : 1;
        unsigned	P5CKSRC2          : 1;
    };
} PWM5CR1bits @ 0x011C;
#endif

// Register: T5CKDIV
volatile unsigned char           T5CKDIV       @ 0x011D;
// bit and bitfield definitions

//conrad add
// Register: EPWMCR0
volatile unsigned char           EPWMCR0       @ 0x011E;
// bit and bitfield definitions
volatile bit P3IOE              @ ((unsigned)&EPWMCR0*8)+0;
volatile bit P4IOE              @ ((unsigned)&EPWMCR0*8)+1;
volatile bit P5IOE              @ ((unsigned)&EPWMCR0*8)+2;
volatile bit P6IOE              @ ((unsigned)&EPWMCR0*8)+3;
volatile bit PCKOE              @ ((unsigned)&EPWMCR0*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	P3IOE            : 1;
        unsigned	P4IOE            : 1;
        unsigned	P5IOE            : 1;
        unsigned	P6IOE            : 1;
        unsigned	                 : 3;
        unsigned	PCKOE            : 1;
    };
} EPWMCR0bits @ 0x011E;
#endif
//conrad add
// Register: CMCON4
volatile unsigned char           CMCON4       @ 0x011F;
// bit and bitfield definitions
volatile bit CMPON0              @ ((unsigned)&CMCON4*8)+0;
volatile bit CMPON1              @ ((unsigned)&CMCON4*8)+1;
volatile bit CMPON2              @ ((unsigned)&CMCON4*8)+2;
volatile bit CMPON3              @ ((unsigned)&CMCON4*8)+3;
volatile bit C1DEB               @ ((unsigned)&CMCON4*8)+5;
volatile bit C2DEB               @ ((unsigned)&CMCON4*8)+6;
volatile bit C3DEB               @ ((unsigned)&CMCON4*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	CMPON0            : 1;
        unsigned	CMPON1            : 1;
        unsigned	CMPON2            : 1;
        unsigned	CMPON3            : 1;
        unsigned	                  : 1;
        unsigned	C1DEB             : 1;
				unsigned	C2DEB             : 1;
				unsigned	C3DEB             : 1;
    };
    struct {
        unsigned	CMPON             : 4;
    };
} CMCON4bits @ 0x011F;
#endif
//bank3

//conrad add
// Register: DEBCR
volatile unsigned char           DEBCR       @ 0x0181;
// bit and bitfield definitions
volatile bit DEBDLY0               @ ((unsigned)&DEBCR*8)+0;
volatile bit DEBDLY1               @ ((unsigned)&DEBCR*8)+1;
volatile bit DEBDLY2               @ ((unsigned)&DEBCR*8)+2;
volatile bit DEBDLY3               @ ((unsigned)&DEBCR*8)+3;
volatile bit DEBDLY4               @ ((unsigned)&DEBCR*8)+4;
volatile bit DEBDLY5               @ ((unsigned)&DEBCR*8)+5;
volatile bit TRIGSRC               @ ((unsigned)&DEBCR*8)+6;
volatile bit OP0RS                 @ ((unsigned)&DEBCR*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	DEBDLY0            : 1;
        unsigned	DEBDLY1            : 1;
        unsigned	DEBDLY2            : 1;
        unsigned	DEBDLY3            : 1;
        unsigned	DEBDLY4            : 1;
        unsigned	DEBDLY5            : 1;
				unsigned	TRIGSRC            : 1;
				unsigned	OP0RS              : 1;
    };
    struct {
        unsigned	DEBDLY             : 6;
    };
} DEBCRbits @ 0x0181;
#endif

//conrad add
// Register: PPGCON1
volatile unsigned char           PPGCON1       @ 0x0188;
// bit and bitfield definitions
volatile bit PPGST               @ ((unsigned)&PPGCON1*8)+0;
volatile bit PSTPEN              @ ((unsigned)&PPGCON1*8)+2;
volatile bit PRSTEN              @ ((unsigned)&PPGCON1*8)+3;
volatile bit PRLSEL              @ ((unsigned)&PPGCON1*8)+4;
volatile bit PWLTEN              @ ((unsigned)&PPGCON1*8)+5;
volatile bit PTRIGM              @ ((unsigned)&PPGCON1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PPGST             : 1;
        unsigned	                  : 1;
        unsigned	PSTPEN            : 1;
        unsigned	PRSTEN            : 1;
        unsigned	PRLSEL            : 1;
        unsigned	PWLTEN            : 1;
				unsigned	                  : 1;
				unsigned	PTRIGM            : 1;
    };
} PPGCON1bits @ 0x0188;
#endif

//conrad add
// Register: PPRH
volatile unsigned char           PPRH       @ 0x0189;
// bit and bitfield definitions
volatile bit PPRA8              @ ((unsigned)&PPRH*8)+0;
volatile bit PPRB8              @ ((unsigned)&PPRH*8)+4;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PPRA8             : 1;
        unsigned	                  : 3;
        unsigned	PPRB8             : 1;
    };
} PPRHbits @ 0x0189;
#endif

// Register: PPRA
volatile unsigned char           PPRA       @ 0x018C;
// Register: PPRB
volatile unsigned char           PPRB       @ 0x018D;
// Register: PWLTPRL
volatile unsigned char           PWLTPRL       @ 0x018E;

//conrad add
// Register: PPGCON2
volatile unsigned char           PPGCON2       @ 0x018F;
// bit and bitfield definitions
volatile bit PPGDLY0              @ ((unsigned)&PPGCON2*8)+0;
volatile bit PPGDLY1              @ ((unsigned)&PPGCON2*8)+1;
volatile bit PPGDLY2              @ ((unsigned)&PPGCON2*8)+2;
volatile bit PPGDLY3              @ ((unsigned)&PPGCON2*8)+3;
volatile bit PPGDLY4              @ ((unsigned)&PPGCON2*8)+4;
volatile bit PPGDLY5              @ ((unsigned)&PPGCON2*8)+5;
volatile bit RELDB                @ ((unsigned)&PPGCON2*8)+6;
volatile bit PPGON                @ ((unsigned)&PPGCON2*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PPGDLY0                : 1;
        unsigned	PPGDLY1                : 1;
        unsigned	PPGDLY2                : 1;
        unsigned	PPGDLY3                : 1;
        unsigned	PPGDLY4            	   : 1;
        unsigned	PPGDLY5                : 1;
    };
    struct {
        unsigned	PPGDLY                 : 6;
				unsigned	RELDB                  : 1;
				unsigned	PPGON                  : 1;
    };
} PPGCON2bits @ 0x018F;
#endif

//conrad add
// Register: CMP0CR
volatile unsigned char           CMP0CR       @ 0x0190;
// bit and bitfield definitions
volatile bit C0COF0              @ ((unsigned)&CMP0CR*8)+0;
volatile bit C0COF1              @ ((unsigned)&CMP0CR*8)+1;
volatile bit C0COF2              @ ((unsigned)&CMP0CR*8)+2;
volatile bit C0COF3              @ ((unsigned)&CMP0CR*8)+3;
volatile bit C0COF4              @ ((unsigned)&CMP0CR*8)+4;
volatile bit C0CSEL              @ ((unsigned)&CMP0CR*8)+5;
volatile bit C0TM                @ ((unsigned)&CMP0CR*8)+6;
volatile bit C0OUT               @ ((unsigned)&CMP0CR*8)+7;
#ifndef _LIB_BUILD
volatile union {
	struct {
        unsigned	C0COF                 : 5;
        unsigned	C0CSEL                : 1;
				unsigned	C0TM                  : 1;
				unsigned	C0OUT                 : 1;
    };
    struct {
        unsigned	C0COF0                : 1;
        unsigned	C0COF1                : 1;
        unsigned	C0COF2                : 1;
        unsigned	C0COF3                : 1;
        unsigned	C0COF4            	  : 1;
    };
} CMP0CRbits @ 0x0190;
#endif
//conrad add
// Register: CMP1CR
volatile unsigned char           CMP1CR       @ 0x0191;
// bit and bitfield definitions
volatile bit C1COF0              @ ((unsigned)&CMP1CR*8)+0;
volatile bit C1COF1              @ ((unsigned)&CMP1CR*8)+1;
volatile bit C1COF2              @ ((unsigned)&CMP1CR*8)+2;
volatile bit C1COF3              @ ((unsigned)&CMP1CR*8)+3;
volatile bit C1COF4              @ ((unsigned)&CMP1CR*8)+4;
volatile bit C1CSEL              @ ((unsigned)&CMP1CR*8)+5;
volatile bit C1TM                @ ((unsigned)&CMP1CR*8)+6;
volatile bit C1OUT               @ ((unsigned)&CMP1CR*8)+7;
#ifndef _LIB_BUILD
volatile union {
	struct {
        unsigned	C1COF                 : 5;
        unsigned	C1CSEL                : 1;
				unsigned	C1TM                  : 1;
				unsigned	C1OUT                 : 1;
    };
    struct {
        unsigned	C1COF0                : 1;
        unsigned	C1COF1                : 1;
        unsigned	C1COF2                : 1;
        unsigned	C1COF3                : 1;
        unsigned	C1COF4            	  : 1;
    };
} CMP1CRbits @ 0x0191;
#endif

//conrad add
// Register: CMP2CR
volatile unsigned char           CMP2CR       @ 0x0192;
// bit and bitfield definitions
volatile bit C2COF0              @ ((unsigned)&CMP2CR*8)+0;
volatile bit C2COF1              @ ((unsigned)&CMP2CR*8)+1;
volatile bit C2COF2              @ ((unsigned)&CMP2CR*8)+2;
volatile bit C2COF3              @ ((unsigned)&CMP2CR*8)+3;
volatile bit C2COF4              @ ((unsigned)&CMP2CR*8)+4;
volatile bit C2CSEL              @ ((unsigned)&CMP2CR*8)+5;
volatile bit C2TM                @ ((unsigned)&CMP2CR*8)+6;
volatile bit C2OUT               @ ((unsigned)&CMP2CR*8)+7;
#ifndef _LIB_BUILD
volatile union {
	struct {
        unsigned	C2COF                 : 5;
        unsigned	C2CSEL                : 1;
				unsigned	C2TM                  : 1;
				unsigned	C2OUT                 : 1;
    };
    struct {
        unsigned	C2COF0                : 1;
        unsigned	C2COF1                : 1;
        unsigned	C2COF2                : 1;
        unsigned	C2COF3                : 1;
        unsigned	C2COF4            	  : 1;
    };
} CMP2CRbits @ 0x0192;
#endif

//conrad add
// Register: CMP3CR
volatile unsigned char           CMP3CR       @ 0x0193;
// bit and bitfield definitions
volatile bit C3COF0              @ ((unsigned)&CMP3CR*8)+0;
volatile bit C3COF1              @ ((unsigned)&CMP3CR*8)+1;
volatile bit C3COF2              @ ((unsigned)&CMP3CR*8)+2;
volatile bit C3COF3              @ ((unsigned)&CMP3CR*8)+3;
volatile bit C3COF4              @ ((unsigned)&CMP3CR*8)+4;
volatile bit C3CSEL              @ ((unsigned)&CMP3CR*8)+5;
volatile bit C3TM                @ ((unsigned)&CMP3CR*8)+6;
volatile bit C3OUT               @ ((unsigned)&CMP3CR*8)+7;
#ifndef _LIB_BUILD
volatile union {
	struct {
        unsigned	C3COF                 : 5;
        unsigned	C3CSEL                : 1;
				unsigned	C3TM                  : 1;
				unsigned	C3OUT                 : 1;
    };
    struct {
        unsigned	C3COF0                : 1;
        unsigned	C3COF1                : 1;
        unsigned	C3COF2                : 1;
        unsigned	C3COF3                : 1;
        unsigned	C3COF4            	  : 1;
    };
} CMP3CRbits @ 0x0193;
#endif

//conrad add
// Register: OP0CR0
volatile unsigned char           OP0CR0       @ 0x0194;
// bit and bitfield definitions
volatile bit OP0COF0              @ ((unsigned)&OP0CR0*8)+0;
volatile bit OP0COF1              @ ((unsigned)&OP0CR0*8)+1;
volatile bit OP0COF2              @ ((unsigned)&OP0CR0*8)+2;
volatile bit OP0COF3              @ ((unsigned)&OP0CR0*8)+3;
volatile bit OP0COF4              @ ((unsigned)&OP0CR0*8)+4;
volatile bit OP0TM                @ ((unsigned)&OP0CR0*8)+6;
volatile bit OP0OUT               @ ((unsigned)&OP0CR0*8)+7;
#ifndef _LIB_BUILD
volatile union {
	struct {
        unsigned	OP0COF                 : 5;
        unsigned	                       : 1;
				unsigned	OP0TM                  : 1;
				unsigned	OP0OUT                 : 1;
    };
    struct {
        unsigned	OP0COF0                : 1;
        unsigned	OP0COF1                : 1;
        unsigned	OP0COF2                : 1;
        unsigned	OP0COF3                : 1;
        unsigned	OP0COF4            	   : 1;
    };
} OP0CR0bits @ 0x0194;
#endif

//conrad add 
volatile unsigned char           TMR6L          @ 0x0198;
// bit and bitfield definitions
volatile unsigned char           TMR6H          @ 0x0199;
// bit and bitfield definitions
volatile bit PR6H0              @ ((unsigned)&TMR6H*8)+0;
volatile bit PR6H1              @ ((unsigned)&TMR6H*8)+1;
volatile bit PR6H2              @ ((unsigned)&TMR6H*8)+2;
volatile bit PR6H3              @ ((unsigned)&TMR6H*8)+3;
volatile bit TMR6H0             @ ((unsigned)&TMR6H*8)+4;
volatile bit TMR6H1             @ ((unsigned)&TMR6H*8)+5;
volatile bit TMR6H2             @ ((unsigned)&TMR6H*8)+6;
volatile bit TMR6H3             @ ((unsigned)&TMR6H*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PR6H             : 4;
        unsigned	TMR6H            : 4;

    };
    struct {
        unsigned	PR6H0           : 1;
        unsigned	PR6H1           : 1;
        unsigned	PR6H2           : 1;
        unsigned	PR6H3           : 1;
        unsigned	TMR6H0          : 1;
        unsigned	TMR6H1          : 1;
        unsigned	TMR6H2          : 1;
				unsigned	TMR6H3          : 1; 
    };
} TMR6Hbits @ 0x0199;
#endif
// Register: PR6L
volatile unsigned char           PR6L          @ 0x019A;
// bit and bitfield definitions

// Register: PWM6CR0
volatile unsigned char           PWM6CR0       @ 0x019B;
// bit and bitfield definitions
volatile bit P6BZR              @ ((unsigned)&PWM6CR0*8)+0;
volatile bit P6CKSRC0           @ ((unsigned)&PWM6CR0*8)+1;
volatile bit P6CKSRC1           @ ((unsigned)&PWM6CR0*8)+2;
volatile bit P6CKSRC2           @ ((unsigned)&PWM6CR0*8)+3;
volatile bit P6PER0             @ ((unsigned)&PWM6CR0*8)+4;
volatile bit P6PER1             @ ((unsigned)&PWM6CR0*8)+5;
volatile bit P6PER2             @ ((unsigned)&PWM6CR0*8)+6;
volatile bit P6INTS             @ ((unsigned)&PWM6CR0*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	P6BZR             : 1;
        unsigned	P6CKSRC           : 3;
        unsigned	P6PER             : 3;
        unsigned	P6INTS            : 1;
    };
    struct {
        unsigned	                  : 1;
        unsigned	P6CKSRC0          : 1;
        unsigned	P6CKSRC1          : 1;
        unsigned	P6CKSRC2          : 1;
        unsigned	P6PER0            : 1;
        unsigned	P6PER1            : 1;
        unsigned	P6PER2            : 1;
    };
} PWM6CR0bits @ 0x019B;
#endif

// Register: PWM6CR1
volatile unsigned char           PWM6CR1       @ 0x019C;
// bit and bitfield definitions
volatile bit TMR6IF              @ ((unsigned)&PWM6CR1*8)+0;
volatile bit TMR6IE              @ ((unsigned)&PWM6CR1*8)+1;
volatile bit TMR6ON              @ ((unsigned)&PWM6CR1*8)+2;
volatile bit TMR6PS0             @ ((unsigned)&PWM6CR1*8)+3;
volatile bit TMR6PS1             @ ((unsigned)&PWM6CR1*8)+4;
volatile bit TMR6PS2             @ ((unsigned)&PWM6CR1*8)+5;
volatile bit P6POL               @ ((unsigned)&PWM6CR1*8)+6;
volatile bit P6EN                @ ((unsigned)&PWM6CR1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TMR6IF            : 1;
        unsigned	TMR6IE            : 1;
        unsigned	TMR6ON            : 1;
        unsigned	TMR6PS            : 3;
        unsigned	P6POL             : 1;
        unsigned	P6EN              : 1;
    };
    struct {
        unsigned	         	      	: 3;
        unsigned	TMR6PS0           : 1;
        unsigned	TMR6PS1           : 1;
        unsigned	TMR6PS2           : 1;
    };
} PWM6CR1bits @ 0x019C;
#endif

// Register: T6CKDIV
volatile unsigned char           T6CKDIV       @ 0x019D;
// bit and bitfield definitions

// Register: PPGCON3
volatile unsigned char           PPGCON3       @ 0x019E;
// bit and bitfield definitions
volatile bit IOEB              @ ((unsigned)&PPGCON3*8)+0;
volatile bit PPGOEB            @ ((unsigned)&PPGCON3*8)+1;
volatile bit PPOL              @ ((unsigned)&PPGCON3*8)+2;
volatile bit PSYNC             @ ((unsigned)&PPGCON3*8)+3;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	IOEB             : 1;
        unsigned	PPGOEB           : 1;
        unsigned	PPOL             : 1;
        unsigned	PSYNC            : 1;
    };
} PPGCON3bits @ 0x019C;
#endif

//--------------------------------------------------------------------------by yangxu
volatile unsigned char           SFR00             @0x000;
volatile unsigned char           SFR01             @0x001;
volatile unsigned char           SFR02             @0x002;
volatile unsigned char           SFR03             @0x003;
volatile unsigned char           SFR04             @0x004;
volatile unsigned char           SFR05             @0x005;
volatile unsigned char           SFR06             @0x006;
volatile unsigned char           SFR07             @0x007;
volatile unsigned char           SFR08             @0x008;
volatile unsigned char           SFR09             @0x009;
volatile unsigned char           SFR0A             @0x00A;
volatile unsigned char           SFR0B             @0x00B;
volatile unsigned char           SFR0C             @0x00C;
volatile unsigned char           SFR0D             @0x00D;
volatile unsigned char           SFR0E             @0x00E;
volatile unsigned char           SFR0F             @0x00F;

volatile unsigned char           SFR10             @0x010;
volatile unsigned char           SFR11             @0x011;
volatile unsigned char           SFR12             @0x012;
volatile unsigned char           SFR13             @0x013;
volatile unsigned char           SFR14             @0x014;
volatile unsigned char           SFR15             @0x015;
volatile unsigned char           SFR16             @0x016;
volatile unsigned char           SFR17             @0x017;
volatile unsigned char           SFR18             @0x018;
volatile unsigned char           SFR19             @0x019;
volatile unsigned char           SFR1A             @0x01A;
volatile unsigned char           SFR1B             @0x01B;
volatile unsigned char           SFR1C             @0x01C;
volatile unsigned char           SFR1D             @0x01D;
volatile unsigned char           SFR1E             @0x01E;
volatile unsigned char           SFR1F             @0x01F;


volatile unsigned char           SFR80             @0x080;
volatile unsigned char           SFR81             @0x081;
volatile unsigned char           SFR82             @0x082;
volatile unsigned char           SFR83             @0x083;
volatile unsigned char           SFR84             @0x084;
volatile unsigned char           SFR85             @0x085;
volatile unsigned char           SFR86             @0x086;
volatile unsigned char           SFR87             @0x087;
volatile unsigned char           SFR88             @0x088;
volatile unsigned char           SFR89             @0x089;
volatile unsigned char           SFR8A             @0x08A;
volatile unsigned char           SFR8B             @0x08B;
volatile unsigned char           SFR8C             @0x08C;
volatile unsigned char           SFR8D             @0x08D;
volatile unsigned char           SFR8E             @0x08E;
volatile unsigned char           SFR8F             @0x08F;

volatile unsigned char           SFR90             @0x090;
volatile unsigned char           SFR91             @0x091;
volatile unsigned char           SFR92             @0x092;
volatile unsigned char           SFR93             @0x093;
volatile unsigned char           SFR94             @0x094;
volatile unsigned char           SFR95             @0x095;
volatile unsigned char           SFR96             @0x096;
volatile unsigned char           SFR97             @0x097;
volatile unsigned char           SFR98             @0x098;
volatile unsigned char           SFR99             @0x099;
volatile unsigned char           SFR9A             @0x09A;
volatile unsigned char           SFR9B             @0x09B;
volatile unsigned char           SFR9C             @0x09C;
volatile unsigned char           SFR9D             @0x09D;
volatile unsigned char           SFR9E             @0x09E;
volatile unsigned char           SFR9F             @0x09F;

volatile unsigned char           SFR100             @0x100;
volatile unsigned char           SFR101             @0x101;
volatile unsigned char           SFR102             @0x102;
volatile unsigned char           SFR103             @0x103;
volatile unsigned char           SFR104             @0x104;
volatile unsigned char           SFR105             @0x105;
volatile unsigned char           SFR106             @0x106;
volatile unsigned char           SFR107             @0x107;
volatile unsigned char           SFR108             @0x108;
volatile unsigned char           SFR109             @0x109;
volatile unsigned char           SFR10A             @0x10A;
volatile unsigned char           SFR10B             @0x10B;
volatile unsigned char           SFR10C             @0x10C;
volatile unsigned char           SFR10D             @0x10D;
volatile unsigned char           SFR10E             @0x10E;
volatile unsigned char           SFR10F             @0x10F;

volatile unsigned char           SFR110             @0x110;
volatile unsigned char           SFR111             @0x111;
volatile unsigned char           SFR112             @0x112;
volatile unsigned char           SFR113             @0x113;
volatile unsigned char           SFR114             @0x114;
volatile unsigned char           SFR115             @0x115;
volatile unsigned char           SFR116             @0x116;
volatile unsigned char           SFR117             @0x117;
volatile unsigned char           SFR118             @0x118;
volatile unsigned char           SFR119             @0x119;
volatile unsigned char           SFR11A             @0x11A;
volatile unsigned char           SFR11B             @0x11B;
volatile unsigned char           SFR11C             @0x11C;
volatile unsigned char           SFR11D             @0x11D;
volatile unsigned char           SFR11E             @0x11E;
volatile unsigned char           SFR11F             @0x11F;

volatile unsigned char           SFR180             @0x180;
volatile unsigned char           SFR181             @0x181;
volatile unsigned char           SFR182             @0x182;
volatile unsigned char           SFR183             @0x183;
volatile unsigned char           SFR184             @0x184;
volatile unsigned char           SFR185             @0x185;
volatile unsigned char           SFR186             @0x186;
volatile unsigned char           SFR187             @0x187;
volatile unsigned char           SFR188             @0x188;
volatile unsigned char           SFR189             @0x189;
volatile unsigned char           SFR18A             @0x18A;
volatile unsigned char           SFR18B             @0x18B;
volatile unsigned char           SFR18C             @0x18C;
volatile unsigned char           SFR18D             @0x18D;
volatile unsigned char           SFR18E             @0x18E;
volatile unsigned char           SFR18F             @0x18F;

volatile unsigned char           SFR190             @0x190;
volatile unsigned char           SFR191             @0x191;
volatile unsigned char           SFR192             @0x192;
volatile unsigned char           SFR193             @0x193;
volatile unsigned char           SFR194             @0x194;
volatile unsigned char           SFR195             @0x195;
volatile unsigned char           SFR196             @0x196;
volatile unsigned char           SFR197             @0x197;
volatile unsigned char           SFR198             @0x198;
volatile unsigned char           SFR199             @0x199;
volatile unsigned char           SFR19A             @0x19A;
volatile unsigned char           SFR19B             @0x19B;
volatile unsigned char           SFR19C             @0x19C;
volatile unsigned char           SFR19D             @0x19D;
volatile unsigned char           SFR19E             @0x19E;
volatile unsigned char           SFR19F             @0x19F;
//---------------------------------------------------------------------------


#endif
