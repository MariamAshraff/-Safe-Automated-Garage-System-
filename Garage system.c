/*
 *  Garage_system.c
 *
 * Created: 2/12/2024 1:15:12 PM
 *  Author: Mariam Ashraf
 */ 


#include <avr/io.h>
#include "LCD.h"
#define  F_CPU 1000000UL
#include <util/delay.h>
#include "std_macros.h"
#include <avr/interrupt.h>
#include "LCD.h"
#include "DIO.h"
#include "keypad.h"
#include "ADC_driver.h"
#include "LED.h"
#include "BUZZER.h"
#define STATUS_LOCATION     0x30
#define PASSWORD_LOCATION1  0x31
#define PASSWORD_LOCATION2  0x32
#define PASSWORD_LOCATION3  0x33
#define PASSWORD_LOCATION4  0x34

// Array to store entered password digits
char arr[4];
unsigned short distance,count,count1,distance1,temperatue,cars=0;
volatile unsigned short a,b,a1,b1;
int main(void)
{
	LCD_vInit();
	timer0_overflow();
	timer2_overflow();
	keypad_vInit();
	ADC_vinit();
	BUZZER_vInit('D',1);
	LED_vInit('D',0);
	char val = NOTPRESSED, i;
	// Set pin D7 as output for ultrasonic sensor trigger
	DIO_vsetPINDir('D',7,1);
	sei();
	SET_BIT(MCUCR,ISC01);
	SET_BIT(MCUCR,ISC00);
	SET_BIT(MCUCR,ISC11);
	SET_BIT(MCUCR,ISC10);
	SET_BIT(GICR,INT0);
	SET_BIT(GICR,INT1);
	if (EEPROM_read(STATUS_LOCATION) == 0xff)
	{
		LCD_clearscreen();
		LCD_vSend_string("Set Password of");
		LCD_movecursor(2, 1);
		LCD_vSend_string("4 digit:");

		// Loop to set a 4-digit password
		for (i = 0; i < 4; i++)
		{
			do
			{
				val = keypad_u8check_press();
			} while (val == NOTPRESSED);

			LCD_vSend_char(val);
			_delay_ms(500);
			LCD_movecursor(2, 9 + i);
			LCD_vSend_char('*');
			EEPROM_write(PASSWORD_LOCATION1 + i, val);
		}

		// Mark the status as password set
		EEPROM_write(STATUS_LOCATION, 0x00);
	}

	while(1)
	{
		label1:
		temperatue=(ADC_u16Read()*0.25);
		if (temperatue>=55)
		{
			
			BUZZER_vTurnOn('D',1);
			timer1_wave_fastPWM_B(0.999999);
			timer1_wave_fastPWM_A(0.999999);
			cars=0;
			LCD_clearscreen();
			LCD_vSend_string("     Fire");
			_delay_ms(700);
		}
		else
		{
			BUZZER_vTurnOff('D',1);
			timer1_wave_fastPWM_B(1.499999);
			timer1_wave_fastPWM_A(1.499999);
		}
		DIO_write('D',7,1);
		_delay_us(50);
		DIO_write('D',7,0);
		
		// Calculate distance
		distance=((a*34600*8)/(F_CPU*2));
		distance1=((a1*34600*8)/(F_CPU*2));
		if (distance1<=30&&distance1>0)
		{
			timer1_wave_fastPWM_B(0.99999);
			_delay_ms(2000);
			timer1_wave_fastPWM_B(1.49999);
			if (cars>0)
			cars--;
		}
		if (distance<=29&&distance>0&&cars<5&&temperatue<55)
		{
			
				label:
				arr[0] = arr[1] = arr[2] = arr[3] = NOTPRESSED;
				LCD_clearscreen();
				LCD_vSend_string("Check Password:");
				LCD_movecursor(2, 6);
				
				// Loop to enter the password for opening the door
				for (i = 0; i < 4; i++)
				{
					do
					{
						DIO_write('D',7,1);
						_delay_us(20);
						DIO_write('D',7,0);
						distance=((a*34600*8)/(F_CPU*2)); // For lack of conflict
						distance1=((a1*34600*8)/(F_CPU*2));
						temperatue=(ADC_u16Read()*0.25);
						arr[i] = keypad_u8check_press();
						
					} while (arr[i] == NOTPRESSED&&distance<=29&&distance1>=30&&temperatue<55);
					if (distance>=29||distance1<=30||temperatue>=55) //For lack of conflict
						goto label1;
					LCD_vSend_char(arr[i]);
					_delay_ms(500);
					LCD_movecursor(2, 6 + i);
					LCD_vSend_char('*');
				}
				
				// Check if the entered password matches
				if (EEPROM_read(PASSWORD_LOCATION1) == arr[0] &&
				EEPROM_read(PASSWORD_LOCATION2) == arr[1] &&
				EEPROM_read(PASSWORD_LOCATION3) == arr[2] &&
				EEPROM_read(PASSWORD_LOCATION4) == arr[3])
				{
					// Display success message and set the flag to open the safe
					LCD_clearscreen();
					LCD_vSend_string(" right password");
					LCD_movecursor(2, 3);
					LCD_vSend_string("Door opened");
					timer1_wave_fastPWM_A(0.99999);
					LED_vTurnOn('D',0);
					_delay_ms(2000);
					timer1_wave_fastPWM_A(1.49999);
					LED_vTurnOff('D',0);
					cars++;
				}
				else
				{
					LCD_clearscreen();
					LCD_vSend_string(" wrong password");
					LCD_movecursor(2,4);
					LCD_vSend_string("Try again");
					goto label;
				}
		}
		else if (temperatue<55)
		{
			if (cars<5)
			{
				LCD_clearscreen();	
				LCD_vSend_string("there are ");
				LCD_vSend_char((5-cars)+48);
				LCD_vSend_string("space");
				LCD_movecursor(2,1);
				LCD_vSend_string("you can enter");
			}
			else
			{
					LCD_clearscreen();
					LCD_vSend_string("garage is full");
					LCD_movecursor(2,1);
					LCD_vSend_string("you can't enter");
			}			
		
		}
		
	}
}
ISR(INT0_vect)
{
	count++;
	if(count==1)
	{
		TCNT0=0;
		SET_BIT(MCUCR,ISC01);
		CLR_BIT(MCUCR,ISC00);
	}
	else if (count==2)
	{
		a1=TCNT0;
		TCNT0=0;
		count=0;
		SET_BIT(MCUCR,ISC01);
		SET_BIT(MCUCR,ISC00);

	}
	else if (count==3)
	{
		b1=TCNT0;
		TCNT0=1;
		count=0;
		SET_BIT(MCUCR,ISC01);
		CLR_BIT(MCUCR,ISC00);

	}

}
ISR(INT1_vect)
{
	count1++;
	if(count1==1)
	{
		TCNT2=0;
		SET_BIT(MCUCR,ISC11);
		CLR_BIT(MCUCR,ISC10);
	}
	else if (count1==2)
	{
		a=TCNT2;
		TCNT2=0;
		count1=0;
		SET_BIT(MCUCR,ISC11);
		SET_BIT(MCUCR,ISC10);

	}
	else if (count1==3)
	{
		b=TCNT2;
		TCNT2=1;
		count1=0;
		SET_BIT(MCUCR,ISC11);
		CLR_BIT(MCUCR,ISC10);

	}

}
