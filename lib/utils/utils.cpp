
#include "utils.h"

void button_led_feedback(uint8_t button, uint8_t led){
    uint8_t button_a_value = 0;
  
    button_a_value = digitalRead(button);
    if(!button_a_value){
        digitalWrite(led, HIGH);
    }
    else {
        digitalWrite(led, LOW);
    }
}
