#include "mbed.h"
#include "SetTime.h"
#include "C12832.h"
#include "Keypad.h"
#include "definitions.h"
#include "hardware.h"
#include "LCD_config.h"
#include "HumTem_config.h"
#include "Thread.h"
#include "SetTime.h"
#include "DHT22.h"
#include "HC_SR04.h"
#include "PWM_config.h"

unsigned int parpadeo;
char asterisco = '*';

void LCD_config_reset() {
	lcd.cls();
	if ( last_key == 'A' ) {
	lcd.locate(0,0);
	lcd.printf("CONFIG. HORA Y FECHA");
	lcd.locate(0,8);
	lcd.printf("%02d:%02d:%02d  %02d.%02d.%04d", time_config.hour,time_config.min,time_config.sec,time_config.day,time_config.month,time_config.year);	
	}
	else if ( last_key == 'F' ) {
	lcd.locate(0,0);
	lcd.printf("CONFIG. RANGO A");
	lcd.locate(0,8);
	lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[0],BUFFER_RANGE[TEMP_a],BUFFER_RANGE[HUM_a]);		
	}	
	else if ( last_key == 'E' ) {
	lcd.locate(0,0);
	lcd.printf("CONFIG. RANGO B");
	lcd.locate(0,8);
	lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[1],BUFFER_RANGE[TEMP_b],BUFFER_RANGE[HUM_b]);	
	}	
	
}

void LCD_config_complete() {	
	lcd.locate(0,0);
  lcd.printf("%c%c:%c%c:%c%c  %c%c.%c%c.%c%c%c%c      ", hora0,hora1,min0,min1,seg0,seg1,dia0,dia1,mes0,mes1,annio0,annio1,annio2,annio3);
  lcd.locate(0,8);	
	lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[0],BUFFER_RANGE[TEMP_a],BUFFER_RANGE[HUM_a]);
	lcd.locate(0,16);
	lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[1],BUFFER_RANGE[TEMP_b],BUFFER_RANGE[HUM_b]);
	lcd.locate(0,24);
	lcd.printf("%c%c%c%c", asterisco,asterisco,asterisco,asterisco);
	lcd.locate(20,24);
	lcd.printf("T:%.1fH:%.1f Dist:%.1fcm",(float)temp_almacenada/10,(float)hum_almacenada/10,distancia_medida);
} 


void LCD_config_time() {
  lcd.locate(0,0);
	lcd.printf("CONFIG. HORA Y FECHA");
  lcd.locate(0,8);
		if (puntero_LCD == &BUFFER_TIME[0]) {
		lcd.printf("%d%d:%02d:%02d  %02d.%02d.%04d",  BUFFER_TIME[0],BUFFER_TIME[1],time_config.min,time_config.sec,time_config.day,time_config.month,time_config.year);
	  }
	  else if (puntero_LCD == &BUFFER_TIME[1]){
		lcd.printf("%d%d:%02d:%02d  %02d.%02d.%04d", BUFFER_TIME[0], BUFFER_TIME[1],time_config.min,time_config.sec,time_config.day,time_config.month,time_config.year);
	  }
	  else if (puntero_LCD == &BUFFER_TIME[2]){
		lcd.printf("%02d:%d%d:%02d  %02d.%02d.%04d", time_config.hour,BUFFER_TIME[2],BUFFER_TIME[3],time_config.sec,time_config.day,time_config.month,time_config.year);
	  }
	  else if (puntero_LCD == &BUFFER_TIME[3]){
		lcd.printf("%02d:%d%d:%02d  %02d.%02d.%04d", time_config.hour,BUFFER_TIME[2],BUFFER_TIME[3],time_config.sec,time_config.day,time_config.month,time_config.year);
	  }
	  else if (puntero_LCD == &BUFFER_TIME[4]){
		lcd.printf("%02d:%02d:%d%d  %02d.%02d.%04d", time_config.hour,time_config.min,BUFFER_TIME[4],BUFFER_TIME[5],time_config.day,time_config.month,time_config.year);
		}
    else if (puntero_LCD == &BUFFER_TIME[5]){
		lcd.printf("%02d:%02d:%d%d  %02d.%02d.%04d", time_config.hour,time_config.min,BUFFER_TIME[4],BUFFER_TIME[5],time_config.day,time_config.month,time_config.year);
		}
		else if (puntero_LCD == &BUFFER_TIME[6]){
		lcd.printf("%02d:%02d:%02d  %d%d.%02d.%04d", time_config.hour,time_config.min,time_config.sec,BUFFER_TIME[6],BUFFER_TIME[7],time_config.month,time_config.year);
		}
		else if (puntero_LCD == &BUFFER_TIME[7]){
		lcd.printf("%02d:%02d:%02d  %d%d.%02d.%04d", time_config.hour,time_config.min,time_config.sec,BUFFER_TIME[6],BUFFER_TIME[7],time_config.month,time_config.year);
		}
		else if (puntero_LCD == &BUFFER_TIME[8]){
		lcd.printf("%02d:%02d:%02d  %02d.%d%d.%04d", time_config.hour,time_config.min,time_config.sec,time_config.day,BUFFER_TIME[8],BUFFER_TIME[9],time_config.year);
		}
		else if (puntero_LCD == &BUFFER_TIME[9]){
		lcd.printf("%02d:%02d:%02d  %02d.%d%d.%04d", time_config.hour,time_config.min,time_config.sec,time_config.day,BUFFER_TIME[8],BUFFER_TIME[9],time_config.year);
		}
		else if (puntero_LCD == &BUFFER_TIME[10]){
		lcd.printf("%02d:%02d:%02d  %02d.%02d.%d%d%d%d", time_config.hour,time_config.min,time_config.sec,time_config.day,time_config.month,BUFFER_TIME[10],BUFFER_TIME[11],BUFFER_TIME[12],BUFFER_TIME[13]);
		}
		else if (puntero_LCD == &BUFFER_TIME[11]){
		lcd.printf("%02d:%02d:%02d  %02d.%02d.%d%d%d%d", time_config.hour,time_config.min,time_config.sec,time_config.day,time_config.month,BUFFER_TIME[10],BUFFER_TIME[11],BUFFER_TIME[12],BUFFER_TIME[13]);
		}
		else if (puntero_LCD == &BUFFER_TIME[12]){
		lcd.printf("%02d:%02d:%02d  %02d.%02d.%d%d%d%d", time_config.hour,time_config.min,time_config.sec,time_config.day,time_config.month,BUFFER_TIME[10],BUFFER_TIME[11],BUFFER_TIME[12],BUFFER_TIME[13]);
		}
		else if (puntero_LCD == &BUFFER_TIME[13]) {
		lcd.printf("%02d:%02d:%02d  %02d.%02d.%d%d%d%d", time_config.hour,time_config.min,time_config.sec,time_config.day,time_config.month,BUFFER_TIME[10],BUFFER_TIME[11],BUFFER_TIME[12],BUFFER_TIME[13]);
		}

}






void LCD_config_range_a() {
	lcd.locate(0,0);
	lcd.printf("CONFIG. RANGO A");
	lcd.locate(0,8);
	
	if (puntero_RANGE == &BUFFER_config_RANGE[0]) {
		lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[0],BUFFER_RANGE[TEMP_a],BUFFER_RANGE[HUM_a]);
	  }
	  else if (puntero_RANGE == &BUFFER_config_RANGE[1]){
		lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[0],BUFFER_RANGE[TEMP_a],BUFFER_RANGE[HUM_a]);
	  }
	  else if (puntero_RANGE == &BUFFER_config_RANGE[2]){
		lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[0],BUFFER_RANGE[TEMP_a],BUFFER_RANGE[HUM_a]);
	  }
	  else if (puntero_RANGE == &BUFFER_config_RANGE[3]){
		lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[0],BUFFER_RANGE[TEMP_a],BUFFER_RANGE[HUM_a]);
	  }
	  else if (puntero_RANGE == &BUFFER_config_RANGE[4]){
		lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[0],BUFFER_RANGE[TEMP_a],BUFFER_RANGE[HUM_a]);
		}
    else if (puntero_RANGE == &BUFFER_config_RANGE[5]){
		lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[0],BUFFER_RANGE[TEMP_a],BUFFER_RANGE[HUM_a]);
		}
		else if (puntero_RANGE == &BUFFER_config_RANGE[6]){
		lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[0],BUFFER_RANGE[TEMP_a],BUFFER_RANGE[HUM_a]);
		}
		else if (puntero_RANGE == &BUFFER_config_RANGE[7]){
		lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[0],BUFFER_RANGE[TEMP_a],BUFFER_RANGE[HUM_a]);
		}
		else if (puntero_RANGE == &BUFFER_config_RANGE[8]){
		lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[0],BUFFER_RANGE[TEMP_a],BUFFER_RANGE[HUM_a]);
		}
		else if (puntero_RANGE == &BUFFER_config_RANGE[9]){
		lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[0],BUFFER_RANGE[TEMP_a],BUFFER_RANGE[HUM_a]);
		}
		else if (puntero_RANGE == &BUFFER_config_RANGE[10]){
		lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[0],BUFFER_RANGE[TEMP_a],BUFFER_RANGE[HUM_a]);
		}
		else if (puntero_RANGE == &BUFFER_config_RANGE[11]){
		lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[0],BUFFER_RANGE[TEMP_a],BUFFER_RANGE[HUM_a]);
		}
		else if (puntero_RANGE == &BUFFER_config_RANGE[12]){
		lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[0],BUFFER_RANGE[TEMP_a],BUFFER_RANGE[HUM_a]);
		}
		else if (puntero_RANGE == &BUFFER_config_RANGE[13]) {
		lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[0],BUFFER_RANGE[TEMP_a],BUFFER_RANGE[HUM_a]);
		}
		else if (puntero_RANGE == &BUFFER_config_RANGE[14]) {
		lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[0],BUFFER_RANGE[TEMP_a],BUFFER_RANGE[HUM_a]);
		}
		else if (puntero_RANGE == &BUFFER_config_RANGE[15]) {
		lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[0],BUFFER_RANGE[TEMP_a],BUFFER_RANGE[HUM_a]);
		}
	
	
}


void LCD_config_range_b() {
	lcd.locate(0,0);
	lcd.printf("CONFIG. RANGO B");
	lcd.locate(0,8);
	
	if (puntero_RANGE_next == &BUFFER_config_RANGE_next[0]) {
	  lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[1],BUFFER_RANGE[TEMP_b],BUFFER_RANGE[HUM_b]);
	  }
	  else if (puntero_RANGE_next == &BUFFER_config_RANGE_next[1]){
	  lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[1],BUFFER_RANGE[TEMP_b],BUFFER_RANGE[HUM_b]);
	  }
	  else if (puntero_RANGE_next == &BUFFER_config_RANGE_next[2]){
	  lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[1],BUFFER_RANGE[TEMP_b],BUFFER_RANGE[HUM_b]);
	  }
	  else if (puntero_RANGE_next == &BUFFER_config_RANGE_next[3]){
	  lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[1],BUFFER_RANGE[TEMP_b],BUFFER_RANGE[HUM_b]);
	  }
	  else if (puntero_RANGE_next == &BUFFER_config_RANGE_next[4]){
	  lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[1],BUFFER_RANGE[TEMP_b],BUFFER_RANGE[HUM_b]);
		}
    else if (puntero_RANGE_next == &BUFFER_config_RANGE_next[5]){
	  lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[1],BUFFER_RANGE[TEMP_b],BUFFER_RANGE[HUM_b]);
		}
		else if (puntero_RANGE_next == &BUFFER_config_RANGE_next[6]){
	  lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[1],BUFFER_RANGE[TEMP_b],BUFFER_RANGE[HUM_b]);
		}
		else if (puntero_RANGE_next == &BUFFER_config_RANGE_next[7]){
	  lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[1],BUFFER_RANGE[TEMP_b],BUFFER_RANGE[HUM_b]);
		}
		else if (puntero_RANGE_next == &BUFFER_config_RANGE_next[8]){
	  lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[1],BUFFER_RANGE[TEMP_b],BUFFER_RANGE[HUM_b]);
		}
		else if (puntero_RANGE_next == &BUFFER_config_RANGE_next[9]){
	  lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[1],BUFFER_RANGE[TEMP_b],BUFFER_RANGE[HUM_b]);
		}
		else if (puntero_RANGE_next == &BUFFER_config_RANGE_next[10]){
	  lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[1],BUFFER_RANGE[TEMP_b],BUFFER_RANGE[HUM_b]);
		}
		else if (puntero_RANGE_next == &BUFFER_config_RANGE_next[11]){
	  lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[1],BUFFER_RANGE[TEMP_b],BUFFER_RANGE[HUM_b]);
		}
		else if (puntero_RANGE_next == &BUFFER_config_RANGE_next[12]){
	  lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[1],BUFFER_RANGE[TEMP_b],BUFFER_RANGE[HUM_b]);
		}
		else if (puntero_RANGE_next == &BUFFER_config_RANGE_next[13]) {
	  lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[1],BUFFER_RANGE[TEMP_b],BUFFER_RANGE[HUM_b]);
		}
		else if (puntero_RANGE_next == &BUFFER_config_RANGE_next[14]) {
	  lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[1],BUFFER_RANGE[TEMP_b],BUFFER_RANGE[HUM_b]);
		}
		else if (puntero_RANGE_next == &BUFFER_config_RANGE_next[15]) {
	  lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[1],BUFFER_RANGE[TEMP_b],BUFFER_RANGE[HUM_b]);
		}
	
	
}



void LCD_config_monitorizando_E() {
	lcd.locate(0,0);
  lcd.printf("%c%c:%c%c:%c%c  %c%c.%c%c.%c%c%c%c EN   ", hora0,hora1,min0,min1,seg0,seg1,dia0,dia1,mes0,mes1,annio0,annio1,annio2,annio3);
  lcd.locate(0,8);	
	lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[0],BUFFER_RANGE[TEMP_a],BUFFER_RANGE[HUM_a]);
	lcd.locate(0,16);
	lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[1],BUFFER_RANGE[TEMP_b],BUFFER_RANGE[HUM_b]);
	lcd.locate(0,24);
	lcd.printf("%.1f", porcentaje*100);
	lcd.locate(22,24);
	lcd.printf("T:%.1fH:%.1fDist:%.1fcm",(float)temp_almacenada/10,(float)hum_almacenada/10,distancia_medida);
	Thread::wait(200);
	lcd.locate(0,0);
  lcd.printf("%c%c:%c%c:%c%c  %c%c.%c%c.%c%c%c%c      ", hora0,hora1,min0,min1,seg0,seg1,dia0,dia1,mes0,mes1,annio0,annio1,annio2,annio3);
  lcd.locate(0,8);	
	lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[0],BUFFER_RANGE[TEMP_a],BUFFER_RANGE[HUM_a]);
	lcd.locate(0,16);
	lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[1],BUFFER_RANGE[TEMP_b],BUFFER_RANGE[HUM_b]);
	lcd.locate(0,24);
	lcd.printf("%.1f", porcentaje*100);
	lcd.locate(22,24);
	lcd.printf("T:%.1fH:%.1fDist:%.1fcm",(float)temp_almacenada/10,(float)hum_almacenada/10,distancia_medida);	
}

void LCD_config_monitorizando_EH() {
	lcd.locate(0,0);
  lcd.printf("%c%c:%c%c:%c%c  %c%c.%c%c.%c%c%c%c EN/HU", hora0,hora1,min0,min1,seg0,seg1,dia0,dia1,mes0,mes1,annio0,annio1,annio2,annio3);
  lcd.locate(0,8);	
	lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[0],BUFFER_RANGE[TEMP_a],BUFFER_RANGE[HUM_a]);
	lcd.locate(0,16);
	lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[1],BUFFER_RANGE[TEMP_b],BUFFER_RANGE[HUM_b]);
	lcd.locate(0,24);
	lcd.printf("%.1f", porcentaje*100);
	lcd.locate(22,24);
	lcd.printf("T:%.1fH:%.1fDist:%.1fcm",(float)temp_almacenada/10,(float)hum_almacenada/10,distancia_medida);	
	Thread::wait(200);
	lcd.locate(0,0);
  lcd.printf("%c%c:%c%c:%c%c  %c%c.%c%c.%c%c%c%c      ", hora0,hora1,min0,min1,seg0,seg1,dia0,dia1,mes0,mes1,annio0,annio1,annio2,annio3);
  lcd.locate(0,8);	
	lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[0],BUFFER_RANGE[TEMP_a],BUFFER_RANGE[HUM_a]);
	lcd.locate(0,16);
	lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[1],BUFFER_RANGE[TEMP_b],BUFFER_RANGE[HUM_b]);
	lcd.locate(0,24);
	lcd.printf("%.1f", porcentaje*100);
	lcd.locate(22,24);
	lcd.printf("T:%.1fH:%.1fDist:%.1fcm",(float)temp_almacenada/10,(float)hum_almacenada/10,distancia_medida);		
}

void LCD_config_monitorizando_C() {
	lcd.locate(0,0);
  lcd.printf("%c%c:%c%c:%c%c  %c%c.%c%c.%c%c%c%c CA   ", hora0,hora1,min0,min1,seg0,seg1,dia0,dia1,mes0,mes1,annio0,annio1,annio2,annio3);
  lcd.locate(0,8);	
	lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[0],BUFFER_RANGE[TEMP_a],BUFFER_RANGE[HUM_a]);
	lcd.locate(0,16);
	lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[1],BUFFER_RANGE[TEMP_b],BUFFER_RANGE[HUM_b]);
	lcd.locate(0,24);
	lcd.printf("%.1f", porcentaje*100);
	lcd.locate(22,24);
	lcd.printf("T:%.1fH:%.1fDist:%.1fcm",(float)temp_almacenada/10,(float)hum_almacenada/10,distancia_medida);		
	Thread::wait(200);
	lcd.locate(0,0);
  lcd.printf("%c%c:%c%c:%c%c  %c%c.%c%c.%c%c%c%c      ", hora0,hora1,min0,min1,seg0,seg1,dia0,dia1,mes0,mes1,annio0,annio1,annio2,annio3);
  lcd.locate(0,8);	
	lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[0],BUFFER_RANGE[TEMP_a],BUFFER_RANGE[HUM_a]);
	lcd.locate(0,16);
	lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[1],BUFFER_RANGE[TEMP_b],BUFFER_RANGE[HUM_b]);
	lcd.locate(0,24);
	lcd.printf("%.1f", porcentaje*100);
	lcd.locate(22,24);
	lcd.printf("T:%.1fH:%.1fDist:%.1fcm",(float)temp_almacenada/10,(float)hum_almacenada/10,distancia_medida);		
}

void LCD_config_monitorizando_CH() {
	lcd.locate(0,0);
  lcd.printf("%c%c:%c%c:%c%c  %c%c.%c%c.%c%c%c%c CA/HU", hora0,hora1,min0,min1,seg0,seg1,dia0,dia1,mes0,mes1,annio0,annio1,annio2,annio3);
  lcd.locate(0,8);	
	lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[0],BUFFER_RANGE[TEMP_a],BUFFER_RANGE[HUM_a]);
	lcd.locate(0,16);
	lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[1],BUFFER_RANGE[TEMP_b],BUFFER_RANGE[HUM_b]);
	lcd.locate(0,24);
	lcd.printf("%.1f", porcentaje*100);
	lcd.locate(22,24);
	lcd.printf("T:%.1fH:%.1fDist:%.1fcm",(float)temp_almacenada/10,(float)hum_almacenada/10,distancia_medida);		
	Thread::wait(200);
	lcd.locate(0,0);
  lcd.printf("%c%c:%c%c:%c%c  %c%c.%c%c.%c%c%c%c      ", hora0,hora1,min0,min1,seg0,seg1,dia0,dia1,mes0,mes1,annio0,annio1,annio2,annio3);
  lcd.locate(0,8);	
	lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[0],BUFFER_RANGE[TEMP_a],BUFFER_RANGE[HUM_a]);
	lcd.locate(0,16);
	lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[1],BUFFER_RANGE[TEMP_b],BUFFER_RANGE[HUM_b]);
	lcd.locate(0,24);
	lcd.printf("%.1f", porcentaje*100);
	lcd.locate(22,24);
	lcd.printf("T:%.1fH:%.1fDist:%.1fcm",(float)temp_almacenada/10,(float)hum_almacenada/10,distancia_medida);			
}

void LCD_config_monitorizando_1() {
	lcd.locate(0,0);
  lcd.printf("%c%c:%c%c:%c%c  %c%c.%c%c.%c%c%c%c      ", hora0,hora1,min0,min1,seg0,seg1,dia0,dia1,mes0,mes1,annio0,annio1,annio2,annio3);
  lcd.locate(0,8);	
	lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[0],BUFFER_RANGE[TEMP_a],BUFFER_RANGE[HUM_a]);
	lcd.locate(0,16);
	lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[1],BUFFER_RANGE[TEMP_b],BUFFER_RANGE[HUM_b]);
	lcd.locate(0,24);
	lcd.printf("%.1f", porcentaje*100);
	lcd.locate(22,24);
	lcd.printf("T:%.1fH:%.1fDist:%.1fcm",(float)temp_almacenada/10,(float)hum_almacenada/10,distancia_medida);		
	
}

void LCD_config_monitorizando_1_H() {
	lcd.locate(0,0);
  lcd.printf("%c%c:%c%c:%c%c  %c%c.%c%c.%c%c%c%c HU   ", hora0,hora1,min0,min1,seg0,seg1,dia0,dia1,mes0,mes1,annio0,annio1,annio2,annio3);
  lcd.locate(0,8);	
	lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[0],BUFFER_RANGE[TEMP_a],BUFFER_RANGE[HUM_a]);
	lcd.locate(0,16);
	lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[1],BUFFER_RANGE[TEMP_b],BUFFER_RANGE[HUM_b]);
	lcd.locate(0,24);
	lcd.printf("%.1f", porcentaje*100);
	lcd.locate(22,24);
	lcd.printf("T:%.1fH:%.1fDist:%.1fcm",(float)temp_almacenada/10,(float)hum_almacenada/10,distancia_medida);
	Thread::wait(200);	
	lcd.locate(0,0);
  lcd.printf("%c%c:%c%c:%c%c  %c%c.%c%c.%c%c%c%c      ", hora0,hora1,min0,min1,seg0,seg1,dia0,dia1,mes0,mes1,annio0,annio1,annio2,annio3);
  lcd.locate(0,8);	
	lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[0],BUFFER_RANGE[TEMP_a],BUFFER_RANGE[HUM_a]);
	lcd.locate(0,16);
	lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[1],BUFFER_RANGE[TEMP_b],BUFFER_RANGE[HUM_b]);
	lcd.locate(0,24);
	lcd.printf("%.1f", porcentaje*100);
	lcd.locate(22,24);
	lcd.printf("T:%.1fH:%.1fDist:%.1fcm",(float)temp_almacenada/10,(float)hum_almacenada/10,distancia_medida);	
}

void LCD_prealarma() {	
	lcd.locate(0,0);
  lcd.printf("%c%c:%c%c:%c%c  %c%c.%c%c.%c%c%c%c      ", hora0,hora1,min0,min1,seg0,seg1,dia0,dia1,mes0,mes1,annio0,annio1,annio2,annio3);
  lcd.locate(0,8);	
	lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[0],BUFFER_RANGE[TEMP_a],BUFFER_RANGE[HUM_a]);
	lcd.locate(0,16);
	lcd.printf("%d%d:%d%d-%d%d:%d%d T%d%d-%d%d H%d%d-%d%d", BUFFER_TR[1],BUFFER_RANGE[TEMP_b],BUFFER_RANGE[HUM_b]);
	lcd.locate(0,24);
	lcd.printf("%.1f", porcentaje*100);
	lcd.locate(22,24);
	lcd.printf("T:%.1fH:%.1fDist:%.1fcm",(float)temp_almacenada/10,(float)hum_almacenada/10,distancia_medida);
	Thread::wait(200);	
  lcd.cls();
}