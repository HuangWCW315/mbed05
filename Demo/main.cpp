#include "mbed.h"
#include "mbed_events.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
InterruptIn btn(SW2);
InterruptIn btn1(SW3);
Serial pc( USBTX, USBRX );

EventQueue operate_at_low_priority;
EventQueue operate_at_high_priority;

void mission_high()
{
  int count = 0;
  for (int i = 0; i < 10000; i++)
    count++;
  pc.printf("High completes mission!\r\n");
}

void mission_low()
{
  int count = 0;
  for (int i = 0; i < 10000; i++)
    count++;
  pc.printf("Low completes mission!\r\n");
}

int main() {
  // low priority thread for calling printf()
  Thread LowThread(osPriorityLow);
  LowThread.start(callback(&operate_at_low_priority, &EventQueue::dispatch_forever));

  // normal priority thread for other events
  Thread HighThread(osPriorityHigh);
  HighThread.start(callback(&operate_at_high_priority, &EventQueue::dispatch_forever));

  // button fall still runs in the ISR
  operate_at_low_priority.call(&mission_low);
  operate_at_high_priority.call(&mission_high);
  while (1) {wait(1);}
}