#include "config.h"
char mode = 'l';

void GetCommand() {
  while (Serial.available()>0) {
    char data = Serial.read();
    Serial.print("input:");
    Serial.println(data);

    if (mode==data)
      return;
    
    switch (data){
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

      default:
        break;    
    }
  }
}
