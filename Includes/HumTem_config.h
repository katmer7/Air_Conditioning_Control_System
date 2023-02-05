#include "mbed.h"
#include "LCD_config.h"

#ifndef  _DHT22_H_
#define  _DHT22_H_

// Variables para almacenar el rango de TEMP y HUM.
typedef struct {
	/***Rango Inferior**/
	unsigned int lower0;
	unsigned int lower1;
	/***Rango superior***/
	unsigned int upper2;
	unsigned int upper3;
} Range;
extern Range BUFFER_RANGE[4];

// Variables para almacenar el rango HORARIO.
typedef struct {
	/***Rango Inferior ***/
	unsigned int time_lower_min0;
	unsigned int time_lower_min1;
	unsigned int time_lower_hour2;
	unsigned int time_lower_hour3;
	/***Rango superior ***/
	unsigned int time_upper_min0;
	unsigned int time_upper_min1;
	unsigned int time_upper_hour2;
	unsigned int time_upper_hour3;
} TimeRange;
extern TimeRange BUFFER_TR[2];

///*** para guardar rangos ***///
void saveKey_Range_A(char key);
void saveKey_Range_B(char key);

// Funciones para cambiar de digito
void Right_Range_A();
void Left_Range_A();

void Right_Range_B();
void Left_Range_B();

extern unsigned int *puntero_RANGE;
extern unsigned int BUFFER_config_RANGE[];
void reset_BUFFER_config_RANGE_A();               // reset del buffer que almacena el nuevo rango

extern unsigned int *puntero_RANGE_next;
extern unsigned int BUFFER_config_RANGE_next[];
void reset_BUFFER_config_RANGE_B();               // reset del buffer que almacena el nuevo rango

#endif
