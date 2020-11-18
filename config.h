/* 配置头文件：引脚定义与全局变量声明*/
#ifndef CONFIG_H
#define CONFIG_H
#include <Arduino.h>

// 点阵屏
#define RowA 2  // 引脚：138输入
#define RowB 3
#define RowC 4
#define RowD 5
#define EN 6    // 引脚：138使能
#define R1 8    // 引脚：595输入
#define CLK 9   // 引脚：595时钟
#define LAT 10  // 引脚：595输出

extern byte Offset;     // 变量：偏移量
extern byte Index;      // 变量：当前字下标
extern byte Delay;      // 变量：延迟标志
extern byte DelayMax;   // 变量：延迟量

void ScanRow(byte r);                       // 
void SendDataHigh(byte data, byte offset);  //
void SendDataLow(byte data, byte offset);   //
void StaticWord(byte r);                    //
void MoveLeft(byte r);                      //
void MoveRight(byte r);                     //
void MoveUp(byte r);                        //
void MoveDown(byte r);                      //

// 蓝牙模块
extern char mode;   // 变量：输入模式
void GetCommand();     // 函数：获得输入模式

// 字模
extern byte WordNum;    // 参数：字库个数
extern byte Word[][32]; // 参数：字库数组

#endif