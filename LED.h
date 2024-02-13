/*
 * LED.h
 *
 * Created: 10/12/2023 11:41:46 AM
 *  Author: VTE
 */ 


#ifndef LED_H_
#define LED_H_
void LED_vInit(unsigned char portname,unsigned char pinnumber);
void LED_vTurnOn(unsigned char portname,unsigned char pinnumber);
void LED_vTurnOff(unsigned char portname,unsigned char pinnumber);
void LED_vToggle(unsigned char portname,unsigned char pinnumber);
unsigned char LED_u8ReadStatus(unsigned char portname,unsigned char pinnumber);





#endif /* LED_H_ */