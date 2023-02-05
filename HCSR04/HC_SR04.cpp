#include "mbed.h"
#include "HC_SR04.h"
#include "hardware.h"


Serial pc (USBTX, USBRX);
Timer time_echo;
float tiempo_sr04 = 0.0;
float distancia_medida = 0.0;
int flag_distancia_min = 0;


/**
 * Funcion llamada por la interrupcion de la Fila 1
 */

void flanco_subida_echo()
{

	time_echo.start();
}

void flanco_bajada_echo()
{
	time_echo.stop();
	tiempo_sr04 = time_echo.read_us();
}

void distancia_objeto()
{
   time_echo.reset();
	 Trigger=1;           // trig tiene que estar a 1 un minimo de 10us, podriamos haber usado un wait_us 
	 Thread::wait(1);  // pero parece más importante liberar la cpu ya que con un ms funciona igual
   Trigger=0;           // cabe destacar que el valor de distancia usado será el de la ultima ejecución de la función
	
	 distancia_medida = tiempo_sr04/58;
}

int deteccion () {

	if (distancia_medida > 0.0 && distancia_medida < 10.0) {
		flag_distancia_min = 1;	
	}
	else {
		flag_distancia_min = 0;
	}
	
	return flag_distancia_min;
}
