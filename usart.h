/* 
 * File:   usart.h
 * Author: YH31
 *
 * Created on May 8, 2020, 9:26 AM
 */
#include <xc.h>
#ifndef USART_H
#define	USART_H
void UsartInit();
void serial_tx(unsigned char val);
void serial_tx_str(const char* val);
unsigned char serial_rx();
#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* USART_H */

