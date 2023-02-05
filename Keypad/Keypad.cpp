#include "mbed.h"
#include "Keypad.h"
#include "joystick.h"

InterruptIn row1(p21);
InterruptIn row2(p13);
InterruptIn row3(p15);
InterruptIn row4(p16);														 
BusOut columns (p20, p19, p18, p17);

uint8_t row;
uint8_t column;
char key;


char last_key;	
int flag_key;


/**
 * Funcion llamada por la interrupcion de la columna 1
 */
void Frow1() {
	if (bounce.read_ms() > 100){
		row = 1;
		bounce.reset();
		getKey();

	}
}

/**
 * Funcion llamada por la interrupcion de la columna 2
 */
void Frow2() {
	if (bounce.read_ms() > 100){
		row = 2;
		bounce.reset();
		getKey();
	}
}

/**
 * Funcion llamada por la interrupcion de la columna 3
 */
void Frow3() {
	if (bounce.read_ms() > 100){
		row = 3;
		bounce.reset();
		getKey();
	}
}

/**
 * Funcion llamada por la interrupcion de la columna 4
 */
void Frow4() {
	if (bounce.read_ms() > 100){
		row = 4;
		bounce.reset();
		getKey();
	}
}

/**
 * Funcion que devuelve la tecla pulsada
 */
void getKey(){
	for (int i= 0; i< 4; i++){
		columns = 0x1 << i;

		if (row1.read() || row2.read() || row3.read() || row4.read()){
			column = i;
			key = keyTable[row-1][column];
			last_key = key;
			flag_key = 1;
			break;
		}
	}
	columns = 0xF;
}		

void resetKey(){
	key = 'X';
	flag_key = 0;
	columns = 0xF;
}
