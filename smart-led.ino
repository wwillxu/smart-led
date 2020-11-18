#include "config.h"

// 初始化函数
void setup () {
  pinMode(RowA, OUTPUT);
  pinMode(RowB, OUTPUT);
  pinMode(RowC, OUTPUT);
  pinMode(RowD, OUTPUT);  // 138片选
  pinMode(EN, OUTPUT);    // 138使能

  pinMode(R1, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(LAT, OUTPUT);

  Serial.begin(9600);

  delay(1000);
}

// 循环函数
void loop () {
  int row = 0;
  // 显示循环
  while (1) {
    GetCommand();       // 获取命令
    switch (mode){      // 更改显示模式
      case 'l':
        MoveLeft(row);
        break;
      case 'r':
        MoveRight(row);
        break;
      case 's':
        StaticWord(row);
        break;
      case 'u':
        MoveUp(row);
        break;
      case 'd':
        MoveDown(row);
        break;
      default:
        break;
    }

    // 显示输出
    digitalWrite(EN, 1);      // 关闭显示
    ScanRow(row);             // 输出行选信号
    digitalWrite(LAT, 0);     // 刷新显示内容
    digitalWrite(LAT, 1);
    digitalWrite(EN, 0);      // 开启显示
    delayMicroseconds(200) ;  // 通过延迟更改刷新频率

    // 行循环
    row++; 
    if (row  == 16)
      row = 0;
  }
}
