#include "mbed.h"
#include "Thread.h"

#ifndef  _JOYSTICK_H_
#define  _JOYSTICK_H_

// Timer para los rebotes
extern Timer bounce;

// Funcion para la interrupcion del boton central
void function_button();	
// Funcion para la interrupcion del boton de bajada
void function_button_down();

#endif
