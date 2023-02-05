#include "mbed.h"

#ifndef MBED_DHT22_H
#define MBED_DHT22_H
 
 void sensor_data();
 void checksum();
 
extern int BUFFER_DHT22[]; // ARRAY PARA ALMACENAR LOS DATOS
extern int BUFFER_RESULTADO;
extern int BUFFER_PARITY;
extern int hum_almacenada, humedad, temperatura, temp_almacenada;
extern int data_bit, data_8bit, i, j;

#endif
