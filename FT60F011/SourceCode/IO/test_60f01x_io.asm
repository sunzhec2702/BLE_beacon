//Deviec:FT60F01X
//-----------------------Variable---------------------------------
//-----------------------Variable END---------------------------------
		ORG		0000H
		LJUMP 	3CAH 			//0000 	3BCA
		ORG		03CAH
		CLRR 	STATUS 			//03CA 	0103
		LJUMP 	3D5H 			//03CB 	3BD5
		STR 	40H 			//03CC 	01C0

		//;test_60f01x_io.c: 77: unsigned char a;
		//;test_60f01x_io.c: 78: for(a=0;a<Time;a++)
		CLRR 	41H 			//03CD 	0141
		LDR 	40H,0 			//03CE 	0840
		SUBWR 	41H,0 			//03CF 	0C41
		BTSC 	STATUS,0 		//03D0 	1403
		RET		 					//03D1 	0004

		//;test_60f01x_io.c: 79: {
		//;test_60f01x_io.c: 80: _nop();
		NOP		 					//03D2 	0000
		INCR	41H,1 			//03D3 	09C1
		LJUMP 	3CEH 			//03D4 	3BCE

		//;test_60f01x_io.c: 125: POWER_INITIAL();
		LCALL 	3E0H 			//03D5 	33E0
		LDWI 	AH 			//03D6 	2A0A

		//;test_60f01x_io.c: 127: {
		//;test_60f01x_io.c: 128: RA4 = 1;
		BCR 	STATUS,5 		//03D7 	1283
		BSR 	5H,4 			//03D8 	1A05

		//;test_60f01x_io.c: 129: DelayMs(10);
		LCALL 	3F0H 			//03D9 	33F0

		//;test_60f01x_io.c: 130: if(RA2 == 1)
		BCR 	STATUS,5 		//03DA 	1283
		BTSC 	5H,2 			//03DB 	1505

		//;test_60f01x_io.c: 131: {
		//;test_60f01x_io.c: 132: RA4 = 0;
		BCR 	5H,4 			//03DC 	1205

		//;test_60f01x_io.c: 133: }
		//;test_60f01x_io.c: 134: DelayMs(10);
		LDWI 	AH 			//03DD 	2A0A
		LCALL 	3F0H 			//03DE 	33F0
		LJUMP 	3D6H 			//03DF 	3BD6

		//;test_60f01x_io.c: 47: OSCCON = 0X00|0X70|0X01;
		LDWI 	71H 			//03E0 	2A71
		BSR 	STATUS,5 		//03E1 	1A83
		STR 	FH 			//03E2 	018F

		//;test_60f01x_io.c: 52: INTCON = 0;
		CLRR 	INTCON 			//03E3 	010B

		//;test_60f01x_io.c: 53: PORTA = 0B00000000;
		BCR 	STATUS,5 		//03E4 	1283
		CLRR 	5H 			//03E5 	0105

		//;test_60f01x_io.c: 54: TRISA = 0B11101111;
		LDWI 	EFH 			//03E6 	2AEF
		BSR 	STATUS,5 		//03E7 	1A83
		STR 	5H 			//03E8 	0185

		//;test_60f01x_io.c: 56: WPUA = 0B00000100;
		LDWI 	4H 			//03E9 	2A04
		STR 	15H 			//03EA 	0195

		//;test_60f01x_io.c: 59: OPTION = 0B00001000;
		LDWI 	8H 			//03EB 	2A08
		STR 	1H 			//03EC 	0181
		BCR 	STATUS,5 		//03ED 	1283
		CLRR 	1BH 			//03EE 	011B
		RET		 					//03EF 	0004
		STR 	42H 			//03F0 	01C2

		//;test_60f01x_io.c: 91: unsigned char a,b;
		//;test_60f01x_io.c: 92: for(a=0;a<Time;a++)
		CLRR 	43H 			//03F1 	0143
		LDR 	42H,0 			//03F2 	0842
		SUBWR 	43H,0 			//03F3 	0C43
		BTSC 	STATUS,0 		//03F4 	1403
		RET		 					//03F5 	0004

		//;test_60f01x_io.c: 93: {
		//;test_60f01x_io.c: 94: for(b=0;b<5;b++)
		CLRR 	44H 			//03F6 	0144

		//;test_60f01x_io.c: 95: {
		//;test_60f01x_io.c: 96: DelayUs(98);
		LDWI 	62H 			//03F7 	2A62
		LCALL 	3CCH 			//03F8 	33CC
		LDWI 	5H 			//03F9 	2A05
		INCR	44H,1 			//03FA 	09C4
		SUBWR 	44H,0 			//03FB 	0C44
		BTSS 	STATUS,0 		//03FC 	1C03
		LJUMP 	3F7H 			//03FD 	3BF7
		INCR	43H,1 			//03FE 	09C3
		LJUMP 	3F2H 			//03FF 	3BF2
			END
