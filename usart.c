/*
 * File:   usart.c
 * Author: YH31
 *
 * Created on May 8, 2020, 9:26 AM
 */



#include "usart.h"
#include "lcd.h"
void UsartInit() {

    //    1.����SPBRG�����ò�����
    //����������
    //�貨����ΪK,SPBRG��ֵΪx
    //���TXSTA<2>��ֵΪ1
    //��ô����ͬ�������첽ʹ�ù�ʽ���£�
    //x=Fosc/(K*16)-1
    //���TXSTA<2>��ֵΪ0
    //ͬ��ģʽ�£�x=Fosc/(K*4)-1
    //�첽ģʽ�£�x=Fosc/(K*64)-1
    //��ǰK=20000000,Ҫ����K=9600,TXSTA<2>=1
    //x=20000000/(9600*16)-1
    SPBRG = 0x82;

    //    2���÷���

    //������ƼĴ���,�첽����ģʽ
    //�ڲ�ʱ��|8λ����|����ʹ��|�첽ģʽ|�Ͳ�����
    //    TXSTA=_TXSTA_TXEN_MASK|_TXSTA_BRGH_MASK;
    TXSTAbits.TX9 = 0; //8λ����
    TXSTAbits.TXEN = 1; //����ʹ��
    TXSTAbits.SYNC = 0; //ʹ���첽ģʽ
    TXSTAbits.BRGH = 1; //ʹ������ģʽ���㲨����
    //    �����Ҫʹ���жϣ���ô�����ж�ʹ��
    //    INTCONbits.GIE=1;
    //    INTCONbits.PEIE=1;
    //    PIE1bits.TXIE=1;


    //3���ý���

    //���տ��ƼĴ���
    //����ʹ�ܣ��ὫRC6/RC7���óɴ������ţ�|8λ����|�첽��������ʹ��,û����żУ��
    //    RCSTA = _RCSTA_SPEN_MASK | _RCSTA_CREN_MASK;
    RCSTAbits.SPEN = 1; //����ʹ��
    RCSTAbits.RX9 = 0; //8λ����
    RCSTAbits.CREN = 1; //�첽��������
    //    �����Ҫʹ���жϣ���ô�����ж�ʹ��
    //    INTCONbits.GIE=1;
    //    INTCONbits.PEIE=1;
    //    PIE1bits.RCIE=1;

}

//���͵�������

void serial_tx(unsigned char val) {

    TXREG = val;
    //TSR��Ϊ�գ�˵��û�д������,TXREG�Ĵ����Ǵ�TSR��
    while (!TXSTAbits.TRMT);
}

//�����ַ���

void serial_tx_str(const char* val) {
    unsigned char i = 0;

    while (val[i]) {
        serial_tx(val[i]);
        i++;
    }
}


//��������
//��ʱʱ��timeount��40us�ı���
unsigned char serial_rx() {
    unsigned int to = 0;

    //���֡���󣬻���������� ��ͨ�����CREN�����ý��
    if (RCSTAbits.FERR || RCSTAbits.OERR)//trata erro
    {
        RCSTAbits.CREN = 0;
        RCSTAbits.CREN = 1;
    }
    //�ж���RCIF״̬�������1,��ô��ʾRCREG�Ĵ����е�ֵ���ǽ��յ���������
    if (PIR1bits.RCIF)
        return RCREG;
    else
        return 0xA5;
}
