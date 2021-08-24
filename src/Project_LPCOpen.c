/*
===============================================================================
 Name        : Project_LPCOpen.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>
#include "sapi_dac.h"
#include "sapi_systick.h"
#include "sapi_gpio.h"
// TODO: insert other include files here
int modo=0;

/*uint16_t n=1;
uint16_t contador=0;
uint16_t cont_amplsen=0;
uint16_t paso_ampl=102;
uint16_t amplitud=1023;*/
uint32_t frecuencia=200000;

// TODO: insert other definitions and declarations here

int main(void) {


#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable
      SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
    // Set the LED to the state of "On"
    Board_LED_Set(0, true);
#endif
#endif

//int si=1;
//int boton=0;
dacInit( DAC_ENABLE);
Init_Tick(frecuencia);
/*gpioInit( 0, 9, GPIO_INPUT );
gpioInit( 0, 8, GPIO_INPUT );
gpioInit( 0, 7, GPIO_INPUT );
gpioInit( 0, 6, GPIO_INPUT );*/
int isen=0;
int seno_vector[10]={512,670,812,926,999,1023,998,926,812,670};
int subida_bajada=1;
    while(1) {

    	/*if(gpioRead(0,9) == 1){boton=1;}
        if(gpioRead(0,8) == 1){boton=2;}
    	if(gpioRead(0,7) == 1){boton=3;}
    	if(gpioRead(0,6) == 1){boton=4;}

    	/*switch (boton){
    		case 1: // triangular 10kH-3,3V
    			amplitud=1023;
    			paso_ampl=102;
    			frecuencia=100000;
    			boton=0;
    			break;
    		case 2: // triangular 1kH-3,3V
    			amplitud=512;
    			paso_ampl=102;
    			frecuencia=10000;
    			boton=0;
    			break;
    		case 3: // triangular 1kH-1.65V
    			amplitud=512;
    			paso_ampl=51;
    			frecuencia=100000;
    			boton=0;
    		    break;
    		case 4: // triangular 10kH-1.65V
    			amplitud=512;
    			paso_ampl=51;
    			frecuencia=10000;
    			boton=0;
    		    break;
    			    }*/

  if(modo==1){
	  if(isen<=10 && subida_bajada==1){
		  dacWrite( DAC , seno_vector[isen]);
		  isen++;
		  if(isen==10){isen=0; subida_bajada=2;}
	  	  }
	  if(isen<=10 && subida_bajada==2){
	  		  dacWrite( DAC , 1023-seno_vector[isen]);
	  		  isen++;
	  		  if(isen==10){isen=0; subida_bajada=1;}
	  	  	  }
	  modo=0;
    	}

      }
    return 0 ;
}


void SysTick_Handler(void){
	modo=1;
    }

