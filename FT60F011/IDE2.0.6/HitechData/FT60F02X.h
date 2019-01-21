
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
volatile bit RP                  @ ((unsigned)&STATUS*8)+5;

volatile bit C               		 @ ((unsigned)&STATUS*8)+0;
volatile bit HC                  @ ((unsigned)&STATUS*8)+1;
volatile bit Z                	 @ ((unsigned)&STATUS*8)+2;
volatile bit nPF                 @ ((unsigned)&STATUS*8)+3;
volatile bit nTF                 @ ((unsigned)&STATUS*8)+4;
volatile bit PAGE                @ ((unsigned)&STATUS*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	CARRY               : 1;
        unsigned	DC                  : 1;
        unsigned	ZERO                : 1;
        unsigned	nPD                 : 1;
        unsigned	nTO                 : 1;
        unsigned	RP                  : 1;
    };
    struct {
        unsigned	C                   : 1;
        unsigned	HC                  : 1;
        unsigned	Z                   : 1;
        unsigned	nPF                 : 1;
        unsigned	nTF                 : 1;
        unsigned	PAGE                : 1;
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
        unsigned	PA0                 : 1;
        unsigned	PA1                 : 1;
        unsigned	PA2                 : 1;
        unsigned	PA3                 : 1;
        unsigned	PA4                 : 1;
        unsigned	PA5                 : 1;
        unsigned	PA6                 : 1;
        unsigned	PA7                 : 1;
    };
} PORTAbits @ 0x005;
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
volatile bit RC6                 @ ((unsigned)&PORTC*8)+6;
volatile bit RC7                 @ ((unsigned)&PORTC*8)+7;

volatile bit PC0                 @ ((unsigned)&PORTC*8)+0;
volatile bit PC1                 @ ((unsigned)&PORTC*8)+1;
volatile bit PC2                 @ ((unsigned)&PORTC*8)+2;
volatile bit PC3                 @ ((unsigned)&PORTC*8)+3;
volatile bit PC4                 @ ((unsigned)&PORTC*8)+4;
volatile bit PC5                 @ ((unsigned)&PORTC*8)+5;
volatile bit PC6                 @ ((unsigned)&PORTC*8)+6;
volatile bit PC7                 @ ((unsigned)&PORTC*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	RC0                 : 1;
        unsigned	RC1                 : 1;
        unsigned	RC2                 : 1;
        unsigned	RC3                 : 1;
        unsigned	RC4                 : 1;
        unsigned	RC5                 : 1;
        unsigned	RC6                 : 1;
        unsigned	RC7                 : 1;
    };
	struct {
        unsigned	PC0                 : 1;
        unsigned	PC1                 : 1;
        unsigned	PC2                 : 1;
        unsigned	PC3                 : 1;
        unsigned	PC4                 : 1;
        unsigned	PC5                 : 1;
        unsigned	PC6                 : 1;
        unsigned	PC7                 : 1;
    };
} PORTCbits @ 0x007;
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

// Register: PIR1
volatile unsigned char           PIR1                @ 0x00C;
// bit and bitfield definitions
volatile bit TMR2IF              @ ((unsigned)&PIR1*8)+1;
volatile bit OSFIF               @ ((unsigned)&PIR1*8)+2;
volatile bit C1IF                @ ((unsigned)&PIR1*8)+3;
volatile bit C2IF                @ ((unsigned)&PIR1*8)+4;
volatile bit CKMEAIF             @ ((unsigned)&PIR1*8)+6;
volatile bit EEIF                @ ((unsigned)&PIR1*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	              		: 1;
        unsigned	TMR2IF            : 1;
        unsigned	OSFIF     			  : 1;
        unsigned	C1IF              : 1;
        unsigned	C2IF       			  : 1;
        unsigned	                  : 1;
        unsigned	CKMEAIF           : 1;
        unsigned	EEIF              : 1;
    };
} PIR1bits @ 0x00C;
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
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T2CKPS              : 2;
        unsigned	TMR2ON              : 1;
        unsigned	TOUTPS              : 4;
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

// Register: CMCON0
volatile unsigned char           CMCON0             @ 0x019;
// bit and bitfield definitions
volatile bit CM0                  @ ((unsigned)&CMCON0*8)+0;
volatile bit CM1                  @ ((unsigned)&CMCON0*8)+1;
volatile bit CM2                  @ ((unsigned)&CMCON0*8)+2;
volatile bit CIS                  @ ((unsigned)&CMCON0*8)+3;
volatile bit C1INV                @ ((unsigned)&CMCON0*8)+4;
volatile bit C2INV                @ ((unsigned)&CMCON0*8)+5;
volatile bit C1OUT                @ ((unsigned)&CMCON0*8)+6;
volatile bit C2OUT                @ ((unsigned)&CMCON0*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	CM                 : 3;
        unsigned	CIS							   : 1;
        unsigned	C1INV              : 1;
        unsigned	C2INV              : 1;
        unsigned	C1OUT              : 1;
        unsigned	C2OUT              : 1;
    };
    struct {
        unsigned	CM0                : 1;
        unsigned	CM1                : 1;
        unsigned	CM2                : 1;
    };
} CMCON0bits @ 0x019;
#endif

// Register: PR0
volatile unsigned char           PR0             @ 0x01A;
// bit and bitfield definitions

// Register: MSCKCON
volatile unsigned char           MSCKCON         @ 0x01B;
// bit and bitfield definitions
volatile bit CKCNTI                   @ ((unsigned)&MSCKCON*8)+1;
volatile bit CKMAVG                   @ ((unsigned)&MSCKCON*8)+2;
volatile bit SLVREN                   @ ((unsigned)&MSCKCON*8)+4;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                     : 1;
        unsigned	CKCNTI               : 1;
        unsigned	CKMAVG               : 1;
        unsigned						           : 1;
        unsigned	SLVREN               : 1;
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

//
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
        unsigned	                    : 1;
        unsigned	TRISA6              : 1;
        unsigned	TRISA7              : 1;
    };
} TRISAbits @ 0x085;
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
volatile bit TRISC6              @ ((unsigned)&TRISC*8)+6;
volatile bit TRISC7              @ ((unsigned)&TRISC*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TRISC0              : 1;
        unsigned	TRISC1              : 1;
        unsigned	TRISC2              : 1;
        unsigned	TRISC3              : 1;
        unsigned	TRISC4              : 1;
        unsigned	TRISC5              : 1;
        unsigned	TRISC6              : 1;
        unsigned	TRISC7              : 1;
    };
    struct {
        unsigned	TRISC               : 8;
    };
} TRISCbits @ 0x087;
#endif

// Register: PIE1
volatile unsigned char           PIE1                @ 0x08C;
// bit and bitfield definitions
volatile bit TMR2IE              @ ((unsigned)&PIE1*8)+1;
volatile bit OSFIE             	 @ ((unsigned)&PIE1*8)+2;
volatile bit C1IE             	 @ ((unsigned)&PIE1*8)+3;
volatile bit C2IE             	 @ ((unsigned)&PIE1*8)+4;
volatile bit CKMEAIE             @ ((unsigned)&PIE1*8)+6;
volatile bit EEIE                @ ((unsigned)&PIE1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                    : 1;
        unsigned	TMR2IE              : 1;
        unsigned	OSFIE               : 1;
		    unsigned	C1IE                : 1;
        unsigned	C2IE                : 1;
		    unsigned	                    : 1;
        unsigned	CKMEAIE             : 1;
        unsigned	EEIE                : 1;
    };
} PIE1bits @ 0x08C;
#endif


// Register: PCON
volatile unsigned char           PCON                @ 0x08E;
// bit and bitfield definitions
volatile bit nBOR                @ ((unsigned)&PCON*8)+0;
volatile bit nPOR                @ ((unsigned)&PCON*8)+1;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	nBOR                : 1;
        unsigned	nPOR                : 1;
    };
} PCONbits @ 0x08E;
#endif

// Register: OSCCON
volatile unsigned char           OSCCON              @ 0x08F;
// bit and bitfield definitions
volatile bit SCS                	  @ ((unsigned)&OSCCON*8)+0;
volatile bit LTS                	  @ ((unsigned)&OSCCON*8)+1;
volatile bit HTS                 	  @ ((unsigned)&OSCCON*8)+2;
volatile bit OSTS                 	@ ((unsigned)&OSCCON*8)+3;
volatile bit IRCF0                  @ ((unsigned)&OSCCON*8)+4;
volatile bit IRCF1                  @ ((unsigned)&OSCCON*8)+5;
volatile bit IRCF2                  @ ((unsigned)&OSCCON*8)+6;
volatile bit LFMOD                  @ ((unsigned)&OSCCON*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
				unsigned	SCS                 : 1;
				unsigned	LTS                 : 1;
        unsigned	HTS                 : 1;
        unsigned	OSTS                : 1;
        unsigned	IRCF                : 3;
        unsigned	LFMOD               : 1;
    };
    struct {
        unsigned	                    : 4;
        unsigned	IRCF0               : 1;
        unsigned	IRCF1               : 1;
        unsigned	IRCF2               : 1;
				unsigned	                    : 1;
    };
} OSCCONbits @ 0x08F;
#endif

// Register: PR2
volatile unsigned char           PR2                 @ 0x092;
// bit and bitfield definitions

// Register: WPUA
volatile unsigned char           WPUA                @ 0x095;
volatile unsigned char           WPU                 @ 0x095;
// bit and bitfield definitions
volatile bit WPUA0               @ ((unsigned)&WPUA*8)+0;
volatile bit WPUA1               @ ((unsigned)&WPUA*8)+1;
volatile bit WPUA2               @ ((unsigned)&WPUA*8)+2;
volatile bit WPUA3               @ ((unsigned)&WPUA*8)+3;
volatile bit WPUA4               @ ((unsigned)&WPUA*8)+4;
volatile bit WPUA6               @ ((unsigned)&WPUA*8)+6;
volatile bit WPUA7               @ ((unsigned)&WPUA*8)+7;

volatile bit WPU0                @ ((unsigned)&WPUA*8)+0;
volatile bit WPU1                @ ((unsigned)&WPUA*8)+1;
volatile bit WPU2                @ ((unsigned)&WPUA*8)+2;
volatile bit WPU3                @ ((unsigned)&WPUA*8)+3;
volatile bit WPU4                @ ((unsigned)&WPUA*8)+4;
volatile bit WPU6                @ ((unsigned)&WPUA*8)+6;
volatile bit WPU7                @ ((unsigned)&WPUA*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	WPUA0               : 1;
        unsigned	WPUA1               : 1;
        unsigned	WPUA2               : 1;
        unsigned	WPUA3               : 1;
        unsigned	WPUA4               : 1;
        unsigned	                    : 1;
        unsigned	WPUA6               : 1;
        unsigned	WPUA7               : 1;
    };
    struct {
        unsigned	WPU0                : 1;
        unsigned	WPU1                : 1;
        unsigned	WPU2                : 1;
        unsigned	WPU3                : 1;
        unsigned	WPU4                : 1;
        unsigned	                    : 1;
        unsigned	WPU6                : 1;
        unsigned	WPU7                : 1;
    };
} WPUAbits @ 0x095;
#endif

// Register: IOCA
volatile unsigned char           IOCA                @ 0x096;
volatile unsigned char           IOC                 @ 0x096;
// bit and bitfield definitions
volatile bit IOCA0               @ ((unsigned)&IOCA*8)+0;
volatile bit IOCA1               @ ((unsigned)&IOCA*8)+1;
volatile bit IOCA2               @ ((unsigned)&IOCA*8)+2;
volatile bit IOCA3               @ ((unsigned)&IOCA*8)+3;
volatile bit IOCA4               @ ((unsigned)&IOCA*8)+4;
volatile bit IOCA5               @ ((unsigned)&IOCA*8)+5;
volatile bit IOCA6               @ ((unsigned)&IOCA*8)+6;
volatile bit IOCA7               @ ((unsigned)&IOCA*8)+7;

volatile bit IOC0                @ ((unsigned)&IOCA*8)+0;
volatile bit IOC1                @ ((unsigned)&IOCA*8)+1;
volatile bit IOC2                @ ((unsigned)&IOCA*8)+2;
volatile bit IOC3                @ ((unsigned)&IOCA*8)+3;
volatile bit IOC4                @ ((unsigned)&IOCA*8)+4;
volatile bit IOC5                @ ((unsigned)&IOCA*8)+5;
volatile bit IOC6                @ ((unsigned)&IOCA*8)+6;
volatile bit IOC7                @ ((unsigned)&IOCA*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	IOCA               : 8;
    };
    struct {
        unsigned	IOC                : 8;
    };
} IOCAbits @ 0x096;
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
//---------------------------------------------------------------------------
#endif
