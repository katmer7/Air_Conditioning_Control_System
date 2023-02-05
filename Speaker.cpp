#include "mbed.h"
#include "hardware.h"
#include "Speaker.h"



void sirena() {
	
	spkr.period(1.0/300.0);
	spkr = 0.5f;          // Ciclo de trabajo	
			   
  Thread::wait(200);	

  spkr = 0.0f; 
  spkr.period(1.0/6000.0);
	spkr = 0.5f;          // Ciclo de trabajo	
	
}

void speaker_fallo() {
		
	spkr.period(0.001);
  spkr = 0.9f;          // Ciclo de trabajo				   
  Thread::wait(1);	
	spkr = 0.0f; 
  spkr.period(0.001);
	spkr = 0.9f;          // Ciclo de trabajo	*/
	
}
