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
  // byte offset = 0;
  // byte k = 0, j = 0;
  // int i;
  while (1) {
  //   for ( i = 0; i < 2; i++) { //2片595
  //     SendDataHigh(~(FontArray[ k + i][row * 2]), 8); 
  //     SendDataHigh(~(FontArray[ k + i][row * 2 + 1]), 8); 
  //   }
  //   if (offset < 8)
  //     SendDataHigh(~(FontArray[k + 2][row * 2]), offset) ;
  //   else
  //   {
  //     SendDataHigh(~(FontArray[k + 2][row * 2]), 8) ;
  //     SendDataHigh(~(FontArray[k + 2][row * 2 + 1]), offset - 8) ;
  //   }
  //   j++;
  //   if (j == 40) //更改流动速度
  //   {
  //     j = 0;
  //     offset++;
  //     if (offset == 16)
  //     {
  //       offset = 0; k++;
  //       if (k == FontNum + 2)
  //         k = 0;
  //     }
  //   }
    MoveLeft(row);

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
