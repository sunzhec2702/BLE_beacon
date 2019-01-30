opt subtitle "HI-TECH Software Omniscient Code Generator (Lite mode) build 10920"

opt pagewidth 120

	opt lm

	processor	16F684
clrc	macro
	bcf	3,0
	endm
clrz	macro
	bcf	3,2
	endm
setc	macro
	bsf	3,0
	endm
setz	macro
	bsf	3,2
	endm
skipc	macro
	btfss	3,0
	endm
skipz	macro
	btfss	3,2
	endm
skipnc	macro
	btfsc	3,0
	endm
skipnz	macro
	btfsc	3,2
	endm
indf	equ	0
indf0	equ	0
pc	equ	2
pcl	equ	2
status	equ	3
fsr	equ	4
fsr0	equ	4
c	equ	1
z	equ	0
pclath	equ	10
	FNCALL	_main,_POWER_INITIAL
	FNCALL	_main,_WDT_INITIAL
	FNCALL	_main,_DelayS
	FNCALL	_main,_DelayMs
	FNCALL	_DelayS,_DelayMs
	FNCALL	_DelayMs,_DelayUs
	FNROOT	_main
	FNCALL	intlevel1,_ISR
	global	intlevel1
	FNROOT	intlevel1
	global	_FSR
<<<<<<< HEAD
psect	text107,local,class=CODE,delta=2
global __ptext107
__ptext107:
=======
psect	text70,local,class=CODE,delta=2
global __ptext70
__ptext70:
>>>>>>> bc517fe... Test on board. No issue is seen so far.
_FSR	set	4
	DABS	1,4,1	;_FSR

	global	_INDF
_INDF	set	0
	DABS	1,0,1	;_INDF

	global	_PCL
_PCL	set	2
	DABS	1,2,1	;_PCL

	global	_PCLATH
_PCLATH	set	10
	DABS	1,10,1	;_PCLATH

	global	_PORTA
_PORTA	set	5
	DABS	1,5,1	;_PORTA

	global	_SFR06
_SFR06	set	6
	DABS	1,6,1	;_SFR06

	global	_SFR07
_SFR07	set	7
	DABS	1,7,1	;_SFR07

	global	_SFR08
_SFR08	set	8
	DABS	1,8,1	;_SFR08

	global	_SFR09
_SFR09	set	9
	DABS	1,9,1	;_SFR09

	global	_STATUS
_STATUS	set	3
	DABS	1,3,1	;_STATUS

	global	_TMR0
_TMR0	set	1
	DABS	1,1,1	;_TMR0

	global	_CCPR1
_CCPR1	set	19
	DABS	1,19,2	;_CCPR1

	global	_TMR1
_TMR1	set	14
	DABS	1,14,2	;_TMR1

	global	_ADCON0
_ADCON0	set	31
	DABS	1,31,1	;_ADCON0

	global	_ADRESH
_ADRESH	set	30
	DABS	1,30,1	;_ADRESH

	global	_CCP1CON
_CCP1CON	set	21
	DABS	1,21,1	;_CCP1CON

	global	_CCPR1H
_CCPR1H	set	20
	DABS	1,20,1	;_CCPR1H

	global	_CCPR1L
_CCPR1L	set	19
	DABS	1,19,1	;_CCPR1L

	global	_CMCON0
_CMCON0	set	25
	DABS	1,25,1	;_CMCON0

	global	_CMCON1
_CMCON1	set	26
	DABS	1,26,1	;_CMCON1

	global	_ECCPAS
_ECCPAS	set	23
	DABS	1,23,1	;_ECCPAS

	global	_INTCONbits
_INTCONbits	set	11
	DABS	1,11,1	;_INTCONbits

	global	_MSCKCONbits
_MSCKCONbits	set	27
	DABS	1,27,1	;_MSCKCONbits

	global	_PCLATHbits
_PCLATHbits	set	10
	DABS	1,10,1	;_PCLATHbits

	global	_PIR1bits
_PIR1bits	set	12
	DABS	1,12,1	;_PIR1bits

	global	_PORTAbits
_PORTAbits	set	5
	DABS	1,5,1	;_PORTAbits

	global	_PORTC
_PORTC	set	7
	DABS	1,7,1	;_PORTC

	global	_PWM1CON
_PWM1CON	set	22
	DABS	1,22,1	;_PWM1CON

	global	_SFR00
_SFR00	set	0
	DABS	1,0,1	;_SFR00

	global	_SFR01
_SFR01	set	1
	DABS	1,1,1	;_SFR01

	global	_SFR02
_SFR02	set	2
	DABS	1,2,1	;_SFR02

	global	_SFR03
_SFR03	set	3
	DABS	1,3,1	;_SFR03

	global	_SFR04
_SFR04	set	4
	DABS	1,4,1	;_SFR04

	global	_SFR05
_SFR05	set	5
	DABS	1,5,1	;_SFR05

	global	_SFR0A
_SFR0A	set	10
	DABS	1,10,1	;_SFR0A

	global	_SFR0B
_SFR0B	set	11
	DABS	1,11,1	;_SFR0B

	global	_SFR0C
_SFR0C	set	12
	DABS	1,12,1	;_SFR0C

	global	_SFR11
_SFR11	set	17
	DABS	1,17,1	;_SFR11

	global	_SFR12
_SFR12	set	18
	DABS	1,18,1	;_SFR12

	global	_SFR18
_SFR18	set	24
	DABS	1,24,1	;_SFR18

	global	_SFR1B
_SFR1B	set	27
	DABS	1,27,1	;_SFR1B

	global	_SFR1C
_SFR1C	set	28
	DABS	1,28,1	;_SFR1C

	global	_SFR1D
_SFR1D	set	29
	DABS	1,29,1	;_SFR1D

	global	_SOSCPRHbits
_SOSCPRHbits	set	29
	DABS	1,29,1	;_SOSCPRHbits

	global	_STATUSbits
_STATUSbits	set	3
	DABS	1,3,1	;_STATUSbits

	global	_T1CON
_T1CON	set	16
	DABS	1,16,1	;_T1CON

	global	_T2CONbits
_T2CONbits	set	18
	DABS	1,18,1	;_T2CONbits

	global	_TMR1H
_TMR1H	set	15
	DABS	1,15,1	;_TMR1H

	global	_TMR1L
_TMR1L	set	14
	DABS	1,14,1	;_TMR1L

	global	_WDTCONbits
_WDTCONbits	set	24
	DABS	1,24,1	;_WDTCONbits

	global	_ADFM
_ADFM	set	255
	DABS	1,31,1	;_ADFM

	global	_ADIF
_ADIF	set	102
	DABS	1,12,1	;_ADIF

	global	_ADON
_ADON	set	248
	DABS	1,31,1	;_ADON

	global	_C
_C	set	24
	DABS	1,3,1	;_C

	global	_C1IF
_C1IF	set	99
	DABS	1,12,1	;_C1IF

	global	_C1INV
_C1INV	set	204
	DABS	1,25,1	;_C1INV

	global	_C1OUT
_C1OUT	set	206
	DABS	1,25,1	;_C1OUT

	global	_C2IF
_C2IF	set	100
	DABS	1,12,1	;_C2IF

	global	_C2INV
_C2INV	set	205
	DABS	1,25,1	;_C2INV

	global	_C2OUT
_C2OUT	set	207
	DABS	1,25,1	;_C2OUT

	global	_C2SYNC
_C2SYNC	set	208
	DABS	1,26,1	;_C2SYNC

	global	_CARRY
_CARRY	set	24
	DABS	1,3,1	;_CARRY

	global	_CCP1IF
_CCP1IF	set	101
	DABS	1,12,1	;_CCP1IF

	global	_CCP1M0
_CCP1M0	set	168
	DABS	1,21,1	;_CCP1M0

	global	_CCP1M1
_CCP1M1	set	169
	DABS	1,21,1	;_CCP1M1

	global	_CCP1M2
_CCP1M2	set	170
	DABS	1,21,1	;_CCP1M2

	global	_CCP1M3
_CCP1M3	set	171
	DABS	1,21,1	;_CCP1M3

	global	_CHS0
_CHS0	set	250
	DABS	1,31,1	;_CHS0

	global	_CHS1
_CHS1	set	251
	DABS	1,31,1	;_CHS1

	global	_CHS2
_CHS2	set	252
	DABS	1,31,1	;_CHS2

	global	_CIS
_CIS	set	203
	DABS	1,25,1	;_CIS

	global	_CKCNTI
_CKCNTI	set	217
	DABS	1,27,1	;_CKCNTI

	global	_CKMAVG
_CKMAVG	set	218
	DABS	1,27,1	;_CKMAVG

	global	_CKMEAIF
_CKMEAIF	set	102
	DABS	1,12,1	;_CKMEAIF

	global	_CM0
_CM0	set	200
	DABS	1,25,1	;_CM0

	global	_CM1
_CM1	set	201
	DABS	1,25,1	;_CM1

	global	_CM2
_CM2	set	202
	DABS	1,25,1	;_CM2

	global	_DC
_DC	set	25
	DABS	1,3,1	;_DC

	global	_DC1B0
_DC1B0	set	172
	DABS	1,21,1	;_DC1B0

	global	_DC1B1
_DC1B1	set	173
	DABS	1,21,1	;_DC1B1

	global	_ECCPAS0
_ECCPAS0	set	188
	DABS	1,23,1	;_ECCPAS0

	global	_ECCPAS1
_ECCPAS1	set	189
	DABS	1,23,1	;_ECCPAS1

	global	_ECCPAS2
_ECCPAS2	set	190
	DABS	1,23,1	;_ECCPAS2

	global	_ECCPASE
_ECCPASE	set	191
	DABS	1,23,1	;_ECCPASE

	global	_ECCPIF
_ECCPIF	set	101
	DABS	1,12,1	;_ECCPIF

	global	_EEIF
_EEIF	set	103
	DABS	1,12,1	;_EEIF

	global	_GIE
_GIE	set	95
	DABS	1,11,1	;_GIE

	global	_GO
_GO	set	249
	DABS	1,31,1	;_GO

	global	_GO_DONE
_GO_DONE	set	249
	DABS	1,31,1	;_GO_DONE

	global	_GO_nDONE
_GO_nDONE	set	249
	DABS	1,31,1	;_GO_nDONE

	global	_HC
_HC	set	25
	DABS	1,3,1	;_HC

	global	_INTE
_INTE	set	92
	DABS	1,11,1	;_INTE

	global	_INTF
_INTF	set	89
	DABS	1,11,1	;_INTF

	global	_IRP
_IRP	set	31
	DABS	1,3,1	;_IRP

	global	_OSFIF
_OSFIF	set	98
	DABS	1,12,1	;_OSFIF

	global	_P1M0
_P1M0	set	174
	DABS	1,21,1	;_P1M0

	global	_P1M1
_P1M1	set	175
	DABS	1,21,1	;_P1M1

	global	_PA0
_PA0	set	40
	DABS	1,5,1	;_PA0

	global	_PA1
_PA1	set	41
	DABS	1,5,1	;_PA1

	global	_PA2
_PA2	set	42
	DABS	1,5,1	;_PA2

	global	_PA3
_PA3	set	43
	DABS	1,5,1	;_PA3

	global	_PA4
_PA4	set	44
	DABS	1,5,1	;_PA4

	global	_PA5
_PA5	set	45
	DABS	1,5,1	;_PA5

	global	_PAGE
_PAGE	set	29
	DABS	1,3,1	;_PAGE

	global	_PAIE
_PAIE	set	91
	DABS	1,11,1	;_PAIE

	global	_PAIF
_PAIF	set	88
	DABS	1,11,1	;_PAIF

	global	_PDC0
_PDC0	set	176
	DABS	1,22,1	;_PDC0

	global	_PDC1
_PDC1	set	177
	DABS	1,22,1	;_PDC1

	global	_PDC2
_PDC2	set	178
	DABS	1,22,1	;_PDC2

	global	_PDC3
_PDC3	set	179
	DABS	1,22,1	;_PDC3

	global	_PDC4
_PDC4	set	180
	DABS	1,22,1	;_PDC4

	global	_PDC5
_PDC5	set	181
	DABS	1,22,1	;_PDC5

	global	_PDC6
_PDC6	set	182
	DABS	1,22,1	;_PDC6

	global	_PEIE
_PEIE	set	94
	DABS	1,11,1	;_PEIE

	global	_PRSEN
_PRSEN	set	183
	DABS	1,22,1	;_PRSEN

	global	_PSSAC0
_PSSAC0	set	186
	DABS	1,23,1	;_PSSAC0

	global	_PSSAC1
_PSSAC1	set	187
	DABS	1,23,1	;_PSSAC1

	global	_PSSBD0
_PSSBD0	set	184
	DABS	1,23,1	;_PSSBD0

	global	_PSSBD1
_PSSBD1	set	185
	DABS	1,23,1	;_PSSBD1

	global	_RA0
_RA0	set	40
	DABS	1,5,1	;_RA0

	global	_RA1
_RA1	set	41
	DABS	1,5,1	;_RA1

	global	_RA2
_RA2	set	42
	DABS	1,5,1	;_RA2

	global	_RA3
_RA3	set	43
	DABS	1,5,1	;_RA3

	global	_RA4
_RA4	set	44
	DABS	1,5,1	;_RA4

	global	_RA5
_RA5	set	45
	DABS	1,5,1	;_RA5

	global	_RAIE
_RAIE	set	91
	DABS	1,11,1	;_RAIE

	global	_RAIF
_RAIF	set	88
	DABS	1,11,1	;_RAIF

	global	_RC0
_RC0	set	56
	DABS	1,7,1	;_RC0

	global	_RC1
_RC1	set	57
	DABS	1,7,1	;_RC1

	global	_RC2
_RC2	set	58
	DABS	1,7,1	;_RC2

	global	_RC3
_RC3	set	59
	DABS	1,7,1	;_RC3

	global	_RC4
_RC4	set	60
	DABS	1,7,1	;_RC4

	global	_RC5
_RC5	set	61
	DABS	1,7,1	;_RC5

	global	_RP
_RP	set	29
	DABS	1,3,1	;_RP

	global	_RP0
_RP0	set	29
	DABS	1,3,1	;_RP0

	global	_RP1
_RP1	set	30
	DABS	1,3,1	;_RP1

	global	_SLVREN
_SLVREN	set	220
	DABS	1,27,1	;_SLVREN

	global	_SWDTEN
_SWDTEN	set	192
	DABS	1,24,1	;_SWDTEN

	global	_T0IE
_T0IE	set	93
	DABS	1,11,1	;_T0IE

	global	_T0IF
_T0IF	set	90
	DABS	1,11,1	;_T0IF

	global	_T1CKPS0
_T1CKPS0	set	132
	DABS	1,16,1	;_T1CKPS0

	global	_T1CKPS1
_T1CKPS1	set	133
	DABS	1,16,1	;_T1CKPS1

	global	_T1GINV
_T1GINV	set	135
	DABS	1,16,1	;_T1GINV

	global	_T1GSS
_T1GSS	set	209
	DABS	1,26,1	;_T1GSS

	global	_T1IF
_T1IF	set	96
	DABS	1,12,1	;_T1IF

	global	_T1OSCEN
_T1OSCEN	set	131
	DABS	1,16,1	;_T1OSCEN

	global	_T2CKPS0
_T2CKPS0	set	144
	DABS	1,18,1	;_T2CKPS0

	global	_T2CKPS1
_T2CKPS1	set	145
	DABS	1,18,1	;_T2CKPS1

	global	_T2IF
_T2IF	set	97
	DABS	1,12,1	;_T2IF

	global	_TMR0IE
_TMR0IE	set	93
	DABS	1,11,1	;_TMR0IE

	global	_TMR0IF
_TMR0IF	set	90
	DABS	1,11,1	;_TMR0IF

	global	_TMR1CS
_TMR1CS	set	129
	DABS	1,16,1	;_TMR1CS

	global	_TMR1GE
_TMR1GE	set	134
	DABS	1,16,1	;_TMR1GE

	global	_TMR1IF
_TMR1IF	set	96
	DABS	1,12,1	;_TMR1IF

	global	_TMR1ON
_TMR1ON	set	128
	DABS	1,16,1	;_TMR1ON

	global	_TMR2IF
_TMR2IF	set	97
	DABS	1,12,1	;_TMR2IF

	global	_TMR2ON
_TMR2ON	set	146
	DABS	1,18,1	;_TMR2ON

	global	_TOUTPS0
_TOUTPS0	set	147
	DABS	1,18,1	;_TOUTPS0

	global	_TOUTPS1
_TOUTPS1	set	148
	DABS	1,18,1	;_TOUTPS1

	global	_TOUTPS2
_TOUTPS2	set	149
	DABS	1,18,1	;_TOUTPS2

	global	_TOUTPS3
_TOUTPS3	set	150
	DABS	1,18,1	;_TOUTPS3

	global	_VCFG
_VCFG	set	254
	DABS	1,31,1	;_VCFG

	global	_WDTPS0
_WDTPS0	set	193
	DABS	1,24,1	;_WDTPS0

	global	_WDTPS1
_WDTPS1	set	194
	DABS	1,24,1	;_WDTPS1

	global	_WDTPS2
_WDTPS2	set	195
	DABS	1,24,1	;_WDTPS2

	global	_WDTPS3
_WDTPS3	set	196
	DABS	1,24,1	;_WDTPS3

	global	_Z
_Z	set	26
	DABS	1,3,1	;_Z

	global	_ZERO
_ZERO	set	26
	DABS	1,3,1	;_ZERO

	global	_nDONE
_nDONE	set	249
	DABS	1,31,1	;_nDONE

	global	_nPD
_nPD	set	27
	DABS	1,3,1	;_nPD

	global	_nPF
_nPF	set	27
	DABS	1,3,1	;_nPF

	global	_nT1SYNC
_nT1SYNC	set	130
	DABS	1,16,1	;_nT1SYNC

	global	_nTF
_nTF	set	28
	DABS	1,3,1	;_nTF

	global	_nTO
_nTO	set	28
	DABS	1,3,1	;_nTO

	global	_OPTION
_OPTION	set	129
	DABS	1,129,1	;_OPTION

	global	_SFR80
_SFR80	set	128
	DABS	1,128,1	;_SFR80

	global	_ADCON1
_ADCON1	set	159
	DABS	1,159,1	;_ADCON1

	global	_ADRESL
_ADRESL	set	158
	DABS	1,158,1	;_ADRESL

	global	_ANSEL
_ANSEL	set	145
	DABS	1,145,1	;_ANSEL

	global	_EECON1bits
_EECON1bits	set	156
	DABS	1,156,1	;_EECON1bits

	global	_EECON2bits
_EECON2bits	set	157
	DABS	1,157,1	;_EECON2bits

	global	_EEDATA
_EEDATA	set	154
	DABS	1,154,1	;_EEDATA

	global	_IOC
_IOC	set	150
	DABS	1,150,1	;_IOC

	global	_IOCAbits
_IOCAbits	set	150
	DABS	1,150,1	;_IOCAbits

	global	_OPTION_REG
_OPTION_REG	set	129
	DABS	1,129,1	;_OPTION_REG

	global	_OPTIONbits
_OPTIONbits	set	129
	DABS	1,129,1	;_OPTIONbits

	global	_OSCCONbits
_OSCCONbits	set	143
	DABS	1,143,1	;_OSCCONbits

	global	_OSCTUNE
_OSCTUNE	set	144
	DABS	1,144,1	;_OSCTUNE

	global	_PCONbits
_PCONbits	set	142
	DABS	1,142,1	;_PCONbits

	global	_PIE1bits
_PIE1bits	set	140
	DABS	1,140,1	;_PIE1bits

	global	_SFR81
_SFR81	set	129
	DABS	1,129,1	;_SFR81

	global	_SFR85
_SFR85	set	133
	DABS	1,133,1	;_SFR85

	global	_SFR8C
_SFR8C	set	140
	DABS	1,140,1	;_SFR8C

	global	_SFR8E
_SFR8E	set	142
	DABS	1,142,1	;_SFR8E

	global	_SFR8F
_SFR8F	set	143
	DABS	1,143,1	;_SFR8F

	global	_SFR92
_SFR92	set	146
	DABS	1,146,1	;_SFR92

	global	_SFR95
_SFR95	set	149
	DABS	1,149,1	;_SFR95

	global	_SFR96
_SFR96	set	150
	DABS	1,150,1	;_SFR96

	global	_SFR9A
_SFR9A	set	154
	DABS	1,154,1	;_SFR9A

	global	_SFR9B
_SFR9B	set	155
	DABS	1,155,1	;_SFR9B

	global	_SFR9C
_SFR9C	set	156
	DABS	1,156,1	;_SFR9C

	global	_SFR9D
_SFR9D	set	157
	DABS	1,157,1	;_SFR9D

	global	_TRISAbits
_TRISAbits	set	133
	DABS	1,133,1	;_TRISAbits

	global	_TRISC
_TRISC	set	135
	DABS	1,135,1	;_TRISC

	global	_VRCON
_VRCON	set	153
	DABS	1,153,1	;_VRCON

	global	_WPU
_WPU	set	149
	DABS	1,149,1	;_WPU

	global	_WPUAbits
_WPUAbits	set	149
	DABS	1,149,1	;_WPUAbits

	global	_ADCS0
_ADCS0	set	1276
	DABS	1,159,1	;_ADCS0

	global	_ADCS1
_ADCS1	set	1277
	DABS	1,159,1	;_ADCS1

	global	_ADCS2
_ADCS2	set	1278
	DABS	1,159,1	;_ADCS2

	global	_ADIE
_ADIE	set	1126
	DABS	1,140,1	;_ADIE

	global	_ANS0
_ANS0	set	1160
	DABS	1,145,1	;_ANS0

	global	_ANS1
_ANS1	set	1161
	DABS	1,145,1	;_ANS1

	global	_ANS2
_ANS2	set	1162
	DABS	1,145,1	;_ANS2

	global	_ANS3
_ANS3	set	1163
	DABS	1,145,1	;_ANS3

	global	_ANS4
_ANS4	set	1164
	DABS	1,145,1	;_ANS4

	global	_ANS5
_ANS5	set	1165
	DABS	1,145,1	;_ANS5

	global	_ANS6
_ANS6	set	1166
	DABS	1,145,1	;_ANS6

	global	_ANS7
_ANS7	set	1167
	DABS	1,145,1	;_ANS7

	global	_C1IE
_C1IE	set	1123
	DABS	1,140,1	;_C1IE

	global	_C2IE
_C2IE	set	1124
	DABS	1,140,1	;_C2IE

	global	_CCP1IE
_CCP1IE	set	1125
	DABS	1,140,1	;_CCP1IE

	global	_CKMEAIE
_CKMEAIE	set	1126
	DABS	1,140,1	;_CKMEAIE

	global	_ECCPIE
_ECCPIE	set	1125
	DABS	1,140,1	;_ECCPIE

	global	_EEIE
_EEIE	set	1127
	DABS	1,140,1	;_EEIE

	global	_HFIOFR
_HFIOFR	set	1146
	DABS	1,143,1	;_HFIOFR

	global	_HTS
_HTS	set	1146
	DABS	1,143,1	;_HTS

	global	_INTEDG
_INTEDG	set	1038
	DABS	1,129,1	;_INTEDG

	global	_IOC0
_IOC0	set	1200
	DABS	1,150,1	;_IOC0

	global	_IOC1
_IOC1	set	1201
	DABS	1,150,1	;_IOC1

	global	_IOC2
_IOC2	set	1202
	DABS	1,150,1	;_IOC2

	global	_IOC3
_IOC3	set	1203
	DABS	1,150,1	;_IOC3

	global	_IOC4
_IOC4	set	1204
	DABS	1,150,1	;_IOC4

	global	_IOC5
_IOC5	set	1205
	DABS	1,150,1	;_IOC5

	global	_IOCA0
_IOCA0	set	1200
	DABS	1,150,1	;_IOCA0

	global	_IOCA1
_IOCA1	set	1201
	DABS	1,150,1	;_IOCA1

	global	_IOCA2
_IOCA2	set	1202
	DABS	1,150,1	;_IOCA2

	global	_IOCA3
_IOCA3	set	1203
	DABS	1,150,1	;_IOCA3

	global	_IOCA4
_IOCA4	set	1204
	DABS	1,150,1	;_IOCA4

	global	_IOCA5
_IOCA5	set	1205
	DABS	1,150,1	;_IOCA5

	global	_IRCF0
_IRCF0	set	1148
	DABS	1,143,1	;_IRCF0

	global	_IRCF1
_IRCF1	set	1149
	DABS	1,143,1	;_IRCF1

	global	_IRCF2
_IRCF2	set	1150
	DABS	1,143,1	;_IRCF2

	global	_LFIOFR
_LFIOFR	set	1145
	DABS	1,143,1	;_LFIOFR

	global	_LFMOD
_LFMOD	set	1151
	DABS	1,143,1	;_LFMOD

	global	_LTS
_LTS	set	1145
	DABS	1,143,1	;_LTS

	global	_OSFIE
_OSFIE	set	1122
	DABS	1,140,1	;_OSFIE

	global	_OSTS
_OSTS	set	1147
	DABS	1,143,1	;_OSTS

	global	_PS0
_PS0	set	1032
	DABS	1,129,1	;_PS0

	global	_PS1
_PS1	set	1033
	DABS	1,129,1	;_PS1

	global	_PS2
_PS2	set	1034
	DABS	1,129,1	;_PS2

	global	_PSA
_PSA	set	1035
	DABS	1,129,1	;_PSA

	global	_RD
_RD	set	1248
	DABS	1,156,1	;_RD

	global	_SBODEN
_SBODEN	set	1140
	DABS	1,142,1	;_SBODEN

	global	_SBOREN
_SBOREN	set	1140
	DABS	1,142,1	;_SBOREN

	global	_SCS
_SCS	set	1144
	DABS	1,143,1	;_SCS

	global	_T0CS
_T0CS	set	1037
	DABS	1,129,1	;_T0CS

	global	_T0SE
_T0SE	set	1036
	DABS	1,129,1	;_T0SE

	global	_T1IE
_T1IE	set	1120
	DABS	1,140,1	;_T1IE

	global	_T2IE
_T2IE	set	1121
	DABS	1,140,1	;_T2IE

	global	_TMR1IE
_TMR1IE	set	1120
	DABS	1,140,1	;_TMR1IE

	global	_TMR2IE
_TMR2IE	set	1121
	DABS	1,140,1	;_TMR2IE

	global	_TRISA0
_TRISA0	set	1064
	DABS	1,133,1	;_TRISA0

	global	_TRISA1
_TRISA1	set	1065
	DABS	1,133,1	;_TRISA1

	global	_TRISA2
_TRISA2	set	1066
	DABS	1,133,1	;_TRISA2

	global	_TRISA3
_TRISA3	set	1067
	DABS	1,133,1	;_TRISA3

	global	_TRISA4
_TRISA4	set	1068
	DABS	1,133,1	;_TRISA4

	global	_TRISA5
_TRISA5	set	1069
	DABS	1,133,1	;_TRISA5

	global	_TRISC0
_TRISC0	set	1080
	DABS	1,135,1	;_TRISC0

	global	_TRISC1
_TRISC1	set	1081
	DABS	1,135,1	;_TRISC1

	global	_TRISC2
_TRISC2	set	1082
	DABS	1,135,1	;_TRISC2

	global	_TRISC3
_TRISC3	set	1083
	DABS	1,135,1	;_TRISC3

	global	_TRISC4
_TRISC4	set	1084
	DABS	1,135,1	;_TRISC4

	global	_TRISC5
_TRISC5	set	1085
	DABS	1,135,1	;_TRISC5

	global	_TUN0
_TUN0	set	1152
	DABS	1,144,1	;_TUN0

	global	_TUN1
_TUN1	set	1153
	DABS	1,144,1	;_TUN1

	global	_TUN2
_TUN2	set	1154
	DABS	1,144,1	;_TUN2

	global	_TUN3
_TUN3	set	1155
	DABS	1,144,1	;_TUN3

	global	_TUN4
_TUN4	set	1156
	DABS	1,144,1	;_TUN4

	global	_ULPWUE
_ULPWUE	set	1141
	DABS	1,142,1	;_ULPWUE

	global	_VR0
_VR0	set	1224
	DABS	1,153,1	;_VR0

	global	_VR1
_VR1	set	1225
	DABS	1,153,1	;_VR1

	global	_VR2
_VR2	set	1226
	DABS	1,153,1	;_VR2

	global	_VR3
_VR3	set	1227
	DABS	1,153,1	;_VR3

	global	_VREN
_VREN	set	1231
	DABS	1,153,1	;_VREN

	global	_VRR
_VRR	set	1229
	DABS	1,153,1	;_VRR

	global	_WPU0
_WPU0	set	1192
	DABS	1,149,1	;_WPU0

	global	_WPU1
_WPU1	set	1193
	DABS	1,149,1	;_WPU1

	global	_WPU2
_WPU2	set	1194
	DABS	1,149,1	;_WPU2

	global	_WPU4
_WPU4	set	1196
	DABS	1,149,1	;_WPU4

	global	_WPU5
_WPU5	set	1197
	DABS	1,149,1	;_WPU5

	global	_WPUA0
_WPUA0	set	1192
	DABS	1,149,1	;_WPUA0

	global	_WPUA1
_WPUA1	set	1193
	DABS	1,149,1	;_WPUA1

	global	_WPUA2
_WPUA2	set	1194
	DABS	1,149,1	;_WPUA2

	global	_WPUA4
_WPUA4	set	1196
	DABS	1,149,1	;_WPUA4

	global	_WPUA5
_WPUA5	set	1197
	DABS	1,149,1	;_WPUA5

	global	_WR
_WR	set	1256
	DABS	1,157,1	;_WR

	global	_WREN
_WREN	set	1250
	DABS	1,156,1	;_WREN

	global	_WREN1
_WREN1	set	1250
	DABS	1,156,1	;_WREN1

	global	_WREN2
_WREN2	set	1252
	DABS	1,156,1	;_WREN2

	global	_WREN3
_WREN3	set	1253
	DABS	1,156,1	;_WREN3

	global	_WRERR
_WRERR	set	1251
	DABS	1,156,1	;_WRERR

	global	_nBOD
_nBOD	set	1136
	DABS	1,142,1	;_nBOD

	global	_nBOR
_nBOR	set	1136
	DABS	1,142,1	;_nBOR

	global	_nPAPU
_nPAPU	set	1039
	DABS	1,129,1	;_nPAPU

	global	_nPOR
_nPOR	set	1137
	DABS	1,142,1	;_nPOR

	global	_nRAPU
_nRAPU	set	1039
	DABS	1,129,1	;_nRAPU

	global	_INTCON
_INTCON	set	11
	DABS	1,11,1	;_INTCON

	global	_PIR1
_PIR1	set	12
	DABS	1,12,1	;_PIR1

	global	_SFR0D
_SFR0D	set	13
	DABS	1,13,1	;_SFR0D

	global	_SFR0E
_SFR0E	set	14
	DABS	1,14,1	;_SFR0E

	global	_SFR0F
_SFR0F	set	15
	DABS	1,15,1	;_SFR0F

	global	_SFR10
_SFR10	set	16
	DABS	1,16,1	;_SFR10

	global	_TMR2
_TMR2	set	17
	DABS	1,17,1	;_TMR2

	global	_SFR13
_SFR13	set	19
	DABS	1,19,1	;_SFR13

	global	_SFR14
_SFR14	set	20
	DABS	1,20,1	;_SFR14

	global	_SFR15
_SFR15	set	21
	DABS	1,21,1	;_SFR15

	global	_SFR16
_SFR16	set	22
	DABS	1,22,1	;_SFR16

	global	_SFR17
_SFR17	set	23
	DABS	1,23,1	;_SFR17

	global	_T2CON
_T2CON	set	18
	DABS	1,18,1	;_T2CON

	global	_WDTCON
_WDTCON	set	24
	DABS	1,24,1	;_WDTCON

	global	_MSCKCON
_MSCKCON	set	27
	DABS	1,27,1	;_MSCKCON

	global	_SFR19
_SFR19	set	25
	DABS	1,25,1	;_SFR19

	global	_SFR1A
_SFR1A	set	26
	DABS	1,26,1	;_SFR1A

	global	_SFR1E
_SFR1E	set	30
	DABS	1,30,1	;_SFR1E

	global	_SFR1F
_SFR1F	set	31
	DABS	1,31,1	;_SFR1F

	global	_SOSCPRH
_SOSCPRH	set	29
	DABS	1,29,1	;_SOSCPRH

	global	_SOSCPRL
_SOSCPRL	set	28
	DABS	1,28,1	;_SOSCPRL

	global	_SFR82
_SFR82	set	130
	DABS	1,130,1	;_SFR82

	global	_SFR83
_SFR83	set	131
	DABS	1,131,1	;_SFR83

	global	_SFR84
_SFR84	set	132
	DABS	1,132,1	;_SFR84

	global	_TRISA
_TRISA	set	133
	DABS	1,133,1	;_TRISA

	global	_PIE1
_PIE1	set	140
	DABS	1,140,1	;_PIE1

	global	_SFR86
_SFR86	set	134
	DABS	1,134,1	;_SFR86

	global	_SFR87
_SFR87	set	135
	DABS	1,135,1	;_SFR87

	global	_SFR88
_SFR88	set	136
	DABS	1,136,1	;_SFR88

	global	_SFR89
_SFR89	set	137
	DABS	1,137,1	;_SFR89

	global	_SFR8A
_SFR8A	set	138
	DABS	1,138,1	;_SFR8A

	global	_SFR8B
_SFR8B	set	139
	DABS	1,139,1	;_SFR8B

	global	_PCON
_PCON	set	142
	DABS	1,142,1	;_PCON

	global	_SFR8D
_SFR8D	set	141
	DABS	1,141,1	;_SFR8D

	global	_OSCCON
_OSCCON	set	143
	DABS	1,143,1	;_OSCCON

	global	_PR2
_PR2	set	146
	DABS	1,146,1	;_PR2

	global	_SFR90
_SFR90	set	144
	DABS	1,144,1	;_SFR90

	global	_SFR91
_SFR91	set	145
	DABS	1,145,1	;_SFR91

	global	_SFR93
_SFR93	set	147
	DABS	1,147,1	;_SFR93

	global	_SFR94
_SFR94	set	148
	DABS	1,148,1	;_SFR94

	global	_WPUA
_WPUA	set	149
	DABS	1,149,1	;_WPUA

	global	_EEDAT
_EEDAT	set	154
	DABS	1,154,1	;_EEDAT

	global	_IOCA
_IOCA	set	150
	DABS	1,150,1	;_IOCA

	global	_SFR97
_SFR97	set	151
	DABS	1,151,1	;_SFR97

	global	_SFR98
_SFR98	set	152
	DABS	1,152,1	;_SFR98

	global	_SFR99
_SFR99	set	153
	DABS	1,153,1	;_SFR99

	global	_EEADR
_EEADR	set	155
	DABS	1,155,1	;_EEADR

	global	_EECON1
_EECON1	set	156
	DABS	1,156,1	;_EECON1

	global	_EECON2
_EECON2	set	157
	DABS	1,157,1	;_EECON2

	global	_SFR9E
_SFR9E	set	158
	DABS	1,158,1	;_SFR9E

	global	_SFR9F
_SFR9F	set	159
	DABS	1,159,1	;_SFR9F

	file	"mg117mcubeacon.as"
	line	#
psect cinit,class=CODE,delta=2
global start_initialization
start_initialization:

psect cinit,class=CODE,delta=2
global end_of_initialization

;End of C runtime variable initialization code

end_of_initialization:
clrf status
ljmp _main	;jump to C main() function
psect	cstackCOMMON,class=COMMON,space=1
global __pcstackCOMMON
__pcstackCOMMON:
	global	?_ISR
?_ISR:	; 0 bytes @ 0x0
	global	??_ISR
??_ISR:	; 0 bytes @ 0x0
	global	?_POWER_INITIAL
?_POWER_INITIAL:	; 0 bytes @ 0x0
	global	?_WDT_INITIAL
?_WDT_INITIAL:	; 0 bytes @ 0x0
	global	?_DelayUs
?_DelayUs:	; 0 bytes @ 0x0
	global	?_DelayMs
?_DelayMs:	; 0 bytes @ 0x0
	global	?_DelayS
?_DelayS:	; 0 bytes @ 0x0
	global	?_main
?_main:	; 2 bytes @ 0x0
	ds	4
	global	??_POWER_INITIAL
??_POWER_INITIAL:	; 0 bytes @ 0x4
	global	??_WDT_INITIAL
??_WDT_INITIAL:	; 0 bytes @ 0x4
	global	??_DelayUs
??_DelayUs:	; 0 bytes @ 0x4
	ds	1
	global	DelayUs@Time
DelayUs@Time:	; 1 bytes @ 0x5
	ds	1
	global	DelayUs@a
DelayUs@a:	; 1 bytes @ 0x6
	ds	1
	global	??_DelayMs
??_DelayMs:	; 0 bytes @ 0x7
	ds	1
	global	DelayMs@Time
DelayMs@Time:	; 1 bytes @ 0x8
	ds	1
	global	DelayMs@a
DelayMs@a:	; 1 bytes @ 0x9
	ds	1
	global	DelayMs@b
DelayMs@b:	; 1 bytes @ 0xA
	ds	1
	global	??_DelayS
??_DelayS:	; 0 bytes @ 0x7
	global	DelayS@Time
DelayS@Time:	; 1 bytes @ 0x7
	ds	1
	global	DelayS@a
DelayS@a:	; 1 bytes @ 0x8
	ds	1
	global	DelayS@b
DelayS@b:	; 1 bytes @ 0x9
	ds	1
	global	??_main
<<<<<<< HEAD
??_main:	; 0 bytes @ 0xB
;;Data sizes: Strings 0, constant 0, data 0, bss 0, persistent 0 stack 0
;;Auto spaces:   Size  Autos    Used
;; COMMON          62     11      11
=======
??_main:	; 0 bytes @ 0xA
;;Data sizes: Strings 0, constant 0, data 0, bss 0, persistent 0 stack 0
;;Auto spaces:   Size  Autos    Used
;; COMMON          62     10      10
>>>>>>> bc517fe... Test on board. No issue is seen so far.

;;
;; Pointer list with targets:



;;
;; Critical Paths under _main in COMMON
;;
;;   _main->_DelayS
;;   _DelayS->_DelayMs
;;   _DelayMs->_DelayUs
;;
;; Critical Paths under _ISR in COMMON
;;
;;   None.

;;
;;Main: autosize = 0, tempsize = 0, incstack = 0, save=0
;;

;;
;;Call Graph Tables:
;;
;; ---------------------------------------------------------------------------------
;; (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;; ---------------------------------------------------------------------------------
;; (0) _main                                                 0     0      0     240
;;                      _POWER_INITIAL
;;                        _WDT_INITIAL
;;                             _DelayS
;;                            _DelayMs
;; ---------------------------------------------------------------------------------
;; (1) _DelayS                                               3     3      0     150
;;                                              7 COMMON     3     3      0
;;                            _DelayMs
;; ---------------------------------------------------------------------------------
;; (1) _DelayMs                                              4     4      0      90
;;                                              7 COMMON     4     4      0
;;                            _DelayUs
;; ---------------------------------------------------------------------------------
;; (2) _DelayUs                                              3     3      0      30
;;                                              4 COMMON     3     3      0
;; ---------------------------------------------------------------------------------
;; (1) _WDT_INITIAL                                          1     1      0       0
;;                                              4 COMMON     1     1      0
;; ---------------------------------------------------------------------------------
;; (1) _POWER_INITIAL                                        1     1      0       0
;;                                              4 COMMON     1     1      0
;; ---------------------------------------------------------------------------------
;; Estimated maximum stack depth 2
;; ---------------------------------------------------------------------------------
;; (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;; ---------------------------------------------------------------------------------
<<<<<<< HEAD
;; (3) _ISR                                                  4     4      0       0
;;                                              0 COMMON     4     4      0
=======
;; (4) _ISR                                                  2     2      0       0
;;                                              0 COMMON     2     2      0
>>>>>>> bc517fe... Test on board. No issue is seen so far.
;; ---------------------------------------------------------------------------------
;; Estimated maximum stack depth 4
;; ---------------------------------------------------------------------------------

;; Call Graph Graphs:

;; _main (ROOT)
;;   _POWER_INITIAL
;;   _WDT_INITIAL
;;   _DelayS
;;     _DelayMs
;;       _DelayUs
;;   _DelayMs
;;     _DelayUs
;;
;; _ISR (ROOT)
;;

;; Address spaces:

;;Name               Size   Autos  Total    Cost      Usage
;;BITCOMMON           3E      0       0       0        0.0%
;;EEDATA             100      0       0       0        0.0%
;;NULL                 0      0       0       0        0.0%
;;CODE                 0      0       0       0        0.0%
<<<<<<< HEAD
;;COMMON              3E      B       B       1       17.7%
=======
;;COMMON              3E      A       A       1       16.1%
>>>>>>> bc517fe... Test on board. No issue is seen so far.
;;BITSFR0              0      0       0       1        0.0%
;;SFR0                 0      0       0       1        0.0%
;;BITSFR1              0      0       0       2        0.0%
;;SFR1                 0      0       0       2        0.0%
;;STACK                0      0       3       2        0.0%
;;ABS                  0      0       0       3        0.0%
;;DATA                 0      0       0       4        0.0%

	global	_main
psect	maintext,global,class=CODE,delta=2
global __pmaintext
__pmaintext:

;; *************** function _main *****************
;; Defined at:
<<<<<<< HEAD
;;		line 122 in file "MG117McuBeacon.C"
=======
;;		line 126 in file "MG117McuBeacon.C"
>>>>>>> bc517fe... Test on board. No issue is seen so far.
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  2  463[COMMON] int 
;; Registers used:
;;		wreg, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 17F/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON
;;      Params:         0
;;      Locals:         0
;;      Temps:          0
;;      Totals:         0
;;Total ram usage:        0 bytes
;; Hardware stack levels required when called:    4
;; This function calls:
;;		_POWER_INITIAL
;;		_WDT_INITIAL
;;		_DelayS
;;		_DelayMs
;; This function is called by:
;;		Startup code after reset
;; This function uses a non-reentrant model
;;
psect	maintext
	file	"MG117McuBeacon.C"
<<<<<<< HEAD
	line	122
=======
	line	126
>>>>>>> bc517fe... Test on board. No issue is seen so far.
	global	__size_of_main
	__size_of_main	equ	__end_of_main-_main
	
_main:	
	opt	stack 4
; Regs used in _main: [wreg+status,2+status,0+pclath+cstack]
<<<<<<< HEAD
	line	123
	
l2322:	
;MG117McuBeacon.C: 123: POWER_INITIAL();
	fcall	_POWER_INITIAL
	line	124
;MG117McuBeacon.C: 124: WDT_INITIAL();
	fcall	_WDT_INITIAL
	line	127
	
l2324:	
;MG117McuBeacon.C: 127: RA2 = 0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	(42/8),(42)&7
	line	128
;MG117McuBeacon.C: 128: DelayMs(100);
	movlw	(064h)
	fcall	_DelayMs
	line	129
	
l2326:	
;MG117McuBeacon.C: 129: RA2 = 1;
	bcf	status, 5	;RP0=0, select bank0
	bsf	(42/8),(42)&7
	line	132
	
l2328:	
;MG117McuBeacon.C: 132: RA5 = 0;
	bcf	(45/8),(45)&7
	line	133
;MG117McuBeacon.C: 133: DelayMs(1500 - 100);
	movlw	(078h)
	fcall	_DelayMs
	line	134
	
l2330:	
;MG117McuBeacon.C: 134: RA5 = 1;
	bcf	status, 5	;RP0=0, select bank0
	bsf	(45/8),(45)&7
	goto	l2332
	line	137
;MG117McuBeacon.C: 137: while (1)
	
l464:	
	line	139
	
l2332:	
# 139 "MG117McuBeacon.C"
clrwdt ;#
psect	maintext
	line	140
	
l2334:	
;MG117McuBeacon.C: 140: SWDTEN = 1;
	bcf	status, 5	;RP0=0, select bank0
	bsf	(192/8),(192)&7
	line	142
	
l2336:	
;MG117McuBeacon.C: 142: RA4 = 0;
	bcf	(44/8),(44)&7
	line	143
;MG117McuBeacon.C: 143: DelayMs(1050);
	movlw	(01Ah)
	fcall	_DelayMs
	line	144
	
l2338:	
;MG117McuBeacon.C: 144: RA4 = 1;
	bcf	status, 5	;RP0=0, select bank0
	bsf	(44/8),(44)&7
	line	145
;MG117McuBeacon.C: 145: DelayMs((1000 - 1050));
	movlw	(0CEh)
	fcall	_DelayMs
	line	147
	
l2340:	
# 147 "MG117McuBeacon.C"
sleep ;#
psect	maintext
	goto	l2332
	line	148
	
l465:	
	line	137
	goto	l2332
	
l466:	
	line	149
	
l467:	
	global	start
	ljmp	start
	opt stack 0
=======
	line	127
	
l1468:	
;MG117McuBeacon.C: 127: POWER_INITIAL();
	fcall	_POWER_INITIAL
	line	128
;MG117McuBeacon.C: 128: WDT_INITIAL();
	fcall	_WDT_INITIAL
	line	133
	
l1470:	
;MG117McuBeacon.C: 133: RA5 = 0;
	bcf	(45/8),(45)&7
	line	134
;MG117McuBeacon.C: 134: DelayS(1);
	movlw	(01h)
	fcall	_DelayS
	line	135
;MG117McuBeacon.C: 135: DelayMs(500);
	movlw	(0F4h)
	fcall	_DelayMs
	line	136
	
l1472:	
;MG117McuBeacon.C: 136: RA5 = 1;
	bcf	status, 5	;RP0=0, select bank0
	bsf	(45/8),(45)&7
	line	137
;MG117McuBeacon.C: 137: DelayMs(10);
	movlw	(0Ah)
	fcall	_DelayMs
	line	139
	
l1474:	
;MG117McuBeacon.C: 139: RA2 = 0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	(42/8),(42)&7
	line	140
;MG117McuBeacon.C: 140: DelayMs(50);
	movlw	(032h)
	fcall	_DelayMs
	line	141
	
l1476:	
;MG117McuBeacon.C: 141: RA2 = 1;
	bcf	status, 5	;RP0=0, select bank0
	bsf	(42/8),(42)&7
	line	142
;MG117McuBeacon.C: 142: DelayMs(10);
	movlw	(0Ah)
	fcall	_DelayMs
	line	147
	
l1478:	
# 147 "MG117McuBeacon.C"
clrwdt ;#
psect	maintext
	line	148
	
l1480:	
;MG117McuBeacon.C: 148: SWDTEN = 1;
	bcf	status, 5	;RP0=0, select bank0
	bsf	(192/8),(192)&7
	line	150
	
l1482:	
;MG117McuBeacon.C: 150: RA4 = 0;
	bcf	(44/8),(44)&7
	line	151
;MG117McuBeacon.C: 151: DelayMs(1);
	movlw	(01h)
	fcall	_DelayMs
	line	152
	
l1484:	
;MG117McuBeacon.C: 152: RA4 = 1;
	bcf	status, 5	;RP0=0, select bank0
	bsf	(44/8),(44)&7
	line	153
;MG117McuBeacon.C: 153: DelayMs((10));
	movlw	(0Ah)
	fcall	_DelayMs
	line	155
	
l1486:	
# 155 "MG117McuBeacon.C"
sleep ;#
psect	maintext
	goto	l1478
	global	start
	ljmp	start
	opt stack 0
psect	maintext
	line	157
>>>>>>> bc517fe... Test on board. No issue is seen so far.
GLOBAL	__end_of_main
	__end_of_main:
;; =============== function _main ends ============

	signat	_main,90
	global	_DelayS
psect	text71,local,class=CODE,delta=2
global __ptext71
__ptext71:

;; *************** function _DelayS *****************
;; Defined at:
;;		line 109 in file "MG117McuBeacon.C"
;; Parameters:    Size  Location     Type
;;  Time            1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  Time            1    7[COMMON] unsigned char 
;;  b               1    9[COMMON] unsigned char 
;;  a               1    8[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 20/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON
;;      Params:         0
;;      Locals:         3
;;      Temps:          0
;;      Totals:         3
;;Total ram usage:        3 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    3
;; This function calls:
;;		_DelayMs
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text71
	file	"MG117McuBeacon.C"
	line	109
	global	__size_of_DelayS
	__size_of_DelayS	equ	__end_of_DelayS-_DelayS
	
_DelayS:	
	opt	stack 4
; Regs used in _DelayS: [wreg+status,2+status,0+pclath+cstack]
;DelayS@Time stored from wreg
	line	111
	movwf	(DelayS@Time)
	
l1450:	
;MG117McuBeacon.C: 110: unsigned char a, b;
;MG117McuBeacon.C: 111: for (a = 0; a < Time; a++)
	clrf	(DelayS@a)
	goto	l1466
	line	113
	
l1452:	
;MG117McuBeacon.C: 112: {
;MG117McuBeacon.C: 113: for (b = 0; b < 10; b++)
	clrf	(DelayS@b)
	line	115
	
l1458:	
;MG117McuBeacon.C: 114: {
;MG117McuBeacon.C: 115: DelayMs(100);
	movlw	(064h)
	fcall	_DelayMs
	line	113
	
l1460:	
	incf	(DelayS@b),f
	
l1462:	
	movlw	(0Ah)
	subwf	(DelayS@b),w
	skipc
	goto	u41
	goto	u40
u41:
	goto	l1458
u40:
	line	111
	
l1464:	
	incf	(DelayS@a),f
	
l1466:	
	movf	(DelayS@Time),w
	subwf	(DelayS@a),w
	skipc
	goto	u51
	goto	u50
u51:
	goto	l1452
u50:
	line	118
	
l461:	
	return
	opt stack 0
GLOBAL	__end_of_DelayS
	__end_of_DelayS:
;; =============== function _DelayS ends ============

	signat	_DelayS,4216
	global	_DelayMs
<<<<<<< HEAD
psect	text108,local,class=CODE,delta=2
global __ptext108
__ptext108:

;; *************** function _DelayMs *****************
;; Defined at:
;;		line 94 in file "MG117McuBeacon.C"
=======
psect	text72,local,class=CODE,delta=2
global __ptext72
__ptext72:

;; *************** function _DelayMs *****************
;; Defined at:
;;		line 98 in file "MG117McuBeacon.C"
>>>>>>> bc517fe... Test on board. No issue is seen so far.
;; Parameters:    Size  Location     Type
;;  Time            1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  Time            1    8[COMMON] unsigned char 
;;  b               1   10[COMMON] unsigned char 
;;  a               1    9[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON
;;      Params:         0
;;      Locals:         3
;;      Temps:          1
;;      Totals:         4
;;Total ram usage:        4 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_DelayUs
;; This function is called by:
;;		_DelayS
;;		_main
;;		_DelayS
;; This function uses a non-reentrant model
;;
<<<<<<< HEAD
psect	text108
	file	"MG117McuBeacon.C"
	line	94
=======
psect	text72
	file	"MG117McuBeacon.C"
	line	98
>>>>>>> bc517fe... Test on board. No issue is seen so far.
	global	__size_of_DelayMs
	__size_of_DelayMs	equ	__end_of_DelayMs-_DelayMs
	
_DelayMs:	
	opt	stack 5
; Regs used in _DelayMs: [wreg+status,2+status,0+pclath+cstack]
;DelayMs@Time stored from wreg
<<<<<<< HEAD
	line	96
	movwf	(DelayMs@Time)
	
l2306:	
;MG117McuBeacon.C: 95: unsigned char a, b;
;MG117McuBeacon.C: 96: for (a = 0; a < Time; a++)
	clrf	(DelayMs@a)
	goto	l2320
	line	97
	
l449:	
	line	98
;MG117McuBeacon.C: 97: {
;MG117McuBeacon.C: 98: for (b = 0; b < 5; b++)
	clrf	(DelayMs@b)
	
l2308:	
	movlw	(05h)
	subwf	(DelayMs@b),w
	skipc
	goto	u2261
	goto	u2260
u2261:
	goto	l2312
u2260:
	goto	l2318
	
l2310:	
	goto	l2318
	line	99
	
l450:	
	line	100
	
l2312:	
;MG117McuBeacon.C: 99: {
;MG117McuBeacon.C: 100: DelayUs(98);
	movlw	(062h)
	fcall	_DelayUs
	line	98
	
l2314:	
	movlw	(01h)
	movwf	(??_DelayMs+0)+0
	movf	(??_DelayMs+0)+0,w
	addwf	(DelayMs@b),f
	
l2316:	
	movlw	(05h)
	subwf	(DelayMs@b),w
	skipc
	goto	u2271
	goto	u2270
u2271:
	goto	l2312
u2270:
	goto	l2318
	
l451:	
	line	96
	
l2318:	
	movlw	(01h)
	movwf	(??_DelayMs+0)+0
	movf	(??_DelayMs+0)+0,w
	addwf	(DelayMs@a),f
	goto	l2320
	
l448:	
	
l2320:	
	movf	(DelayMs@Time),w
	subwf	(DelayMs@a),w
	skipc
	goto	u2281
	goto	u2280
u2281:
	goto	l449
u2280:
	goto	l453
	
l452:	
	line	103
=======
	line	100
	movwf	(DelayMs@Time)
	
l1432:	
;MG117McuBeacon.C: 99: unsigned char a, b;
;MG117McuBeacon.C: 100: for (a = 0; a < Time; a++)
	clrf	(DelayMs@a)
	goto	l1448
	line	102
	
l1434:	
;MG117McuBeacon.C: 101: {
;MG117McuBeacon.C: 102: for (b = 0; b < 5; b++)
	clrf	(DelayMs@b)
	line	104
	
l1440:	
;MG117McuBeacon.C: 103: {
;MG117McuBeacon.C: 104: DelayUs(98);
	movlw	(062h)
	fcall	_DelayUs
	line	102
	
l1442:	
	incf	(DelayMs@b),f
	
l1444:	
	movlw	(05h)
	subwf	(DelayMs@b),w
	skipc
	goto	u21
	goto	u20
u21:
	goto	l1440
u20:
	line	100
	
l1446:	
	incf	(DelayMs@a),f
	
l1448:	
	movf	(DelayMs@Time),w
	subwf	(DelayMs@a),w
	skipc
	goto	u31
	goto	u30
u31:
	goto	l1434
u30:
	line	107
>>>>>>> bc517fe... Test on board. No issue is seen so far.
	
l453:	
	return
	opt stack 0
GLOBAL	__end_of_DelayMs
	__end_of_DelayMs:
;; =============== function _DelayMs ends ============

	signat	_DelayMs,4216
	global	_DelayUs
<<<<<<< HEAD
psect	text109,local,class=CODE,delta=2
global __ptext109
__ptext109:

;; *************** function _DelayUs *****************
;; Defined at:
;;		line 86 in file "MG117McuBeacon.C"
=======
psect	text73,local,class=CODE,delta=2
global __ptext73
__ptext73:

;; *************** function _DelayUs *****************
;; Defined at:
;;		line 90 in file "MG117McuBeacon.C"
>>>>>>> bc517fe... Test on board. No issue is seen so far.
;; Parameters:    Size  Location     Type
;;  Time            1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  Time            1    5[COMMON] unsigned char 
;;  a               1    6[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON
;;      Params:         0
;;      Locals:         2
;;      Temps:          1
;;      Totals:         3
;;Total ram usage:        3 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_DelayMs
;; This function uses a non-reentrant model
;;
<<<<<<< HEAD
psect	text109
	file	"MG117McuBeacon.C"
	line	86
=======
psect	text73
	file	"MG117McuBeacon.C"
	line	90
>>>>>>> bc517fe... Test on board. No issue is seen so far.
	global	__size_of_DelayUs
	__size_of_DelayUs	equ	__end_of_DelayUs-_DelayUs
	
_DelayUs:	
	opt	stack 5
; Regs used in _DelayUs: [wreg+status,2+status,0]
;DelayUs@Time stored from wreg
<<<<<<< HEAD
	line	88
	movwf	(DelayUs@Time)
	
l2300:	
;MG117McuBeacon.C: 87: unsigned char a;
;MG117McuBeacon.C: 88: for (a = 0; a < Time; a++)
	clrf	(DelayUs@a)
	goto	l2304
	line	89
	
l443:	
	line	90
;MG117McuBeacon.C: 89: {
;MG117McuBeacon.C: 90: _nop();
	nop
	line	88
	
l2302:	
	movlw	(01h)
	movwf	(??_DelayUs+0)+0
	movf	(??_DelayUs+0)+0,w
	addwf	(DelayUs@a),f
	goto	l2304
	
l442:	
	
l2304:	
=======
	line	92
	movwf	(DelayUs@Time)
	
l1426:	
;MG117McuBeacon.C: 91: unsigned char a;
;MG117McuBeacon.C: 92: for (a = 0; a < Time; a++)
	clrf	(DelayUs@a)
	goto	l1430
	line	93
	
l443:	
	line	94
;MG117McuBeacon.C: 93: {
;MG117McuBeacon.C: 94: _nop();
	nop
	line	92
	
l1428:	
	incf	(DelayUs@a),f
	
l1430:	
>>>>>>> bc517fe... Test on board. No issue is seen so far.
	movf	(DelayUs@Time),w
	subwf	(DelayUs@a),w
	skipc
	goto	u2251
	goto	u2250
u2251:
	goto	l443
<<<<<<< HEAD
u2250:
	goto	l445
	
l444:	
	line	92
=======
u10:
	line	96
>>>>>>> bc517fe... Test on board. No issue is seen so far.
	
l445:	
	return
	opt stack 0
GLOBAL	__end_of_DelayUs
	__end_of_DelayUs:
;; =============== function _DelayUs ends ============

	signat	_DelayUs,4216
	global	_WDT_INITIAL
<<<<<<< HEAD
psect	text110,local,class=CODE,delta=2
global __ptext110
__ptext110:

;; *************** function _WDT_INITIAL *****************
;; Defined at:
;;		line 78 in file "MG117McuBeacon.C"
=======
psect	text74,local,class=CODE,delta=2
global __ptext74
__ptext74:

;; *************** function _WDT_INITIAL *****************
;; Defined at:
;;		line 82 in file "MG117McuBeacon.C"
>>>>>>> bc517fe... Test on board. No issue is seen so far.
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON
;;      Params:         0
;;      Locals:         0
;;      Temps:          1
;;      Totals:         1
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
<<<<<<< HEAD
psect	text110
	file	"MG117McuBeacon.C"
	line	78
=======
psect	text74
	file	"MG117McuBeacon.C"
	line	82
>>>>>>> bc517fe... Test on board. No issue is seen so far.
	global	__size_of_WDT_INITIAL
	__size_of_WDT_INITIAL	equ	__end_of_WDT_INITIAL-_WDT_INITIAL
	
_WDT_INITIAL:	
	opt	stack 6
; Regs used in _WDT_INITIAL: [wreg]
<<<<<<< HEAD
	line	79
	
l1420:	
# 79 "MG117McuBeacon.C"
clrwdt ;#
psect	text110
	line	80
;MG117McuBeacon.C: 80: PSA = 1;
	bsf	status, 5	;RP0=1, select bank1
	bsf	(1035/8)^080h,(1035)&7
	line	81
	
l1422:	
;MG117McuBeacon.C: 81: WDTCON = 0B00010100;
=======
	line	83
	
l1420:	
# 83 "MG117McuBeacon.C"
clrwdt ;#
psect	text74
	line	84
;MG117McuBeacon.C: 84: PSA = 1;
	bsf	status, 5	;RP0=1, select bank1
	bsf	(1035/8)^080h,(1035)&7
	line	85
	
l1422:	
<<<<<<< HEAD
;MG117McuBeacon.C: 85: WDTCON = 0B00010100;
>>>>>>> bc517fe... Test on board. No issue is seen so far.
	movlw	(014h)
	movwf	(??_WDT_INITIAL+0)+0
	movf	(??_WDT_INITIAL+0)+0,w
=======
;MG117McuBeacon.C: 85: WDTCON = 0B00010110;
	movlw	(016h)
>>>>>>> e33996d... Fix the Normal button release hold period and updated the WDT period
	bcf	status, 5	;RP0=0, select bank0
	movwf	(24)	;volatile
<<<<<<< HEAD
	line	82
	
l1424:	
;MG117McuBeacon.C: 82: SWDTEN = 0;
	bcf	(192/8),(192)&7
	line	83
=======
	line	86
	
l1424:	
;MG117McuBeacon.C: 86: SWDTEN = 0;
	bcf	(192/8),(192)&7
	line	87
>>>>>>> bc517fe... Test on board. No issue is seen so far.
	
l439:	
	return
	opt stack 0
GLOBAL	__end_of_WDT_INITIAL
	__end_of_WDT_INITIAL:
;; =============== function _WDT_INITIAL ends ============

	signat	_WDT_INITIAL,88
	global	_POWER_INITIAL
<<<<<<< HEAD
psect	text111,local,class=CODE,delta=2
global __ptext111
__ptext111:

;; *************** function _POWER_INITIAL *****************
;; Defined at:
;;		line 47 in file "MG117McuBeacon.C"
=======
psect	text75,local,class=CODE,delta=2
global __ptext75
__ptext75:

;; *************** function _POWER_INITIAL *****************
;; Defined at:
;;		line 51 in file "MG117McuBeacon.C"
>>>>>>> bc517fe... Test on board. No issue is seen so far.
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON
;;      Params:         0
;;      Locals:         0
;;      Temps:          1
;;      Totals:         1
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
<<<<<<< HEAD
psect	text111
	file	"MG117McuBeacon.C"
	line	47
=======
psect	text75
	file	"MG117McuBeacon.C"
	line	51
>>>>>>> bc517fe... Test on board. No issue is seen so far.
	global	__size_of_POWER_INITIAL
	__size_of_POWER_INITIAL	equ	__end_of_POWER_INITIAL-_POWER_INITIAL
	
_POWER_INITIAL:	
	opt	stack 6
<<<<<<< HEAD
; Regs used in _POWER_INITIAL: [wreg]
	line	48
	
l1392:	
;MG117McuBeacon.C: 48: OSCCON = 0B01110001;
=======
; Regs used in _POWER_INITIAL: [wreg+status,2]
	line	52
	
l1392:	
;MG117McuBeacon.C: 52: OSCCON = 0B01110001;
>>>>>>> bc517fe... Test on board. No issue is seen so far.
	movlw	(071h)
	movwf	(??_POWER_INITIAL+0)+0
	movf	(??_POWER_INITIAL+0)+0,w
	bsf	status, 5	;RP0=1, select bank1
	movwf	(143)^080h	;volatile
<<<<<<< HEAD
	line	52
	
l1394:	
;MG117McuBeacon.C: 52: INTCON = 0;
	clrf	(11)	;volatile
	line	53
	
l1396:	
;MG117McuBeacon.C: 53: PORTA = 0B00000000;
	bcf	status, 5	;RP0=0, select bank0
	clrf	(5)	;volatile
	line	54
	
l1398:	
;MG117McuBeacon.C: 54: RA2 = 1;
	bsf	(42/8),(42)&7
	line	55
	
l1400:	
;MG117McuBeacon.C: 55: RA4 = 1;
	bsf	(44/8),(44)&7
	line	56
	
l1402:	
;MG117McuBeacon.C: 56: RA5 = 1;
	bsf	(45/8),(45)&7
	line	58
;MG117McuBeacon.C: 58: TRISA = 0B11111111;
=======
	line	56
	
l1394:	
;MG117McuBeacon.C: 56: INTCON = 0;
	clrf	(11)	;volatile
	line	57
	
l1396:	
;MG117McuBeacon.C: 57: PORTA = 0B00000000;
	bcf	status, 5	;RP0=0, select bank0
	clrf	(5)	;volatile
	line	58
	
l1398:	
;MG117McuBeacon.C: 58: RA2 = 1;
	bsf	(42/8),(42)&7
	line	59
	
l1400:	
;MG117McuBeacon.C: 59: RA4 = 1;
	bsf	(44/8),(44)&7
	line	60
	
l1402:	
;MG117McuBeacon.C: 60: RA5 = 1;
	bsf	(45/8),(45)&7
	line	62
;MG117McuBeacon.C: 62: TRISA = 0B11111111;
>>>>>>> bc517fe... Test on board. No issue is seen so far.
	movlw	(0FFh)
	movwf	(??_POWER_INITIAL+0)+0
	movf	(??_POWER_INITIAL+0)+0,w
	bsf	status, 5	;RP0=1, select bank1
	movwf	(133)^080h	;volatile
<<<<<<< HEAD
	line	60
	
l1404:	
;MG117McuBeacon.C: 60: TRISA2 = 0;
	bcf	(1066/8)^080h,(1066)&7
	line	61
	
l1406:	
;MG117McuBeacon.C: 61: TRISA4 = 0;
	bcf	(1068/8)^080h,(1068)&7
	line	62
	
l1408:	
;MG117McuBeacon.C: 62: TRISA5 = 0;
	bcf	(1069/8)^080h,(1069)&7
	line	64
	
l1410:	
;MG117McuBeacon.C: 64: RA2 = 1;
	bcf	status, 5	;RP0=0, select bank0
	bsf	(42/8),(42)&7
	line	65
	
l1412:	
;MG117McuBeacon.C: 65: RA4 = 1;
	bsf	(44/8),(44)&7
	line	66
	
l1414:	
;MG117McuBeacon.C: 66: RA5 = 1;
	bsf	(45/8),(45)&7
	line	68
	
l1416:	
;MG117McuBeacon.C: 68: WPUA = 0B00000000;
	bsf	status, 5	;RP0=1, select bank1
	clrf	(149)^080h	;volatile
	line	69
;MG117McuBeacon.C: 69: OPTION = 0B00001000;
	movlw	(08h)
	movwf	(??_POWER_INITIAL+0)+0
	movf	(??_POWER_INITIAL+0)+0,w
	movwf	(129)^080h	;volatile
	line	70
	
l1418:	
;MG117McuBeacon.C: 70: MSCKCON = 0B00000000;
	bcf	status, 5	;RP0=0, select bank0
	clrf	(27)	;volatile
	line	75
=======
	line	64
	
l1404:	
;MG117McuBeacon.C: 64: TRISA2 = 0;
	bcf	(1066/8)^080h,(1066)&7
	line	65
	
l1406:	
;MG117McuBeacon.C: 65: TRISA4 = 0;
	bcf	(1068/8)^080h,(1068)&7
	line	66
	
l1408:	
;MG117McuBeacon.C: 66: TRISA5 = 0;
	bcf	(1069/8)^080h,(1069)&7
	line	68
	
l1410:	
;MG117McuBeacon.C: 68: RA2 = 1;
	bcf	status, 5	;RP0=0, select bank0
	bsf	(42/8),(42)&7
	line	69
	
l1412:	
;MG117McuBeacon.C: 69: RA4 = 1;
	bsf	(44/8),(44)&7
	line	70
	
l1414:	
;MG117McuBeacon.C: 70: RA5 = 1;
	bsf	(45/8),(45)&7
	line	72
	
l1416:	
;MG117McuBeacon.C: 72: WPUA = 0B00000000;
	bsf	status, 5	;RP0=1, select bank1
	clrf	(149)^080h	;volatile
	line	73
	
l1418:	
;MG117McuBeacon.C: 73: OPTION = 0B00001000;
	movlw	(08h)
	movwf	(129)^080h	;volatile
	line	74
;MG117McuBeacon.C: 74: MSCKCON = 0B00000000;
	bcf	status, 5	;RP0=0, select bank0
	clrf	(27)	;volatile
	line	79
>>>>>>> bc517fe... Test on board. No issue is seen so far.
	
l436:	
	return
	opt stack 0
GLOBAL	__end_of_POWER_INITIAL
	__end_of_POWER_INITIAL:
;; =============== function _POWER_INITIAL ends ============

	signat	_POWER_INITIAL,88
	global	_ISR
<<<<<<< HEAD
psect	text112,local,class=CODE,delta=2
global __ptext112
__ptext112:

;; *************** function _ISR *****************
;; Defined at:
;;		line 42 in file "MG117McuBeacon.C"
=======
psect	text76,local,class=CODE,delta=2
global __ptext76
__ptext76:

;; *************** function _ISR *****************
;; Defined at:
;;		line 46 in file "MG117McuBeacon.C"
>>>>>>> bc517fe... Test on board. No issue is seen so far.
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		None
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON
;;      Params:         0
;;      Locals:         0
;;      Temps:          4
;;      Totals:         4
;;Total ram usage:        4 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		Interrupt level 1
;; This function uses a non-reentrant model
;;
<<<<<<< HEAD
psect	text112
	file	"MG117McuBeacon.C"
	line	42
=======
psect	text76
	file	"MG117McuBeacon.C"
	line	46
>>>>>>> bc517fe... Test on board. No issue is seen so far.
	global	__size_of_ISR
	__size_of_ISR	equ	__end_of_ISR-_ISR
	
_ISR:	
	opt	stack 4
; Regs used in _ISR: []
psect	intentry,class=CODE,delta=2
global __pintentry
__pintentry:
global interrupt_function
interrupt_function:
	global saved_w
	saved_w	set	btemp+0
	movwf	saved_w
	swapf	status,w
	movwf	(??_ISR+0)
	movf	fsr0,w
	movwf	(??_ISR+1)
	movf	pclath,w
	movwf	(??_ISR+2)
	bcf	status, 5	;RP0=0, select bank0
	movf	btemp+1,w
	movwf	(??_ISR+3)
	ljmp	_ISR
<<<<<<< HEAD
psect	text112
	line	43
=======
psect	text76
	line	47
>>>>>>> bc517fe... Test on board. No issue is seen so far.
	
i1l433:	
	movf	(??_ISR+3),w
	movwf	btemp+1
	movf	(??_ISR+2),w
	movwf	pclath
	movf	(??_ISR+1),w
	movwf	fsr0
	swapf	(??_ISR+0)^0FFFFFF80h,w
	movwf	status
	swapf	saved_w,f
	swapf	saved_w,w
	retfie
	opt stack 0
GLOBAL	__end_of_ISR
	__end_of_ISR:
;; =============== function _ISR ends ============

	signat	_ISR,88
<<<<<<< HEAD
psect	text113,local,class=CODE,delta=2
global __ptext113
__ptext113:
=======
psect	text77,local,class=CODE,delta=2
global __ptext77
__ptext77:
>>>>>>> bc517fe... Test on board. No issue is seen so far.
	global	btemp
	btemp set 07Eh

	DABS	1,126,2	;btemp
	global	wtemp0
	wtemp0 set btemp
	end
