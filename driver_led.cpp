/* LED驱动：基础输入函数与多个显示模式*/
#include "config.h"
byte Offset = 0;      // 偏移量
byte Index = 0;       // 当前字下标
byte Delay = 0;       // 延迟标志
byte DelayMax = 100;  // 延迟量

/***************************************************************************/
// ScanRow 138行扫描
void ScanRow(byte r) {
  digitalWrite(RowA, (r & 0x01));
  digitalWrite(RowB, (r & 0x02));
  digitalWrite(RowC, (r & 0x04));
  digitalWrite(RowD, (r & 0x08));
}

// SendDataHigh 595高位输入
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

// SendDataLow 595低位输入
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
// StaticWord 静态显示
void StaticWord(byte r) {
  int i;
  for ( i = 0; i < 2; i++) { 
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

// MoveLeft 向左移动
void MoveLeft(byte r) {
  int i;
  for ( i = 0; i < 2; i++) { 
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
  if (Delay == DelayMax) 
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

// MoveRight 向右移动
void MoveRight(byte r) {
  if (Offset < 8)
    SendDataLow(~(Word[Index][r * 2 + 1]), Offset) ;
  else
  {
    SendDataLow(~(Word[Index][r * 2]), Offset - 8) ;
    SendDataLow(~(Word[Index][r * 2 + 1]), 8) ;
  }
  SendDataHigh(~(Word[ Index + 1][r * 2]), 8); 
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

// MoveUp 向上移动
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

// MoveDown 向下移动
void MoveDown(byte r) {
  int i;
  if (r - Offset<0){
    for ( i = 0; i < 2; i++) { 
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
