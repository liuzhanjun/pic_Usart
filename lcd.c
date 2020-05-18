/*
 * File:   lcd.c
 * Author: YH31
 *
 * Created on May 8, 2020, 8:07 AM
 */


#include "lcd.h"

void delay(uint24_t delay) {

    while (delay--) {

    }

}

void lcdCMD(char cmd) {
    //������ʱ40us,���滻��æλ���
    delay(200);
    RE0 = 0; //RSָ��ģʽ
    //RW=0,��Ϊ�ӵأ����Բ���Ҫ������
    PORTD = cmd;
    //RE1һ��������д�����
    RE1 = 1; //������д��
    RE1 = 0; //д�����
}

//xΪ�����꣬yΪ������ x=0-15,y=0-1

void setPostion2(int x, int y) {
    char postion = (0x40 * y + x);
    //����ָ����������
    lcdCMD(postion | 0x80);
}

//xΪ�����꣬yΪ������ x=0-15,y=0-1

void setPostion1(int x) {

    if (x > 31) {
        x %= 32;
        //������������
        if (x == 0) {
            lcdCMD(0x01);
            delay(8000);
        }
    }
    char postion = x;
    if (x > 15) {
        postion = (0x40 + (x % 16));
    }
    //����ָ����������
    lcdCMD(postion | 0x80);
}

void lcdWriteData(char data) {
    delay(200); //������ʱ40us,���滻��æλ���
    RE0 = 1; //RSд����ģʽ
    //RW=0,��Ϊ�ӵأ����Բ���Ҫ������
    PORTD = data;
    //RE1һ��������д�����
    RE1 = 1; //������д��
    RE1 = 0; //д�����
}

void sendWrite2(char * a, int x, int y) {
    //����DDRAM������
    setPostion2(x, y);
    while (*a != '\0') {
        lcdWriteData(*a++);
    }

}

void showLcd(char * a, int x) {
    //����DDRAM������
    setPostion1(x);
    while (*a != '\0') {
        lcdWriteData(*a++);
    }

}

void initLcd() {
    //��E0��E1���
    TRISE0 = 0;
    TRISE1 = 0;
    TRISD = 0; //D��ȫ������Ϊ���
    //    ��ʱ15ms
    delay(75000);
    //    дָ��38//�������� 8λ���ݽӿڣ�������ʾ��5x7����
    lcdCMD(0x38);
    //    ��ʱ5ms
    delay(25000);
    //    дָ��38//�������� 8λ���ݽӿڣ�������ʾ��5x7����
    lcdCMD(0x38);
    //    ��ʱ5ms
    delay(25000);
    //    дָ��38//�������� 8λ���ݽӿڣ�������ʾ��5x7����
    lcdCMD(0x38);
    //дָ��0E��ʾ����
    lcdCMD(0x0E);

    //дָ��06
    lcdCMD(0x06);
    //дָ��01:����
    lcdCMD(0x01);

}
