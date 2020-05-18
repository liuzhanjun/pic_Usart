/*
 * File:   usart.c
 * Author: YH31
 *
 * Created on May 8, 2020, 9:26 AM
 */



#include "usart.h"
#include "lcd.h"
void UsartInit() {

    //    1.配置SPBRG，设置波特率
    //波特率设置
    //设波特率为K,SPBRG的值为x
    //如果TXSTA<2>的值为1
    //那么无论同步还是异步使用公式如下：
    //x=Fosc/(K*16)-1
    //如果TXSTA<2>的值为0
    //同步模式下：x=Fosc/(K*4)-1
    //异步模式下：x=Fosc/(K*64)-1
    //当前K=20000000,要设置K=9600,TXSTA<2>=1
    //x=20000000/(9600*16)-1
    SPBRG = 0x82;

    //    2配置发送

    //传输控制寄存器,异步传输模式
    //内部时钟|8位传输|传输使能|异步模式|低波特率
    //    TXSTA=_TXSTA_TXEN_MASK|_TXSTA_BRGH_MASK;
    TXSTAbits.TX9 = 0; //8位传输
    TXSTAbits.TXEN = 1; //传输使能
    TXSTAbits.SYNC = 0; //使用异步模式
    TXSTAbits.BRGH = 1; //使用那种模式计算波特率
    //    如果需要使用中断，那么配置中断使能
    //    INTCONbits.GIE=1;
    //    INTCONbits.PEIE=1;
    //    PIE1bits.TXIE=1;


    //3配置接收

    //接收控制寄存器
    //接收使能（会将RC6/RC7配置成串口引脚）|8位接收|异步连续接收使能,没有奇偶校验
    //    RCSTA = _RCSTA_SPEN_MASK | _RCSTA_CREN_MASK;
    RCSTAbits.SPEN = 1; //接收使能
    RCSTAbits.RX9 = 0; //8位传输
    RCSTAbits.CREN = 1; //异步连续接收
    //    如果需要使用中断，那么配置中断使能
    //    INTCONbits.GIE=1;
    //    INTCONbits.PEIE=1;
    //    PIE1bits.RCIE=1;

}

//发送单个数据

void serial_tx(unsigned char val) {

    TXREG = val;
    //TSR不为空，说明没有传输完毕,TXREG寄存器是从TSR中
    while (!TXSTAbits.TRMT);
}

//发送字符串

void serial_tx_str(const char* val) {
    unsigned char i = 0;

    while (val[i]) {
        serial_tx(val[i]);
        i++;
    }
}


//接收数据
//超时时间timeount是40us的倍数
unsigned char serial_rx() {
    unsigned int to = 0;

    //如果帧错误，或者溢出错误 ，通过清除CREN再设置解决
    if (RCSTAbits.FERR || RCSTAbits.OERR)//trata erro
    {
        RCSTAbits.CREN = 0;
        RCSTAbits.CREN = 1;
    }
    //判断下RCIF状态，如果是1,那么表示RCREG寄存器中的值就是接收到的数据来
    if (PIR1bits.RCIF)
        return RCREG;
    else
        return 0xA5;
}
