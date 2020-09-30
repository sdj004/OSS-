/*
 * buzzer.h
 *
 * Created: 2019-12-19 오전 10:50:31
 *  Author: kimy0
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_

void delay_us_Melody(int data);
void Sound(unsigned int ch, unsigned int time);


void S_Start();
void S_Ending();
void S_Pass();
void S_Fail();



#endif /* BUZZER_H_ */