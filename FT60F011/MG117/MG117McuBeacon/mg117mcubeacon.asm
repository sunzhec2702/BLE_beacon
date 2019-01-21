//Deviec:FT60F01X
//-----------------------Variable---------------------------------
		_ISR		EQU		7BEE38H
		_ISR		EQU		7BEE38H
//-----------------------Variable END---------------------------------
		ORG		0000H
		LJUMP 	0AH 			//0000 	380A
		ORG		0004H
		STR 	7EH 			//0004 	01FE
		SWAPR 	STATUS,0 		//0005 	0703
		STR 	40H 			//0006 	01C0
		LDR 	PCLATH,0 		//0007 	080A
		STR 	41H 			//0008 	01C1
		LJUMP 	5DH 			//0009 	385D
		LJUMP 	64H 			//000A 	3864

		//;MG117McuBeacon.C: 49: OSCCON = 0B01110001;
		LDWI 	71H 			//000B 	2A71
		ORG		000CH
		BSR 	STATUS,5 		//000C 	1A83
		STR 	FH 			//000D 	018F

		//;MG117McuBeacon.C: 53: INTCON = 0;
		CLRR 	INTCON 			//000E 	010B

		//;MG117McuBeacon.C: 54: PORTA = 0B00000000;
		BCR 	STATUS,5 		//000F 	1283
		CLRR 	5H 			//0010 	0105
		LDWI 	FFH 			//0011 	2AFF

		//;MG117McuBeacon.C: 55: RA2 = 1;
		BSR 	5H,2 			//0012 	1905

		//;MG117McuBeacon.C: 56: RA4 = 1;
		BSR 	5H,4 			//0013 	1A05
		ORG		0014H
		BSR 	5H,5 			//0014 	1A85

		//;MG117McuBeacon.C: 59: TRISA = 0B11111111;
		BSR 	STATUS,5 		//0015 	1A83
		STR 	5H 			//0016 	0185

		//;MG117McuBeacon.C: 61: TRISA2 = 0;
		BCR 	5H,2 			//0017 	1105

		//;MG117McuBeacon.C: 62: TRISA4 = 0;
		BCR 	5H,4 			//0018 	1205

		//;MG117McuBeacon.C: 63: TRISA5 = 0;
		BCR 	5H,5 			//0019 	1285

		//;MG117McuBeacon.C: 65: RA2 = 1;
		BCR 	STATUS,5 		//001A 	1283
		BSR 	5H,2 			//001B 	1905
		ORG		001CH

		//;MG117McuBeacon.C: 66: RA4 = 1;
		BSR 	5H,4 			//001C 	1A05

		//;MG117McuBeacon.C: 67: RA5 = 1;
		BSR 	5H,5 			//001D 	1A85

		//;MG117McuBeacon.C: 69: WPUA = 0B00000000;
		BSR 	STATUS,5 		//001E 	1A83
		CLRR 	15H 			//001F 	0115

		//;MG117McuBeacon.C: 70: OPTION = 0B00001000;
		LDWI 	8H 			//0020 	2A08
		STR 	1H 			//0021 	0181

		//;MG117McuBeacon.C: 71: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//0022 	1283
		CLRR 	1BH 			//0023 	011B
		ORG		0024H
		RET		 					//0024 	0004

		//;MG117McuBeacon.C: 124: POWER_INITIAL();
		LCALL 	BH 			//0025 	300B

		//;MG117McuBeacon.C: 125: WDT_INITIAL();
		LCALL 	56H 			//0026 	3056
		LDWI 	64H 			//0027 	2A64

		//;MG117McuBeacon.C: 128: RA2 = 0;
		BCR 	5H,2 			//0028 	1105

		//;MG117McuBeacon.C: 129: DelayMs(100);
		LCALL 	3DH 			//0029 	303D
		LDWI 	78H 			//002A 	2A78

		//;MG117McuBeacon.C: 130: RA2 = 1;
		BCR 	STATUS,5 		//002B 	1283
		ORG		002CH
		BSR 	5H,2 			//002C 	1905
		BCR 	5H,5 			//002D 	1285

		//;MG117McuBeacon.C: 134: DelayMs(1500 - 100);
		LCALL 	3DH 			//002E 	303D

		//;MG117McuBeacon.C: 135: RA5 = 1;
		BCR 	STATUS,5 		//002F 	1283
		BSR 	5H,5 			//0030 	1A85
		CLRWDT	 			//0031 	0001
		LDWI 	1AH 			//0032 	2A1A

		//;MG117McuBeacon.C: 141: SWDTEN = 1;
		BCR 	STATUS,5 		//0033 	1283
		ORG		0034H
		BSR 	18H,0 			//0034 	1818
		BCR 	5H,4 			//0035 	1205

		//;MG117McuBeacon.C: 144: DelayMs(1050);
		LCALL 	3DH 			//0036 	303D
		LDWI 	CEH 			//0037 	2ACE

		//;MG117McuBeacon.C: 145: RA4 = 1;
		BCR 	STATUS,5 		//0038 	1283
		BSR 	5H,4 			//0039 	1A05

		//;MG117McuBeacon.C: 146: DelayMs((1000 - 1050));
		LCALL 	3DH 			//003A 	303D
		SLEEP	 			//003B 	0002
		ORG		003CH
		LJUMP 	31H 			//003C 	3831
		STR 	44H 			//003D 	01C4

		//;MG117McuBeacon.C: 96: unsigned char a, b;
		//;MG117McuBeacon.C: 97: for (a = 0; a < Time; a++)
		CLRR 	45H 			//003E 	0145
		LDR 	44H,0 			//003F 	0844
		SUBWR 	45H,0 			//0040 	0C45
		BTSC 	STATUS,0 		//0041 	1403
		RET		 					//0042 	0004

		//;MG117McuBeacon.C: 98: {
		//;MG117McuBeacon.C: 99: for (b = 0; b < 5; b++)
		CLRR 	46H 			//0043 	0146
		ORG		0044H

		//;MG117McuBeacon.C: 100: {
		//;MG117McuBeacon.C: 101: DelayUs(98);
		LDWI 	62H 			//0044 	2A62
		LCALL 	4DH 			//0045 	304D
		LDWI 	5H 			//0046 	2A05
		INCR	46H,1 			//0047 	09C6
		SUBWR 	46H,0 			//0048 	0C46
		BTSS 	STATUS,0 		//0049 	1C03
		LJUMP 	44H 			//004A 	3844
		INCR	45H,1 			//004B 	09C5
		ORG		004CH
		LJUMP 	3FH 			//004C 	383F
		STR 	42H 			//004D 	01C2

		//;MG117McuBeacon.C: 88: unsigned char a;
		//;MG117McuBeacon.C: 89: for (a = 0; a < Time; a++)
		CLRR 	43H 			//004E 	0143
		LDR 	42H,0 			//004F 	0842
		SUBWR 	43H,0 			//0050 	0C43
		BTSC 	STATUS,0 		//0051 	1403
		RET		 					//0052 	0004

		//;MG117McuBeacon.C: 90: {
		//;MG117McuBeacon.C: 91: _nop();
		NOP		 					//0053 	0000
		ORG		0054H
		INCR	43H,1 			//0054 	09C3
		LJUMP 	4FH 			//0055 	384F
		CLRWDT	 			//0056 	0001
		LDWI 	14H 			//0057 	2A14

		//;MG117McuBeacon.C: 81: PSA = 1;
		BSR 	STATUS,5 		//0058 	1A83
		BSR 	1H,3 			//0059 	1981

		//;MG117McuBeacon.C: 82: WDTCON = 0B00010100;
		BCR 	STATUS,5 		//005A 	1283
		STR 	18H 			//005B 	0198
		ORG		005CH
		RET		 					//005C 	0004
		LDR 	41H,0 			//005D 	0841
		STR 	PCLATH 			//005E 	018A
		SWAPR 	40H,0 			//005F 	0740
		STR 	STATUS 			//0060 	0183
		SWAPR 	7EH,1 			//0061 	07FE
		SWAPR 	7EH,0 			//0062 	077E
		RETI		 			//0063 	0009
		ORG		0064H
		CLRR 	STATUS 			//0064 	0103
		LJUMP 	25H 			//0065 	3825
			END
