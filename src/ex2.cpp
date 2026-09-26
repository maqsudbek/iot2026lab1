


#include "Arduino.h"

#define GREEN_LED_PIN 27

#define BTN_PIN 25

bool prevBtnState = LOW;

/****************************************************/
void setup(void) 
{
    pinMode(GREEN_LED_PIN, OUTPUT); // GREEN LED
    pinMode(BTN_PIN, INPUT); // BTN

    Serial.begin(115200);
}


/****************************************************/
void loop(void) 
{
    bool btnState = digitalRead(BTN_PIN);
    
    if (btnState == HIGH && prevBtnState == LOW) {
        digitalWrite(GREEN_LED_PIN, HIGH);
        Serial.println("GREEN=1");
        
    } else if (btnState == LOW && prevBtnState == HIGH) {
        digitalWrite(GREEN_LED_PIN, LOW);
        Serial.println("GREEN=0");
    }

    prevBtnState = btnState;
}
