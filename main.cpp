#include "mbed.h"
#include "definitions.h"
#include "hardware.h"
#include "joystick.h"
#include "Thread.h"
#include "Keypad.h"
#include "C12832.h"
#include "Small_6.h"
#include "Arial24x23.h"
#include "SetTime.h"
#include "LCD_config.h"
#include "HumTem_config.h"
#include "Remote_Control.h"
#include "DHT22.h"
#include "HC_SR04.h"
#include "PWM_config.h"
#include "Speaker.h"

unsigned int estado, cambio_estado, s, ena, validar_clave = 0, clave_valida = 0;
struct tm t;
Timer time_prealarma;
unsigned int run = 1;
unsigned int  primera_vez_1 = 1;
unsigned int  primera = 1;
unsigned int f = 1;
struct mail_t {
char password[4];
char password_oculta;
};

Mail<mail_t, 16> mail_box;

////////////////// Rtos timer
void led4_f (void const *argument) { led4 = !led4; }
RtosTimer led4_timer (callback(&led4_f,(void*)NULL), osTimerPeriodic);

void RGB_red (void const *argument) {

	if (ena)
	{
		R= 0;
		G=1;
		B=1;
	}
	else
	{
	  R= 1;
		G=1;
		B=1;
	}
	ena =  !ena;
		
}
RtosTimer RGB_red_timer (callback(&RGB_red,(void*)NULL), osTimerPeriodic);

void speaker_c (void const *argument) {


	if (s)
	{
				spkr.period(1.0/500.0);
	      spkr = 0.5f;          // Ciclo de trabajo
	      Thread::wait(300);
	}
	else
	{
	      spkr = 0.0f;          // Ciclo de trabajo
	}
	s =  !s;	
	
}

RtosTimer speaker_c_timer (callback(&speaker_c,(void*)NULL), osTimerPeriodic);

void RGB_colour (void const *argument) {

		if (run == 1)
	{
		R = 0;
		G = 1;
		B = 1;
	}
	else if (run == 2)
	{
	  R = 1;
		G = 0;
		B = 1;
	}
	else if (run == 3) {
	  R = 1;
		G = 1;
		B = 0;
    run = 0;		
	}	
	run++;	
	
}

RtosTimer RGB_colour_timer (callback(&RGB_colour,(void*)NULL), osTimerPeriodic);

void LCD_fail (void const *argument) {

	if (f)
	{
  lcd.locate(0,0);
  lcd.printf("FAIL");
	}
	else
	{
  lcd.cls();
	}
	f =  !f;
		
}

RtosTimer LCD_fail_timer (callback(&LCD_fail,(void*)NULL), osTimerPeriodic);
//////////////////////////////////////////////////////////////

void function_SISTEMA() {
mail_t *puntero_mail;
osEvent evento;	
	
 while (1) {
	   switch(estado) { 
		
		   case APAGADO: 
     	     R = 0; G = 1; B = 1;                      // RGB rojo
			     lcd.cls();
			     led4_timer.stop();
				   led4 = 0;		
			     mando();                                  // Funcion para el control remoto
			     
			   if (flag_boton_correcto) {			 
					 
			     SISTEMA.signal_wait(0x0001);              // Señal del mando/joystick
					 SISTEMA.signal_clr(0x0001);
	                    
			     estado = CONFIGURACION;
					 flag_boton_correcto = 0; 
					 if (primera_vez_1) {
					 primera_vez_1 = 0; 
			 		 SET_RTC.signal_set(0x0002);               // Configuracion de fecha y hora
					 }
					 R = 1; G = 1; B = 1; 
					 R.period(0.9);				 
			   }
				 break;
			 
		 case CONFIGURACION:	
           led4_timer.stop();		
				   led4 = 0;				 
			     R = 0.5; G = 0.5; B = 1;                  // RGB amarillo	 
		       LCD.signal_set(0x0008);	
		     
		 // Cambio de fecha y hora
			    if (key == 'A') { 
					 resetKey();
						
					 reset_BUFFER_TIME();                      // reset buffer de configuracion    
					 LCD.signal_set(0x0010);                   // reset LCD
           estado = SET_TIME;
			    }
					
		 // Cambio del primer rango mostrado por el LCD
					else if (key == 'F') {
					 resetKey();
           reset_BUFFER_config_RANGE_A();            // reset buffer de configuracion     	
				   LCD.signal_set(0x0010);                   // reset LCD			
					 estado = SET_RANGE_A;
					}
					
		 // Cambio del segundo rango mostrado por el LCD					
					else if (key == 'E') {
					 resetKey();						
           reset_BUFFER_config_RANGE_B();            // reset buffer de configuracion    	
				   LCD.signal_set(0x0010);                   // reset LCD					
					 estado = SET_RANGE_B;
					}
					
	 	// Cambio de estado	
          else if (key == 'D') {
				  resetKey();							
          R.period(0.0);
					R = 1; G = 1; B = 1; 	
					lcd.cls();
          estado = MONITORIZACION;
			  }			
				
				// Para poder apagar el sistema
				if (flag_boton_correcto) {			 
					 
			     SISTEMA.signal_wait(0x0001);              // Señal del joystick
					 SISTEMA.signal_clr(0x0001);
	         flag_boton_correcto = 0; 
					 Thread::wait(2000);          
			     estado = APAGADO;		
			   }	
				 break;
					
			 case MONITORIZACION:
				 R = 1; G = 1; B = 1;
       	 LCD.signal_set(0x0100);     // señal al hilo LCD que se encarga de monitorizar los datos
        
			 //  flag de cambio de estado segun condiciones de monitorizacion    
			  if (cambio_estado) {
					 estado = PREALARMA;
					 cambio_estado = 0;
           speaker_c_timer.start(500);
				 }
			// Tecla C para volver al estado de configuracion
				else if (key == 'C') {
					 resetKey();
					 estado = CONFIGURACION;
					 R.period(0.9);						
				}
				
				// Para poder apagar el sistema
				if (flag_boton_correcto) {			 
					 
			     SISTEMA.signal_wait(0x0001);              // Señal del joystick
					 SISTEMA.signal_clr(0x0001);
					 R.period(0.9);
	         flag_boton_correcto = 0; 
					 Thread::wait(2000);           
			     estado = APAGADO;		
			   }	
			   break;
			 	 
			 case PREALARMA:
				led4_timer.stop();	
				led4 = 0;
			  Thread::wait(1000);
			  sensor_data();
			  comprobacion_rango_horario();			 
        time_prealarma.start();
			  LCD.signal_set(0x0400); //////////////// nueva linea
			 
			  if (time_prealarma.read_ms() >= 8000) {	
				time_prealarma.stop();
        time_prealarma.reset();					
			  speaker_c_timer.stop();
			  spkr.period(0.0);
			  spkr = 0.0f;       
			 			 
			  estado = ALARMA;
		    R.period(0.1);
			 	RGB_red_timer.start(500);
				lcd.cls();	

				}
				 if (programacion_lcd() == 1 || programacion_lcd() == 2 || programacion_lcd() == 3 || programacion_lcd() == 4 ||  programacion_lcd() ==5 || programacion_lcd() == 6){
				time_prealarma.stop();					 
				time_prealarma.reset();	 
				estado = MONITORIZACION;
				speaker_c_timer.stop();
			  spkr = 0.0f;  					 
			  spkr.period(0.0);	 
					 
				}				
				 break;
			 
			 case ALARMA:			 
        sirena();
			 	if (key == 'F' && validar_clave == 0) {
					 resetKey();
					 validar_clave = 1;
           puntero_mail = mail_box.alloc();
           puntero_mail-> password[0] = '2';
					 puntero_mail-> password[1] = '7';
					 puntero_mail-> password[2] = '0';
				   puntero_mail-> password[3] = '7';
				   puntero_mail-> password_oculta = '*';					 			 
					 mail_box.put(puntero_mail);
           					 
				}
				else if ( clave_valida ) {
           clave_valida = 0;
					 RGB_red_timer.stop();
					 spkr.period(0.0);
			     spkr =0.0f;
					 R.period(0.0);
           Thread::wait(600);
					 lcd.cls();
					 estado = FALLO; 
					 G.period(0.1); 
			     RGB_colour_timer.start(700);
           lcd.set_font((unsigned char*) Arial24x23);   				// Inicializacion el LCD a la fuente mas grande de la libreria
					 LCD_fail_timer.start(400);
					 
			 }					
				 break;
			 
			 case FALLO:
          speaker_fallo();
			 		distancia_objeto();
			 			 
			 		evento = SISTEMA.signal_wait(0,200);
			    if (evento.value.signals & 0x0200 && deteccion() == 1) {
					SISTEMA.signal_clr(0x0200);	
					lcd.cls();
					spkr = 0.0f;
          lcd.set_font((unsigned char*) Small_6);   				// Inicializacion el LCD a la fuente mas pequeña de la libreria	
				  LCD_fail_timer.stop();
					lcd.cls();
			    RGB_colour_timer.stop();	
					R = 1; G = 1; B = 1;						
          G.period(0.0);	
					R.period(0.9);						
					estado = CONFIGURACION; 							
					}
				 break;

			 
			 case SET_TIME:	
		 // Mover el cursor a la izquierda				 
				   if (flag_key && key == 'B') {
						 resetKey();
						 Left();
					 }
		 // Mover el cursor a la derecha					 
					 else if (flag_key && key == 'C') {
						 resetKey();
						 Right();
					 }
		 // Confirmacion de la nueva fecha y hora				 
					 else if (flag_key && key == 'D') {
						resetKey(); 
					  lcd.cls();
						SET_RTC.signal_set(0x0002);            // señal para introducir el nuevo valor en el hilo RTC
						estado = CONFIGURACION;
					 }
   			   else if (flag_key) {                    // Flag de pulsacion de un tecla
					 saveKey(key);                           // Almacena la tecla
					 LCD.signal_set(0x0020);
				   }
					 
			 case SET_RANGE_A:		
		 // Mover el cursor a la izquierda					 
				   if (flag_key && key == 'B') {
						 resetKey();
						 Left_Range_A();
					 }
		 // Mover el cursor a la derecha							 
					 else if (flag_key && key == 'C') {
						 resetKey();						 
						 Right_Range_A();
					 }
		 // Confirmacion el nuevo valor del rango	A			 
					 else if (flag_key && key == 'D') {
						resetKey(); 
					  lcd.cls();
						estado = CONFIGURACION;
					 }
   			   else if (flag_key) {                    // Flag de pulsacion de un tecla
					 saveKey_Range_A(key);                   // Almacena la tecla
					 LCD.signal_set(0x0040);
				   }
         break;
					 					 
       case SET_RANGE_B:
		 // Mover el cursor a la izquierda					 
				   if (flag_key && key == 'B') {
						 resetKey();
						 Left_Range_B();
					 }
		 // Mover el cursor a la derecha						 
					 else if (flag_key && key == 'C') {
						 resetKey();
						 Right_Range_B();
					 }
		 // Confirmacion el nuevo valor del rango	B			  					 
					 else if (flag_key && key == 'D') {
						resetKey(); 
						lcd.cls();
						estado = CONFIGURACION;
					 }
   			   else if (flag_key) {                    // Flag de pulsacion de un tecla
					 saveKey_Range_B(key);                   // Almacena la tecla
					 LCD.signal_set(0x0080); 
				   }
			   break;
					 
		} // Fin switch 	
		 
	}//Fin while		 
}



void function_PASSWORD() {

char password_check[4];
int i = 0 ;

	while (1) {
	
		osEvent evt = mail_box.get(); // solo se activa cuando le llega un evento.
        if (evt.status == osEventMail) {
            mail_t *puntero_mail = (mail_t*)evt.value.p;
					
					lcd.locate(1,0);
			    lcd.printf("Introduzca la clave:\n");	
					
    do {
	     if (flag_key && i == 0) {
				 lcd.cls();
		     password_check[i] = key;
         resetKey();
				 lcd.locate(1,0);
				 lcd.printf("Introduzca la clave:\n");				 
				 lcd.locate(1,10);
				 lcd.printf("%c\n", puntero_mail-> password_oculta);
		     i++;
	      }	
       else if (flag_key && i == 1) {
		     password_check[i] = key; 
         resetKey();				 
         lcd.locate(1,0);
				 lcd.printf("Introduzca la clave:\n");				 
				 lcd.locate(1,10);
				 lcd.printf("%c%c\n", puntero_mail-> password_oculta,puntero_mail-> password_oculta);
		     i++;
        }
       else if (flag_key && i == 2) {
		     password_check[i] = key;
         resetKey();
         lcd.locate(1,0);
				 lcd.printf("Introduzca la clave:\n");				 
				 lcd.locate(1,10);
				 lcd.printf("%c%c%c\n", puntero_mail-> password_oculta,puntero_mail-> password_oculta,puntero_mail-> password_oculta);
		     i++;
        }
       else if (flag_key && i == 3) {
		     password_check[i] = key;				 
         resetKey();
         lcd.locate(1,0);
				 lcd.printf("Introduzca la clave:\n");				 
				 lcd.locate(1,10);
				 lcd.printf("%c%c%c%c\n", puntero_mail-> password_oculta,puntero_mail-> password_oculta,puntero_mail-> password_oculta,puntero_mail-> password_oculta);
		     i++;
        }	
			 else if (flag_key || i == 4) {
				 if (key == 'D') {
					lcd.cls();
				  resetKey();
					 if (puntero_mail-> password[0] == password_check[0] && puntero_mail-> password[1] == password_check[1] && puntero_mail-> password[2] == password_check[2] && puntero_mail-> password[3] == password_check[3]) {
					   lcd.locate(1,0);
				     lcd.printf("Clave correcta\n");
					   validar_clave = 0;
					 
				    }
          else
					{
						 lcd.cls();
					   lcd.locate(1,0);
						 lcd.printf("Clave Incorrecta\n");
						 lcd.locate(1,10);
						 lcd.printf("Introduzca la clave:\n");
						 password_check[0] = '0';
						 password_check[1] = '0';
					 	 password_check[2] = '0';
						 password_check[3] = '0';
						 i = 0;

					}
					
			 } // fin D
     }	
				
	
		 } while(validar_clave);
		
			clave_valida = 1;
			mail_box.free(puntero_mail); 
		}	// fin mail
	
 } // fin while 
}



void function_SET_RTC ()   {

while (1) {		

// Fecha y hora inicial	
	if (primera) {
	primera = 0;
  SET_RTC.signal_wait(0x0002);
	SET_RTC.signal_clr(0x0002);
	
  t.tm_sec = 10;    // 0-59
	t.tm_min = 12;    // 0-59
	t.tm_hour = 17;   // 0-23
	t.tm_mday = 14;   // 1-31
	t.tm_mon = 4;     // 0-11
	t.tm_year = 117;  //año 2017	
	set_time(mktime(&t)); 
    
// Rangos iniciales
	// Rango a	
	   BUFFER_RANGE[HUM_a].lower0 = 3;
     BUFFER_RANGE[HUM_a].lower1 = 0;
	
	   BUFFER_RANGE[HUM_a].upper2 = 6;
     BUFFER_RANGE[HUM_a].upper3 = 5;
	
	   BUFFER_RANGE[TEMP_a].lower0 = 2;
     BUFFER_RANGE[TEMP_a].lower1 = 0;
	
	   BUFFER_RANGE[TEMP_a].upper2 = 2;
     BUFFER_RANGE[TEMP_a].upper3 = 7;
	    
	   BUFFER_TR[0].time_lower_min0 = 1;
	   BUFFER_TR[0].time_lower_min1 = 0;
		 BUFFER_TR[0].time_lower_hour2 = 0;
		 BUFFER_TR[0].time_lower_hour3 = 0;
		 
		 BUFFER_TR[0].time_upper_min0 = 1;
		 BUFFER_TR[0].time_upper_min1 = 9;
		 BUFFER_TR[0].time_upper_hour2 = 5;
		 BUFFER_TR[0].time_upper_hour3 = 9;		 
	// Rango b
	   BUFFER_RANGE[HUM_b].lower0 = 5;
     BUFFER_RANGE[HUM_b].lower1 = 0;
	   BUFFER_RANGE[HUM_b].upper2 = 8;
     BUFFER_RANGE[HUM_b].upper3 = 5;
	
	   BUFFER_RANGE[TEMP_b].lower0 = 1;
     BUFFER_RANGE[TEMP_b].lower1 = 5;
	   BUFFER_RANGE[TEMP_b].upper2 = 2;
     BUFFER_RANGE[TEMP_b].upper3 = 2;	
		 
		 BUFFER_TR[1].time_lower_min0 = 2;
	   BUFFER_TR[1].time_lower_min1 = 0;
		 BUFFER_TR[1].time_lower_hour2 = 0;
		 BUFFER_TR[1].time_lower_hour3 = 0;
		 
		 BUFFER_TR[1].time_upper_min0 = 0;
		 BUFFER_TR[1].time_upper_min1 = 9;
		 BUFFER_TR[1].time_upper_hour2 = 5;
		 BUFFER_TR[1].time_upper_hour3 = 9;
	 }
	
// Valor de la fecha y hora configurada por el usuario	 
	SET_RTC.signal_wait(0x0002);
	SET_RTC.signal_clr(0x0002);
	
	t.tm_sec = time_config.sec; 
	t.tm_min = time_config.min;   
	t.tm_hour = time_config.hour;   
	t.tm_mday = time_config.day;   
	t.tm_mon = time_config.month;    
	t.tm_year = time_config.year;   
	set_time(mktime(&t)); 
	
 } // fin while
}	





void function_LCD() {
	
osEvent evento;	
	
	while(1) {
		 evento = LCD.signal_wait(0);

		//Reset LCD
		if (evento.value.signals & 0x0010) {
			LCD.signal_clr(0xFFFF);
			LCD_config_reset();		
		}
		//Valores LCD
    else if (evento.value.signals & 0x0008) { 
			LCD.signal_clr(0xFFFF);
			DATA_RTC.signal_set(0x0004);                // hilo RTC para obtener los datos
			distancia_objeto();
			sensor_data();	  
      LCD_config_complete();
		}
		//Configuracion fecha y hora LCD
		else if (evento.value.signals & 0x0020) { 
			LCD.signal_clr(0xFFFF);
      LCD_config_time();			
		}
		// Configuracion rango A LCD
		else if (evento.value.signals & 0x0040) { 
			LCD.signal_clr(0xFFFF);
      LCD_config_range_a();			
		}
		// Configuracion rango B LCD
	  else if (evento.value.signals & 0x0080) {
			LCD.signal_clr(0xFFFF);
      LCD_config_range_b();			
		}
		///////////// texto intermitente ////////////////////
		else if (evento.value.signals & 0x0100) {  

			LCD.signal_clr(0xFFFF);
			DATA_RTC.signal_set(0x0004);                // hilo RTC para obtener los datos	
			distancia_objeto();
			sensor_data();
			comprobacion_rango_horario();

			if (programacion_lcd() == 1) { 
				LCD_config_monitorizando_C();
				led4_timer.stop();
				led4 = 0;					
				flag_a = 0;
				flag_b = 0;
				aviso = 0;
			}
			else if(programacion_lcd() == 2) {
				LCD_config_monitorizando_CH();
				led4_timer.start(300);	
				flag_a = 0;
				flag_b = 0;
				aviso = 0;
			}
			else if(programacion_lcd() == 3) {
				LCD_config_monitorizando_E();
				led4_timer.stop();
				led4 = 0;	
				flag_a = 0;
				flag_b = 0;
				aviso = 0;				
			}
			else if(programacion_lcd() == 4) {
				LCD_config_monitorizando_EH();
				led4_timer.start(300);	
				flag_a = 0;
				flag_b = 0;
				aviso = 0;				
			}
			else if(programacion_lcd() == 5 || programacion_lcd() == 8) {
				led4_timer.stop();
				led4 = 0;	
        LCD_config_monitorizando_1();	
				flag_a = 0;
				flag_b = 0;
				aviso = 0;				
			}	
			else if(programacion_lcd() == 6) {
        LCD_config_monitorizando_1_H();	
				led4_timer.start(300);	
				flag_a = 0;
				flag_b = 0;
				aviso = 0;				
			}
			else if(programacion_lcd() == 7) {
				led4_timer.stop();
				led4 = 0;
				flag_a = 0;
				flag_b = 0;
				aviso = 0;
				cambio_estado = 1;
	// me vy al otro stado			
			}		
		}
		else if (evento.value.signals & 0x0400) {  
	  LCD.signal_clr(0xFFFF);	
		LCD_prealarma();	
		}

	} // Fin while
}



void function_DATA_RTC() {
	
	while(1)  
	{		

		DATA_RTC.signal_wait(0x0004); 
		DATA_RTC.signal_clr(0x0004);
		time_t seconds = time(NULL); 

	// Extraemos informacion de fecha y hora de la RTC	
		strftime(buffer_dia, 3,"%d\n" ,localtime(&seconds));
		strftime(buffer_mes, 3,"%m\n" ,localtime(&seconds));
		strftime(buffer_annio, 4,"%Y\n" ,localtime(&seconds));
		strftime(buffer_hora, 3,"%H\n" ,localtime(&seconds));
		strftime(buffer_min, 3,"%M\n" ,localtime(&seconds));
		strftime(buffer_seg, 3,"%S\n" ,localtime(&seconds));
		
	// Almacenamos informacion para poder representarla
		dia0 = buffer_dia[0];
		dia1 = buffer_dia[1];
		
		mes0 = buffer_mes[0];
		mes1 = buffer_mes[1];
		
		annio0 = buffer_annio[0];
		annio1 = buffer_annio[1];
		annio2 = buffer_annio[2];
		annio3 = buffer_annio[3];
		
		hora0 = buffer_hora[0];
		hora1 = buffer_hora[1];
		
		min0 = buffer_min[0];
		min1 = buffer_min[1];
		
		seg0 = buffer_seg[0];
		seg1 = buffer_seg[1];
		
	}	// Fin while	
}




int main(){
	
	// Activacion de las interrupciones de la fila del teclado por flanco de subida
  row1.rise(&Frow1);
	row2.rise(&Frow2);
	row3.rise(&Frow3);
	row4.rise(&Frow4);
	// activacion de las filas (pull-up)
	columns = 0xF;    

	// Inicializacion del timer para los rebotes del teclado
	bounce.start();
	
	// Activacion del joystick por flanco de bajada
	button.fall(&function_button);
	button_down.fall(&function_button_down);
	
	// Activacion del IR por flanco de bajada y de subida
	ir.rise(&flanco_subida_IR);
	ir.fall(&flanco_bajada_IR);	
	
	// El sistema empieza en el estado de APAGADO.
	estado = APAGADO;
		
	// Inicializacion de los hilos
	SISTEMA.start(function_SISTEMA);
	SET_RTC.start(function_SET_RTC);
	DATA_RTC.start(function_DATA_RTC);
	LCD.start(function_LCD);
	PASSWORD.start(function_PASSWORD);
  
	// Inicializacion el LCD a la fuente mas pequeña de la libreria
  lcd.set_font((unsigned char*) Small_6);
	lcd.cls();                              //Limpiamos LCD
	 
	// Activacion del sensor de distancia por flanco de bajada y de subida
	 Echo.rise(&flanco_subida_echo);
	 Echo.fall(&flanco_bajada_echo);
		
	// main pasa al estado de espera
  Thread::wait(osWaitForever);

}
