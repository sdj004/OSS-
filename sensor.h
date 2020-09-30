
#ifndef SENSOR_H_
#define SENSOR_H_

unsigned int Read_Adc_Data(unsigned char adc_input);
void LCD_Decimal(unsigned char num, short AD_dat);
int joystick_move_char(int *x_char,int *y_char); 
void ADC_init(void);
void Port_init(void);
void init_devices(void);
void Interrupt_init(void) ;
void acc(int *x,int *y,int *z);
void led_port(int i);
#endif /* SENSOR_H_ */