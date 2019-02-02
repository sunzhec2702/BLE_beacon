//Deviec:FT60F01X
//-----------------------Variable---------------------------------
		_ISR		EQU		7BEE50H
		_ISR		EQU		7BEE50H
//-----------------------Variable END---------------------------------
		ORG		0000H
		LJUMP 	0AH 			//0000 	380A
		ORG		0004H
		STR 	7EH 			//0004 	01FE
		SWAPR 	STATUS,0 		//0005 	0703
		STR 	40H 			//0006 	01C0
		LDR 	PCLATH,0 		//0007 	080A
		STR 	41H 			//0008 	01C1
		LJUMP 	72H 			//0009 	3872
		LJUMP 	79H 			//000A 	3879

		//;MG117McuBeacon.C: 130: POWER_INITIAL();
		LCALL 	27H 			//000B 	3027
		ORG		000CH

		//;MG117McuBeacon.C: 131: WDT_INITIAL();
		LCALL 	6AH 			//000C 	306A
		LDWI 	1H 			//000D 	2A01

		//;MG117McuBeacon.C: 136: RA5 = 0;
		BCR 	5H,5 			//000E 	1285

		//;MG117McuBeacon.C: 137: DelayS(1);
		LCALL 	41H 			//000F 	3041

		//;MG117McuBeacon.C: 138: DelayMs(500);
		LDWI 	F4H 			//0010 	2AF4
		LCALL 	51H 			//0011 	3051
		LDWI 	32H 			//0012 	2A32

		//;MG117McuBeacon.C: 139: RA5 = 1;
		BCR 	STATUS,5 		//0013 	1283
		ORG		0014H
		BSR 	5H,5 			//0014 	1A85
		BCR 	5H,2 			//0015 	1105

		//;MG117McuBeacon.C: 142: DelayMs(50);
		LCALL 	51H 			//0016 	3051
		LDWI 	AH 			//0017 	2A0A

		//;MG117McuBeacon.C: 143: RA2 = 1;
		BCR 	STATUS,5 		//0018 	1283
		BSR 	5H,2 			//0019 	1905

		//;MG117McuBeacon.C: 144: DelayMs(10);
		LCALL 	51H 			//001A 	3051
		CLRWDT	 			//001B 	0001
		ORG		001CH
		LDWI 	1H 			//001C 	2A01

		//;MG117McuBeacon.C: 150: SWDTEN = 1;
		BCR 	STATUS,5 		//001D 	1283
		BSR 	18H,0 			//001E 	1818
		BCR 	5H,4 			//001F 	1205

		//;MG117McuBeacon.C: 153: DelayMs(1);
		LCALL 	51H 			//0020 	3051
		LDWI 	AH 			//0021 	2A0A

		//;MG117McuBeacon.C: 154: RA4 = 1;
		BCR 	STATUS,5 		//0022 	1283
		BSR 	5H,4 			//0023 	1A05
		ORG		0024H

		//;MG117McuBeacon.C: 155: DelayMs((10));
		LCALL 	51H 			//0024 	3051
		SLEEP	 			//0025 	0002
		LJUMP 	1BH 			//0026 	381B

		//;MG117McuBeacon.C: 52: OSCCON = 0B01010001;
		LDWI 	51H 			//0027 	2A51
		BSR 	STATUS,5 		//0028 	1A83
		STR 	FH 			//0029 	018F

		//;MG117McuBeacon.C: 57: INTCON = 0;
		CLRR 	INTCON 			//002A 	010B

		//;MG117McuBeacon.C: 58: PORTA = 0B00000000;
		BCR 	STATUS,5 		//002B 	1283
		ORG		002CH
		CLRR 	5H 			//002C 	0105
		LDWI 	FFH 			//002D 	2AFF

		//;MG117McuBeacon.C: 59: RA2 = 1;
		BSR 	5H,2 			//002E 	1905

		//;MG117McuBeacon.C: 60: RA4 = 1;
		BSR 	5H,4 			//002F 	1A05
		BSR 	5H,5 			//0030 	1A85

		//;MG117McuBeacon.C: 63: TRISA = 0B11111111;
		BSR 	STATUS,5 		//0031 	1A83
		STR 	5H 			//0032 	0185

		//;MG117McuBeacon.C: 66: TRISA2 = 0;
		BCR 	5H,2 			//0033 	1105
		ORG		0034H

		//;MG117McuBeacon.C: 67: TRISA4 = 0;
		BCR 	5H,4 			//0034 	1205

		//;MG117McuBeacon.C: 68: TRISA5 = 0;
		BCR 	5H,5 			//0035 	1285

		//;MG117McuBeacon.C: 70: RA2 = 1;
		BCR 	STATUS,5 		//0036 	1283
		BSR 	5H,2 			//0037 	1905

		//;MG117McuBeacon.C: 71: RA4 = 1;
		BSR 	5H,4 			//0038 	1A05

		//;MG117McuBeacon.C: 72: RA5 = 1;
		BSR 	5H,5 			//0039 	1A85

		//;MG117McuBeacon.C: 74: WPUA = 0B00000000;
		BSR 	STATUS,5 		//003A 	1A83
		CLRR 	15H 			//003B 	0115
		ORG		003CH

		//;MG117McuBeacon.C: 75: OPTION = 0B00001000;
		LDWI 	8H 			//003C 	2A08
		STR 	1H 			//003D 	0181

		//;MG117McuBeacon.C: 77: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//003E 	1283
		CLRR 	1BH 			//003F 	011B
		RET		 					//0040 	0004
		STR 	47H 			//0041 	01C7

		//;MG117McuBeacon.C: 113: unsigned char a, b;
		//;MG117McuBeacon.C: 114: for (a = 0; a < Time; a++)
		CLRR 	48H 			//0042 	0148
		LDR 	47H,0 			//0043 	0847
		ORG		0044H
		SUBWR 	48H,0 			//0044 	0C48
		BTSC 	STATUS,0 		//0045 	1403
		RET		 					//0046 	0004

		//;MG117McuBeacon.C: 115: {
		//;MG117McuBeacon.C: 116: for (b = 0; b < 10; b++)
		CLRR 	49H 			//0047 	0149

		//;MG117McuBeacon.C: 117: {
		//;MG117McuBeacon.C: 118: DelayMs(100);
		LDWI 	64H 			//0048 	2A64
		LCALL 	51H 			//0049 	3051
		LDWI 	AH 			//004A 	2A0A
		INCR	49H,1 			//004B 	09C9
		ORG		004CH
		SUBWR 	49H,0 			//004C 	0C49
		BTSS 	STATUS,0 		//004D 	1C03
		LJUMP 	48H 			//004E 	3848
		INCR	48H,1 			//004F 	09C8
		LJUMP 	43H 			//0050 	3843
		STR 	44H 			//0051 	01C4

		//;MG117McuBeacon.C: 102: unsigned char a, b;
		//;MG117McuBeacon.C: 103: for (a = 0; a < Time; a++)
		CLRR 	45H 			//0052 	0145
		LDR 	44H,0 			//0053 	0844
		ORG		0054H
		SUBWR 	45H,0 			//0054 	0C45
		BTSC 	STATUS,0 		//0055 	1403
		RET		 					//0056 	0004

		//;MG117McuBeacon.C: 104: {
		//;MG117McuBeacon.C: 105: for (b = 0; b < 5; b++)
		CLRR 	46H 			//0057 	0146

		//;MG117McuBeacon.C: 106: {
		//;MG117McuBeacon.C: 107: DelayUs(25);
		LDWI 	19H 			//0058 	2A19
		LCALL 	61H 			//0059 	3061
		LDWI 	5H 			//005A 	2A05
		INCR	46H,1 			//005B 	09C6
		ORG		005CH
		SUBWR 	46H,0 			//005C 	0C46
		BTSS 	STATUS,0 		//005D 	1C03
		LJUMP 	58H 			//005E 	3858
		INCR	45H,1 			//005F 	09C5
		LJUMP 	53H 			//0060 	3853
		STR 	42H 			//0061 	01C2

		//;MG117McuBeacon.C: 94: unsigned char a;
		//;MG117McuBeacon.C: 95: for (a = 0; a < Time; a++)
		CLRR 	43H 			//0062 	0143
		LDR 	42H,0 			//0063 	0842
		ORG		0064H
		SUBWR 	43H,0 			//0064 	0C43
		BTSC 	STATUS,0 		//0065 	1403
		RET		 					//0066 	0004

		//;MG117McuBeacon.C: 96: {
		//;MG117McuBeacon.C: 97: _nop();
		NOP		 					//0067 	0000
		INCR	43H,1 			//0068 	09C3
		LJUMP 	63H 			//0069 	3863
		CLRWDT	 			//006A 	0001
		LDWI 	16H 			//006B 	2A16
		ORG		006CH

		//;MG117McuBeacon.C: 87: PSA = 1;
		BSR 	STATUS,5 		//006C 	1A83
		BSR 	1H,3 			//006D 	1981

		//;MG117McuBeacon.C: 88: WDTCON = 0B00010110;
		BCR 	STATUS,5 		//006E 	1283
		STR 	18H 			//006F 	0198

		//;MG117McuBeacon.C: 89: SWDTEN = 0;
		BCR 	18H,0 			//0070 	1018
		RET		 					//0071 	0004
		LDR 	41H,0 			//0072 	0841
		STR 	PCLATH 			//0073 	018A
		ORG		0074H
		SWAPR 	40H,0 			//0074 	0740
		STR 	STATUS 			//0075 	0183
		SWAPR 	7EH,1 			//0076 	07FE
		SWAPR 	7EH,0 			//0077 	077E
		RETI		 			//0078 	0009
		CLRR 	STATUS 			//0079 	0103
		LJUMP 	0BH 			//007A 	380B
			END
