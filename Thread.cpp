#include "mbed.h"
#include "Thread.h"
#include "Remote_Control.h"

// Hilo para el automata de control del sistema
Thread SISTEMA;
// Hilo para el automata de configuracion del sistema
Thread CONF_SISTEMA;
// Hilo para cargar la hora y fecha
Thread SET_RTC;
// Hilo para obtener los datos de hoa y fecha
Thread DATA_RTC;
// Hilo para representar los datos por el LCD
Thread LCD;
// Hilo que gestiona la contraseña
Thread PASSWORD;
// Hilo para el sensor de temperatura/humedad
Thread DHT22;
// Hilo para el sensor de distancia
Thread HCSR04;
