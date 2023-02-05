#include "mbed.h"
#include "DHT22.h"
#include "hardware.h"


// Variables
int BUFFER_DHT22 [5]; // ARRAY PARA ALMACENAR LOS DATOS
int BUFFER_RESULTADO;
int BUFFER_PARITY;
int hum_almacenada, humedad, temperatura, temp_almacenada;
int data_bit, data_8bit, i, j;


void sensor_data() {
	
	 dht.output();   // pin como salida
   dht.write(0);   // escribimos un nivel bajo
	
   wait_ms(10);      // tiempo minimo que hay q esperar para recibir una respuesta del sensor
	
   dht.write(1);
	 wait_us(100);
   dht.input();

   wait_us(80);
	 
 // Empieza comunicacion con el sensor
	
    for (i=0; i<5; i++) {
			
        for (j=0; j<8; j++) {
					  // Espera uno/cero
            while (dht);
            while (!dht);
				    // Almacena los 40 bits de datos
            wait_us(50);
            data_bit = dht;          						
            data_bit = data_bit << (7-j);
            data_8bit = data_8bit|data_bit;
        }
        BUFFER_DHT22[i] = data_8bit;
				data_8bit = 0;
    }		
checksum(); // comprobar la paridad
}


void checksum() {
	
  BUFFER_RESULTADO = BUFFER_DHT22[0] + BUFFER_DHT22[1] +BUFFER_DHT22[2] + BUFFER_DHT22[3];
  BUFFER_RESULTADO = BUFFER_RESULTADO % 256;
	BUFFER_PARITY = BUFFER_DHT22[4];
	
	if ( BUFFER_RESULTADO == BUFFER_PARITY ) {
		
		humedad = BUFFER_DHT22[0]*256 + BUFFER_DHT22[1];
    hum_almacenada = humedad; // guardamos el valor en una señal adicional
    
		temperatura = BUFFER_DHT22[2]*256 + BUFFER_DHT22[3];	
		temp_almacenada = temperatura;
		
		}
}

