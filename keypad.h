/*
 * keypad.h
 *
 * Created: 11/7/2023 11:52:26 PM
 *  Author: VTE
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_
#define keypadPort 'B'
#define NOTPRESSED 0xff
#include "DIO.h"
void keypad_vInit();
char keypad_u8check_press();

#endif /* KEYPAD_H_ */