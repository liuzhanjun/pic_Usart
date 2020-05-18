/*
 * File:   main.c
 * Author: YH31
 *
 * Created on May 7, 2020, 3:06 PM
 */

// PIC16F877A Configuration Bit Settings
// 'C' source line config statements
// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include "lcd.h"
#include "usart.h"



void main(void) {


    UsartInit();
    initLcd();
    char getData = 0;
    int index=0;
    while (1) {
        if (PIR1bits.RCIF) {//等待接收串口信息，
            getData = serial_rx();
            if (getData != 0) {
                //将接收到的串口信息显示在LCD屏幕上
                showLcd(&getData, index);
                getData = 0;
                index++;
            }
        }
    };
    return;
}

//void main(void) {
//
//
//    UsartInit();
//    initLcd();
//    char getData = 0;
//    char * data = "hello world";
//    serial_tx_str(data);
//    while (1);
//    return;
//
//
//}
