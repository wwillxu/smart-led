/* 蓝牙驱动：读取输入命令并更改模式或速度*/
#include "config.h"
char mode = 'l';

void GetCommand() {
  while (Serial.available()>0) {
    // 读取输入
    char data = Serial.read(); 
    Serial.print("input:");
    Serial.println(data);

    // 相同命令返回
    if (mode==data) 
      return;

    // 写入命令
    switch (data){  
      // 更改模式
      case 's':
        mode = data;
        Serial.println("mode:stop");
        break;
      case 'r':
        mode = data;
        Serial.println("mode:right");
        break;
      case 'l':
        mode = data;
        Serial.println("mode:left");  
        break;    
      case 'u':
        mode = data;
        Serial.println("mode:up");    
        break;      
      case 'd':
        mode = data;
        Serial.println("mode:down");   
        break;

      // 更改速度
      case 'a':
        DelayMax = 20;
        Serial.println("speed:20");   
        break; 
      case 'b':
        DelayMax = 100;
        Serial.println("speed:100");    
        break;    
      case 'c':
        DelayMax = 240;
        Serial.println("speed:240");  
        break;

      // 忽略范围外字符
      default:
        break;    
    }
  }
}
