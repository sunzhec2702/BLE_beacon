//Deviec:FT60F01X
//-----------------------Variable---------------------------------
		_ISR		EQU		53F218H
		_ISR		EQU		53F218H
//-----------------------Variable END---------------------------------
		ORG		0000H
		LJUMP 	0AH 			//0000 	380A
		ORG		0004H
		STR 	7EH 			//0004 	01FE
		SWAPR 	STATUS,0 		//0005 	0703
		STR 	40H 			//0006 	01C0
		LDR 	PCLATH,0 		//0007 	080A
		STR 	41H 			//0008 	01C1
		LJUMP 	75H 			//0009 	3875
		LJUMP 	7CH 			//000A 	387C

		//;MG117McuBeacon.C: 127: POWER_INITIAL();
		LCALL 	2AH 			//000B 	302A
		ORG		000CH

		//;MG117McuBeacon.C: 128: WDT_INITIAL();
		LCALL 	6DH 			//000C 	306D
		LDWI 	1H 			//000D 	2A01

		//;MG117McuBeacon.C: 133: RA5 = 0;
		BCR 	5H,5 			//000E 	1285

		//;MG117McuBeacon.C: 134: DelayS(1);
		LCALL 	44H 			//000F 	3044

		//;MG117McuBeacon.C: 135: DelayMs(500);
		LDWI 	F4H 			//0010 	2AF4
		LCALL 	54H 			//0011 	3054
		LDWI 	AH 			//0012 	2A0A

		//;MG117McuBeacon.C: 136: RA5 = 1;
		BCR 	STATUS,5 		//0013 	1283
		ORG		0014H
		BSR 	5H,5 			//0014 	1A85

		//;MG117McuBeacon.C: 137: DelayMs(10);
		LCALL 	54H 			//0015 	3054
		LDWI 	32H 			//0016 	2A32

		//;MG117McuBeacon.C: 139: RA2 = 0;
		BCR 	STATUS,5 		//0017 	1283
		BCR 	5H,2 			//0018 	1105

		//;MG117McuBeacon.C: 140: DelayMs(50);
		LCALL 	54H 			//0019 	3054
		LDWI 	AH 			//001A 	2A0A

		//;MG117McuBeacon.C: 141: RA2 = 1;
		BCR 	STATUS,5 		//001B 	1283
		ORG		001CH
		BSR 	5H,2 			//001C 	1905

		//;MG117McuBeacon.C: 142: DelayMs(10);
		LCALL 	54H 			//001D 	3054
		CLRWDT	 			//001E 	0001
		LDWI 	1H 			//001F 	2A01

		//;MG117McuBeacon.C: 148: SWDTEN = 1;
		BCR 	STATUS,5 		//0020 	1283
		BSR 	18H,0 			//0021 	1818
		BCR 	5H,4 			//0022 	1205

		//;MG117McuBeacon.C: 151: DelayMs(1);
		LCALL 	54H 			//0023 	3054
		ORG		0024H
		LDWI 	AH 			//0024 	2A0A

		//;MG117McuBeacon.C: 152: RA4 = 1;
		BCR 	STATUS,5 		//0025 	1283
		BSR 	5H,4 			//0026 	1A05

		//;MG117McuBeacon.C: 153: DelayMs((10));
		LCALL 	54H 			//0027 	3054
		SLEEP	 			//0028 	0002
		LJUMP 	1EH 			//0029 	381E

		//;MG117McuBeacon.C: 52: OSCCON = 0B01110001;
		LDWI 	71H 			//002A 	2A71
		BSR 	STATUS,5 		//002B 	1A83
		ORG		002CH
		STR 	FH 			//002C 	018F

		//;MG117McuBeacon.C: 56: INTCON = 0;
		CLRR 	INTCON 			//002D 	010B

		//;MG117McuBeacon.C: 57: PORTA = 0B00000000;
		BCR 	STATUS,5 		//002E 	1283
		CLRR 	5H 			//002F 	0105
		LDWI 	FFH 			//0030 	2AFF

		//;MG117McuBeacon.C: 58: RA2 = 1;
		BSR 	5H,2 			//0031 	1905

		//;MG117McuBeacon.C: 59: RA4 = 1;
		BSR 	5H,4 			//0032 	1A05
		BSR 	5H,5 			//0033 	1A85
		ORG		0034H

		//;MG117McuBeacon.C: 62: TRISA = 0B11111111;
		BSR 	STATUS,5 		//0034 	1A83
		STR 	5H 			//0035 	0185

		//;MG117McuBeacon.C: 64: TRISA2 = 0;
		BCR 	5H,2 			//0036 	1105

		//;MG117McuBeacon.C: 65: TRISA4 = 0;
		BCR 	5H,4 			//0037 	1205

		//;MG117McuBeacon.C: 66: TRISA5 = 0;
		BCR 	5H,5 			//0038 	1285

		//;MG117McuBeacon.C: 68: RA2 = 1;
		BCR 	STATUS,5 		//0039 	1283
		BSR 	5H,2 			//003A 	1905

		//;MG117McuBeacon.C: 69: RA4 = 1;
		BSR 	5H,4 			//003B 	1A05
		ORG		003CH

		//;MG117McuBeacon.C: 70: RA5 = 1;
		BSR 	5H,5 			//003C 	1A85

		//;MG117McuBeacon.C: 72: WPUA = 0B00000000;
		BSR 	STATUS,5 		//003D 	1A83
		CLRR 	15H 			//003E 	0115

		//;MG117McuBeacon.C: 73: OPTION = 0B00001000;
		LDWI 	8H 			//003F 	2A08
		STR 	1H 			//0040 	0181

		//;MG117McuBeacon.C: 74: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//0041 	1283
		CLRR 	1BH 			//0042 	011B
		RET		 					//0043 	0004
		ORG		0044H
		STR 	47H 			//0044 	01C7

		//;MG117McuBeacon.C: 110: unsigned char a, b;
		//;MG117McuBeacon.C: 111: for (a = 0; a < Time; a++)
		CLRR 	48H 			//0045 	0148
		LDR 	47H,0 			//0046 	0847
		SUBWR 	48H,0 			//0047 	0C48
		BTSC 	STATUS,0 		//0048 	1403
		RET		 					//0049 	0004

		//;MG117McuBeacon.C: 112: {
		//;MG117McuBeacon.C: 113: for (b = 0; b < 10; b++)
		CLRR 	49H 			//004A 	0149

		//;MG117McuBeacon.C: 114: {
		//;MG117McuBeacon.C: 115: DelayMs(100);
		LDWI 	64H 			//004B 	2A64
		ORG		004CH
		LCALL 	54H 			//004C 	3054
		LDWI 	AH 			//004D 	2A0A
		INCR	49H,1 			//004E 	09C9
		SUBWR 	49H,0 			//004F 	0C49
		BTSS 	STATUS,0 		//0050 	1C03
		LJUMP 	4BH 			//0051 	384B
		INCR	48H,1 			//0052 	09C8
		LJUMP 	46H 			//0053 	3846
		ORG		0054H
		STR 	44H 			//0054 	01C4

		//;MG117McuBeacon.C: 99: unsigned char a, b;
		//;MG117McuBeacon.C: 100: for (a = 0; a < Time; a++)
		CLRR 	45H 			//0055 	0145
		LDR 	44H,0 			//0056 	0844
		SUBWR 	45H,0 			//0057 	0C45
		BTSC 	STATUS,0 		//0058 	1403
		RET		 					//0059 	0004

		//;MG117McuBeacon.C: 101: {
		//;MG117McuBeacon.C: 102: for (b = 0; b < 5; b++)
		CLRR 	46H 			//005A 	0146

		//;MG117McuBeacon.C: 103: {
		//;MG117McuBeacon.C: 104: DelayUs(98);
		LDWI 	62H 			//005B 	2A62
		ORG		005CH
		LCALL 	64H 			//005C 	3064
		LDWI 	5H 			//005D 	2A05
		INCR	46H,1 			//005E 	09C6
		SUBWR 	46H,0 			//005F 	0C46
		BTSS 	STATUS,0 		//0060 	1C03
		LJUMP 	5BH 			//0061 	385B
		INCR	45H,1 			//0062 	09C5
		LJUMP 	56H 			//0063 	3856
		ORG		0064H
		STR 	42H 			//0064 	01C2

		//;MG117McuBeacon.C: 91: unsigned char a;
		//;MG117McuBeacon.C: 92: for (a = 0; a < Time; a++)
		CLRR 	43H 			//0065 	0143
		LDR 	42H,0 			//0066 	0842
		SUBWR 	43H,0 			//0067 	0C43
		BTSC 	STATUS,0 		//0068 	1403
		RET		 					//0069 	0004

		//;MG117McuBeacon.C: 93: {
		//;MG117McuBeacon.C: 94: _nop();
		NOP		 					//006A 	0000
		INCR	43H,1 			//006B 	09C3
		ORG		006CH
		LJUMP 	66H 			//006C 	3866
		CLRWDT	 			//006D 	0001
		LDWI 	16H 			//006E 	2A16

		//;MG117McuBeacon.C: 84: PSA = 1;
		BSR 	STATUS,5 		//006F 	1A83
		BSR 	1H,3 			//0070 	1981

		//;MG117McuBeacon.C: 85: WDTCON = 0B00010110;
		BCR 	STATUS,5 		//0071 	1283
		STR 	18H 			//0072 	0198

		//;MG117McuBeacon.C: 86: SWDTEN = 0;
		BCR 	18H,0 			//0073 	1018
		ORG		0074H
		RET		 					//0074 	0004
		LDR 	41H,0 			//0075 	0841
		STR 	PCLATH 			//0076 	018A
		SWAPR 	40H,0 			//0077 	0740
		STR 	STATUS 			//0078 	0183
		SWAPR 	7EH,1 			//0079 	07FE
		SWAPR 	7EH,0 			//007A 	077E
		RETI		 			//007B 	0009
		ORG		007CH
		CLRR 	STATUS 			//007C 	0103
		LJUMP 	0BH 			//007D 	380B
			END
