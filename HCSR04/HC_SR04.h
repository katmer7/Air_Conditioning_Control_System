#include "mbed.h"

#ifndef  _HC_SR04_H_
#define  _HC_SR04_H_

extern Timer time_echo;
extern float tiempo_sr04;
extern float distancia_medida;
extern int flag_distancia_min;

void flanco_subida_echo();
void flanco_bajada_echo();
void function_trigger();
void distancia_objeto();
int deteccion();
#endif
