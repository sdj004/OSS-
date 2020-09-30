/*
 * event.c
 *
 * Created: 2019-12-19 오전 12:55:43
 *  Author: kimy0
 */ 

#include "_main.h"
#include "sensor.h"
#include "_glcd2.h"


int catching(int flag){
	flag=0;
	int x_after,x_before,y_after,y_before,z_after,z_before;
	ScreenBuffer_clear();
	lcd_clear();
	lcd_string(4,2,"Throw fishing rod");
	acc(&x_before, &y_before,&z_before);
	
	for(int i=1;i<=5;i++)
	{
		_delay_ms(500);
		lcd_xy(7,8);
		GLCD_1DigitDecimal(i,1);
	}
	acc(&x_after, &y_after,&z_after);
	_delay_ms(1000);
	lcd_clear();
	
	if(y_before-y_after > 30){
		flag = 1;
		}else{
		flag = 0;
	}

	return flag;
}

