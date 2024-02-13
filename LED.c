/*
 * LED.c
 *
 * Created: 10/12/2023 11:41:19 AM
 *  Author: VTE
 */ 
#include "DIO.h";
void LED_vInit(unsigned char portname,unsigned char pinnumber){
	DIO_vsetPINDir(portname,pinnumber,1);
}
void LED_vTurnOn(unsigned char portname,unsigned char pinnumber)
{
	DIO_write(portname,pinnumber,1);
}
void LED_vTurnOff(unsigned char portname,unsigned char pinnumber)
{
	DIO_write(portname,pinnumber,0);
}
void LED_vToggle(unsigned char portname,unsigned char pinnumber){
	DIO_togglepin(portname,pinnumber);
}
unsigned char LED_u8ReadStatus(unsigned char portname,unsigned char pinnumber){
	return DIO_u8read(portname,pinnumber);
}	