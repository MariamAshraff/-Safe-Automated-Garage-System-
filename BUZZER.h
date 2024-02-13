/*
 * LED.h
 *
 * Created: 10/12/2023 11:41:46 AM
 *  Author: VTE
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_
void BUZZER_vInit(unsigned char portname,unsigned char pinnumber);
void BUZZER_vTurnOn(unsigned char portname,unsigned char pinnumber);
void BUZZER_vTurnOff(unsigned char portname,unsigned char pinnumber);
void BUZZER_vToggle(unsigned char portname,unsigned char pinnumber);
unsigned char BUZZER_u8ReadStatus(unsigned char portname,unsigned char pinnumber);





#endif /* BUZZER_H_ */