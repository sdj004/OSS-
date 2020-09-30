
 #define F_CPU 16000000UL
 #include <util/delay.h>
 #include <avr/interrupt.h>
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include <avr/io.h>
 #include "_glcd2.h"
 #include "_main.h"		

 unsigned int Data_ADC3 = 0;		//조이스틱 상하 값
 unsigned int Data_ADC4 = 1;		//조이스틱 좌우 값
 unsigned int Data_ADC5 = 0;
 unsigned int Data_ADC6 = 0;
 unsigned int Data_ADC7 = 0;

 #define ADC_VREF_TYPE 0x00		//사용기준전압 REFS
 #define ADC_AVCC_TYPE 0x40		//사용기준전압 AVCC
 #define ADC_RES_TYPE 0x80		//사용기준전압 RES
 #define ADC_2_56_TYPE 0xc0		//사용기준전압 2.56
 
 char Dis_Scr_IO_ON[]={"O"};
 char Dis_Scr_IO_OFF[]={"X"};
 char Dis_Scr1[]={"#$%&'()*+,-./0123456"};
 char Dis_Scr2[]={"789:;<=>?@ABCDEFGHIJ"};
 char Dis_Scr3[]={"KLMNOPQRSTUVWXYZ[]{}"};
 
 unsigned int Read_Adc_Data(unsigned char adc_input){	
	 unsigned int adc = 0;
	 ADCSRA = 0xC3;	
	 ADMUX = adc_input | ADC_AVCC_TYPE;
	 ADCSRA |= 0x40;
	 while((ADCSRA & 0x10) != 0x10);
	 adc += ADCL+ (ADCH * 256);
	 ADCSRA = 0x00;
	 return adc;
 }

 void LCD_Decimal(unsigned char num, short AD_dat){
	 unsigned char Decimal[5];
	 Decimal[4] = AD_dat / 10000;	//1000 자리 아스키 값 저장
	 AD_dat %= 10000;	//나머지 값 저장
	 Decimal[3] = AD_dat / 1000;	//1000 자리 아스키 값 저장
	 AD_dat %= 1000;	//나머지 값 저장
	 Decimal[2] = AD_dat / 1000;	//1000 자리 아스키 값 저장
	 AD_dat %= 100;	//나머지 값 저장
	 Decimal[1] = AD_dat / 10;	//1000 자리 아스키 값 저장
	 AD_dat %= 10;	//나머지 값 저장
	 Decimal[0] = AD_dat;	//1000 자리 아스키 값 저장
	 
	 if(num==0){ //data_ad3 변환
		 lcd_xy(5,11); GLCD_1DigitDecimal(Decimal[4],1);		//10000자리 출력
		 lcd_string(5,12,".");
		 lcd_xy(5,13); GLCD_1DigitDecimal(Decimal[3],1);		//1000자리 출력
		 lcd_xy(5,14); GLCD_1DigitDecimal(Decimal[2],1);		//100자리 출력
		 lcd_xy(5,15); GLCD_1DigitDecimal(Decimal[1],1);		//10자리 출력
		 lcd_xy(5,16); GLCD_1DigitDecimal(Decimal[0],1);		//1자리 출력
		 lcd_xy(5,11); GLCD_1DigitDecimal(Decimal[4],1);		//10000자리 출력
	 }
	 if(num==1){ //data_ad3 변환
		 lcd_xy(7,11); GLCD_1DigitDecimal(Decimal[4],1);		//10000자리 출력
		 lcd_string(7,12,".");
		 lcd_xy(7,13); GLCD_1DigitDecimal(Decimal[3],1);		//1000자리 출력
		 lcd_xy(7,14); GLCD_1DigitDecimal(Decimal[2],1);		//100자리 출력
		 lcd_xy(7,15); GLCD_1DigitDecimal(Decimal[1],1);		//10자리 출력
		 lcd_xy(7,16); GLCD_1DigitDecimal(Decimal[0],1);		//1자리 출력
		 lcd_xy(7,11); GLCD_1DigitDecimal(Decimal[4],1);		//10000자리 출력
	 }
 }

 void acc(int *x,int *y,int *z){
	 
		 Data_ADC5 = Read_Adc_Data(5)-352+32;		// 아날로그 5번 포트 읽기
		 Data_ADC6 = Read_Adc_Data(6)-358+62;		// 아날로그 6번 포트 읽기
		 Data_ADC7 = Read_Adc_Data(7);				// 아날로그 7번 포트 읽기
 
		 _delay_ms(500);
 
		*x=Data_ADC5;
		*y=Data_ADC6;
		*z=Data_ADC7;

}

 int joystick_move_char(int *x_char,int *y_char){

	 int flag, xtmp, ytmp;
	 flag = -1;
	 xtmp =*x_char;
	 ytmp =*y_char;
	 Data_ADC3 = Read_Adc_Data(3) / 14;	//3번포트 읽기
	 Data_ADC4 = Read_Adc_Data(4) / 8;	//4번 포트 읽기
	 _delay_ms(30);
	 
	 if(Data_ADC3 < 20){	//Up
		 flag =0;
		 _delay_ms(10);
	 }
	 else if(Data_ADC3 > 50){	//Down
		flag =1;
		 _delay_ms(10);
		 }else if(Data_ADC4 > 90){	//Left
		flag =2;	 
		 _delay_ms(10);
	 }
	 else if(Data_ADC4 < 20){	//Right
		 flag=3;
		 _delay_ms(10);
	}
	switch(flag){
	case 0:*x_char =xtmp-1;return 0;break;
	case 1:*x_char =xtmp+1;return 1;break;
	case 2:*y_char =ytmp-1;return 2;break;
	case 3:*y_char =ytmp+1;return 3;break;
	default:return 0;break;
	}
 }
 
 void Port_init(void){
	 PORTA=0x00; DDRA=0xff;
	 PORTB=0xff; DDRB=0xff;
	 PORTC=0x00; DDRC=0xf0;
	 PORTD=0xff; DDRD=0x00;
	 PORTE=0x00; DDRE=0xff;
	 PORTF=0x00; DDRF=0x00;
 }
 
 void ADC_init(){
	 ADCSRA = 0x00; 
	 ADMUX = 0x00;	
	 ACSR = 0x80;
	 ADCSRA = 0xC3;
 }

 void init_devices(void){
	 cli();
	 Port_init();
	 ADC_init();
	 lcd_init();
	 sei();
 }

 void Interrupt_init(void) {
	 EICRA = 0xFF;
	 EIMSK = 0x0F;	//INT0~3번 사용
	 DDRD = 0x00;
}

 void led_port(int i){
	int option[]={0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff};
	PORTB &=~option[i];
}
