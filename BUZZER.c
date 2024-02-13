/*
 * LED.c
 *
 * Created: 10/12/2023 11:41:19 AM
 *  Author: VTE
 */ 
#include "DIO.h";
void BUZZER_vInit(unsigned char portname,unsigned char pinnumber){
	//DIO_setPINDir(portname,pinnumber,1);
	DIO_vsetPINDir(portname,pinnumber,1);
}
void BUZZER_vTurnOn(unsigned char portname,unsigned char pinnumber)
{
	DIO_write(portname,pinnumber,1);
}
void BUZZER_vTurnOff(unsigned char portname,unsigned char pinnumber)
{
	DIO_write(portname,pinnumber,0);
}
void BUZZER_vToggle(unsigned char portname,unsigned char pinnumber){
	DIO_togglepin(portname,pinnumber);
}
unsigned char BUZZER_u8ReadStatus(unsigned char portname,unsigned char pinnumber){
	return DIO_u8read(portname,pinnumber);
}	