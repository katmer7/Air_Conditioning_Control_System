#include "mbed.h"


#ifndef  _PWM_CONFIG_H_
#define  _PWM_CONFIG_H_

// Variables digitos del RTC
extern unsigned int hora_unidades;
extern unsigned int hora_decenas;
extern unsigned int min_unidades;
extern unsigned int min_decenas;
// Variables hora y minutos RTC
extern unsigned int hora_rtc;
extern unsigned int minutos_rtc;
// Variables Hora y minutos del Rango A (izq)
extern unsigned int hora_rangoA_i;
extern unsigned int minutos_rangoA_i;
//                                      (dcha)
extern unsigned int hora_rangoA_d;
extern unsigned int minutos_rangoA_d;         
// Variables Hora y minutos del Rango B (izq)
extern unsigned int hora_rangoB_i;
extern unsigned int minutos_rangoB_i;
//                                      (dcha)
extern unsigned int hora_rangoB_d;
extern unsigned int minutos_rangoB_d;     

// Variables para el calculo de la PWM
extern unsigned int numero_izq;	    // Rango izquierda de la tabla
extern unsigned int numero_dcha;    // Rango derecha de la tabla
extern float numero_programado;    // Valor medio
extern float diferencia;           // Diferencia entre la temperatura media y el valor medio
extern float porcentaje; // ciclo de trabajo
extern float periodo;    // periodo de la señal

extern unsigned int aviso;

// Variables humedad Rango 
extern unsigned int hum_rango_i;  //(izq)
extern unsigned int hum_rango_d;  // (dcha)                                            


extern unsigned int humificando;
extern float humedad_programada;

extern unsigned int flag_a; // falta q lo haga solo en el rango horario correspondiente
extern unsigned int flag_b;

void PWM_config();
void comprobacion_rango_horario();
int comprobacion_humedad();
int programacion_lcd();

#endif
