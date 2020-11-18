#include "config.h"

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

void loop () {
  int row = 0;
  while (1) {
    GetCommand();
    switch (mode){
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

    digitalWrite(EN, 1);      // 改变138使能，关闭显示
    ScanRow(row);             // 输出138行选信号，行扫描
    digitalWrite(LAT, 0);     // 595刷新
    digitalWrite(LAT, 1);
    digitalWrite(EN, 0);      // 改变138使能，开启显示

    delayMicroseconds(200) ;  // 通过延迟更改刷新频率

    row++;
    if (row  == 16)
      row = 0;
  }
}
