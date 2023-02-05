#include "mbed.h"
#include "SetTime.h"
#include "Keypad.h"
#include "Thread.h"

// Variables que almacenan la fecha y hora del RTC
char buffer_dia[3];
char buffer_mes[3];
char buffer_annio[4];
char buffer_hora[3];
char buffer_min[3];
char buffer_seg[3];

char dia0;
char mes0;
char hora0;
char min0;
char seg0;

char annio0;
char annio1;
char annio2;
char annio3;

char dia1;
char mes1;
char hora1;
char min1;
char seg1;

// Variables para almacenar la fecha y hora configuradas
struct time time_config;
unsigned int BUFFER_TIME[14] = {0};

unsigned int *puntero_LCD = NULL;

// Funcion para cambiar de digito hacia la derecha
void Right() { 
	if (puntero_LCD != &BUFFER_TIME[13]) puntero_LCD ++;
}

// Funcion para cambiar de digito hacia la izquierda
void Left() { 
	if (puntero_LCD != &BUFFER_TIME[0]) puntero_LCD --;
}

// Funcion que almacena los nuevos valores
void saveKey(char key) {
	int key_int = (int) (key - 48);
	
			if ( key >= '0' && key <= '9' ) {
	
				
				if ( puntero_LCD == &BUFFER_TIME[9] ) {				
					if ( BUFFER_TIME[8] == 1 ) {
						if (key_int <= 1) 
						*puntero_LCD = key_int; }
         else { 
						*puntero_LCD = key_int; }							
       }
		
				else if ( puntero_LCD == &BUFFER_TIME[8] ) {				
					if ( (key_int == 1) && BUFFER_TIME[9] <= 1 ) {
						*puntero_LCD = key_int; }
          else if (key_int == 0){ 
						*puntero_LCD = key_int; }							
        }
				
				else if ( puntero_LCD == &BUFFER_TIME[7] ) {				
					if ( BUFFER_TIME[6] == 3 ) {
						 if (key_int <= 1) 
						  *puntero_LCD = key_int; }
          else { 
						  *puntero_LCD = key_int; }							
       } 
				
			 else if ( puntero_LCD == &BUFFER_TIME[6] ) {				
					if ( (key_int == 3) && BUFFER_TIME[7] <= 1 ) {
						*puntero_LCD = key_int; }
          else if (key_int == 0 || key_int == 1 || key_int == 2){ 
						*puntero_LCD = key_int; }							
        }
        
				else if ( puntero_LCD == &BUFFER_TIME[5] ) {				
						*puntero_LCD = key_int; 			
        }
				
				else if ( puntero_LCD == &BUFFER_TIME[4] ) {				
						if (key_int <= 5) 
						  *puntero_LCD = key_int; 			
        }
				
       else if ( puntero_LCD == &BUFFER_TIME[3] ) {				
						*puntero_LCD = key_int; 			
        }
				
				else if ( puntero_LCD == &BUFFER_TIME[2] ) {				
						if (key_int <= 5) 
						  *puntero_LCD = key_int; 			
        }				
		    
				else if ( puntero_LCD == &BUFFER_TIME[1] ) {				
					if ( BUFFER_TIME[0] == 2 ) {
						if (key_int <= 3) 
						*puntero_LCD = key_int; }
         else { 
						*puntero_LCD = key_int; }							
       }
		    
			 else if ( puntero_LCD == &BUFFER_TIME[0] ) {				
					if ( (key_int == 2) && BUFFER_TIME[1] <= 3 ) {
						*puntero_LCD = key_int; }
          else if (key_int == 0 || key_int == 1 ){ 
						*puntero_LCD = key_int; }							
        }
			 ///// Configuracion del año /////
			 else if ( puntero_LCD == &BUFFER_TIME[13] ) {				
					if ( BUFFER_TIME[11] == 2 ) {
						if (key_int == 0) 
						*puntero_LCD = key_int; }
         else { 
						*puntero_LCD = key_int; }							
       }
			 
			 else if ( puntero_LCD == &BUFFER_TIME[12] ) {				
					if ( BUFFER_TIME[11] == 2 ) {
						if (key_int == 0) 
						*puntero_LCD = key_int; }
         else { 
						*puntero_LCD = key_int; }							
       }
			 
			 else if ( puntero_LCD == &BUFFER_TIME[11] ) {				
					if ( (key_int <= 2)  && BUFFER_TIME[12] == 0 && BUFFER_TIME[13] == 0 ) {
						*puntero_LCD = key_int;
					}					
         else if (key_int == 0 || key_int == 1 ) { 
						*puntero_LCD = key_int; 
				  }							
       }							
       		 
			 else if ( puntero_LCD == &BUFFER_TIME[10] ) {				
						if (key_int == 0) 
						*puntero_LCD = key_int; 					
       }
				 
		 
			 
			 
	 } // Fin if.
    
	 resetKey();	                                                   // Reset de la tecla pulsada
	 
	 
    // Nuevas variables para representar	 
	  time_config.hour = BUFFER_TIME[0]*10 + BUFFER_TIME[1];
	  time_config.min = BUFFER_TIME[2]*10 + BUFFER_TIME[3]; 
    time_config.sec = BUFFER_TIME[4]*10 + BUFFER_TIME[5]; 

    time_config.day = BUFFER_TIME[6]*10 + BUFFER_TIME[7]; 
    time_config.month = BUFFER_TIME[8]*10 + BUFFER_TIME[9]; 
    time_config.year = BUFFER_TIME[10]*1000 + BUFFER_TIME[11]*100 + BUFFER_TIME[12]*10 + BUFFER_TIME[13]; 	 
 
}


void reset_BUFFER_TIME() {
	
	puntero_LCD = &BUFFER_TIME[13];                  // La configuracion empieza por los años
	memset(&BUFFER_TIME,0,sizeof(unsigned int)*14);  // Reset del array que almacena la fecha y hora
	
	// Valores iniciales a representar 
		time_config.hour = 0;
	  time_config.min = 0; 
    time_config.sec = 0; 
    time_config.day = 0; 
    time_config.month = 0; 
    time_config.year = 0; 	
	
}
