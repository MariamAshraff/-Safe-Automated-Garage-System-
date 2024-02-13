/*
 * EEPROM.c
 *
 * Created: 12/2/2023 5:23:12 PM
 *  Author: VTE
 */ 
#include <avr/io.h>
#include "std_macros.h"
void EEPROM_write(unsigned short address, unsigned char data){
	EEARL=(char)address;
	EEARH=(char)(address<<8);
	EEDR=data;
	SET_BIT(EECR,EEMWE);
	SET_BIT(EECR,EEWE);
	while(READ_BIT(EECR,EEWE)==1);
}
unsigned char EEPROM_read(unsigned short address){
	EEARL=(char)address;
	EEARH=(char)(address<<8);
	SET_BIT(EECR,EERE);
	return EEDR;
}