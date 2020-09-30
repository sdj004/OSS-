/*
 * buzzer.c
 *
 * Created: 2019-12-19 오전 10:50:42
 *  Author: kimy0
 */ 

 #include <avr/io.h>
 #define F_CPU 16000000UL
 #include <util/delay.h>
 #include <avr/interrupt.h>
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>

 #include "_main.h"
 #include "buzzer.h"

 #define    LDo        395
 #define    LRe        354
 #define    LMi        316
 #define    LFa        298
 #define    LSo        266
 #define    LLa        237
 #define    LSi        212

 #define    BDo        200
 #define    BRe        178
 #define    BMi        159
 #define    BFa        150
 #define    BSo        134
 #define    BLa        112
 #define    BSi        107

 #define    HDo        101
 #define    HRe        90
 #define    HMi        80
 #define    HFa        76
 #define    HSo        68
 #define    HLa        61
 #define    HSi        54

 #define    hDo        51
 #define    RB        50
 #define    LB        65
 #define    SB        30
 #define    BB        35

 #define     Buzzer_Port     PORTG
 #define     Buzzer_Pin      4
 #define     MelOn    SETBIT(Buzzer_Port, Buzzer_Pin)
 #define     MelOff   CLEARBIT(Buzzer_Port, Buzzer_Pin)

 void delay_us_Melody(int data)
 {	int i;	for(i=0;i<data;i++)	{		_delay_us(1);	}}

 void Sound(unsigned int ch, unsigned int time)
 {
	 unsigned int tim;
	 tim=ch;
	 tim=tim*1000/time;
	 while(tim--)
	 {
		 MelOn;
		 delay_us_Melody(time);
		 MelOff;
		 delay_us_Melody(time);
	 }

 }
 
 void S_Start(){
	 Sound(BB, BRe);
	 Sound(BB, BSo);
	 Sound(BB, BSo);
	 delay_us_Melody(200);
	 Sound(BB, BRe);
	 Sound(BB, BSo);
	 Sound(BB, BSo);
	 delay_us_Melody(200);	 
	 Sound(BB, BSo);
	 Sound(BB, BRe);
	 Sound(BB, BSo);
	 Sound(BB, BSi);
	 Sound(BB, HRe);
	 Sound(BB, BSi);
	 delay_us_Melody(200);	 
	 Sound(BB, HRe);	 
	 Sound(BB, BSi);	   
	 Sound(BB, BSi);	 
	 delay_us_Melody(200);	 
	 Sound(BB, HDo);
	 Sound(BB, BLa);
	 Sound(BB, BLa);
	 delay_us_Melody(200);	 
	 Sound(BB, BSo);	
	 Sound(BB, BSi);
	 Sound(BB, BSi);	
	 Sound(BB, BLa);
	 Sound(BB, BSo);	 
	 Sound(BB, BRe);
	 delay_us_Melody(200);	 
	 Sound(BB, BRe);
	 Sound(BB, BSo);
	 Sound(BB, BSo);
	 delay_us_Melody(200);	 
	 Sound(BB, BRe);
	 Sound(BB, BSo);
	 Sound(BB, BSo);
	 delay_us_Melody(200);	 
	 Sound(BB, BSo);
	 Sound(BB, BRe);
	 Sound(BB, BSo);
	 Sound(BB, BSi);
	 Sound(BB, HRe);
	 Sound(BB, BSi);
	 delay_us_Melody(200);	 
	 Sound(BB, HRe);
	 Sound(BB, HDo);
	 Sound(BB, BSi);
	 Sound(BB, BLa);
	 Sound(BB, BSo);
	 Sound(BB, BFa);
	 Sound(BB, BMi);
	 Sound(BB, BRe);
	 Sound(BB, BMi);	 	 
	 Sound(BB, BFa);	
	 Sound(BB, BSo);
	 _delay_ms(1000);	  	 	   
 }
 
 void S_Ending(){
	 Sound(BB, BRe);
	 Sound(BB, BRe);
	 Sound(BB, BMi);
	 Sound(BB, BRe);
	 Sound(BB, BSo);
	 Sound(BB, BSo);
_delay_ms(200);
	 Sound(BB, BRe);
	 Sound(BB, BRe);
	 Sound(BB, BMi);
	 Sound(BB, BRe);
	 Sound(BB, BLa);
	 Sound(BB, BLa);
	 Sound(BB, BSo);
_delay_ms(200);
	 Sound(BB, BRe);
	 Sound(BB, BRe);
	 Sound(BB, HRe);
	 Sound(BB, BSi);
	 Sound(BB, BSo);
	 Sound(BB, BFa);
	 Sound(BB, BMi);
	 
	 Sound(BB, HDo);
	 Sound(BB, HDo);
		 Sound(BB, BSi);
 	 Sound(BB, BSo);
	 Sound(BB, BLa);
	 Sound(BB, BLa);
	 Sound(BB, BSo);

	 
 }
 
 
 void S_Pass(){
	 Sound(BB, HDo);
	 Sound(BB, HDo);
 }
 
 void S_Fail(){
	 Sound(BB, LDo);
	 Sound(BB, LDo);
 }