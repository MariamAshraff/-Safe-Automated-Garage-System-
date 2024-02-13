/*
 * lcd.c
 *
 * Created: 11/6/2023 12:12:32 AM
 *  Author: VTE
 */ 
#include "LCD.h"
#define  F_CPU 8000000UL 
#include <util/delay.h>

void LCD_vInit(void)
{
	_delay_ms(200);
	#if defined eight_bits_mode
	DIO_vsetPINDir('A',0,1);
	DIO_vsetPINDir('A',1,1);
	DIO_vsetPINDir('A',2,1);
	DIO_vsetPINDir('A',3,1);
	DIO_vsetPINDir('A',4,1);
	DIO_vsetPINDir('A',5,1);
	DIO_vsetPINDir('A',6,1);
	DIO_vsetPINDir('A',7,1);
	DIO_vsetPINDir('A',EN,1);
	DIO_vsetPINDir('A',RW,1);
	DIO_vsetPINDir('A',RS,1);
	DIO_write('A',RW,0);
	LCD_vSend_cmd(EIGHT_BITS); 
	_delay_ms(1);
	LCD_vSend_cmd(CURSOR_ON_DISPLAN_ON);
	_delay_ms(1);
	LCD_vSend_cmd(CLR_SCREEN);
	_delay_ms(10);
	LCD_vSend_cmd(ENTRY_MODE); 
	_delay_ms(1); 
	
	#elif defined four_bits_mode
	DIO_vsetPINDir('A',4,1);
	DIO_vsetPINDir('A',5,1);
	DIO_vsetPINDir('A',6,1);
	DIO_vsetPINDir('A',7,1);
	DIO_vsetPINDir('A',EN,1);
	DIO_vsetPINDir('A',RW,1);
	DIO_vsetPINDir('A',RS,1);
   	DIO_write('A',RW,0);
	LCD_vSend_cmd(RETURN_HOME); 
	_delay_ms(10);
	LCD_vSend_cmd(FOUR_BITS);
	_delay_ms(1);
	LCD_vSend_cmd(CURSOR_ON_DISPLAN_ON);
	_delay_ms(1);
	LCD_vSend_cmd(CLR_SCREEN);
	_delay_ms(10);
	LCD_vSend_cmd(ENTRY_MODE);
	_delay_ms(1);
	#endif
}


static void send_falling_edge(void)
{
	DIO_write('A',EN,1);
	_delay_ms(2);
	DIO_write('A',EN,0);
	_delay_ms(2);
}
void LCD_vSend_cmd(char cmd)
{
	#if defined eight_bits_mode
	DIO_write_port('A',cmd);
	DIO_write('A',RS,0);
	send_falling_edge();
	
	#elif defined four_bits_mode
	write_high_nibble('A',cmd>>4);
	DIO_write('A',RS,0);
	send_falling_edge();
	write_high_nibble('A',cmd);
	DIO_write('A',RS,0);
	send_falling_edge();
	#endif
	_delay_ms(1);
}

void LCD_vSend_char(char data)
{
	#if defined eight_bits_mode
	DIO_write_port('A',data);
	DIO_write('A',RS,1);
	send_falling_edge();
	
	#elif defined four_bits_mode
	write_high_nibble('A',data>>4);
	DIO_write('A',RS,1);
	send_falling_edge();
	write_high_nibble('A',data);
	DIO_write('A',RS,1);
	send_falling_edge();
	#endif
	_delay_ms(1);
}


void LCD_vSend_string(char *data)
{
	while((*data)!='\0')
	{
		LCD_vSend_char(*data);
		data++;
	}
}
void LCD_clearscreen()
{
	LCD_vSend_cmd(CLR_SCREEN);
	_delay_ms(10);
}
void LCD_movecursor(char row,char coloumn)
{
	char data ;
	if(row>2||row<1||coloumn>16||coloumn<1)
	{
		data=0x80;
	}
	else if(row==1)
	{
		data=0x80+coloumn-1 ;
	}
	else if (row==2)
	{
		data=0xc0+coloumn-1;
	}
	LCD_vSend_cmd(data);
	_delay_ms(1);
}
