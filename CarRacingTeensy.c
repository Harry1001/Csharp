#include <stdint.h>
#include <stdio.h>
#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>
#include <cpu_speed.h>
#include <graphics.h>
#include <macros.h>
#include <lcd_model.h>
#include <math.h>
#include "sprite.h"
#include "lcd.h"
#include <stdlib.h>
#include<assert.h>
#include <stdbool.h>
#include "cab202_adc.h"


#define BIT(x) (1 << (x))
#define OVERFLOW_TOP (1023)
#define ADC_MAX (1023)

#define X1_ROAD 25
#define X2_ROAD 57

#define YUP_ROAD 10
#define YLW_ROAD 48

#define THRESHOLD 512


#define W_CAR 8
#define H_CAR 11

#define W_FUEL_DEPOT 8
#define H_FUEL_DEPOT 11


#define W_HOUSE 9
#define H_HOUSE 10

#define W_TREE 8
#define H_TREE 8

#define W_OBSTACLE 7
#define H_OBSTACLE 6

#define NUM_OF_TREES (3)
#define NUM_OF_HOUSE (3)

#define NUM_OF_FUEL_DEPOT (2)
#define NUM_OF_OBSTACLES (2)

bool game_over  = false;

bool dont_play_again = false;
Sprite tree[NUM_OF_TREES];
Sprite house[NUM_OF_HOUSE ];


int curve_road_x1;
int curve_road_x2;
Sprite obstacle[NUM_OF_OBSTACLES];
Sprite fuel_depot;
bool play_again = false;

Sprite car;
double distance = 0;
bool collided_with_fuel = false;

float x_car = 38;
float y_car = 35;
double speed = 0;
double fuel = 10;
double time = 0;
int condition = 100;


void create_car(void);


uint8_t car_bitmap[] = {
	0b00111100,
	0b01111110,
	0b01000010,
	0b01000010,
	0b10100101,
	0b00100100,
	0b00100100,
	0b01100110,
	0b01000010,
	0b01111110,
	0b00111100
};

uint8_t house_bitmap[] = {
	0b00001000, 0b00000000,
	0b00010100, 0b00000000,
	0b00100010, 0b00000000,
	0b01000001, 0b00000000,
	0b11000001, 0b10000000,
	0b01011101, 0b00000000,
	0b01010101, 0b00000000,
	0b01011101, 0b00000000,
	0b01000001, 0b00000000,
	0b01111111, 0b00000000,
	
};

uint8_t fuel_bitmap[] = {
	0b11111111,
	0b10000001,
	0b10111101,
	0b10100001,
	0b10100001,
	0b10111101,
	0b10100001,
	0b10100001,
	0b10100001,
	0b10000001,
	0b11111111
};

uint8_t tree_bitmap[] = {
	0b00011000,
	0b00100100,
	0b01000010,
	0b10000001,
	0b00011000,
	0b00011000,
	0b00011000,
	0b00011000
};


uint8_t obstacle_bitmap[] = {
	0b1000011,
	0b0111110,
	0b0011100,
	0b0011100,
	0b0011100,
	0b0100010,
	
};

int button_presssed = 0;


const unsigned char microsoft [] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf0, 0xf0, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf0, 0xf0, 0xf0, 0xf0, 0x60, 0x00, 0x00, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xb0, 0xbc, 0xbf, 0xbf, 0xbf, 0xbf, 0x9f, 0xdf, 0xdf, 0x9f, 0x9f, 0x9f, 0xbf, 0xbf, 0xbf, 0x3f, 0x3f, 0x7f, 0x7f, 0x1f, 0x07, 0xc1, 0xf0, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf0, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x0f, 0xc3, 0xf0, 0xfc, 0xfe, 0xfc, 0xfd, 0xf9, 0xf9, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0x3d, 0x0d, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x01, 0x00, 0x0c, 0x0f, 0x0f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x0f, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};


char buffer[15];

uint8_t screen_buffer[LCD_BUFFER_SIZE];

void display_data_on_screen(){
lcd_position(0, 0);

	// Iterate through our buffer and write each byte to the LCD.
	for ( int i = 0; i < LCD_BUFFER_SIZE; i++ ) {
		lcd_write(LCD_D, screen_buffer[i]);
	}
}

void set_duty_cycle(int duty_cycle) {
	// (a)	Set bits 8 and 9 of Output Compare Register 4A.
	TC4H = duty_cycle >> 8;

	// (b)	Set bits 0..7 of Output Compare Register 4A.
	OCR4A = duty_cycle & 0xff;
}

void draw_double(uint8_t x, uint8_t y, double variables) {
	snprintf( buffer, 15, "%.2f", variables );
	draw_string( x, y, buffer, FG_COLOUR );
}

bool button_clicked = false;


void spalsh_screen(){
	clear_screen();
	
	draw_string( 0, 0, "Car Race", FG_COLOUR );
    draw_string( 0, 8, "Harmanjeet Singh",FG_COLOUR );
    draw_string( 0, 16, "N9920811", FG_COLOUR );
	draw_string( 0, 24, "Turn Left: L SW1", FG_COLOUR );
	draw_string( 0, 32, "Turn Right: R SW2", FG_COLOUR );
	 draw_string( 0, 40, "Pause Game - SW3", FG_COLOUR );
//	  draw_string( 0, 40, "by pressing SW3", FG_COLOUR );
	
	
	show_screen();
}


void draw_int(uint8_t x, uint8_t y, int variables) {
	snprintf( buffer, 15, "%d", variables );
	draw_string( x, y, buffer, FG_COLOUR );
}



/*volatile int overflow_counter0 = 0;
double timer0(){
	double time0 = (overflow_counter0 * 256.0 + TCNT0) * 1024.0 / 8000000.0;
	return time0;
}*/


void calculate_distance(){
	distance = distance + (time * speed * 0.02);
}


volatile uint32_t overflow_count = 0;
	ISR(TIMER1_OVF_vect) {

		overflow_count++;

	}

	
//Check if car collides with other object
bool collided (Sprite *sprite1, Sprite *sprite2 ) {
	
	int th = round(sprite1->y);
	
	
	int lh = round(sprite1->x);
	
	
	int rh = lh + sprite1->width ;
	
	
	int bh = th + sprite1->height;
	

	int tz = round(sprite2->y);
	
	
	int lz = round(sprite2->x);
	
	
	int rz = lz + sprite2->width ;
	

	int bz = tz + sprite2->height ;
	
	if ( tz > bh ) return false;
	if ( th > bz ) return false;
	if ( lh > rz ) return false;
	if ( lz > rh ) return false;
	
	
	return true;
}

double get_elapsed_time(void) {

		double total_time = (overflow_count * 65536.0 + TCNT1) * 256.0 / 8000000 ;
		return total_time ;

	}
	
void fuel_consumption(){
	
	fuel = fuel - (0.005 * speed);
}


void draw_curve_road(){
	
	/*int distance1 = distance;
	if(speed == 0){
		distance1 = 0;*/
		
		int value1 = 7;
		int value2 = 15;
		double value3 = 0.1;
		int Xroad1Excess = 30;
		int Xroad2Excess = 60;
		
		for ( double i=10; i<LCD_Y; i++ ){
				//double y =3.14;

				//double rleft= sin(y+ distance);
				double p = value1*sin ((i/value2)+distance*value3)+Xroad1Excess;
				double q = value1*sin ((i/value2)+distance*value3)+Xroad2Excess;
				draw_pixel ((int )p,(int)i,FG_COLOUR);
				draw_pixel ((int )q,(int)i,FG_COLOUR);
				curve_road_x1 = round(p);
				curve_road_x2 = round(q);
				
				
				//show_screen();
		}
	
}
	
//double timeX = 0;
void fill_fuel_if_parked(){
	//timeX += timer0() ;
	
	if(((fuel_depot.y >= car.y - 10) || (fuel_depot.y < car.y + 10) ) && abs(fuel_depot.x - car.x) <= 10){
	//	TCCR0B = 5;
		//if(timeX >= 3){
			fuel = 10;
		//}else if((timeX<=2 && timeX>=1.5) && fuel < 5)
			fuel = 5;
		//else if((timeX>=0.8 && timeX<=1.4) && fuel < 3)
			fuel=3;
		//else 
			if(fuel < 2)	
			fuel = 2;
		//}
			
		
		fuel = 10;
	}
	//TCCR0B = 0;
	
}
	
	
void dashboard(){
	//clear_screen();
	time = get_elapsed_time();
	calculate_distance();
	//double time = get_current_time();
	draw_int( 10, 0, speed );
	
	draw_int( 68, 0, fuel );
	draw_string(0,0,"S:",FG_COLOUR);
	//draw_formatted(0,0, "Spd: %d", speed);
	draw_string(25,0,"C:",FG_COLOUR);
	draw_int(35, 0, condition);
	draw_string(56,0,"F:",FG_COLOUR);
	draw_line(0,10, 90,10, '*'); 
	
	
	//d bshow_screen();
}


void draw_road(){
	draw_line(X1_ROAD,YUP_ROAD, X1_ROAD,YLW_ROAD, '*');
	draw_line(X2_ROAD,YUP_ROAD,X2_ROAD, YLW_ROAD, '*');
}

void create_car(){
	//int x = rand() % (_X - W);
	//int y = rand() % (LCD_Y - H);
	sprite_init(&car, x_car, y_car, W_CAR, H_CAR, car_bitmap);
}
void draw_car(){
	sprite_draw(&car);
	
}
void create_house(){
	//int x = rand() % (_X - W);
	//int y = rand() % (LCD_Y - H);
	for(int index = 0; index < NUM_OF_HOUSE ; index++)
	{
		int x = rand() %  (LCD_X) ;
	    int y = (rand() + H_HOUSE + 4) %  (LCD_Y - H_HOUSE) ;
		
		while(x + W_HOUSE > X1_ROAD && x < X2_ROAD + W_HOUSE){
			x = rand() % (LCD_X - W_HOUSE);
		}
		sprite_init(&house[index], x, y, W_HOUSE, H_HOUSE, house_bitmap);
		
	}
	
}

void create_obstacle(){
	//int x = rand() % (_X - W);
	//int y = rand() % (LCD_Y - H);
	for(int index = 0; index < NUM_OF_OBSTACLES ; index++)
	{
		//int x = rand()  %  (LCD_X - W_OBSTACLE) ;
		int x = (rand() + X1_ROAD + 17) %  (X2_ROAD );
	    int y = (rand() + H_OBSTACLE+ 8) %  (LCD_Y - H_OBSTACLE) ;
		
		/*while(x  < X1_ROAD + 5  && x > X2_ROAD){
			
			x = rand() % (LCD_X - W_OBSTACLE);
		}*/
		sprite_init(&obstacle[index], x, y, W_OBSTACLE, H_OBSTACLE, obstacle_bitmap);
		
	
	}
	
}


void create_trees(){
	//int x = rand() % (_X - W);
	//int y = rand() % (LCD_Y - H);
	for(int index = 0; index < NUM_OF_TREES ; index++)
	{
		int x = rand() %  (LCD_X) ;
	    int y = (rand() + 13 + H_TREE + 27) %  (LCD_Y - H_TREE) ;
		
		while(x + W_TREE > X1_ROAD && x < X2_ROAD){
			x = rand() % (LCD_X - W_TREE);
		}
		sprite_init(&tree[index], x, y, W_TREE, H_TREE, tree_bitmap);
		
	}
	
}

void draw_obstacles(){
	for(int index = 0; index < NUM_OF_OBSTACLES; index++){
		
		sprite_draw(&obstacle[index]);
	}
	
	
	
}


void draw_trees(){
	for(int index = 0; index < NUM_OF_TREES; index++){
		
		sprite_draw(&tree[index]);
	}
	
	
}

void create_fuel_depot(){
	
		int get_road_side = (rand() % 2);
		if(get_road_side == 1){
			
			sprite_init(&fuel_depot, X1_ROAD - 2*W_HOUSE, 15, W_FUEL_DEPOT, H_FUEL_DEPOT, fuel_bitmap);
		}
		else{
			sprite_init(&fuel_depot, X2_ROAD + 10, 10, W_FUEL_DEPOT, H_FUEL_DEPOT, fuel_bitmap);
		}
		
	
	
	
}
void draw_fuel_depot(){
	
		sprite_draw(&fuel_depot);
	
	
}


bool sprite_move_to( Sprite *sprite, double x, double y ) {
	assert( sprite != NULL );
	int x0 = round( sprite->x +1 );
	int y0 = round( sprite->y );
	sprite->x = x;
	sprite->y = y;
	int x1 = round( sprite->x + 1 );
	int y1 = round( sprite->y );
	return ( x1 != x0 ) || ( y1 != y0 );
}
	
	

void draw_house(){
	for(int index = 0; index < NUM_OF_HOUSE * 2; index++){
		
		sprite_draw(&house[index]);
	}
	
	
	
}

void move_car(sprite_id car, int x){

	int current_x_car = car->x;
	if(x == 1){										
		if(current_x_car < 76)
		
		car->x = car->x + ( 1 * speed);
	}
		
	else{
		if(current_x_car > 0)
		car->x = car->x - ( 1 * speed);
		
	}
	//show_screen();
	
}


/*void decrease_speed_if_offroad(sprite_id car){
	
	if(car->x < 20 || car->x > 56){
		if(speed > 3){
			speed = 3;
		}else if((right_adc > THRESHOLD))
			speed = speed + 0.03;
		//if(speed < 3){
			//speed = speed + 0.1;
		//}//
	}
}*/
void adc_init() {
	// ADC Enable and pre-scaler of 128: ref table 24-5 in datasheet
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t adc_read(uint8_t channel) {
	// Select AVcc voltage reference and pin combination.
	// Low 5 bits of channel spec go in ADMUX(MUX4:0)
	// 5th bit of channel spec goes in ADCSRB(MUX5).
	ADMUX = (channel & ((1 << 5) - 1)) | (1 << REFS0);
	ADCSRB = (channel & (1 << 5));

	// Start single conversion by setting ADSC bit in ADCSRA
	ADCSRA |= (1 << ADSC);

	// Wait for ADSC bit to clear, signalling conversion complete.
	while ( ADCSRA & (1 << ADSC) ) {}

	// Result now available.
	return ADC;
}

void setup(void) {
	SET_BIT(PORTC, 7);
	set_clock_speed(CPU_8MHz);
	lcd_init(72);
	
	CLEAR_BIT(DDRB, 0);
	CLEAR_BIT(DDRB, 1);
	CLEAR_BIT(DDRD, 0);
	CLEAR_BIT(DDRF, 5);
	CLEAR_BIT(DDRF, 6);
	
	create_car();
	create_house();
	create_fuel_depot();
	create_trees();
	create_obstacle();
	
	//ACD implement
	adc_init();
	SET_BIT(DDRB, 2);
	SET_BIT(DDRB, 3);
	
	 TCCR1A = 0;

	  TCCR1B = 0;





	//	(b) Enable timer overflow for Timer 1.

		 TIMSK1 = 1;
		 
		
	 

	//Debouncing
	TCCR0A = 0;
	TCCR0B = 4; 
	
	//	(b) Enable timer overflow interrupt for Timer 0.
	TIMSK0 = 1;
	
	 sei();
	//CLEAR_BIT(DDRB, 0);
	
	
	////////////////// PWM
	//		yielding a cycle of 1024 ticks per overflow.
	TC4H = OVERFLOW_TOP >> 8;
	OCR4C = OVERFLOW_TOP & 0xff;

	// (b)	Use OC4A for PWM. Remember to set DDR for C7.
	TCCR4A = BIT(COM4A1) | BIT(PWM4A);
	SET_BIT(DDRC, 7);

	// (c)	Set pre-scale to "no pre-scale" 
	TCCR4B = BIT(CS42) | BIT(CS41) | BIT(CS40);

	// (c.1) If you must adjust TCCR4C, be surgical. If you clear
	//		bits COM4A1 and COM4A0 you will _disable_ PWM on OC4A, 
	//		because the COM4Ax and COM4Bx hardware pins appear in
	//		both TCCR4A and TCCR4C!

	/* In this example, TCCR4C is not needed */

	// (d)	Select Fast PWM
	TCCR4D = 0;
}


void over_game(){
	while(!button_clicked){
		clear_screen();
		//check if won or lose
		
		if(distance >=300){
		draw_string( 0, 0, "You won the Game!",FG_COLOUR );
		}else if((fuel <=0)|| condition <=0){
			draw_string( 0, 0, "You lose, Sadly!",FG_COLOUR );
			
		}
		else {
			draw_string( 0, 0, "Car Vanished!",FG_COLOUR );
			
		}
		draw_string( 0, 9, "Time: ", FG_COLOUR );
		draw_double(37, 9, time);
		draw_string( 0, 19, "Dis: ", FG_COLOUR );
		draw_double(27, 19, distance);
		draw_string( 0, 29, "Play Again: SW2 ", FG_COLOUR );
		
		draw_string( 0, 38, "QUIT: SW3", FG_COLOUR );
		
		
		if(BIT_IS_SET(PINF, 5)){
			
			
			
			button_clicked = true;
			game_over = true;
		}
		
		else if(BIT_IS_SET(PINF, 6)){
			
			play_again = true;
			speed = 0;
			distance = 0;
			fuel = 10;
			condition = 100;
			time = 0;
			
			button_clicked = true;
			game_over = false;
			//setup();
			overflow_count = 0;
			//_delay_ms(100);
			
		}
		
		
		
		//if(dont_play_again)
			//complete_game_over = true;
		show_screen();
	}
	button_clicked = false;
}


/*ISR(TIMER0_OVF_vect) {
	overflow_counter0 ++;
}
	*/
volatile uint8_t bit_count = 0;

//	(g) Define a volatile global 8-bit unsigned global variable 
//	called switch_closed which will store the current state of the switch.
volatile uint8_t switch_closed ;



//	(h) Define an interrupt service routine to process timer overflow
//	interrupts for Timer 0. Every time the interrupt service
//	routine is called, bit_count should:

ISR(TIMER0_OVF_vect){
	
	uint8_t mask= 0b00000111;


	int value_pins[5] = {BIT_VALUE(PINB, 0), BIT_VALUE(PINB, 1), BIT_VALUE(PIND, 0), BIT_VALUE(PINF, 5), BIT_VALUE(PINF, 6)}; 

	for (int i = 0; i<5; i++){
		bit_count= (bit_count<<1 & mask) | value_pins[i];
	

		if (bit_count==mask)
		{ 

			switch_closed=1;
		}
		if (bit_count ==5){
			switch_closed=0;
		}
	}

}


	
bool sprite_move( Sprite *sprite, double dx, double dy ) {
	assert( sprite != NULL );
	int x0 = round( sprite->x );
	int y0 = round( sprite->y );
	sprite->x += dx;
	sprite->y += dy;
	
	int x1 = round( sprite->x );
	int y1 = round( sprite->y );
	return ( x1 != x0 ) || ( y1 != y0 );
}

void draw_pixels_on_screen(){
	lcd_position(0,0);
	for(int x = 0; x< 504; x++){
		lcd_write(LCD_D, pgm_read_byte(&microsoft[x]));
	}
}
void move_scenary(){
	if(speed > 0){
		for(int index = 0; index < NUM_OF_HOUSE; index++){
		
			sprite_move( &house[index], 0, 0.20 * speed);
		}
		
		for(int index = 0; index < NUM_OF_HOUSE; index++){
			if(house[index].y >= LCD_Y + H_HOUSE){
				int x = rand() %  (LCD_X - W_HOUSE) ;
				int y =  11 ;
		
				while(x  > X1_ROAD - 9 && x < X2_ROAD + 9){
					x = rand() % (LCD_X - W_HOUSE);
				}
				sprite_move_to( &house[index], x, y );
			}
		}
		
		
		
		for(int index = 0; index < NUM_OF_OBSTACLES; index++){
		
			sprite_move( &obstacle[index], 0, 0.20 * speed);
		}
		
		for(int index = 0; index < NUM_OF_OBSTACLES; index++){
			if(obstacle[index].y >= LCD_Y + H_OBSTACLE){
				//int x = rand()  %  (LCD_X - W_OBSTACLE) ;
				int x = ((rand() + X1_ROAD ) %  (LCD_X - W_OBSTACLE));
				
				sprite_move_to( &obstacle[index], x, 10 ); 
			}
		}
		
		for(int index = 0; index < NUM_OF_TREES; index++){
		
			sprite_move( &tree[index], 0, 0.20 * speed);
		}
		
		for(int index = 0; index < NUM_OF_TREES; index++){
			if(tree[index].y >= LCD_Y + H_TREE){
				int x = rand() %  (LCD_X - W_TREE) ;
				int y =  11 ;
		
				while(x  > X1_ROAD - 10 && x < X2_ROAD + 10){
					x = rand() % (LCD_X - W_TREE);
				}
				sprite_move_to( &tree[index], x, y );
			}
		}
		//if(fuel_depot.y >= LCD_Y + H_FUEL_DEPOT){
				
		int get_road_side = (rand() % 2);
		if(get_road_side == 1){
			sprite_move( &fuel_depot, 0, 0.20 * speed);
				//sprite_init(&fuel_depot, X1_ROAD - W_HOUSE, 15, W_FUEL_DEPOT, H_FUEL_DEPOT, fuel_bitmap);
		}
		else{
			sprite_move( &fuel_depot, 0, 0.20 * speed);
			//sprite_init(&fuel_depot, X2_ROAD - W_HOUSE, 10, W_FUEL_DEPOT, H_FUEL_DEPOT, fuel_bitmap);
		}
		
		if(fuel_depot.y >= LCD_Y + H_FUEL_DEPOT){
			int get_road_side = (rand() % 10);
			if(get_road_side > 5){
				sprite_move_to( &fuel_depot, X1_ROAD - W_HOUSE -10, 10);	
					//sprite_init(&fuel_depot, X1_ROAD - W_HOUSE, 15, W_FUEL_DEPOT, H_FUEL_DEPOT, fuel_bitmap);
			}
			else if(get_road_side <= 5){
				sprite_move_to( &fuel_depot, X2_ROAD + 10 , 10 );	
				//sprite_init(&fuel_depot, X2_ROAD - W_HOUSE, 10, W_FUEL_DEPOT, H_FUEL_DEPOT, fuel_bitmap);
			}
		}
		
			
		
	}
	
}
////int is_paused = 0;

//int first_time = 1;



bool pause_it = false;

void pause_view(){
	
		if(BIT_IS_SET(PINF, 5)){
			pause_it = true;
			clear_screen();
		
			TCCR1B = 0;
		}
		
		while(pause_it){
			
			draw_string( 10, 0, "Paused View", FG_COLOUR );
			draw_string( 0, 12, "Time: ", FG_COLOUR );
			draw_double(37, 12, time);
			draw_string( 0, 22, "Dis: ", FG_COLOUR );
			draw_double(27, 22, distance);
			draw_string( 0, 0, "Resume - SW2  ", FG_COLOUR );
			
			
			show_screen();
			if(BIT_IS_SET(PINF, 6)){
				pause_it = false;
				break;
			}
		}
		
	
}

void check_for_collision(){
	
	
	for(int index = 0; index < NUM_OF_HOUSE; index++){
		
			if(collided(&car, &house[index])){
				condition -= 10;
				speed = 0;
				fuel = 10;
				sprite_move_to(&car, x_car, y_car );
				
			}
			
	}
	for(int index = 0; index < NUM_OF_OBSTACLES; index++){
		
			if(collided(&car, &obstacle[index])){
				condition -= 10;
				speed = 0;
				fuel = 10;
				sprite_move_to(&car, x_car, y_car );
				if((obstacle[index].x > x_car - 10 && obstacle[index].x < x_car + 10) && (obstacle[index].y > LCD_Y - H_CAR - 10)){
					
					sprite_move_to(&obstacle[index], ((rand() + X1_ROAD ) %  (LCD_X - W_OBSTACLE)) , 10 );
				}
			}
	}
	for(int index = 0; index < NUM_OF_TREES; index++){
		
			if(collided(&car, &tree[index])){
				condition -= 10;
				fuel = 10;
				speed = 0;
				sprite_move_to(&car, x_car, y_car );
				
				
			}
	}
	if(collided(&car, &fuel_depot)){
		//collided_with_fuel = true;
			over_game();
			condition -= 10;
			fuel = 10;
			speed = 0;
			sprite_move_to(&car, x_car, y_car );
	}
	
}
	
	


void process(void) {
	
	
	static uint8_t prevState = 0;
	
	if ( switch_closed != prevState ) {
		prevState = switch_closed;
	}
		
		
		
		
		if(BIT_IS_SET(PINF, 5) || BIT_IS_SET(PINF, 6)) 
			button_presssed = 1;
		
		
		if(button_presssed){
			
			int left_adc = adc_read(0);

			set_duty_cycle(ADC_MAX - left_adc);
			
			
			
			
			
			
			
			fuel_consumption();
			TCCR1B = 4;
			clear_screen();
			dashboard();
			move_scenary();
			fill_fuel_if_parked();
			
			//check_if_paused();
			//first_time = 0;
			//draw_road();
			
			draw_curve_road();
			draw_car();
			draw_fuel_depot();
			
			draw_house();
			draw_trees();
			draw_obstacles();
			pause_view();
			//int left_adc = adc_read(0);
			
			
			int right_adc = adc_read(1);
			 left_adc = adc_read(0);
			
			///if( left_adc < THRESHOLD-20){
				
			WRITE_BIT(PORTB, 2, left_adc < THRESHOLD - 300);
			WRITE_BIT(PORTB, 3, left_adc > THRESHOLD + 300);
			//}

			
			//Call separate function
			
			if( (BIT_IS_SET(PINB, 1)||(left_adc < THRESHOLD-100))&& speed > 0 ){
				//if( left_adc < THRESHOLD-20){
				
			//if( right_adc < THRESHOLD-20 && speed > 0 ){
				
				move_car(&car, -1);
			}else if((BIT_IS_SET(PIND, 0)||( left_adc > THRESHOLD + 100)) && speed >= 0){
				
			//else if( right_adc > THRES HOLD+20 && speed > 0){
				
				move_car(&car, 1);	
			}
			
			//else if(BIT_IS_SET(PIND, 1) && speed < 10){
				 if( (right_adc > THRESHOLD) && speed < 10){
					
					if((car.x < curve_road_x1 || car.x > curve_road_x2)){
					
				//decrease_speed_if_offroad(&car);
				
				
					if(speed > 3){
						speed = 3;
					} if((right_adc > THRESHOLD))
					speed = speed + 0.03;
				
				
					/*if(speed < 3){
						speed = speed + 0.1;
					}*/
		
					}else{
					speed = speed + 0.15;
					}
				
				}//else if(BIT_IS_SET(PINB, 7) && speed > 0){
				else if( (right_adc < THRESHOLD) && speed >=  0){
					
				speed = speed - 0.3;
				
				
			}
			
			
			
			else if((!(right_adc > THRESHOLD) && (!(right_adc < THRESHOLD)))&& (speed > 1) && (car.x > curve_road_x1 && car.x < curve_road_x2)){
				speed = speed - 0.2;
			}
			else if((!(right_adc > THRESHOLD) && (!(right_adc < THRESHOLD)))&& (speed > 1) && (car.x < curve_road_x1 || car.x > curve_road_x2)){
				
				
					speed = speed - 0.1;
				
			}
			else if(((right_adc > THRESHOLD)  && (!(right_adc < THRESHOLD)))&& (speed < 1) && (car.x > curve_road_x1 && car.x < curve_road_x2)){
				//if(speed<=1)
				speed = speed + 0.2	;
			
				//speed = 1;
				
			}else if(((right_adc > THRESHOLD) && (!(right_adc < THRESHOLD)))&& (speed < 1) && (car.x < curve_road_x1 || car.x > curve_road_x2)){
				//if(speed<=1)
				speed = speed + 0.1	;
			
				//speed = 1;
				
			}
	
			if(car.x < 20 || car.x > 56){
				if(speed > 3){
					speed = 3;
				}else if((right_adc > THRESHOLD))
					speed = speed + 0.03;
				/*if(speed < 3){
					speed = speed + 0.1;
				}*/
			}
			show_screen();
			
			if(fuel <=0)
				over_game();
				//game_over = true;
				
			else if(distance >= 1000){
				over_game();
				//game_over = true;
			}
			else if(condition <= 0){
				over_game();
			}
			check_for_collision();
			
			//draw_formatted( 0, 20, buffer, sizeof(buffer), "Right ADC: %d", right_adc );
			
		}
		else spalsh_screen();
			
	
	
}



int main(void) {
	
	setup();
	
	draw_pixels_on_screen();
	_delay_ms(3000);
	for ( ;; ) {
		
		while(!game_over){
			
			process();
		
		}
		
		
		clear_screen();
		draw_string( 25, 15, "Bye! ", FG_COLOUR );
		draw_string( 0, 22, "Hope you enjoyed!!  ", FG_COLOUR );
		show_screen();
		
		
		_delay_ms(10);
	}
}

