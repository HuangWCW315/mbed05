#include "mbed.h"

Ticker time_up;
DigitalOut redLED(LED1);
DigitalIn SW(SW3);
void blink(){
    redLED = !redLED;
}

int main(){
    time_up.attach( &blink, 1 );
    while(1)
    {
        if (SW == 0)
            time_up.detach();
    }
}