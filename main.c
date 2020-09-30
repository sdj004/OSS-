/*
 * 12154893.c
 *
 * Created: 2019-12-18 오후 2:23:42
 * Author : kimy0
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "_glcd2.h"
#include "_main.h"
#include "sensor.h"
#include "bitmap_map.h"

#include "bitmap_char.h"
#include "bitmap_fish.h"
#include "event.h"
#include "buzzer.h"

//전역변수
static int switch_flag =0;
static int flag=0;
static int flag2 =0;
static int move=0;
static int ending_count = 0;

const unsigned char *main_char[4] = {main_char_back,main_char_front,main_char_left,main_char_right};	
const unsigned char *field_map[1] = {field_map1};
const unsigned char *intro[7] = {intro_1,intro_2,intro_3,intro_4, intro_5, intro_6, intro_7};
const unsigned char *fish_char[6] = {fish_0, fish_1, fish_2, fish_3, fish_4, fish_5};
const unsigned char *Lsea[2] = {Lsea_map1, Lsea_map2};
const unsigned char *Rsea[2] = {Rsea_map1, Rsea_map2};
const unsigned char *Beyoung[8] = {beyoung1,beyoung2,beyoung3,beyoung4,beyoung5,beyoung6,beyoung7,beyoung8};
const char *fish_name[] ={"Goldfish", "Flatfish", "Crawfish", "Jellyfish", "Snail", "Pufferfish"};
static int check_fish[14] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	
//함수 선언
int battle_page(int enemy_count);
int map_change(int *x_char, int *y_char,int battle_flag);
void glcd_char(int *x_char, int *y_char);
int location_check(int *x_char,int *y_char,int enemy_count);
void battle_end(int battle_flag,int enemy_count);
void fishing(int *x_char, int *y_char);
void ending();

//ISR
SIGNAL(INT0_vect) {	switch_flag =1;}

int main(void)
{
	//지역변수
	int x_char,y_char;

	init_devices();
	Interrupt_init();
	lcd_clear();
	ScreenBuffer_clear();

	x_char = 40;
	y_char = 40;

	while(1){ //처음 시작
		S_Start();
		lcd_string(7,0," ... wait ..");
		
		for(int i =0;i<6;i++){
			glcd_draw_bitmap(intro[i],0,0,64,128); // 비룡이 일화 설명
			lcd_string(7,0,"PRESS START BUTTON 0");
			if(i==0) {
				_delay_ms(100);
			}
			else {
				_delay_ms(1000);
			}
		}
		if(switch_flag){switch_flag=0;break;}
	}
	//게임 시작
	glcd_draw_bitmap(field_map[0],0,0,64,128);
	while(1){
		glcd_char(&x_char,&y_char);
		_delay_ms(10);
		if(switch_flag){
			flag = catching(flag); //낚시대 던지기
			
			ScreenBuffer_clear();
			lcd_clear();
			
			if(flag == 1){ //낚시 시작
				PORTB = 0xff;
				lcd_string(7,4,"fishing START");
				_delay_ms(1000);
				fishing(&x_char, &y_char);
				
				if(flag2 == 1){ //낚시 성공 시 랜덤으로 보여주기
						lcd_clear();
						int n = rand() % 15; //0~14
						
						while(check_fish[n] == 1){ // 뜬 건 다시 안 뜨게
							n = rand() % 15;
						}
						
						if(n<6){
							//0~5 물고기
							glcd_draw_bitmap(fish_char[n], 0,40,56,56);
							lcd_string(7,6, fish_name[n]);

						}else{
							//비룡이 조각 
							glcd_draw_bitmap(Beyoung[n-6], 0,0,64,128);
							lcd_string(7,4, " Lucky!!!! ");
							
							check_fish[n]=1;
							ending_count++;
							
						}
						_delay_ms(2500);
						lcd_clear();
						
						
					}
			}else{
				lcd_string(7,4,"FAIL");
			}
			
			if(ending_count == 8){
				PORTB = 0x00;
				break;
			}else{
				glcd_draw_bitmap(field_map[0],0,0,64,128);
				PORTB = 0xff;
				led_port(ending_count); //포트 불 끄기 비룡이 조각을 모으면 켜져야함
				switch_flag=0;
			}

		}
		
		if(ending_count == 8){
			break;
		}
	}
	lcd_clear();
	glcd_draw_bitmap(intro[6],0,0,64,128);
	lcd_string(7,0,"happy ending");
	while(1){
			S_Ending();
			for(int j=0; j<9;j++){
				led_port(j);
				_delay_ms(500);					
			}		
		}
	
	
}

void glcd_char(int *x_char, int *y_char){
	glcd_draw_bitmap(main_char[move],*x_char,*y_char,16,16);
	move = joystick_move_char(x_char,y_char);
}

void fishing(int *x_char, int *y_char){
	flag2 = 0;
	int suc = 0;
	int cnt=0;
	int move;

	//10번만 낚시
	while(flag2 == 0 && cnt <10){

		int pos = rand()%2; //왼쪽 오른쪽
		int ran = rand()%2; //랜덤 그림
		
		if(pos==0){
			glcd_draw_bitmap(Rsea[ran],0,0,64,128);
			lcd_string(7,4," >> Right!! >> ");
			_delay_ms(500);
			move = joystick_move_char(x_char, y_char);
			if(move == 3){
				S_Pass();
				suc++;
				led_port(suc);
			}else S_Fail();
		}else{
			glcd_draw_bitmap(Lsea[ran],0,0,64,128);
			lcd_string(7,6," << Left!! << ");
			_delay_ms(500);
			move = joystick_move_char(x_char, y_char);
			if(move == 2){
				suc++;
				led_port(suc);
				S_Pass();
			}else S_Fail();			
		}
		_delay_ms(1500);
		lcd_clear();
		cnt++;
		if(suc == 8) {
			flag2=1;
			lcd_string(7,6,"Success!!!!");
			_delay_ms(500);
			break;
		}
	}
	
}
