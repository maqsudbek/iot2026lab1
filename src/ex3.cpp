


#include "Arduino.h"


#define BLUE_LED_PIN 14
#define GREEN_LED_PIN 27
#define YELLOW_LED_PIN 12
#define RED_LED_PIN 26


/****************************************************/
void setup(void) 
{
    Serial.begin(115200);

    pinMode(BLUE_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(YELLOW_LED_PIN, OUTPUT);
    pinMode(RED_LED_PIN, OUTPUT);
}


/****************************************************/
void loop(void) 
{
    int val = analogRead(33);


    if (val >= 0 && val <= 1023){
        digitalWrite(BLUE_LED_PIN, HIGH);
        digitalWrite(GREEN_LED_PIN, LOW);
        digitalWrite(YELLOW_LED_PIN, LOW);
        digitalWrite(RED_LED_PIN, LOW);
        
    }
    else if (val >= 1024 && val <= 2047){
        digitalWrite(GREEN_LED_PIN, HIGH);
        digitalWrite(BLUE_LED_PIN, LOW);
        digitalWrite(YELLOW_LED_PIN, LOW);
        digitalWrite(RED_LED_PIN, LOW);
    }
    else if (val >= 2048 && val <= 3071){
        digitalWrite(YELLOW_LED_PIN, HIGH);
        digitalWrite(BLUE_LED_PIN, LOW);
        digitalWrite(GREEN_LED_PIN, LOW);
        digitalWrite(RED_LED_PIN, LOW);
    }
    else if (val >= 3072 && val <= 4095){
        digitalWrite(RED_LED_PIN, HIGH);
        digitalWrite(BLUE_LED_PIN, LOW);
        digitalWrite(GREEN_LED_PIN, LOW);
        digitalWrite(YELLOW_LED_PIN, LOW);
    }

}
