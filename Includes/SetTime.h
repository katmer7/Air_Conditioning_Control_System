#include "mbed.h"

#ifndef  _SET_TIME_H_
#define  _SET_TIME_H_

// Variables que almacenan la fecha y hora del RTC
extern char buffer_dia[3];
extern char buffer_mes[3];
extern char buffer_annio[4];
extern char buffer_hora[3];
extern char buffer_min[3];
extern char buffer_seg[3];

extern char dia0;
extern char mes0;
extern char hora0;
extern char min0;
extern char seg0;

extern char annio0;
extern char annio1;
extern char annio2;
extern char annio3;

extern char dia1;
extern char mes1;
extern char hora1;
extern char min1;
extern char seg1;


// Funciones para almacenar la nuva fecha y hora, resetear y mover el puntero
extern unsigned int *puntero_LCD;
void saveKey(char key);
void Right();
void Left();
void reset_BUFFER_TIME();


// Variables para almacenar la fecha y hora configuradas
struct time  {  //structure of the time record    
	int sec;                          
	int min;
  int hour;
  int day;
	int month;
	int year;
};

extern struct time time_config;
extern unsigned int BUFFER_TIME[];

#endif
