#include "config.h"

void ScanRow(byte r) { 
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
    if(data & 0x80)
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
    if(data & 0x01)
      digitalWrite(R1, 1);
    else
      digitalWrite(R1, 0);
    data = data >> 1;
    digitalWrite(CLK, 0);
    digitalWrite(CLK, 1);
  }
}