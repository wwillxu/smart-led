#include "config.h"
byte Offset = 0;
byte Index = 0;
byte Delay = 0;
byte DelayMax = 100;

void ScanRow(byte r) {
  digitalWrite(RowA, (r & 0x01));
  digitalWrite(RowB, (r & 0x02));
  digitalWrite(RowC, (r & 0x04));
  digitalWrite(RowD, (r & 0x08));
}

void SendDataHigh(byte data, byte offset) {
  int i;
  for (i = 0; i < offset; i++)
  {
    digitalWrite(R1, bitRead(data, 7 - i));
    // if (data & 0x80)
    //   digitalWrite(R1, 1);
    // else
    //   digitalWrite(R1, 0);
    // data = data << 1;
    digitalWrite(CLK, 0);
    digitalWrite(CLK, 1);
  }
}

void SendDataLow(byte data, byte offset) {
  int i;
  for (i = 0; i < offset; i++)
  {
    digitalWrite(R1, bitRead(data, offset - 1 - i));
    digitalWrite(CLK, 0);
    digitalWrite(CLK, 1);
  }
}

/***************************************************************************/
void StaticWord(byte r) {
  int i;
  for ( i = 0; i < 2; i++) { //2*2片595
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
}

void MoveLeft(byte r) {
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

void MoveRight(byte r) {
  if (Offset < 8)
    SendDataLow(~(Word[Index][r * 2 + 1]), Offset) ;
  else
  {
    SendDataLow(~(Word[Index][r * 2]), Offset - 8) ;
    SendDataLow(~(Word[Index][r * 2 + 1]), 8) ;
  }
  SendDataHigh(~(Word[ Index + 1][r * 2]), 8); //SPI
  SendDataHigh(~(Word[ Index + 1][r * 2 + 1]), 8);
  if (Offset < 8)
  {
    SendDataHigh(~(Word[Index + 2][r * 2]), 8) ;
    SendDataHigh(~(Word[Index + 2][r * 2 + 1]), 8 - Offset) ;
  }
  else
  {
    SendDataHigh(~(Word[Index + 2][r * 2]), 16 - Offset) ;
  }
  Delay++;
  if (Delay == DelayMax) 
  {
    Delay = 0;
    Offset++;
    if (Offset == 16)
    {
      Offset = 0;
      if (Index == 0) {
        Index = WordNum + 2;
      }
      Index--;
    }
  }
}

void MoveUp(byte r) {
  int i;
  if (r + Offset<16){
    for ( i = 0; i < 2; i++) { 
      SendDataHigh(~(Word[ Index + i][(r + Offset)  * 2]),8); 
      SendDataHigh(~(Word[ Index + i][(r + Offset)  * 2 + 1]),8);
    }
  }else{
    for ( i = 0; i < 2; i++) { 
      SendDataHigh(~(Word[ Index + i+2][(r + Offset) % 16 * 2]),8); 
      SendDataHigh(~(Word[ Index + i+2][(r + Offset) % 16 * 2 + 1]),8);
    }  }


  Delay++;
  if (Delay == DelayMax) 
  {
    Delay = 0;
    Offset++;
    if (Offset == 16)
    {
      Offset = 0;Index+=2;
      if (Index >= WordNum) {
        Index = 0;
      }
      //Index--;
    }
  }
}

void MoveDown(byte r) {
  int i;
  if (r - Offset<0){
    for ( i = 0; i < 2; i++) { 
      // SendByte(~(hz[ k+i][(row-offset+16)%16*2]));  //SPI      
      // SendByte(~(hz[ k+i][(row-offset+16)%16*2+1]));  //SPI 
      SendDataHigh(~(Word[ Index + i-2][(r - Offset+16) % 16 * 2]),8); 
      SendDataHigh(~(Word[ Index + i-2][(r - Offset+16) % 16 * 2 + 1]),8);
    }
  }else{
    for ( i = 0; i < 2; i++) { 
      SendDataHigh(~(Word[ Index + i][(r - Offset+16) % 16 * 2]),8); 
      SendDataHigh(~(Word[ Index + i][(r - Offset+16) % 16 * 2 + 1]),8);
    }  }


  Delay++;
  if (Delay == DelayMax) 
  {
    Delay = 0;
    Offset++;
    if (Offset == 16)
    {
      Offset = 0;Index-=2;
      if (Index <= 2) {
        Index = WordNum+2;
      }
    }
  }
}
