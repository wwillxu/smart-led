/* 配置头文件：引脚定义与全局变量声明*/
#ifndef CONFIG_H
#define CONFIG_H
#include <Arduino.h>

// 点阵屏
#define RowA 2  // 138输入
#define RowB 3
#define RowC 4
#define RowD 5
#define EN 6    // 138使能
#define R1 8    // 595输入
#define CLK 9   // 595时钟
#define LAT 10  // 595输出

void ScanRow(byte r);
void SendDataHigh(byte data, byte offset);
void SendDataLow(byte data, byte offset);



// 蓝牙模块

// 字模
extern byte FontNum;
extern byte FontArray[][32];

#endif