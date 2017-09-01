/*
 * sapi_fatfs.h
 *
 *  Created on: 13/8/2017
 *      Author: root
 */

#ifndef _SAPI_INC_SAPI_FATFS_H_
#define _SAPI_INC_SAPI_FATFS_H_

#include "sapi_datatypes.h"
#include "sapi_peripheral_map.h"

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/


/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

void Montar_SD(void);
void Leer_SD(const TCHAR*, const void*, uint16_t);
void Escribir_SD(const TCHAR*, const void*, uint16_t);
void Desmontar_SD(void);

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/

#endif /*_SAPI_INC_SAPI_FATFS_H_ */
