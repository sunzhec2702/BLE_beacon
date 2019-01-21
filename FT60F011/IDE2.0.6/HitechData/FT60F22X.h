
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
    		unsigned        							:1;
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
        unsigned	RA                  : 8;
    };
    struct {
        unsigned	PA                  : 8;
    };
} PORTAbits @ 0x005;
#endif

// Register: PORTB
volatile unsigned char           PORTB               @ 0x006;
// bit and bitfield definitions
volatile bit RB0                 @ ((unsigned)&PORTB*8)+0;
volatile bit RB1                 @ ((unsigned)&PORTB*8)+1;
volatile bit RB2                 @ ((unsigned)&PORTB*8)+2;
volatile bit RB3                 @ ((unsigned)&PORTB*8)+3;
volatile bit RB4                 @ ((unsigned)&PORTB*8)+4;
volatile bit RB5                 @ ((unsigned)&PORTB*8)+5;
volatile bit RB6                 @ ((unsigned)&PORTB*8)+6;
volatile bit RB7                 @ ((unsigned)&PORTB*8)+7;

volatile bit PB0                 @ ((unsigned)&PORTB*8)+0;
volatile bit PB1                 @ ((unsigned)&PORTB*8)+1;
volatile bit PB2                 @ ((unsigned)&PORTB*8)+2;
volatile bit PB3                 @ ((unsigned)&PORTB*8)+3;
volatile bit PB4                 @ ((unsigned)&PORTB*8)+4;
volatile bit PB5                 @ ((unsigned)&PORTB*8)+5;
volatile bit PB6                 @ ((unsigned)&PORTB*8)+6;
volatile bit PB7                 @ ((unsigned)&PORTB*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	RB0                 : 1;
        unsigned	RB1                 : 1;
        unsigned	RB2                 : 1;
        unsigned	RB3                 : 1;
        unsigned	RB4                 : 1;
        unsigned	RB5                 : 1;
        unsigned	RB6                 : 1;
        unsigned	RB7                 : 1;
    };
	struct {
        unsigned	PB0                 : 1;
        unsigned	PB1                 : 1;
        unsigned	PB2                 : 1;
        unsigned	PB3                 : 1;
        unsigned	PB4                 : 1;
        unsigned	PB5                 : 1;
        unsigned	PB6                 : 1;
        unsigned	PB7                 : 1;
    };
    struct {
        unsigned	RB                  : 8;
    };
    struct {
        unsigned	PB                  : 8;
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
    struct {
        unsigned	RC                  : 8;
    };
    struct {
        unsigned	PC                  : 8;
    };
} PORTCbits @ 0x007;
#endif

// Register: PORTD
volatile unsigned char           PORTD               @ 0x008;
// bit and bitfield definitions
volatile bit RD0                 @ ((unsigned)&PORTD*8)+0;
volatile bit RD1                 @ ((unsigned)&PORTD*8)+1;

volatile bit PD0                 @ ((unsigned)&PORTD*8)+0;
volatile bit PD1                 @ ((unsigned)&PORTD*8)+1;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	RD0                 : 1;
        unsigned	RD1                 : 1;
    };
	
	struct {
        unsigned	PD0                 : 1;
        unsigned	PD1                 : 1;
    };
    struct {
        unsigned	RD                  : 2;
    };
    struct {
        unsigned	PD                  : 2;
    };
} PORTDbits @ 0x008;
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
volatile bit TMR1IF              @ ((unsigned)&PIR1*8)+0;
volatile bit TMR2IF              @ ((unsigned)&PIR1*8)+1;
volatile bit OSFIF               @ ((unsigned)&PIR1*8)+2;
volatile bit C0IF                @ ((unsigned)&PIR1*8)+3;
volatile bit I2CIF               @ ((unsigned)&PIR1*8)+4;
volatile bit LVDIF               @ ((unsigned)&PIR1*8)+5;
volatile bit CKMEAIF             @ ((unsigned)&PIR1*8)+6;
volatile bit EEIF                @ ((unsigned)&PIR1*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TMR1IF        			: 1;
        unsigned	TMR2IF              : 1;
        unsigned	OSFIF         			: 1;
        unsigned	C0IF          			: 1;
        unsigned	I2CIF          			: 1;
        unsigned	LVDIF               : 1;
        unsigned	CKMEAIF             : 1;
        unsigned	EEIF                : 1;
    };
} PIR1bits @ 0x00C;
#endif


// Register: TMR1L
volatile unsigned char           TMR1L              @ 0x00E;
// bit and bitfield definitions

// Register: TMR1H
volatile unsigned char           TMR1H              @ 0x00F;
// bit and bitfield definitions

// Register: T1CON
volatile unsigned char           T1CON              @ 0x010;
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
        unsigned	TMR1ON        			: 1;
        unsigned	TMR1CS              : 1;
        unsigned	T1SYNC              : 1;
        unsigned	T1OSCEN             : 1;
        unsigned	T1CKPS              : 2;
        unsigned	TMR1GE              : 1;
        unsigned	T1GINV              : 1;
    };
    struct {
        unsigned	                   : 4;
        unsigned	T1CKPS0            : 1;
        unsigned	T1CKPS1            : 1;
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
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T2CKPS              : 2;
        unsigned	                    : 1;
        unsigned	TOUTPS              : 4;
    };
    struct {
        unsigned	T2CKPS0             : 1;
        unsigned	T2CKPS1             : 1;
        unsigned	TMR2ON              : 1;
        unsigned	TOUTPS0             : 1;
        unsigned	TOUTPS1             : 1;
        unsigned	TOUTPS2             : 1;
        unsigned	TOUTPS3             : 1;
    };
} T2CONbits @ 0x012;
#endif
// bit and bitfield definitions

// Register: CMP0CR0
volatile unsigned char           CMP0CR0               @ 0x015;
// bit and bitfield definitions
volatile bit C0COF0              @ ((unsigned)&CMP0CR0*8)+0;
volatile bit C0COF1              @ ((unsigned)&CMP0CR0*8)+1;
volatile bit C0COF2              @ ((unsigned)&CMP0CR0*8)+2;
volatile bit C0COF3              @ ((unsigned)&CMP0CR0*8)+3;
volatile bit C0COF4              @ ((unsigned)&CMP0CR0*8)+4;
volatile bit C0CSEL              @ ((unsigned)&CMP0CR0*8)+5;
volatile bit C0TM                @ ((unsigned)&CMP0CR0*8)+6;
volatile bit C0OUT               @ ((unsigned)&CMP0CR0*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	C0COF               : 5;
    };
    struct {
        unsigned	C0COF0              : 1;
        unsigned	C0COF1              : 1;
        unsigned	C0COF2              : 1;
        unsigned	C0COF3              : 1;
        unsigned	C0COF4              : 1;
        unsigned	C0CSEL              : 1;
        unsigned	C0TM                : 1;
        unsigned	C0OUT               : 1;
    };
} CMP0CR0bits @ 0x015;
#endif
// bit and bitfield definitions

// Register: CMP0CR1
volatile unsigned char           CMP0CR1               @ 0x016;
// bit and bitfield definitions
volatile bit C0ON                 @ ((unsigned)&CMP0CR1*8)+0;
volatile bit C0OE                 @ ((unsigned)&CMP0CR1*8)+1;
volatile bit C0HYSEN              @ ((unsigned)&CMP0CR1*8)+2;
volatile bit C0DEB                @ ((unsigned)&CMP0CR1*8)+3;
volatile bit C0POL                @ ((unsigned)&CMP0CR1*8)+4;
volatile bit C0PSEL               @ ((unsigned)&CMP0CR1*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	C0ON                : 1;
        unsigned	C0OE                : 1;
        unsigned	C0HYSEN             : 1;
        unsigned	C0DEB               : 1;
        unsigned	C0POL               : 1;
        unsigned	C0PSEL              : 1;
    };
} CMP0CR1bits @ 0x016;
#endif
// bit and bitfield definitions

// Register: RSTCON
volatile unsigned char           RSTCON             @ 0x017;
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
volatile unsigned char           MISC0             @ 0x019;
// bit and bitfield definitions
volatile bit INTEDG0              @ ((unsigned)&MISC0*8)+0;
volatile bit INTEDG1              @ ((unsigned)&MISC0*8)+1;
volatile bit IRMOD                @ ((unsigned)&MISC0*8)+2;
volatile bit REMDAT               @ ((unsigned)&MISC0*8)+3;
volatile bit I2CEN                @ ((unsigned)&MISC0*8)+4;
volatile bit SWRSTF               @ ((unsigned)&MISC0*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	INTEDG             : 2;
        unsigned	IRMOD						   : 1;
        unsigned	REMDAT             : 1;
        unsigned	I2CEN              : 1;
        unsigned	                   : 1;
        unsigned	                   : 1;
        unsigned	SWRSTF             : 1;
    };
    struct {
        unsigned	INTEDG0            : 1;
        unsigned	INTEDG1            : 1;
    };
} MISC0bits @ 0x019;
#endif

// Register: PR0
volatile unsigned char           LEDDRV             @ 0x01A;
// bit and bitfield definitions

// Register: MSCKCON
volatile unsigned char           MSCKCON         @ 0x01B;
// bit and bitfield definitions
volatile bit CKCNTI                   @ ((unsigned)&MSCKCON*8)+1;
volatile bit CKMAVG                   @ ((unsigned)&MSCKCON*8)+2;
volatile bit SLVREN                   @ ((unsigned)&MSCKCON*8)+4;
volatile bit T2CKSRC                  @ ((unsigned)&MSCKCON*8)+5;
//volatile bit LVROE                    @ ((unsigned)&MSCKCON*8)+6;
//volatile bit BGRBOE                   @ ((unsigned)&MSCKCON*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                     : 1;
        unsigned	CKCNTI               : 1;
        unsigned	CKMAVG               : 1;
        unsigned	                     : 1;
        unsigned	SLVREN               : 1;
        unsigned	T2CKSRC						   : 1;
       // unsigned	LVROE                : 1;
       // unsigned	BGRBE                : 1;
    };
} MSCKCONbits @ 0x01B;
#endif

// Register: SOSCPRL
volatile unsigned char           SOSCPRL             @ 0x01C;
// bit and bitfield definitions

// Register: SOSCPRH
volatile unsigned char           SOSCPRH              @ 0x01D;
// bit and bitfield definitions
volatile bit SOSCPRH0              @ ((unsigned)&SOSCPRH*8)+0;
volatile bit SOSCPRH1              @ ((unsigned)&SOSCPRH*8)+1;
volatile bit SOSCPRH2              @ ((unsigned)&SOSCPRH*8)+2;
volatile bit SOSCPRH3              @ ((unsigned)&SOSCPRH*8)+3;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	SOSCPRH            : 4;
    };
    struct {
        unsigned	SOSCPRH0           : 1;
        unsigned	SOSCPRH1           : 1;
        unsigned	SOSCPRH2           : 1;
        unsigned	SOSCPRH3           : 1;
    };
} SOSCPRHbits @ 0x01D;
#endif

//-----------------------------------------------------------------
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
volatile bit nPAPU               @ ((unsigned)&OPTION*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PS                  : 3;
        unsigned	PSA                 : 1;
        unsigned	T0SE                : 1;
        unsigned	T0CS                : 1;
        unsigned	                    : 1;
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
        unsigned	TRISA               : 8;
    };
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
} TRISAbits @ 0x085;
#endif


// Register: TRISB
volatile unsigned char           TRISB               @ 0x086;
// bit and bitfield definitions
volatile bit TRISB0              @ ((unsigned)&TRISB*8)+0;
volatile bit TRISB1              @ ((unsigned)&TRISB*8)+1;
volatile bit TRISB2              @ ((unsigned)&TRISB*8)+2;
volatile bit TRISB3              @ ((unsigned)&TRISB*8)+3;
volatile bit TRISB4              @ ((unsigned)&TRISB*8)+4;
volatile bit TRISB5              @ ((unsigned)&TRISB*8)+5;
volatile bit TRISB6              @ ((unsigned)&TRISB*8)+6;
volatile bit TRISB7              @ ((unsigned)&TRISB*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TRISB               : 8;
    };
    struct {
        unsigned	TRISB0              : 1;
        unsigned	TRISB1              : 1;
        unsigned	TRISB2              : 1;
        unsigned	TRISB3              : 1;
        unsigned	TRISB4              : 1;
        unsigned	TRISB5              : 1;
        unsigned	TRISB6              : 1;
        unsigned	TRISB7              : 1;
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
volatile bit TRISC6              @ ((unsigned)&TRISC*8)+6;
volatile bit TRISC7              @ ((unsigned)&TRISC*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TRISC               : 8;
    };
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
} TRISCbits @ 0x087;
#endif

// Register: TRISD
volatile unsigned char           TRISD               @ 0x088;
// bit and bitfield definitions
volatile bit TRISD0              @ ((unsigned)&TRISD*8)+0;
volatile bit TRISD1              @ ((unsigned)&TRISD*8)+1;
#ifndef _LIB_TRISDD
volatile union {
    struct {
        unsigned	TRISD              : 2;
    };
    struct {
        unsigned	TRISD0             : 1;
        unsigned	TRISD1             : 1;
    };
} TRISDbits @ 0x088;
#endif


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

// Register: PIE1
volatile unsigned char           PIE1                @ 0x08C;
// bit and bitfield definitions
volatile bit TMR1IE              @ ((unsigned)&PIE1*8)+0;
volatile bit TMR2IE              @ ((unsigned)&PIE1*8)+1;
volatile bit OSFIE               @ ((unsigned)&PIE1*8)+2;
volatile bit C0IE                @ ((unsigned)&PIE1*8)+3;
volatile bit I2CIE               @ ((unsigned)&PIE1*8)+4;
volatile bit LVDIE               @ ((unsigned)&PIE1*8)+5;
volatile bit CKMEAIE             @ ((unsigned)&PIE1*8)+6;
volatile bit EEIE                @ ((unsigned)&PIE1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TMR1IE              : 1;
        unsigned	TMR2IE              : 1;
        unsigned	OSFIE               : 1;
        unsigned	C0IE                : 1;
        unsigned	IC2IE               : 1;
        unsigned	LVDIE	              : 1;
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
volatile bit LFMOD                 @ ((unsigned)&OSCCON*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	SCS                    : 1;
        unsigned	LTS                    : 1;
        unsigned	HTS                    : 1;
        unsigned	OSTS                   : 1;
        unsigned	IRCF                	 : 3;
        unsigned	LFMOD                  : 1;
    };
    struct {
        unsigned	                    : 4;
        unsigned	IRCF0               : 1;
        unsigned	IRCF1               : 1;
        unsigned	IRCF2               : 1;
    };
} OSCCONbits @ 0x08F;
#endif


// Register: ANSEL
volatile unsigned char           ANSEL0              @ 0x091;
// bit and bitfield definitions

// Register: PR2
volatile unsigned char           PR2                 @ 0x092;
// bit and bitfield definitions

// Register: WPUD
volatile unsigned char           WPUD                @ 0x093;
// bit and bitfield definitions
volatile bit WPUD0               @ ((unsigned)&WPUD*8)+0;
volatile bit WPUD1               @ ((unsigned)&WPUD*8)+1;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	WPUD               : 2;
    };
} WPUDbits @ 0x093;
#endif
// Register: WPUB
volatile unsigned char           WPUB                @ 0x094;
// bit and bitfield definitions
volatile bit WPUB0               @ ((unsigned)&WPUB*8)+0;
volatile bit WPUB1               @ ((unsigned)&WPUB*8)+1;
volatile bit WPUB2               @ ((unsigned)&WPUB*8)+2;
volatile bit WPUB3               @ ((unsigned)&WPUB*8)+3;
volatile bit WPUB4               @ ((unsigned)&WPUB*8)+4;
volatile bit WPUB5               @ ((unsigned)&WPUB*8)+5;
volatile bit WPUB6               @ ((unsigned)&WPUB*8)+6;
volatile bit WPUB7               @ ((unsigned)&WPUB*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	WPUB               : 8;
    };
} WPUBbits @ 0x094;
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

// Register: IOCA
volatile unsigned char           IOCA                @ 0x096;
volatile unsigned char           IOFA                @ 0x096;
// bit and bitfield definitions
volatile bit IOCA0               @ ((unsigned)&IOCA*8)+0;
volatile bit IOCA1               @ ((unsigned)&IOCA*8)+1;
volatile bit IOCA2               @ ((unsigned)&IOCA*8)+2;
volatile bit IOCA3               @ ((unsigned)&IOCA*8)+3;
volatile bit IOCA4               @ ((unsigned)&IOCA*8)+4;
volatile bit IOCA5               @ ((unsigned)&IOCA*8)+5;
volatile bit IOCA6               @ ((unsigned)&IOCA*8)+6;
volatile bit IOCA7               @ ((unsigned)&IOCA*8)+7;

volatile bit IOFA0               @ ((unsigned)&IOFA*8)+0;
volatile bit IOFA1               @ ((unsigned)&IOFA*8)+1;
volatile bit IOFA2               @ ((unsigned)&IOFA*8)+2;
volatile bit IOFA3               @ ((unsigned)&IOFA*8)+3;
volatile bit IOFA4               @ ((unsigned)&IOFA*8)+4;
volatile bit IOFA5               @ ((unsigned)&IOFA*8)+5;
volatile bit IOFA6               @ ((unsigned)&IOFA*8)+6;
volatile bit IOFA7               @ ((unsigned)&IOFA*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	IOCA               : 8;
    };
    struct {
        unsigned	IOFA               : 8;
    };
} IOCAbits @ 0x096;
#endif

// Register: WPUC
volatile unsigned char           WPUC                @ 0x097;
// bit and bitfield definitions
volatile bit WPUC0               @ ((unsigned)&WPUC*8)+0;
volatile bit WPUC1               @ ((unsigned)&WPUC*8)+1;
volatile bit WPUC2               @ ((unsigned)&WPUC*8)+2;
volatile bit WPUC3               @ ((unsigned)&WPUC*8)+3;
volatile bit WPUC4               @ ((unsigned)&WPUC*8)+4;
volatile bit WPUC5               @ ((unsigned)&WPUC*8)+5;
volatile bit WPUC6               @ ((unsigned)&WPUC*8)+6;
volatile bit WPUC7               @ ((unsigned)&WPUC*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	WPUC               : 8;
    };
} WPUCbits @ 0x097;
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
volatile bit WRLVD               @ ((unsigned)&EECON1*8)+6;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	RD                  : 1;
        unsigned	                    : 1;
        unsigned	WREN1               : 1;
        unsigned	WRERR               : 1;
        unsigned	WREN2               : 1;
        unsigned	WREN3               : 1;
        unsigned	WRLVD               : 1;
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


// Register: CS0CON
volatile unsigned char           CS0CON             @ 0x0C0;
// bit and bitfield definitions
volatile bit SCIE              @ ((unsigned)&CS0CON*8)+0;
volatile bit CMPIE             @ ((unsigned)&CS0CON*8)+1;
volatile bit EOSIE             @ ((unsigned)&CS0CON*8)+2;
volatile bit CHBUFE            @ ((unsigned)&CS0CON*8)+5;
volatile bit CS0STR            @ ((unsigned)&CS0CON*8)+6;
volatile bit CS0EN             @ ((unsigned)&CS0CON*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	SCIE                : 1;
        unsigned	CMPIE               : 1;
        unsigned	EOSIE               : 1;
        unsigned	                    : 2;
        unsigned	CHBUFE              : 1;
        unsigned	CS0STR              : 1;
        unsigned	CS0EN               : 1;
    };
} CS0CONbits @ 0x0C0;
#endif

// Register: CS0STAT
volatile unsigned char           CS0STAT             @ 0x0C1;
// bit and bitfield definitions
volatile bit MULTRES             @ ((unsigned)&CS0STAT*8)+0;
volatile bit CS0BUSY             @ ((unsigned)&CS0STAT*8)+1;
volatile bit CS0INTF             @ ((unsigned)&CS0STAT*8)+5;
volatile bit EOSIF               @ ((unsigned)&CS0STAT*8)+6;
volatile bit CS0CMPF             @ ((unsigned)&CS0STAT*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	MULTRES               : 1;
        unsigned	CS0BUSY               : 1;
        unsigned	               			  : 3;
        unsigned	CS0INTF               : 1;
        unsigned	EOSIF                 : 1;
        unsigned	CS0CMPF               : 1;
    };
} CS0STATbits @ 0x0C1;
#endif

// Register: CS0CF
volatile unsigned char           CS0CF             @ 0x0C2;
// bit and bitfield definitions
volatile bit MULTPOL             @ ((unsigned)&CS0CF*8)+0;
volatile bit CS0ACU0             @ ((unsigned)&CS0CF*8)+1;
volatile bit CS0ACU1             @ ((unsigned)&CS0CF*8)+2;
volatile bit CS0ACU2             @ ((unsigned)&CS0CF*8)+3;
volatile bit CS0CR0              @ ((unsigned)&CS0CF*8)+4;
volatile bit CS0CR1              @ ((unsigned)&CS0CF*8)+5;
volatile bit CS0MCEN             @ ((unsigned)&CS0CF*8)+6;
volatile bit CS0CMPE             @ ((unsigned)&CS0CF*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	MULTRES               : 1;
        unsigned	CS0ACU                : 3;
        unsigned	CS0CR          			  : 2;
        unsigned	CS0MCEN               : 1;
        unsigned	CS0CMPE               : 1;
    };
    struct {
        unsigned	                      : 1;
        unsigned	CS0ACU0               : 1;
        unsigned	CS0ACU1               : 1;
        unsigned	CS0ACU2               : 1;
        unsigned	CS0CR0         			  : 1;
        unsigned	CS0CR1         			  : 1;
    };
} CS0CFbits @ 0x0C2;
#endif

// Register: CS0SCAN
volatile unsigned char           CS0SCAN             @ 0x0C3;
// bit and bitfield definitions
volatile bit MASCAN             @ ((unsigned)&CS0SCAN*8)+6;
volatile bit AUSCAN             @ ((unsigned)&CS0SCAN*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                      : 6;
        unsigned	MASCAN                : 1;
        unsigned	AUSCAN          		  : 1;
    };
} CS0SCANbits @ 0x0C3;
#endif

// Register: CS0MX
volatile unsigned char           CS0MX             @ 0x0C5;
// bit and bitfield definitions
volatile bit CS0MX0             @ ((unsigned)&CS0MX*8)+0;
volatile bit CSOMX1             @ ((unsigned)&CS0MX*8)+1;
volatile bit CSOMX2             @ ((unsigned)&CS0MX*8)+2;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	CS0MX0                : 1;
        unsigned	CS0MX1          		  : 1;
        unsigned	CS0MX2          		  : 1;
    };
} CS0MXbits @ 0x0C5;
#endif

// Register: CHRES0
volatile unsigned char           CHRES0             @ 0x0C9;
// bit and bitfield definitions

// Register: IOMASK0
volatile unsigned char           IOMASK0            @ 0x0CD;
// bit and bitfield definitions

// Register: AUTMRH
volatile unsigned char           AUTMRH            @ 0x0CE;
volatile unsigned char           CAPTMPH           @ 0x0CE;
// bit and bitfield definitions

// Register: AUTMRL
volatile unsigned char           AUTMRL            @ 0x0CF;
volatile unsigned char           CAPTMPL           @ 0x0CF;
// bit and bitfield definitions

// Register: PINMON0
volatile unsigned char           PINMON0           @ 0x0D0;
// bit and bitfield definitions
volatile bit PMONEN8             @ ((unsigned)&PINMON0*8)+0;
volatile bit PMONEN9             @ ((unsigned)&PINMON0*8)+1;
volatile bit PMONEN10            @ ((unsigned)&PINMON0*8)+2;
volatile bit PMONEN11            @ ((unsigned)&PINMON0*8)+3;
volatile bit PMONEN12            @ ((unsigned)&PINMON0*8)+4;
volatile bit PMONEN13            @ ((unsigned)&PINMON0*8)+5;
volatile bit CS0PEVT             @ ((unsigned)&PINMON0*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PMONEN8               : 1;
        unsigned	PMONEN9               : 1;
        unsigned	PMONEN10              : 1;
        unsigned	PMONEN11              : 1;
        unsigned	PMONEN12              : 1;
        unsigned	PMONEN13              : 1;
        unsigned	          		        : 1;
        unsigned	CS0PEVT          		  : 1;
    };
} PINMON0bits @ 0x0D0;
#endif

// Register: CS0ADJ0
volatile unsigned char           CS0ADJ0           @ 0x0D1;
// bit and bitfield definitions
volatile bit DTMX0               @ ((unsigned)&CS0ADJ0*8)+0;
volatile bit DTMX1               @ ((unsigned)&CS0ADJ0*8)+1;
volatile bit DTMX2               @ ((unsigned)&CS0ADJ0*8)+2;
volatile bit CGMX0               @ ((unsigned)&CS0ADJ0*8)+3;
volatile bit CGMX1               @ ((unsigned)&CS0ADJ0*8)+4;
volatile bit CGMX2               @ ((unsigned)&CS0ADJ0*8)+5;
volatile bit DRMX0               @ ((unsigned)&CS0ADJ0*8)+6;
volatile bit DRMX1               @ ((unsigned)&CS0ADJ0*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	DTMX                  : 3;
        unsigned	CGMX      		        : 3;
        unsigned	DRMX             		  : 2;
    };
    struct {
        unsigned	DTMX0                  : 1;
        unsigned	DTMX1                  : 1;
        unsigned	DTMX2                  : 1;
        unsigned	CGMX0      		         : 1;
        unsigned	CGMX1      		         : 1;
        unsigned	CGMX2     		         : 1;
        unsigned	DRMX0             		 : 1;
        unsigned	DRMX1             		 : 1;
    };
} CS0ADJ0bits @ 0x0D1;
#endif

// Register: CS0ADJ1
volatile unsigned char           CS0ADJ1           @ 0x0D2;
// bit and bitfield definitions
volatile bit DTMULT0               @ ((unsigned)&CS0ADJ1*8)+0;
volatile bit DTMULT1               @ ((unsigned)&CS0ADJ1*8)+1;
volatile bit DTMULT2               @ ((unsigned)&CS0ADJ1*8)+2;
volatile bit CGMULT0               @ ((unsigned)&CS0ADJ1*8)+3;
volatile bit CGMULT1               @ ((unsigned)&CS0ADJ1*8)+4;
volatile bit CGMULT2               @ ((unsigned)&CS0ADJ1*8)+5;
volatile bit DRMULT1               @ ((unsigned)&CS0ADJ1*8)+6;
volatile bit DRMULT0               @ ((unsigned)&CS0ADJ1*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	DTMULT                  : 3;
        unsigned	CGMULT     		          : 3;
        unsigned	DRMULT             		  : 2;
    };
    struct {
        unsigned	DTMULT0                 : 1;
        unsigned	DTMULT1                 : 1;
        unsigned	DTMULT2                 : 1;
        unsigned	CGMULT0    		          : 1;
        unsigned	CGMULT1    		          : 1;
        unsigned	CGMULT2    		          : 1;
        unsigned	DRMULT0            		  : 1;
        unsigned	DRMULT1            		  : 1;
    };
} CS0ADJ1bits @ 0x0D2;
#endif


// Register: CS0ADJ2
volatile unsigned char           CS0ADJ2           @ 0x0D3;
// bit and bitfield definitions
volatile bit CS0LP0               @ ((unsigned)&CS0ADJ2*8)+0;
volatile bit CS0LP1               @ ((unsigned)&CS0ADJ2*8)+1;
volatile bit CS0LP2               @ ((unsigned)&CS0ADJ2*8)+2;
volatile bit CS0RP0               @ ((unsigned)&CS0ADJ2*8)+3;
volatile bit CS0RP1               @ ((unsigned)&CS0ADJ2*8)+4;
volatile bit CS0IA0               @ ((unsigned)&CS0ADJ2*8)+5;
volatile bit CS0IA1               @ ((unsigned)&CS0ADJ2*8)+6;
volatile bit CS0IA2               @ ((unsigned)&CS0ADJ2*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	CS0LP                   : 3;
        unsigned	CS0RP             		  : 2;
        unsigned	CS0IA     		          : 3;
    };
    struct {
        unsigned	CS0LP0                  : 1;
        unsigned	CS0LP1                  : 1;
        unsigned	CS0LP2                  : 1;
        unsigned	CS0RP0    		          : 1;
        unsigned	CS0RP1    		          : 1;
        unsigned	CS0IA0    		          : 1;
        unsigned	CS0IA1            		  : 1;
        unsigned	CS0IA2            		  : 1;
    };
} CS0ADJ2bits @ 0x0D3;
#endif


// Register: CHPOL0
volatile unsigned char           CHPOL0            @ 0x0D7;
// bit and bitfield definitions

// Register: CS0THCF0
volatile unsigned char          CS0THCF0           @ 0x0D8;
// bit and bitfield definitions
volatile bit ACCRST               @ ((unsigned)&CS0THCF0*8)+4;
volatile bit UFORCE               @ ((unsigned)&CS0THCF0*8)+5;
volatile bit THUMOD               @ ((unsigned)&CS0THCF0*8)+6;
volatile bit UPDEN                @ ((unsigned)&CS0THCF0*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                        : 4;
        unsigned	ACCRST                  : 1;
        unsigned	UFORCE                  : 1;
        unsigned	THUMOD                  : 1;
        unsigned	UPDEN     		          : 1;
    };
} CS0THCF0bits @ 0x0D8;
#endif


// Register: CS0THCF1
volatile unsigned char          CS0THCF1           @ 0x0D9;
// bit and bitfield definitions
volatile bit DEADSC0                @ ((unsigned)&CS0THCF1*8)+0;
volatile bit DEADSC1                @ ((unsigned)&CS0THCF1*8)+1;
volatile bit DEADSC2                @ ((unsigned)&CS0THCF1*8)+2;
volatile bit DEADSC3                @ ((unsigned)&CS0THCF1*8)+3;
volatile bit THGAP0                 @ ((unsigned)&CS0THCF1*8)+4;
volatile bit THGAP1                 @ ((unsigned)&CS0THCF1*8)+5;
volatile bit THGAP2                 @ ((unsigned)&CS0THCF1*8)+6;
volatile bit THGAP3                 @ ((unsigned)&CS0THCF1*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	DEADSC                  : 4;
        unsigned	THGAP                   : 4;
    };
    struct {
        unsigned	DEADSC0                 : 1;
        unsigned	DEADSC1                 : 1;
        unsigned	DEADSC2                 : 1;
        unsigned	DEADSC3                 : 1;
        unsigned	THGAP0                  : 1;
        unsigned	THGAP1                  : 1;
        unsigned	THGAP2                  : 1;
        unsigned	THGAP3                  : 1;
    };
} CS0THCF1bits @ 0x0D9;
#endif

// Register: CS0TEST
volatile unsigned char          CS0TEST           @ 0x0DA;
// bit and bitfield definitions
volatile bit PORDIR                @ ((unsigned)&CS0TEST*8)+0;
volatile bit CSST0                 @ ((unsigned)&CS0TEST*8)+1;
volatile bit CSST1                 @ ((unsigned)&CS0TEST*8)+2;
volatile bit CSST2                 @ ((unsigned)&CS0TEST*8)+3;
volatile bit CSST3                 @ ((unsigned)&CS0TEST*8)+4;
volatile bit CSST4                 @ ((unsigned)&CS0TEST*8)+5;
volatile bit TESTM0                @ ((unsigned)&CS0TEST*8)+6;
volatile bit TESTM1                @ ((unsigned)&CS0TEST*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                        : 1;
        unsigned	CSST                    : 5;
        unsigned	TESTM                   : 2;
    };
    struct {
        unsigned	PORDIR                  : 1;
        unsigned	CSST0                   : 1;
        unsigned	CSST1                   : 1;
        unsigned	CSST2                   : 1;
        unsigned	CSST3                   : 1;
        unsigned	CSST4                   : 1;
        unsigned	TESTM0                  : 1;
        unsigned	TESTM1                  : 1;
    };
} CS0TESTbits @ 0x0DA;
#endif

// Register: PMONEN
volatile unsigned char          PINMON1           @ 0x0DB;
// bit and bitfield definitions

// Register: PMONEN
volatile unsigned char          CS0RSTC           @ 0x0DC;

// bit and bitfield definitions
// Special function register definitions: Bank 2

// Register: TMR3L
volatile unsigned char           TMR3L          @ 0x010C;
// bit and bitfield definitions

// Register: TMR3H
volatile unsigned char           PR3H          @ 0x010D;
// bit and bitfield definitions
volatile bit PR3H0              @ ((unsigned)&PR3H*8)+0;
volatile bit PR3H1              @ ((unsigned)&PR3H*8)+1;
volatile bit PR3H2              @ ((unsigned)&PR3H*8)+2;
volatile bit PR3H3              @ ((unsigned)&PR3H*8)+3;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PR3H                : 4;
    };
    struct {
        unsigned	PR3H0             : 1;
        unsigned	PR3H1             : 1;
        unsigned	PR3H2             : 1;
        unsigned	PR3H3             : 1;
    };
} PR3Hbits @ 0x010D;
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
        unsigned	                  : 1;
        unsigned	P3CKSRC           : 3;
        unsigned	P3PER             : 3;
    };
    struct {
        unsigned	P3BZR             : 1;
        unsigned	P3CKSRC0          : 1;
        unsigned	P3CKSRC1          : 1;
        unsigned	P3CKSRC2          : 1;
        unsigned	P3PER0            : 1;
        unsigned	P3PER1            : 1;
        unsigned	P3PER2            : 1;
        unsigned	P3INTS            : 1;
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
        unsigned	                  : 3;
        unsigned	TMR3PS            : 3;
    };
    struct {
        unsigned	TMR3IF            : 1;
        unsigned	TMR3IE            : 1;
        unsigned	TMR3ON            : 1;
        unsigned	TMR3PS0           : 1;
        unsigned	TMR3PS1           : 1;
        unsigned	TMR3PS2           : 1;
        unsigned	P3PER             : 1;
        unsigned	P3INTS            : 1;
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
volatile unsigned char           PR4H          @ 0x0113;
// bit and bitfield definitions
volatile bit PR4H0              @ ((unsigned)&PR4H*8)+0;
volatile bit PR4H1              @ ((unsigned)&PR4H*8)+1;
volatile bit PR4H2              @ ((unsigned)&PR4H*8)+2;
volatile bit PR4H3              @ ((unsigned)&PR4H*8)+3;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PR4H                : 4;
    };
    struct {
        unsigned	PR4H0             : 1;
        unsigned	PR4H1             : 1;
        unsigned	PR4H2             : 1;
        unsigned	PR4H3             : 1;
    };
} PR4Hbits @ 0x0113;
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
        unsigned	                  : 1;
        unsigned	P4CKSRC           : 3;
        unsigned	P4PER             : 3;
    };
    struct {
        unsigned	P4BZR             : 1;
        unsigned	P4CKSRC0          : 1;
        unsigned	P4CKSRC1          : 1;
        unsigned	P4CKSRC2          : 1;
        unsigned	P4PER0            : 1;
        unsigned	P4PER1            : 1;
        unsigned	P4PER2            : 1;
        unsigned	P4INTS            : 1;
        	
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
        unsigned	                  : 1;
        unsigned	                  : 1;
        unsigned	                  : 1;
        unsigned	TMR4PS            : 3;
    };
    struct {
        unsigned	TMR4IF            : 1;
        unsigned	TMR4IE            : 1;
        unsigned	TMR4ON            : 1;
        unsigned	TMR4PS0           : 1;
        unsigned	TMR4PS1           : 1;
        unsigned	TMR4PS2           : 1;
        unsigned	P4POL             : 1;
        unsigned	P4EN              : 1;
    };
} PWM4CR1bits @ 0x0116;
#endif

// Register: T4CKDIV
volatile unsigned char           T4CKDIV       @ 0x0117;
// bit and bitfield definitions

// Register: TMR3H
volatile unsigned char           TMR3H          @ 0x0118;
// bit and bitfield definitions
volatile bit TMR3H0              @ ((unsigned)&TMR3H*8)+0;
volatile bit TMR3H1              @ ((unsigned)&TMR3H*8)+1;
volatile bit TMR3H2              @ ((unsigned)&TMR3H*8)+2;
volatile bit TMR3H3              @ ((unsigned)&TMR3H*8)+3;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TMR3H                : 4;
    };
    struct {
        unsigned	TMR3H0             : 1;
        unsigned	TMR3H1             : 1;
        unsigned	TMR3H2             : 1;
        unsigned	TMR3H3             : 1;
    };
} TMR3Hbits @ 0x0118;
#endif
// bit and bitfield definitions

// Register: TMR4H
volatile unsigned char           TMR4H          @ 0x0119;
// bit and bitfield definitions
volatile bit TMR4H0              @ ((unsigned)&TMR4H*8)+0;
volatile bit TMR4H1              @ ((unsigned)&TMR4H*8)+1;
volatile bit TMR4H2              @ ((unsigned)&TMR4H*8)+2;
volatile bit TMR4H3              @ ((unsigned)&TMR4H*8)+3;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TMR4H                : 4;
    };
    struct {
        unsigned	TMR4H0             : 1;
        unsigned	TMR4H1             : 1;
        unsigned	TMR4H2             : 1;
        unsigned	TMR4H3             : 1;
    };
} TMR4Hbits @ 0x0119;
#endif

// Register: I2CSTAT
volatile unsigned char           I2CSTAT          @ 0x011A;
// bit and bitfield definitions
volatile bit I2CBUSY               @ ((unsigned)&I2CSTAT*8)+0;
volatile bit I2CTXM                @ ((unsigned)&I2CSTAT*8)+1;
volatile bit I2CTXACK              @ ((unsigned)&I2CSTAT*8)+2;
volatile bit I2CRXACK              @ ((unsigned)&I2CSTAT*8)+3;
volatile bit I2CRW                 @ ((unsigned)&I2CSTAT*8)+4;
volatile bit I2CMATF               @ ((unsigned)&I2CSTAT*8)+6;
volatile bit I2CDF                 @ ((unsigned)&I2CSTAT*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	I2CBUSY              : 1;
        unsigned	I2CTXM               : 1;
        unsigned	I2CTXACK             : 1;
        unsigned	I2CRXACK             : 1;
        unsigned	I2CRW                : 1;
        unsigned	                     : 1;
        unsigned	I2CMATF              : 1;
        unsigned	I2CDF                : 1;
    };
} I2CSTATbits @ 0x011A;
#endif

// Register: I2CSLA
volatile unsigned char           I2CSLA       @ 0x011B;
// bit and bitfield definitions
volatile bit DMY0                @ ((unsigned)&I2CSLA*8)+0;
volatile bit I2CSLA0             @ ((unsigned)&I2CSLA*8)+1;
volatile bit I2CSLA1             @ ((unsigned)&I2CSLA*8)+2;
volatile bit I2CSLA2             @ ((unsigned)&I2CSLA*8)+3;
volatile bit I2CSLA3             @ ((unsigned)&I2CSLA*8)+4;
volatile bit I2CSLA4             @ ((unsigned)&I2CSLA*8)+5;
volatile bit I2CSLA5             @ ((unsigned)&I2CSLA*8)+6;
volatile bit I2CSLA6             @ ((unsigned)&I2CSLA*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	DMY0              : 1;
        unsigned	I2CSLA            : 7;
    };
    struct {
        unsigned	DMY0              : 1;
        unsigned	I2CSLA0           : 1;
        unsigned	I2CSLA1           : 1;
        unsigned	I2CSLA2           : 1;
        unsigned	I2CSLA3           : 1;
        unsigned	I2CSLA4           : 1;
        unsigned	I2CSLA5           : 1;
        unsigned	I2CSLA6           : 1;
        	
    };
} I2CSLAbits @ 0x011B;
#endif

// Register: I2CDAT
volatile unsigned char           I2CDAT       @ 0x011C;
volatile unsigned char           I2CDATA      @ 0x011C;
// bit and bitfield definitions

// Register: T5CKDIV
volatile unsigned char           I2CMTC       @ 0x011D;
// bit and bitfield definitions
volatile bit I2CTOV                @ ((unsigned)&I2CMTC*8)+6;
volatile bit I2CMEN                @ ((unsigned)&I2CMTC*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                  : 5;
        unsigned	I2CTOV            : 1;
        unsigned	I2CMEN            : 1;
    };
  }I2CMTCbits @0x011D;
#endif

// Register: EPWMCR0
volatile unsigned char           EPWMCR0       @ 0x011E;
// bit and bitfield definitions
volatile bit P3IOE                @ ((unsigned)&I2CMTC*8)+0;
volatile bit P4IOE                @ ((unsigned)&I2CMTC*8)+1;
volatile bit P3FCKS               @ ((unsigned)&I2CMTC*8)+4;
volatile bit P4FCKS               @ ((unsigned)&I2CMTC*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	P3IOE            : 1;
        unsigned	P4IOE            : 1;
        unsigned	                 : 1;
        unsigned	                 : 1;
        unsigned	P3FCKS           : 1;
        unsigned	P4FCKS           : 1;
    };
  }EPWMCR0bits @0x011E;
#endif
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

volatile unsigned char           SFRC0             @0x0C0;
volatile unsigned char           SFRC1             @0x0C1;
volatile unsigned char           SFRC2             @0x0C2;
volatile unsigned char           SFRC3             @0x0C3;
volatile unsigned char           SFRC4             @0x0C4;
volatile unsigned char           SFRC5             @0x0C5;
volatile unsigned char           SFRC6             @0x0C6;
volatile unsigned char           SFRC7             @0x0C7;
volatile unsigned char           SFRC8             @0x0C8;
volatile unsigned char           SFRC9             @0x0C9;
volatile unsigned char           SFRCA             @0x0CA;
volatile unsigned char           SFRCB             @0x0CB;
volatile unsigned char           SFRCC             @0x0CC;
volatile unsigned char           SFRCD             @0x0CD;
volatile unsigned char           SFRCE             @0x0CE;
volatile unsigned char           SFRCF             @0x0CF;

volatile unsigned char           SFRD0             @0x0D0;
volatile unsigned char           SFRD1             @0x0D1;
volatile unsigned char           SFRD2             @0x0D2;
volatile unsigned char           SFRD3             @0x0D3;
volatile unsigned char           SFRD4             @0x0D4;
volatile unsigned char           SFRD5             @0x0D5;
volatile unsigned char           SFRD6             @0x0D6;
volatile unsigned char           SFRD7             @0x0D7;
volatile unsigned char           SFRD8             @0x0D8;
volatile unsigned char           SFRD9             @0x0D9;
volatile unsigned char           SFRDA             @0x0DA;
volatile unsigned char           SFRDB             @0x0DB;
volatile unsigned char           SFRDC             @0x0DC;
volatile unsigned char           SFRDD             @0x0DD;
volatile unsigned char           SFRDE             @0x0DE;
volatile unsigned char           SFRDF             @0x0DF;

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
//---------------------------------------------------------------------------
//#endif  
