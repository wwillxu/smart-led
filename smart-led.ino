#include "config.h"

void setup () {
  pinMode(RowA, OUTPUT);
  pinMode(RowB, OUTPUT);
  pinMode(RowC, OUTPUT);
  pinMode(RowD, OUTPUT);  //138片选
  pinMode(EN, OUTPUT);    //138 使能

  pinMode(R1, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(LAT, OUTPUT);

  Serial.begin(9600);

  delay(1000);
}

void loop () {
  byte row = 0;
  while (1) {
    //MoveLeft(row);
    MoveRight(row);

    digitalWrite(EN, 1);      //关闭显示
    ScanRow(row);             //换行
    digitalWrite(LAT, 0);     //595刷新
    digitalWrite(LAT, 1);
    delayMicroseconds(500) ;  //节电用,
    digitalWrite(EN, 0);      //开启显示

    //delayMicroseconds(5) ;  //刷新频率调,

    row++;
    if (row  == 16)
      row = 0;
  }
}
