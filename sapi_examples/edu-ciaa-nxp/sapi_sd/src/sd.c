/*
 * sd.c
 *
 *  Created on: 15/8/2017
 *      Author: root
 */

#include "sd.h"   // <= su propio archivo de cabecera
#include "sapi.h"     // <= Biblioteca sAPI
#include "speak.h"

#define FILENAME_7 "siete.raw"
#define FILENAME_70 "setenta.raw"
#define FILENAME_800 "ochocien.raw"
#define FILENAME_1000 "mil.raw"
#define FILENAME_y "y.raw"

#define TOTAL_SAMPLES_SIETE	5337
#define TOTAL_SAMPLES_SETENTA	6540
#define TOTAL_SAMPLES_MIL	4028
#define TOTAL_SAMPLES_OCHOCIENTOS	7384
#define TOTAL_SAMPLES_Y	2717
#define PERIODO			125 //FRECUENCIA A LA QUE SE REPRODUCE: 8000Hz

/*==================[definiciones de datos internos]=========================*/
char siete [5337];
char setenta [6540];
char mil [4028];
char ochocientos [7384];
char y[2717];

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/

// FUNCION que se ejecuta cada vez que ocurre un Tick
bool_t diskTickHook( void *ptr );
//bool_t SacaDato2( void *ptr );

void SacaDato(uint16_t periodo, uint32_t samples, char *buffer)
{
	uint32_t indice=0;
	//uint16_t *rbuff = (uint16_t*)buffer;
	while(indice< samples)
	{
		dacWrite(DAC, buffer[indice]);
		indice ++;
		delay(periodo);
	}

}


/*==================[funcion principal]======================================*/

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void ){

   // ---------- CONFIGURACIONES ------------------------------
   // Inicializar y configurar la plataforma
   boardConfig();

   // SPI configuration
   spiConfig( SPI0 );

   dacConfig( DAC_ENABLE );

   // Inicializar el conteo de Ticks con resolución de 10ms,
   // con tickHook diskTickHook


   Montar_SD();

   Leer_SD( FILENAME_7 , siete, TOTAL_SAMPLES_SIETE);
   Leer_SD( FILENAME_70 , setenta, TOTAL_SAMPLES_SETENTA);
   Leer_SD( FILENAME_800 , ochocientos, TOTAL_SAMPLES_OCHOCIENTOS);
   Leer_SD( FILENAME_1000 , mil, TOTAL_SAMPLES_MIL);
   Leer_SD( FILENAME_y , y , TOTAL_SAMPLES_Y);

   Desmontar_SD();

   tickConfig2(1,0);
   SacaDato(PERIODO, TOTAL_SAMPLES_MIL, mil);
   SacaDato(PERIODO, TOTAL_SAMPLES_OCHOCIENTOS, ochocientos);
   SacaDato(PERIODO, TOTAL_SAMPLES_SETENTA, setenta);
   SacaDato(PERIODO, TOTAL_SAMPLES_Y, y);
   SacaDato(PERIODO, TOTAL_SAMPLES_SIETE, siete);



   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE )
   {

   }

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontroladore y no es llamado/ por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

// FUNCION que se ejecuta cada vezque ocurre un Tick
bool_t diskTickHook( void *ptr ){
   disk_timerproc();   // Disk timer process
   return 1;
}

/*bool_t SacaDato2( void *ptr )
{
	static uint32_t indice = 0;
	//static uint16_t dato;
	if (indice>84036)
	{
		indice=0;
	}
	//dato=setenta[indice];
	dacWrite(DAC, speak[indice]);
	indice++;

	return 1;
}*/


/*==================[fin del archivo]========================================*/
