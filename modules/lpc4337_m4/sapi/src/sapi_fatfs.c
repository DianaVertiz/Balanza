/* * sapi_fatfs.c

 *
 *  Created on: 13/8/2017
 *      Author: root
 */

#include "sapi_fatfs.h"
#include "chip.h"


static FATFS fs;           // <-- FatFs work area needed for each volume
static FIL fp;             // <-- File object needed for each open file
uint16_t nbytes;

void Montar_SD()
{
	uint8_t result =1;
// Give a work area to the default drive
	result= f_mount( &fs, "", 0 );
if( result== FR_OK )
	{
		gpioWrite( LEDG, ON );
	}
else
	{
		gpioWrite( LEDR, ON );
	}
}

void Leer_SD(const TCHAR* nombre, const void* buffer, uint16_t bytes)
{
	uint8_t result =1;

	result = f_open( &fp, nombre, FA_READ | FA_OPEN_EXISTING );

	if( result == FR_OK )
	{
			f_read( &fp, buffer, bytes, &nbytes );

			if(nbytes= bytes){ gpioWrite( LED1, ON );}

	        f_close(&fp);
    }
}

void Escribir_SD(const TCHAR* nombre, const void* buffer, uint16_t bytes)
{
	uint8_t result =1;
	//result = f_open( &fp, nombre, FA_WRITE | FA_OPEN_APPEND ); //agrega al archivo
																// abre el archivo y posiciona el cursor al final

	result = f_open( &fp, nombre, FA_WRITE |  FA_CREATE_ALWAYS );
	if(result == FR_OK )
		{
		       f_write( &fp, buffer, bytes, &nbytes );

		       if(nbytes= bytes){ gpioWrite( LED1, ON );}

		       f_close(&fp);
	    }
}

void Desmontar_SD()
{
	f_mount(NULL, "", 0);
}




