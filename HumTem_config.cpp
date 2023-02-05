#include "mbed.h"
#include "HumTem_config.h"
#include "definitions.h"
#include "Keypad.h"
#include "Thread.h"

Range  BUFFER_RANGE[4];
TimeRange BUFFER_TR[2];

unsigned int BUFFER_config_RANGE[16] = {0};
unsigned int *puntero_RANGE = NULL;


unsigned int *puntero_RANGE_next = NULL;
unsigned int BUFFER_config_RANGE_next[16] = {0};

// Cambiar digito hacia la derecha
void Right_Range_A() {
	if (puntero_RANGE != &BUFFER_config_RANGE[15]) puntero_RANGE ++;
}
// Cambiar digito hacia la izquierda
void Left_Range_A(){
 if (puntero_RANGE != &BUFFER_config_RANGE[0]) puntero_RANGE --;
}

void saveKey_Range_A(char key) {
 int key_int = (int) (key - 48);
	
		 if ( key >= '0' && key <= '9' ) {
 				    
					if ( puntero_RANGE == &BUFFER_config_RANGE[15] ) {	
           *puntero_RANGE = key_int;
					}				
					else if ( puntero_RANGE == &BUFFER_config_RANGE[14] ) {
					 *puntero_RANGE = key_int;
					}
					else if ( puntero_RANGE == &BUFFER_config_RANGE[13] ) {
					 *puntero_RANGE = key_int;
					}
					else if ( puntero_RANGE == &BUFFER_config_RANGE[12] ) {
					 *puntero_RANGE = key_int;
					}
					else if ( puntero_RANGE == &BUFFER_config_RANGE[11] ) {
					 *puntero_RANGE = key_int;
					}
					else if ( puntero_RANGE == &BUFFER_config_RANGE[10] ) {
					 *puntero_RANGE = key_int;
					}
					else if ( puntero_RANGE == &BUFFER_config_RANGE[9] ) {
					 *puntero_RANGE = key_int;
					}
					else if ( puntero_RANGE == &BUFFER_config_RANGE[8] ) {
					 *puntero_RANGE = key_int;
					}
					
				   ///// Configuracion de la hora /////
					else if ( puntero_RANGE == &BUFFER_config_RANGE[7] ) {
					 *puntero_RANGE = key_int;
					}
					else if ( puntero_RANGE == &BUFFER_config_RANGE[6] ) {
						if (key_int <= 5) 
					 *puntero_RANGE = key_int;
					}
					
			  	else if ( puntero_RANGE == &BUFFER_config_RANGE[5] ) {				
					if ( BUFFER_config_RANGE[4] == 2 ) {
						if (key_int <= 3) 
						*puntero_RANGE = key_int; }
          else { 
						*puntero_RANGE = key_int; }							
					}		    
					else if ( puntero_RANGE == &BUFFER_config_RANGE[4] ) {				
					if ( (key_int == 2) && BUFFER_config_RANGE[5] <= 3 ) {
						*puntero_RANGE = key_int; }
          else if (key_int == 0 || key_int == 1 ){ 
						*puntero_RANGE = key_int; }							
					}
			
					else if ( puntero_RANGE == &BUFFER_config_RANGE[3] ) {
					 *puntero_RANGE = key_int;
					}
					else if ( puntero_RANGE == &BUFFER_config_RANGE[2] ) {
						if (key_int <= 5) 
					 *puntero_RANGE = key_int;
					}
			
				 	else if ( puntero_RANGE == &BUFFER_config_RANGE[1] ) {				
					if ( BUFFER_config_RANGE[0] == 2 ) {
						if (key_int <= 3) 
						*puntero_RANGE = key_int; }
          else { 
						*puntero_RANGE = key_int; }							
					}		    
					else if ( puntero_RANGE == &BUFFER_config_RANGE[0] ) {				
					if ( (key_int == 2) && BUFFER_config_RANGE[1] <= 3 ) {
						*puntero_RANGE = key_int; }
          else if (key_int == 0 || key_int == 1 ){ 
						*puntero_RANGE = key_int; }							
					}
			
   	 } // Fin if
    resetKey();			                                                   // reset de la tecla pulsada	
	
		 // Nuevas variables para representar	 
		 BUFFER_RANGE[HUM_a].lower0 = BUFFER_config_RANGE[12];
     BUFFER_RANGE[HUM_a].lower1 = BUFFER_config_RANGE[13];
	
	   BUFFER_RANGE[HUM_a].upper2 = BUFFER_config_RANGE[14];
     BUFFER_RANGE[HUM_a].upper3 = BUFFER_config_RANGE[15];
	
	   BUFFER_RANGE[TEMP_a].lower0 = BUFFER_config_RANGE[8];
     BUFFER_RANGE[TEMP_a].lower1 = BUFFER_config_RANGE[9];
	
	   BUFFER_RANGE[TEMP_a].upper2 = BUFFER_config_RANGE[10];
     BUFFER_RANGE[TEMP_a].upper3 = BUFFER_config_RANGE[11];
	    
	   BUFFER_TR[0].time_lower_min0 = BUFFER_config_RANGE[0];
	   BUFFER_TR[0].time_lower_min1 = BUFFER_config_RANGE[1];
		 BUFFER_TR[0].time_lower_hour2 = BUFFER_config_RANGE[2];
		 BUFFER_TR[0].time_lower_hour3 = BUFFER_config_RANGE[3];
		 
		 BUFFER_TR[0].time_upper_min0 = BUFFER_config_RANGE[4];
		 BUFFER_TR[0].time_upper_min1 = BUFFER_config_RANGE[5];
		 BUFFER_TR[0].time_upper_hour2 = BUFFER_config_RANGE[6];
		 BUFFER_TR[0].time_upper_hour3 = BUFFER_config_RANGE[7];
		 
 }

 
void reset_BUFFER_config_RANGE_A() {
	puntero_RANGE = &BUFFER_config_RANGE[15];                    // La configuración empieza por la humedad
	memset(&BUFFER_config_RANGE,0,sizeof(unsigned int)*16);      // Reset array
		
	   // Valores iniciales a representar 	
	   BUFFER_RANGE[HUM_a].lower0 = 0;
     BUFFER_RANGE[HUM_a].lower1 = 0;
	
	   BUFFER_RANGE[HUM_a].upper2 = 0;
     BUFFER_RANGE[HUM_a].upper3 = 0;
	
	   BUFFER_RANGE[TEMP_a].lower0 = 0;
     BUFFER_RANGE[TEMP_a].lower1 = 0;
	
	   BUFFER_RANGE[TEMP_a].upper2 = 0;
     BUFFER_RANGE[TEMP_a].upper3 = 0;
	    
	   BUFFER_TR[0].time_lower_min0 = 0;
	   BUFFER_TR[0].time_lower_min1 = 0;
		 BUFFER_TR[0].time_lower_hour2 = 0;
		 BUFFER_TR[0].time_lower_hour3 = 0;
		 
		 BUFFER_TR[0].time_upper_min0 = 0;
		 BUFFER_TR[0].time_upper_min1 = 0;
		 BUFFER_TR[0].time_upper_hour2 = 0;
		 BUFFER_TR[0].time_upper_hour3 = 0; 
}
 



// Cambiar digito hacia la derecha
void Right_Range_B() {
 if (puntero_RANGE_next != &BUFFER_config_RANGE_next[15]) puntero_RANGE_next ++;
}
// Cambiar digito hacia la izquierda
void Left_Range_B(){
 if (puntero_RANGE_next != &BUFFER_config_RANGE_next[0]) puntero_RANGE_next --;
}




void saveKey_Range_B(char key) {
 int key_int = (int) (key - 48);
	
			if ( key >= '0' && key <= '9' ) {
 				    
					if ( puntero_RANGE_next == &BUFFER_config_RANGE_next[15] ) {	
           *puntero_RANGE_next = key_int;
					  }				
					else if ( puntero_RANGE_next == &BUFFER_config_RANGE_next[14] ) {
					 *puntero_RANGE_next = key_int;
				   	}
					else if ( puntero_RANGE_next == &BUFFER_config_RANGE_next[13] ) {
					 *puntero_RANGE_next = key_int;
						}
					else if ( puntero_RANGE_next == &BUFFER_config_RANGE_next[12] ) {
					 *puntero_RANGE_next = key_int;
						}
					else if ( puntero_RANGE_next == &BUFFER_config_RANGE_next[11] ) {
					 *puntero_RANGE_next = key_int;
						}
					else if ( puntero_RANGE_next == &BUFFER_config_RANGE_next[10] ) {
					 *puntero_RANGE_next = key_int;
						}
					else if ( puntero_RANGE_next == &BUFFER_config_RANGE_next[9] ) {
					 *puntero_RANGE_next = key_int;
						}
					else if ( puntero_RANGE_next == &BUFFER_config_RANGE_next[8] ) {
					 *puntero_RANGE_next = key_int; 
						}
					
					///// Configuracion de la hora /////
					else if ( puntero_RANGE_next == &BUFFER_config_RANGE_next[7] ) {
					 *puntero_RANGE_next = key_int;
						}
					else if ( puntero_RANGE_next == &BUFFER_config_RANGE_next[6] ) {
						if (key_int <= 5) 
					 *puntero_RANGE_next = key_int;
						}
						
			  	else if ( puntero_RANGE_next == &BUFFER_config_RANGE_next[5] ) {				
					   if ( BUFFER_config_RANGE[4] == 2 ) {
								if (key_int <= 3) 
						    *puntero_RANGE_next = key_int; }
								else { 
								*puntero_RANGE_next = key_int; }							
							}		    
					else if ( puntero_RANGE_next == &BUFFER_config_RANGE_next[4] ) {				
							if ( (key_int == 2) && BUFFER_config_RANGE_next[5] <= 3 ) {
									*puntero_RANGE_next = key_int; }
							else if (key_int == 0 || key_int == 1 ){ 
									*puntero_RANGE_next = key_int; }							
						}
			
					else if ( puntero_RANGE_next == &BUFFER_config_RANGE_next[3] ) {
							*puntero_RANGE_next = key_int;
						}
					else if ( puntero_RANGE_next == &BUFFER_config_RANGE_next[2] ) {
								if (key_int <= 5) 
								*puntero_RANGE_next = key_int;
						}
			
				 	else if ( puntero_RANGE_next == &BUFFER_config_RANGE_next[1] ) {				
							if ( BUFFER_config_RANGE[0] == 2 ) {
									if (key_int <= 3) 
										*puntero_RANGE_next = key_int; }
									else { 
										*puntero_RANGE_next = key_int; }							
						}		    
					else if ( puntero_RANGE_next == &BUFFER_config_RANGE_next[0] ) {				
								if ( (key_int == 2) && BUFFER_config_RANGE_next[1] <= 3 ) {
									*puntero_RANGE_next = key_int; }
								else if (key_int == 0 || key_int == 1 ){ 
									*puntero_RANGE_next = key_int; }							
						}
			
   	}
    resetKey();				                                                   // Reset de la tecla pulsada
	
		 // Nuevas variables para representar	 		
		 BUFFER_RANGE[HUM_b].lower0 = BUFFER_config_RANGE_next[12];
     BUFFER_RANGE[HUM_b].lower1 = BUFFER_config_RANGE_next[13];
		
	   BUFFER_RANGE[HUM_b].upper2 = BUFFER_config_RANGE_next[14];
     BUFFER_RANGE[HUM_b].upper3 = BUFFER_config_RANGE_next[15];
	
	   BUFFER_RANGE[TEMP_b].lower0 = BUFFER_config_RANGE_next[8];
     BUFFER_RANGE[TEMP_b].lower1 = BUFFER_config_RANGE_next[9];
		
	   BUFFER_RANGE[TEMP_b].upper2 = BUFFER_config_RANGE_next[10];
     BUFFER_RANGE[TEMP_b].upper3 = BUFFER_config_RANGE_next[11];
		 
		 BUFFER_TR[1].time_lower_min0 = BUFFER_config_RANGE_next[0];
	   BUFFER_TR[1].time_lower_min1 = BUFFER_config_RANGE_next[1];
		 BUFFER_TR[1].time_lower_hour2 = BUFFER_config_RANGE_next[2];
		 BUFFER_TR[1].time_lower_hour3 = BUFFER_config_RANGE_next[3];
		 
		 BUFFER_TR[1].time_upper_min0 = BUFFER_config_RANGE_next[4];
		 BUFFER_TR[1].time_upper_min1 = BUFFER_config_RANGE_next[5];
		 BUFFER_TR[1].time_upper_hour2 = BUFFER_config_RANGE_next[6];
		 BUFFER_TR[1].time_upper_hour3 = BUFFER_config_RANGE_next[7];
	
}


void reset_BUFFER_config_RANGE_B() {
	puntero_RANGE_next = &BUFFER_config_RANGE_next[15];            // La configuración empieza por la humedad
	memset(&BUFFER_config_RANGE_next,0,sizeof(unsigned int)*16);   // Reset array	
	
		 // Valores iniciales a representar 
		 BUFFER_RANGE[HUM_b].lower0 = 0;
     BUFFER_RANGE[HUM_b].lower1 = 0;
	   BUFFER_RANGE[HUM_b].upper2 = 0;
     BUFFER_RANGE[HUM_b].upper3 = 0;
	
	   BUFFER_RANGE[TEMP_b].lower0 = 0;
     BUFFER_RANGE[TEMP_b].lower1 = 0;
	   BUFFER_RANGE[TEMP_b].upper2 = 0;
     BUFFER_RANGE[TEMP_b].upper3 = 0;	
		 
		 BUFFER_TR[1].time_lower_min0 = 0;
	   BUFFER_TR[1].time_lower_min1 = 0;
		 BUFFER_TR[1].time_lower_hour2 = 0;
		 BUFFER_TR[1].time_lower_hour3 = 0;
		 
		 BUFFER_TR[1].time_upper_min0 = 0;
		 BUFFER_TR[1].time_upper_min1 = 0;
		 BUFFER_TR[1].time_upper_hour2 = 0;
		 BUFFER_TR[1].time_upper_hour3 = 0;
		 
}
