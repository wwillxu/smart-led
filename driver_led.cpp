#include "config.h"
byte Offset = 0;
byte Index = 0;
byte Delay = 0;
byte DelayMax = 60;

void ScanRow(byte r){
  digitalWrite(RowA, (r & 0x01));
  digitalWrite(RowB, (r & 0x02));
  digitalWrite(RowC, (r & 0x04));
  digitalWrite(RowD, (r & 0x08));
}

void SendDataHigh(byte data, byte offset)
{
  byte i;
  for (i = 0; i < offset; i++)
  {
    //digitalWrite(R1, bitRead(data, 7 - i));
    if (data & 0x80)
      digitalWrite(R1, 1);
    else
      digitalWrite(R1, 0);
    data = data << 1;
    digitalWrite(CLK, 0);
    digitalWrite(CLK, 1);
  }
}

void SendDataLow(byte data, byte offset)
{
  byte i;
  for (i = 0; i < offset; i++)
  {
    //digitalWrite(R1, bitRead(data, offset - 1 - i));
    if (data & 0x01)
      digitalWrite(R1, 1);
    else
      digitalWrite(R1, 0);
    data = data >> 1;
    digitalWrite(CLK, 0);
    digitalWrite(CLK, 1);
  }
}

void MoveLeft(byte r){
    int i;
    for ( i = 0; i < 2; i++) { //2片595
      SendDataHigh(~(Word[ Index + i][r * 2]), 8); 
      SendDataHigh(~(Word[ Index + i][r * 2 + 1]), 8); 
    }
    if (Offset < 8)
      SendDataHigh(~(Word[Index + 2][r * 2]), Offset) ;
    else
    {
      SendDataHigh(~(Word[Index + 2][r * 2]), 8) ;
      SendDataHigh(~(Word[Index + 2][r * 2 + 1]), Offset - 8) ;
    }
    Delay++;
    if (Delay == DelayMax) //更改流动速度
    {
      Delay = 0;
      Offset++;
      if (Offset == 16)
      {
        Offset = 0; Index++;
        if (Index == WordNum + 2)
          Index = 0;
      }
    }
}