#include "mbed.h"
#include "joystick.h"
#include "hardware.h"
#include "Thread.h"
#include "Remote_Control.h"

// Timer para los rebotes
Timer bounce;

// Funcion para la interrupcion del boton central
void function_button() {
	if (bounce.read_ms() > 200) {
		bounce.reset();	
		flag_boton_correcto = 1;
    SISTEMA.signal_set(0x0001);
	}	
}

// Funcion para la interrupcion del boton de bajada
void function_button_down() {
	if (bounce.read_ms() > 200) {
		bounce.reset();	
    SISTEMA.signal_set(0x0200);
	}		
}
