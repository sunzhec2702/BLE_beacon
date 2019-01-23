//Deviec:FT60F01X
//-----------------------Variable---------------------------------
//-----------------------Variable END---------------------------------
		ORG		0000H
		LJUMP 	3B9H 			//0000 	3BB9
		ORG		03B9H
		CLRR 	STATUS 			//03B9 	0103
		LJUMP 	3C4H 			//03BA 	3BC4
		STR 	40H 			//03BB 	01C0

		//;TEST_60F01x_SLEEP.c: 72: unsigned char a;
		//;TEST_60F01x_SLEEP.c: 73: for(a=0;a<Time;a++)
		CLRR 	41H 			//03BC 	0141
		LDR 	40H,0 			//03BD 	0840
		SUBWR 	41H,0 			//03BE 	0C41
		BTSC 	STATUS,0 		//03BF 	1403
		RET		 					//03C0 	0004
		CLRWDT	 			//03C1 	0001
		INCR	41H,1 			//03C2 	09C1
		LJUMP 	3BDH 			//03C3 	3BBD

		//;TEST_60F01x_SLEEP.c: 120: POWER_INITIAL();
		LCALL 	3D1H 			//03C4 	33D1
		LDWI 	3H 			//03C5 	2A03

		//;TEST_60F01x_SLEEP.c: 121: RA1 = 1;
		BSR 	5H,1 			//03C6 	1885
		BSR 	5H,0 			//03C7 	1805

		//;TEST_60F01x_SLEEP.c: 123: DelayS(3);
		LCALL 	3F0H 			//03C8 	33F0

		//;TEST_60F01x_SLEEP.c: 124: RA1 = 0;
		BCR 	STATUS,5 		//03C9 	1283
		BCR 	5H,1 			//03CA 	1085

		//;TEST_60F01x_SLEEP.c: 125: RA0 = 0;
		BCR 	5H,0 			//03CB 	1005
		CLRWDT	 			//03CC 	0001

		//;TEST_60F01x_SLEEP.c: 129: _nop();
		NOP		 					//03CD 	0000
		SLEEP	 			//03CE 	0002

		//;TEST_60F01x_SLEEP.c: 131: _nop();
		NOP		 					//03CF 	0000
		LJUMP 	3CCH 			//03D0 	3BCC

		//;TEST_60F01x_SLEEP.c: 46: OSCCON = 0X00|0X70|0X01;
		LDWI 	71H 			//03D1 	2A71
		BSR 	STATUS,5 		//03D2 	1A83
		STR 	FH 			//03D3 	018F

		//;TEST_60F01x_SLEEP.c: 50: INTCON = 0;
		CLRR 	INTCON 			//03D4 	010B

		//;TEST_60F01x_SLEEP.c: 51: PORTA = 0B00000000;
		BCR 	STATUS,5 		//03D5 	1283
		CLRR 	5H 			//03D6 	0105

		//;TEST_60F01x_SLEEP.c: 52: TRISA = 0B00000000;
		BSR 	STATUS,5 		//03D7 	1A83
		CLRR 	5H 			//03D8 	0105

		//;TEST_60F01x_SLEEP.c: 53: WPUA = 0B00100000;
		LDWI 	20H 			//03D9 	2A20
		STR 	15H 			//03DA 	0195

		//;TEST_60F01x_SLEEP.c: 56: OPTION = 0B00001000;
		LDWI 	8H 			//03DB 	2A08
		STR 	1H 			//03DC 	0181

		//;TEST_60F01x_SLEEP.c: 58: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//03DD 	1283
		CLRR 	1BH 			//03DE 	011B
		RET		 					//03DF 	0004
		STR 	42H 			//03E0 	01C2

		//;TEST_60F01x_SLEEP.c: 86: unsigned char a,b;
		//;TEST_60F01x_SLEEP.c: 87: for(a=0;a<Time;a++)
		CLRR 	43H 			//03E1 	0143
		LDR 	42H,0 			//03E2 	0842
		SUBWR 	43H,0 			//03E3 	0C43
		BTSC 	STATUS,0 		//03E4 	1403
		RET		 					//03E5 	0004

		//;TEST_60F01x_SLEEP.c: 88: {
		//;TEST_60F01x_SLEEP.c: 89: for(b=0;b<5;b++)
		CLRR 	44H 			//03E6 	0144

		//;TEST_60F01x_SLEEP.c: 90: {
		//;TEST_60F01x_SLEEP.c: 91: DelayUs(197);
		LDWI 	C5H 			//03E7 	2AC5
		LCALL 	3BBH 			//03E8 	33BB
		LDWI 	5H 			//03E9 	2A05
		INCR	44H,1 			//03EA 	09C4
		SUBWR 	44H,0 			//03EB 	0C44
		BTSS 	STATUS,0 		//03EC 	1C03
		LJUMP 	3E7H 			//03ED 	3BE7
		INCR	43H,1 			//03EE 	09C3
		LJUMP 	3E2H 			//03EF 	3BE2
		STR 	45H 			//03F0 	01C5

		//;TEST_60F01x_SLEEP.c: 103: unsigned char a,b;
		//;TEST_60F01x_SLEEP.c: 104: for(a=0;a<Time;a++)
		CLRR 	46H 			//03F1 	0146
		LDR 	45H,0 			//03F2 	0845
		SUBWR 	46H,0 			//03F3 	0C46
		BTSC 	STATUS,0 		//03F4 	1403
		RET		 					//03F5 	0004

		//;TEST_60F01x_SLEEP.c: 105: {
		//;TEST_60F01x_SLEEP.c: 106: for(b=0;b<10;b++)
		CLRR 	47H 			//03F6 	0147

		//;TEST_60F01x_SLEEP.c: 107: {
		//;TEST_60F01x_SLEEP.c: 108: DelayMs(100);
		LDWI 	64H 			//03F7 	2A64
		LCALL 	3E0H 			//03F8 	33E0
		LDWI 	AH 			//03F9 	2A0A
		INCR	47H,1 			//03FA 	09C7
		SUBWR 	47H,0 			//03FB 	0C47
		BTSS 	STATUS,0 		//03FC 	1C03
		LJUMP 	3F7H 			//03FD 	3BF7
		INCR	46H,1 			//03FE 	09C6
		LJUMP 	3F2H 			//03FF 	3BF2
			END
