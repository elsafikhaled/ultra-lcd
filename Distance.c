/*
 * Distance.c
 *
 *  Created on: ٣١‏/٠١‏/٢٠١٧
 *      Author: El-safi
 */

#include "lcdEKE.h"
#include "Timer0.h"

//#define BUZZER_ON (PORTD |=(1<<PD5))
//#define BUZZER_OFF (PORTD &=~(1<<PD5))
#define TRIGGER_ON  (PORTB |=(1<<PB1))
#define TRIGGER_OFF  (PORTB &=~(1<<PB1))



int main(void){
    FP32_t distance=0;U16_t time_signal=0;
	DDRB|=(1<<PB1);
	DDRB&=~(1<<PB0);
    TRIGGER_OFF;
	EKE_LCD_INIT();
	timer0_watch_init();

	while(1){


                TRIGGER_OFF;
                _delay_us(15);
                TRIGGER_ON;
                _delay_us(10);
                TRIGGER_OFF;

                while((PINB&(1<<PB0))==0);// wait for echo to be sent
                timer0_watch_start();
                while((PINB&(1<<PB0)));
                timer0_watch_stop();
                time_signal=timer0_watch_time();
                distance=0.017*(float)time_signal;

                EKE_clear_lcd();
		        goToRowColumn(1,1);
		        EKE_LCD_string((U8_t*)"distance: ");
		        goToRowColumn(2,1);

		        if(distance<=110){
		        EKE_LCD_intNumASCII((U16_t)distance);
		        goToRowColumn(2,6);
		        EKE_LCD_string((U8_t*)"CM ");
		        }
		        else{
		        	EKE_clear_lcd();
			        EKE_LCD_string((U8_t*)"Out of Range ");

		        }

                _delay_ms(500);

	}
	return 0;
}
