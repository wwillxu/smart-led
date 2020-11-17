#include "config.h"
char mode = 'l';

void GetMode(){
    while (Serial.available()){
        char data = Serial.read();
        Serial.println(data);
        mode = data;
    }
}