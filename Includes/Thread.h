#include "mbed.h"

#ifndef  _THREAD_H_
#define  _THREAD_H_

// Hilo para el automata de control del sistema
extern Thread SISTEMA;
// Hilo para el automata de configuracion del sistema
extern Thread CONF_SISTEMA;
// Hilo para cargar la hora y fecha
extern Thread SET_RTC;
// Hilo para obtener los datos de hoa y fecha
extern Thread DATA_RTC;
// Hilo para representar los datos por el LCD
extern Thread LCD;
// Hilo que gestiona la contraseña
extern Thread PASSWORD;
// Hilo para el sensor de temperatura/humedad
extern Thread DHT22;
// Hilo para el sensor de distancia
extern Thread HCSR04;
#endif
