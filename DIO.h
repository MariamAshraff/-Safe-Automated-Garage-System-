/*
 * DIO.h
 *
 * Created: 10/11/2023 9:58:42 AM
 *  Author: VTE
 */ 


#ifndef DIO_H_
#define DIO_H_
void DIO_vsetPINDir(unsigned char portName,unsigned char pinNumber,unsigned char direction);
void DIO_write(unsigned char portName,unsigned char pinNumber,unsigned char outputValue);
void DIO_togglepin(unsigned char portname,unsigned char pinnumber);
unsigned char DIO_u8read(unsigned char portname,unsigned char pinnumber);
void DIO_vset_port_direction(unsigned char portname,unsigned char direction);
void DIO_write_port(unsigned char portname,unsigned char portvalue);
unsigned char DIO_read_port(unsigned char portname);
void DIO_toggle_port(char port);
void DIO_vconnectpullup(char portname ,char pinnumber, char connect_pullup);
void write_low_nibble(unsigned char portname,unsigned char value);
void write_high_nibble(unsigned char portname,unsigned char value);



#endif /* DIO_H_ */