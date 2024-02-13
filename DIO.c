/*
 * DIO.c
 *
 * Created: 10/11/2023 9:58:30 AM
 *  Author: VTE
 */ 

#include <avr/io.h>
#include "std_macros.h"
void DIO_vsetPINDir(unsigned char portName,unsigned char pinNumber,unsigned char direction){
	
	switch(portName)
	{
		case 'A':
		case 'a':
		if (direction==1)
		SET_BIT(DDRA,pinNumber);
		else
		CLR_BIT(DDRA,pinNumber);
		break;
		
		case 'B':
		case 'b':
		if (direction==1)
		SET_BIT(DDRB,pinNumber);
		else
		CLR_BIT(DDRB,pinNumber);
		break;
		
		case 'C':
		case 'c':
		if (direction==1)
		SET_BIT(DDRC,pinNumber);
		else
		CLR_BIT(DDRC,pinNumber);
		break;
		
		case 'D':
		case 'd':
		if (direction==1)
		SET_BIT(DDRD,pinNumber);
		else
		CLR_BIT(DDRD,pinNumber);
		break;
		
		default:
		break;
	}
	
}

void DIO_write(unsigned char portName,unsigned char pinNumber,unsigned char outputValue){
	
	switch(portName)
	{
		case 'A':
		case 'a':
		if (outputValue==1)
		SET_BIT(PORTA,pinNumber);
		else
		CLR_BIT(PORTA,pinNumber);
		break;
		
		case 'B':
		case 'b':
		if (outputValue==1)
		SET_BIT(PORTB,pinNumber);
		else
		CLR_BIT(PORTB,pinNumber);
		break;
		
		case 'C':
		case 'c':
		if (outputValue==1)
		SET_BIT(PORTC,pinNumber);
		else
		CLR_BIT(PORTC,pinNumber);
		break;
		
		case 'D':
		case 'd':
		if (outputValue==1)
		SET_BIT(PORTD,pinNumber);
		else
		CLR_BIT(PORTD,pinNumber);
		break;
		
		default:
		break;
	}
	
}
void DIO_togglepin(unsigned char portname,unsigned char pinnumber){
	
	switch(portname)
	{
		case 'A':
		case 'a':
		TOG_BIT(PORTA,pinnumber);
		break;
		case 'B':
		case 'b':
		TOG_BIT(PORTB,pinnumber);
		break;
		case 'C':
		case 'c':
		TOG_BIT(PORTC,pinnumber);
		break;
		case 'D':
		case 'd':
		TOG_BIT(PORTD,pinnumber);
		break;
	}
}
unsigned char DIO_u8read(unsigned char portname,unsigned char pinnumber)
{
	unsigned char return_value=0;
	switch(portname)
	{
		case 'A' :
		return_value=READ_BIT(PINA,pinnumber);
		break;
		
		case 'B' :
		return_value=READ_BIT(PINB,pinnumber);
		break;
		
		case 'C' :
		return_value=READ_BIT(PINC,pinnumber);
		break;
		
		case 'D' :
		return_value=READ_BIT(PIND,pinnumber);
		break;
		default:
		break;
	}
	return return_value ;
}

void DIO_set_port_direction(unsigned char portname,unsigned char direction){
	switch(portname)
	{
		case 'A' :
		case 'a' :
		DDRA=direction; 
		break ;
		case 'B':
		case 'b':
		DDRB=direction;
		break ;
		case 'C' :
		case 'c' :
		DDRC=direction; 
		break ;
		case 'D':
		case 'd' :
		DDRD=direction; 
		break ;
		default:
		break ;
	}
}
void DIO_write_port(unsigned char portname,unsigned char portvalue)
{
	switch(portname)
	{
		case 'A' :
		case 'a' :
		PORTA=portvalue; 
		break ;
		case 'B':
		case 'b' :
		PORTB=portvalue; 
		break ;
		case 'C' :
		case 'c' :
		PORTC=portvalue; 
		break ;
		case 'D':
		case 'd' :
		PORTD=portvalue; 
		break ;
		default:
		break ;
	}
}

unsigned char DIO_read_port(unsigned char portname)
{
	unsigned char return_val=0;
	switch(portname)
	{
		case 'A' :
		case 'a' :
		return_val=PINA; 
		break ;
		case 'B':
		case 'b' :
		return_val=PINB;
		break ;
		case 'C' :
		case 'c' :
		return_val=PINC; 
		break ;
		case 'D':
		case 'd' :
		return_val=PIND; 
		break ;
		default:
		break ;
	}
	return return_val;
}
void DIO_toggle_port(char port)
{
	switch(port)
	{
		case 'A':
		case 'a':
		PORTA=~PORTA;
		break;
		case 'B':
		case 'b':
		PORTB=~PORTB;
		break;
		case 'C':
		case 'c':
		PORTC=~PORTC;
		break;
		case 'D':
		case 'd':
		PORTD=~PORTD;
		break;
		default:
		break ;
	}
	
}
void DIO_vconnectpullup(char portname ,char pinnumber, char connect_pullup)
{
	switch(portname)
	{
		case 'A':
		if(connect_pullup==1)
		{
			SET_BIT(PORTA,pinnumber);
		}
		else
		{
			CLR_BIT(PORTA,pinnumber);
		}
		break;
		case 'B':
		if(connect_pullup==1)
		{
			SET_BIT(PORTB,pinnumber);
		}
		else
		{
			CLR_BIT(PORTB,pinnumber);
		}
		break;
		case 'C':
		if(connect_pullup==1)
		{
			SET_BIT(PORTC,pinnumber);
			
		}
		else
		{
			CLR_BIT(PORTC,pinnumber);
		}
		break;
		case 'D':
		if(connect_pullup==1)
		{
			SET_BIT(PORTD,pinnumber);
			
		}
		else
		{
			CLR_BIT(PORTD,pinnumber);
		}
		break;
		
	}
}
void write_high_nibble(unsigned char portname,unsigned char value)
{
	value<<=4;
	switch(portname)
	{
		case 'A':
		PORTA&=0x0f;
		PORTA|=value;
		case 'B':
		PORTB&=0x0f;
		PORTB|=value;
		case 'C':
		PORTC&=0x0f;
		PORTC|=value;
		case 'D':
		PORTD&=0x0f;
		PORTD|=value;
	}
}
void write_low_nibble(unsigned char portname,unsigned char value)
{
	value&=0x0f;
	switch(portname)
	{
		case 'A':
		PORTA&=0xf0;
		PORTA|=value;
		case 'B':
		PORTB&=0xf0;
		PORTB|=value;
		case 'C':
		PORTC&=0xf0;
		PORTC|=value;
		case 'D':
		PORTD&=0xf0;
		PORTD|=value;
	}
}
