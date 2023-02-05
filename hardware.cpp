#include "mbed.h"
#include "hardware.h"
#include "rtos.h"
#include "Thread.h"

//Pines RGB
PwmOut R (p23);
PwmOut G (p24);
PwmOut B (p25);
// Pines LCD.
C12832 lcd (p5,p7,p6,p8,p11);
// Pines Joystick
InterruptIn button (p14);
InterruptIn button_down (p12);
// Pin DHT22
DigitalInOut dht (p9);
// Pines HCSR04
DigitalOut  Trigger (p30);
InterruptIn Echo (p29);  
// Pin IR receiver
InterruptIn ir (p28);
// Pin speaker
PwmOut spkr (p22);
// LED4
DigitalOut led4 (LED4);
