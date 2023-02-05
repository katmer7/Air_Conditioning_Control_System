#include "mbed.h"

#ifndef KEYPAD_H
#define KEYPAD_H


						              // col1, col2, col3, col4
const char keyTable[4][4] = { '1',  '2',  '3',  'F', // row1
							                '4',  '5',  '6',  'E', // row2
							                '7',  '8',  '9',  'D', // row3
							                'A',  '0',  'B',  'C'  // row4
							              };

void Frow1();
void Frow2();
void Frow3();
void Frow4();
void getKey();
void resetKey();
							
extern InterruptIn row1, row2, row3, row4;

extern BusOut columns;
extern uint8_t row, column;
extern char key;
extern int flag_key;
														
extern char last_key;													
#endif
