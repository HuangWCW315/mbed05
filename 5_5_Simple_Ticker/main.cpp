#include "mbed.h"

Ticker time_up;
DigitalOut blueLED(LED_BLUE);
DigitalIn switch1(SW2);
DigitalIn switch2(SW3);
void blink(){
    blueLED = !blueLED;
}

int main(){
    time_up.attach( &blink, 0.5f );
    while(1)
    {
        if (switch2 == 0)
            time_up.detach();
        if (switch1 == 0)
            time_up.attach( &blink, 0.5f );
        
    }
}