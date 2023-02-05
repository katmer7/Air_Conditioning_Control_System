#include "mbed.h"
#include "C12832.h"

#ifndef  _HARDWARE_H_
#define  _HARDWARE_H_

//Pines RGB
extern PwmOut R;
extern PwmOut G;
extern PwmOut B;
// Pines LCD.
extern C12832 lcd;
// Pines Joystick
extern InterruptIn button;
extern InterruptIn button_down;
// Pin DHT22
extern DigitalInOut dht;
// Pines HCSR04
extern DigitalOut  Trigger;
extern InterruptIn Echo;  
// Pin IR receiver
extern InterruptIn ir;
// Pin speaker
extern PwmOut spkr;
// LED4
extern DigitalOut led4;
#endif
