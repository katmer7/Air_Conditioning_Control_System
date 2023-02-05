#include "mbed.h"
#include "HumTem_config.h"
#include "SetTime.h"
#include "DHT22.h"
#include "definitions.h"
#include "HumTem_config.h"


// Variables digitos del RTC
unsigned int hora_unidades;
unsigned int hora_decenas;
unsigned int min_unidades;
unsigned int min_decenas;
// Variables hora y minutos RTC
unsigned int hora_rtc;
unsigned int minutos_rtc;
// Variables Hora y minutos del Rango A (izq)
unsigned int hora_rangoA_i;
unsigned int minutos_rangoA_i;
//                                      (dcha)
unsigned int hora_rangoA_d;
unsigned int minutos_rangoA_d;         
// Variables Hora y minutos del Rango B (izq)
unsigned int hora_rangoB_i;
unsigned int minutos_rangoB_i;
//                                      (dcha)
unsigned int hora_rangoB_d;
unsigned int minutos_rangoB_d;     

// Variables para el calculo de la PWM
unsigned int numero_izq;	    // Rango izquierda de la tabla
unsigned int numero_dcha;    // Rango derecha de la tabla
float numero_programado;    // Valor medio
float diferencia;           // Diferencia entre la temperatura media y el valor medio
float porcentaje; // ciclo de trabajo
float periodo;    // periodo de la señal

unsigned int aviso;

// Variables humedad Rango 
unsigned int hum_rango_i;  //(izq)
unsigned int hum_rango_d;  // (dcha)                                            


unsigned int humificando;
float humedad_programada;

unsigned int flag_a; // falta q lo haga solo en el rango horario correspondiente
unsigned int flag_b;


void PWM_config() {

          // Numero de los rangos	
			if (flag_a == 1) {	
				numero_izq = BUFFER_RANGE[TEMP_a].lower0 * 10 + BUFFER_RANGE[TEMP_a].lower1;    // 20 ej.
				numero_dcha = BUFFER_RANGE[TEMP_a].upper2 * 10 + BUFFER_RANGE[TEMP_a].upper3 ;  // 27 ej.   
				}
			else if (flag_b == 1) {	
				numero_izq = BUFFER_RANGE[TEMP_b].lower0 * 10 + BUFFER_RANGE[TEMP_b].lower1;    // 15 ej.
				numero_dcha = BUFFER_RANGE[TEMP_b].upper2 * 10 + BUFFER_RANGE[TEMP_b].upper3 ;  // 22 ej.
				}	
	
	
			if ( ( (temp_almacenada/10.0) >= numero_izq*1.0) && ( (temp_almacenada/10.0) <= numero_dcha*1.0) )  {

					// Numero progrmado ( mitad de los rangos )	
							numero_programado = (numero_dcha*1.0 + numero_izq*1.0)/2.0;

					// nivel alto
							diferencia = (temp_almacenada/10.0) - numero_programado;
							if (diferencia  < 0.0) {
									diferencia = 0 - diferencia;
								}
	
						// Hay que diferenciar entre dos periodos
							if (numero_programado > (temp_almacenada/10.0)) {	 
								periodo = numero_programado - numero_izq*1.0;	 									
							}
						else {
								periodo = numero_dcha*1.0 - numero_programado;  	 
							}	
						
							porcentaje = diferencia / (periodo*1.0);
			}
			else {
				porcentaje = 0.0;
			}
			
				// Rango A
	if (flag_a == 1) {
	hum_rango_i = BUFFER_RANGE[HUM_a].lower0*10 + BUFFER_RANGE[HUM_a].lower1;
	hum_rango_d = BUFFER_RANGE[HUM_a].upper2*10 + BUFFER_RANGE[HUM_a].upper3;
	}
	else if ( flag_b == 1) {
	// Rango B
	hum_rango_i = BUFFER_RANGE[HUM_b].lower0*10 + BUFFER_RANGE[HUM_b].lower1;
  hum_rango_d = BUFFER_RANGE[HUM_b].upper2*10 + BUFFER_RANGE[HUM_b].upper3;
	}

}	
	
	
void comprobacion_rango_horario() {
	
	   // Hora de char a entero por digito
		 hora_unidades =(int) (hora1 - 48);
	   hora_decenas = (int) (hora0 - 48); 
     min_unidades = (int) (min1 - 48);
	   min_decenas =  (int) (min0 - 48);
	
	   // Hora y minutos
	   hora_rtc = hora_decenas*10 + hora_unidades;
	   minutos_rtc = min_decenas*10 + min_unidades;
	
	   // Hora y minutos del Rango A (izq)
	   hora_rangoA_i = BUFFER_TR[0].time_lower_min0*10 + BUFFER_TR[0].time_lower_min1;
     minutos_rangoA_i = BUFFER_TR[0].time_lower_hour2*10 + 	BUFFER_TR[0].time_lower_hour3;
	   // Hora y minutos del Rango A (dcha)	
	   hora_rangoA_d = BUFFER_TR[0].time_upper_min0*10 + BUFFER_TR[0].time_upper_min1;
     minutos_rangoA_d = BUFFER_TR[0].time_upper_hour2*10 + 	BUFFER_TR[0].time_upper_hour3;	
	
	   // Hora y minutos del Rango B (izq)
	   hora_rangoB_i = BUFFER_TR[1].time_lower_min0*10 + BUFFER_TR[1].time_lower_min1;
     minutos_rangoB_i = BUFFER_TR[0].time_lower_hour2*10 + 	BUFFER_TR[1].time_lower_hour3;
	   // Hora y minutos del Rango B (dcha)	
	   hora_rangoB_d = BUFFER_TR[1].time_upper_min0*10 + BUFFER_TR[0].time_upper_min1;
     minutos_rangoB_d = BUFFER_TR[1].time_upper_hour2*10 + 	BUFFER_TR[1].time_upper_hour3;	
		
	

	 if ( ((hora_rtc == hora_rangoA_i && minutos_rtc >= minutos_rangoA_i) || (hora_rtc > hora_rangoA_i)) && ((hora_rtc <= hora_rangoA_d)  ||  (hora_rtc == hora_rangoA_d && minutos_rtc < minutos_rangoA_d)) ) {
            flag_a = 1;	      
						PWM_config();	
			
    } // Rango A
	 
	 else if ( ((hora_rtc == hora_rangoB_i && minutos_rtc >= minutos_rangoB_i) || (hora_rtc > hora_rangoB_i )) || ((hora_rtc <= hora_rangoB_d)  ||  (hora_rtc == hora_rangoB_d && minutos_rtc < hora_rangoB_d)) ) { // comparacion todo el rango	
            flag_b = 1;		 
				    PWM_config();		 
	  } // Rango B 
	  
}



int comprobacion_humedad() {
	
		 if ( ((hum_almacenada/10.0) >= hum_rango_i*1.0) && ( (hum_almacenada/10.0) <= hum_rango_d*1.0) ) {      

				   humedad_programada = (hum_rango_i*1.0 + hum_rango_d*1.0)/2.0;
				 
				  if ( hum_almacenada/10.0 < humedad_programada) {
						humificando = 1;
					}
					else 
						humificando = 0;	 		 
    } 
		 
		return humificando;
	
}



int programacion_lcd() { // rehacer
comprobacion_humedad();
	
	// Dentro del rango  horario A o B, y esty dentro de los rangos de temperatura y humedad
	if ( ( (temp_almacenada/10.0) >= numero_izq*1.0) && ( (temp_almacenada/10.0) <= numero_dcha*1.0) && (flag_a == 1 || flag_b == 1) && ((hum_almacenada/10.0) >= hum_rango_i*1.0) && ( (hum_almacenada/10.0) <= hum_rango_d*1.0) ) {    
	
      if ( (numero_programado > (temp_almacenada/10.0)) && comprobacion_humedad() == 0 ) { // Temp debajo de la programada y hum = 0 CALENTANDO
				
				aviso = 1;
			}
			else if ( (numero_programado > (temp_almacenada/10.0)) && comprobacion_humedad() == 1 ) { // Calentando y humificando
			
				aviso = 2;				
			}
			else if ( (numero_programado < (temp_almacenada/10.0)) && comprobacion_humedad() == 0 ) { // ENFRIANDO
			
				aviso = 3;				
			}
			else if ( (numero_programado < (temp_almacenada/10.0)) && comprobacion_humedad() == 1 ) { // ENFRIANDO y HUMIFICANDO
			
				aviso = 4;				
			}
			else if ( (numero_programado == (temp_almacenada/10.0)) && comprobacion_humedad() == 0 ) { // temperatura = valor programado
				
        aviso = 5;
			}
			else if ( (numero_programado == (temp_almacenada/10.0)) && comprobacion_humedad() == 1 ) { // temperatura = valor programado y HUMIFICANDO
				
        aviso = 6;
			}
	
	}
  // Estoy dentro del rango horario pero no sty dentro de alguno de los rangos de temperatura o humedad ( aqui cambio de estado )
	else if (flag_a == 1 || flag_b == 1) {              
		
			aviso = 7;	
	}
	// no estoy dentro de ninguno de los rangos horarios ( no monitorizo nada )
	else if (flag_a == 0 && flag_b == 0) {    
	
			aviso = 8;			
	}		
	return aviso;
}




