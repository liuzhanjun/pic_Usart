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
    //这里延时40us,可替换成忙位检测
    delay(200);
    RE0 = 0; //RS指令模式
    //RW=0,因为接地，所以不许要设置了
    PORTD = cmd;
    //RE1一个周期内写入完毕
    RE1 = 1; //将设置写入
    RE1 = 0; //写入完毕
}

//x为横坐标，y为纵坐标 x=0-15,y=0-1

void setPostion2(int x, int y) {
    char postion = (0x40 * y + x);
    //发送指令设置坐标
    lcdCMD(postion | 0x80);
}

//x为横坐标，y为纵坐标 x=0-15,y=0-1

void setPostion1(int x) {

    if (x > 31) {
        x %= 32;
        //发送清屏命令
        if (x == 0) {
            lcdCMD(0x01);
            delay(8000);
        }
    }
    char postion = x;
    if (x > 15) {
        postion = (0x40 + (x % 16));
    }
    //发送指令设置坐标
    lcdCMD(postion | 0x80);
}

void lcdWriteData(char data) {
    delay(200); //这里延时40us,可替换成忙位检测
    RE0 = 1; //RS写数据模式
    //RW=0,因为接地，所以不许要设置了
    PORTD = data;
    //RE1一个周期内写入完毕
    RE1 = 1; //将设置写入
    RE1 = 0; //写入完毕
}

void sendWrite2(char * a, int x, int y) {
    //设置DDRAM的坐标
    setPostion2(x, y);
    while (*a != '\0') {
        lcdWriteData(*a++);
    }

}

void showLcd(char * a, int x) {
    //设置DDRAM的坐标
    setPostion1(x);
    while (*a != '\0') {
        lcdWriteData(*a++);
    }

}

void initLcd() {
    //打开E0，E1输出
    TRISE0 = 0;
    TRISE1 = 0;
    TRISD = 0; //D口全部设置为输出
    //    延时15ms
    delay(75000);
    //    写指令38//功能设置 8位数据接口，两行显示，5x7点阵
    lcdCMD(0x38);
    //    延时5ms
    delay(25000);
    //    写指令38//功能设置 8位数据接口，两行显示，5x7点阵
    lcdCMD(0x38);
    //    延时5ms
    delay(25000);
    //    写指令38//功能设置 8位数据接口，两行显示，5x7点阵
    lcdCMD(0x38);
    //写指令0E显示设置
    lcdCMD(0x0E);

    //写指令06
    lcdCMD(0x06);
    //写指令01:清屏
    lcdCMD(0x01);

}
