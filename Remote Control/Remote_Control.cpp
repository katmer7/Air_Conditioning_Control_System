#include "mbed.h"
#include "Remote_Control.h"
#include "joystick.h"
#include "hardware.h"
#include "Thread.h"

// Timer para contar la duracion del pulso a nivel bajo 
Timer time_IR;
// Variable para almacena el tiempo de duracion de un bit de datos
unsigned int time_bit;

// En orden:
// Variable que almacena el bit de start
// Variable para almacenar cada bit del comando del control remoto
// Variable para almacenar cada bit de la direccion del control remoto
// Variable que contiene el comando
// Variable que contiene la direccion
// Variable que contiene el ultimo comando pulsado
// Variable que contiene la ultima direccion pulsada
// Flag para indicar que se ha pulsado el boton correcto
unsigned int data_ir, data_direccion, comando, direccion, comando_ultimo, direccion_ultima, flag_boton_correcto;

// Funcion para parar y leer el timer cuando se detecte una interrupcion por flanco de subida
void flanco_subida_IR()  // al reveess
{ 
	time_IR.stop();
	time_bit = time_IR.read_us();         

}

// Funcion para resetear y arrancar el timer cuando se detecte una interrupcion por flanco de bajada
void flanco_bajada_IR()
{ 
	time_IR.reset();
	time_IR.start();
}

void mando() {

       // La señal que se recibe esta activa a nivel bajo:						  
            while (ir && flag_boton_correcto == 0);                                 // Espera del bit de start
	         
          	if (flag_boton_correcto == 0) {
							
	          while (!ir);                                // Bit de start
	          if ( time_bit > 2400) { data_ir = ir; }    // Tiempo a nivel alto de 600 us, analizo el bit anterior y lo almaceno
						else { data_ir = !ir; }                       
					  data_ir = data_ir << (7);
	          comando = comando|data_ir;	
			// Fin del bit de start
			 
			// Comienzo del COMANDO. Se recibe el bit de menor peso primero
						while(ir); 
						while(!ir);                                 // bit(0) del comando
						if (time_bit > 1200) { data_ir = ir; }     // Tiempo a nivel alto de 600 us, analizo el bit anterior y lo almaceno
						else { data_ir = !ir; }
					  data_ir = data_ir << (6);
	          comando = comando|data_ir;		          

						while (ir);
	          while (!ir);        												  // bit(1) del comando
						if (time_bit > 1200) { data_ir = ir; }       // Tiempo a nivel alto de 600 us, analizo el bit anterior y lo almaceno 
						else { data_ir = !ir; }
					  data_ir = data_ir << (5);
	          comando = comando|data_ir;	
						
					  while (ir);
	          while (!ir);        												  // bit(2) del comando
						if (time_bit > 1200) { data_ir = ir; }       // Tiempo a nivel alto de 600 us, analizo el bit anterior y lo almaceno   
						else { data_ir = !ir; }
					  data_ir = data_ir << (4);
	          comando = comando|data_ir;	
						
						while (ir);
	          while (!ir);        												  // bit(3) del comando
						if (time_bit > 1200) { data_ir = ir; }       // Tiempo a nivel alto de 600 us, analizo el bit anterior y lo almaceno  
						else { data_ir = !ir; }
					  data_ir = data_ir << (3);
	          comando = comando|data_ir;	
						
						while (ir);
	          while (!ir);        												  // bit(4) del comando
						if (time_bit > 1200) { data_ir = ir; }       // Tiempo a nivel alto de 600 us, analizo el bit anterior y lo almaceno  
						else { data_ir = !ir; }
					  data_ir = data_ir << (2);
	          comando = comando|data_ir;	
						
						while (ir); 
	          while (!ir);        												  // bit(5) del comando
						if (time_bit > 1200) { data_ir = ir; }       // Tiempo a nivel alto de 600 us, analizo el bit anterior y lo almaceno 
						else { data_ir = !ir; }
					  data_ir = data_ir << (1);
	          comando = comando|data_ir;	
						
						while (ir); 
	          while (!ir);        												  // bit(6) del comando
						if (time_bit > 1200) { data_ir = ir; }       // Tiempo a nivel alto de 600 us, analizo el bit anterior y lo almaceno
						else { data_ir = !ir; }
	          comando = comando|data_ir;	
			

			// Comienzo de la DIRECCION. Se recibe el bit de menor peso primero	
						while (ir); 
	          while (!ir);        												  // bit(0) de la direccion
						if (time_bit > 1200) { data_direccion = ir; }      
						else { data_direccion = !ir; }
					  data_direccion = data_direccion << (4);
	          direccion = direccion|data_direccion;							

						while (ir);
	          while (!ir);        												  // bit(1) de la direccion
						if (time_bit > 1200) { data_direccion = ir; }  
						else { data_direccion = !ir; }
					  data_direccion = data_direccion << (3);
	          direccion = direccion|data_direccion;							
						
						while (ir);
	          while (!ir);        												  // bit(2) de la direccion
						if (time_bit > 1200) { data_direccion = ir; }  
						else { data_direccion = !ir; }
					  data_direccion = data_direccion << (2);
	          direccion = direccion|data_direccion;

						while (ir);
	          while (!ir);        												  // bit(3) de la direccion
						if (time_bit > 1200) { data_direccion = ir; }  
						else { data_direccion = !ir; }
					  data_direccion = data_direccion << (1);
	          direccion = direccion|data_direccion;

						while (ir); 
	          while (!ir);        												  // bit(4) de la direccion
						if (time_bit > 1200) { data_direccion = ir; }  
						else { data_direccion = !ir; }
					  data_direccion = data_direccion << (0);
	          direccion = direccion|data_direccion;		
				// Almacenamos valor		
						Thread::wait(100);
						comando_ultimo = comando;
						direccion_ultima = direccion;
				// Borramos variables
						direccion = 0;
						comando = 0;
						
					}
				if ( (comando_ultimo == 0x88) ) {
				   flag_boton_correcto = 1;
			     SISTEMA.signal_set(0x0001);
				}	
		
}
