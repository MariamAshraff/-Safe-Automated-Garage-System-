/*
 * EEPROM.h
 *
 * Created: 12/2/2023 5:23:29 PM
 *  Author: VTE
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

void EEPROM_write(unsigned short address, unsigned char data);
unsigned char EEPROM_read(unsigned short address);


#endif /* EEPROM_H_ */