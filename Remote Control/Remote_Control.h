#include "mbed.h"
#include "Thread.h"

#ifndef  _REMOTE_CONTROL_H_
#define  _REMOTE_CONTROL_H_

// Timer para contar la duracion del pulso a nivel bajo 
extern Timer time_IR;
// Variable que almacena el tiempo de duracion de un bit de datos
extern unsigned int time_bit;

// En orden
// Variable que almacena el bit de start
// Variable para almacenar cada bit del comando del control remoto
// Variable para almacenar cada bit de la direccion del control remoto
// Variable que contiene el comando
// Variable que contiene la direccion
// Variable que contiene el ultimo comando pulsado
// Variable que contiene la ultima direccion pulsada
// Flag para indicar que se ha pulsado el boton correcto
extern unsigned int data_ir, data_direccion, comando, direccion, comando_ultimo, direccion_ultima, flag_boton_correcto;

// Funcion para parar y leer el timer cuando se detecte una interrupcion por flanco de subida
void flanco_subida_IR();
// Funcion para resetear y arrancar el timer cuando se detecte una interrupcion por flanco de bajada
void flanco_bajada_IR();
void mando();
#endif
