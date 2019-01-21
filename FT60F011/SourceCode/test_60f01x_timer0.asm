//Deviec:FT60F01X
//-----------------------Variable---------------------------------
		_ISR		EQU		12FBFCH
		_ISR		EQU		12FBFCH
//-----------------------Variable END---------------------------------
		ORG		0000H
		LJUMP 	0AH 			//0000 	380A
		ORG		0004H
		STR 	7EH 			//0004 	01FE
		SWAPR 	STATUS,0 		//0005 	0703
		STR 	40H 			//0006 	01C0
		LDR 	PCLATH,0 		//0007 	080A
		STR 	41H 			//0008 	01C1
		LJUMP 	1BH 			//0009 	381B
		LJUMP 	34H 			//000A 	3834

		//;TEST_60F01x_Timer0.c: 55: OSCCON = 0B01110001;
		LDWI 	71H 			//000B 	2A71
		BSR 	STATUS,5 		//000C 	1A83
		STR 	FH 			//000D 	018F

		//;TEST_60F01x_Timer0.c: 58: INTCON = 0;
		CLRR 	INTCON 			//000E 	010B

		//;TEST_60F01x_Timer0.c: 59: PORTA = 0B00000000;
		BCR 	STATUS,5 		//000F 	1283
		CLRR 	5H 			//0010 	0105

		//;TEST_60F01x_Timer0.c: 60: TRISA = 0B11101111;
		LDWI 	EFH 			//0011 	2AEF
		BSR 	STATUS,5 		//0012 	1A83
		STR 	5H 			//0013 	0185

		//;TEST_60F01x_Timer0.c: 62: WPUA = 0B00000100;
		LDWI 	4H 			//0014 	2A04
		STR 	15H 			//0015 	0195

		//;TEST_60F01x_Timer0.c: 64: OPTION = 0B00001000;
		LDWI 	8H 			//0016 	2A08
		STR 	1H 			//0017 	0181

		//;TEST_60F01x_Timer0.c: 67: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//0018 	1283
		CLRR 	1BH 			//0019 	011B
		RET		 					//001A 	0004

		//;TEST_60F01x_Timer0.c: 38: if(T0IE && T0IF)
		BTSC 	INTCON,5 		//001B 	168B
		BTSS 	INTCON,2 		//001C 	1D0B
		LJUMP 	22H 			//001D 	3822
		LDWI 	10H 			//001E 	2A10

		//;TEST_60F01x_Timer0.c: 39: {
		//;TEST_60F01x_Timer0.c: 42: T0IF = 0;
		BCR 	INTCON,2 		//001F 	110B
		BCR 	STATUS,5 		//0020 	1283
		XORWR 	5H,1 			//0021 	0485
		LDR 	41H,0 			//0022 	0841
		STR 	PCLATH 			//0023 	018A
		SWAPR 	40H,0 			//0024 	0740
		STR 	STATUS 			//0025 	0183
		SWAPR 	7EH,1 			//0026 	07FE
		SWAPR 	7EH,0 			//0027 	077E
		RETI		 			//0028 	0009

		//;TEST_60F01x_Timer0.c: 145: POWER_INITIAL();
		LCALL 	BH 			//0029 	300B

		//;TEST_60F01x_Timer0.c: 146: TIMER0_INITIAL();
		LCALL 	2FH 			//002A 	302F

		//;TEST_60F01x_Timer0.c: 147: GIE = 1;
		BSR 	INTCON,7 		//002B 	1B8B

		//;TEST_60F01x_Timer0.c: 148: T0IE = 1;
		BSR 	INTCON,5 		//002C 	1A8B

		//;TEST_60F01x_Timer0.c: 150: {
		//;TEST_60F01x_Timer0.c: 151: _nop();
		NOP		 					//002D 	0000
		LJUMP 	2DH 			//002E 	382D

		//;TEST_60F01x_Timer0.c: 81: OPTION = 0B00000111;
		LDWI 	7H 			//002F 	2A07
		BSR 	STATUS,5 		//0030 	1A83
		STR 	1H 			//0031 	0181

		//;TEST_60F01x_Timer0.c: 87: T0IF = 0;
		BCR 	INTCON,2 		//0032 	110B
		RET		 					//0033 	0004
		CLRR 	STATUS 			//0034 	0103
		LJUMP 	29H 			//0035 	3829
			END
