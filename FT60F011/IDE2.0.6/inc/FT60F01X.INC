          LIST

;==========================================================================
;  MPASM FMD60F011 processor include
; 
;  (c) Copyright 1999-2015 Fremont Micro Devices Ltd., All rights reserved
;==========================================================================

        NOLIST

;==========================================================================
;  This header file defines configurations, registers, and other useful
;  bits of information for the FMD60F011 microcontroller.  These names
;  are taken to match the data sheets as closely as possible.
;
;  Note that the processor must be selected before this file is included.
;  The processor may be selected the following ways:
;
;       1. Command line switch:
;               C:\MPASM MYFILE.ASM /FMD60F011
;       2. LIST directive in the source file
;               LIST   P=FMD60F011
;       3. Processor Type entry in the MPASM full-screen interface
;       4. Setting the processor in the MPLAB Project Dialog
;==========================================================================
;==========================================================================
;
;       Verify Processor
;
;==========================================================================
;==========================================================================
;
;       Register Definitions
;
;==========================================================================
W                EQU  H'0000' 
F                EQU  H'0001'
R                EQU  H'0001'				
;----- Register Files -----------------------------------------------------
;-----Bank0------------------
INDF             EQU  H'0000'
TMR0             EQU  H'0001'
PCL              EQU  H'0002'
STATUS           EQU  H'0003'
FSR              EQU  H'0004'
PORTA            EQU  H'0005'
PCLATH           EQU  H'000A'
INTCON           EQU  H'000B'
PIR1             EQU  H'000C'
TMR2             EQU  H'0011'
T2CON            EQU  H'0012'
WDTCON           EQU  H'0018'
MSCKCON          EQU  H'001B'
SOSCPRL          EQU  H'001C'
SOSCPRH          EQU  H'001D'
;-----Bank1------------------
OPTION      	 EQU  H'0081'
OPTION_REG       EQU  H'0081'
TRISA            EQU  H'0085'
PIE1             EQU  H'008C'
PCON             EQU  H'008E'
OSCCON           EQU  H'008F'
PR2              EQU  H'0092'
WPU              EQU  H'0095'
WPUA             EQU  H'0095'
IOC              EQU  H'0096'
IOCA             EQU  H'0096'
EEDAT            EQU  H'009A'
EEDATA           EQU  H'009A'
EEADR            EQU  H'009B'
EEADDR           EQU  H'009B'
EECON1           EQU  H'009C'
EECON2           EQU  H'009D'
;-----Bank0------------------
;----- STATUS Bits -----------------------------------------------------
C                EQU  H'0000'
DC               EQU  H'0001'
HC				 EQU  H'0001'
Z                EQU  H'0002'
PF               EQU  H'0003'
NOT_PD           EQU  H'0003'
TF               EQU  H'0004'
NOT_TO           EQU  H'0004'
PAGE			 EQU  H'0005'
RP0              EQU  H'0005'
RP               EQU  H'0005'
;----- PORTA Bits -----------------------------------------------------
RA0              EQU  H'0000'
PA0              EQU  H'0000'
RA1              EQU  H'0001'
PA1              EQU  H'0001'
RA2              EQU  H'0002'
PA2              EQU  H'0002'
RA3              EQU  H'0003'
PA3              EQU  H'0003'
RA4              EQU  H'0004'
PA4              EQU  H'0004'
RA5              EQU  H'0005'
PA5              EQU  H'0005'
;----- INTCON Bits -----------------------------------------------------
RAIF             EQU  H'0000'
PAIF             EQU  H'0000'
INTF             EQU  H'0001'
T0IF             EQU  H'0002'
TMR0IF           EQU  H'0002'
RAIE             EQU  H'0003'
PAIE             EQU  H'0003'
INTE             EQU  H'0004'
T0IE             EQU  H'0005'
TMR0IE           EQU  H'0005'
PEIE             EQU  H'0006'
GIE              EQU  H'0007'
;----- PIR1 Bits -----------------------------------------------------
TMR2IF           EQU  H'0001'
T2IF             EQU  H'0001'
CKMEAIF          EQU  H'0006'
EEIF             EQU  H'0007'
;----- T2CON Bits -----------------------------------------------------
T2CKPS0          EQU  H'0000'
T2CKPS1          EQU  H'0001'
TMR2ON           EQU  H'0002'
TOUTPS0          EQU  H'0003'
TOUTPS1          EQU  H'0004'
TOUTPS2          EQU  H'0005'
TOUTPS3          EQU  H'0006'
;----- WDTCON Bits -----------------------------------------------------
SWDTEN           EQU  H'0000'
WDTPS0           EQU  H'0001'
WDTPS1           EQU  H'0002'
WDTPS2           EQU  H'0003'
WDTPS3           EQU  H'0004'

;----- MSCKCON Bits -----------------------------------------------------
CKCNTI           EQU  H'0001'
CKMAVG           EQU  H'0002'
SLVREN			 EQU  H'0004'
;-----Bank1------------------
;----- OPTION_REG Bits -----------------------------------------------------
PS0              EQU  H'0000'
PS1              EQU  H'0001'
PS2              EQU  H'0002'
PSA              EQU  H'0003'
T0SE             EQU  H'0004'
T0CS             EQU  H'0005'
INTEDG           EQU  H'0006'
PAPU			 EQU  H'0007'
NOT_PAPU         EQU  H'0007'
NOT_RAPU         EQU  H'0007'
;----- TRISA Bits -----------------------------------------------------
TRISA0           EQU  H'0000'
TRISA1           EQU  H'0001'
TRISA2           EQU  H'0002'
TRISA4           EQU  H'0004'
TRISA5           EQU  H'0005'
;----- PIE1 Bits -----------------------------------------------------
T2IE             EQU  H'0001'
TMR2IE           EQU  H'0001'
CKMEAIE          EQU  H'0006'
EEIE             EQU  H'0007'
;----- PCON Bits -----------------------------------------------------
BOR              EQU  H'0000'
NOT_BOR          EQU  H'0000'
POR              EQU  H'0001'
NOT_POR          EQU  H'0001'
;----- OSCCON Bits -----------------------------------------------------
LTS              EQU  H'0001'
LFIOFR			 EQU  H'0001'
HTS              EQU  H'0002'
HFIOFR			 EQU  H'0002'
IRCF0            EQU  H'0004'
IRCF1            EQU  H'0005'
IRCF2            EQU  H'0006'
LFMOD			 EQU  H'0007'
;----- WPUA Bits -----------------------------------------------------
WPUA0            EQU  H'0000'
WPUA1            EQU  H'0001'
WPUA2            EQU  H'0002'
WPUA4            EQU  H'0004'
WPUA5            EQU  H'0005'
WPU0             EQU  H'0000'
WPU1             EQU  H'0001'
WPU2             EQU  H'0002'
WPU4             EQU  H'0004'
WPU5             EQU  H'0005'
;----- IOCA Bits -----------------------------------------------------
IOCA0            EQU  H'0000'
IOCA1            EQU  H'0001'
IOCA2            EQU  H'0002'
IOCA3            EQU  H'0003'
IOCA4            EQU  H'0004'
IOCA5            EQU  H'0005'
IOC0             EQU  H'0000'
IOC1             EQU  H'0001'
IOC2             EQU  H'0002'
IOC3             EQU  H'0003'
IOC4             EQU  H'0004'
IOC5             EQU  H'0005'
;----- EECON1 Bits -----------------------------------------------------
RD               EQU  H'0000'
WREN1			 EQU  H'0002'
WRERR            EQU  H'0003'
WREN2			 EQU  H'0004'
WREN3			 EQU  H'0005'
;----- EECON2 Bits -----------------------------------------------------
WR               EQU  H'0000'
        LIST
