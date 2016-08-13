/* 
 * File:   inicio.h
 * Author: Wendy Mazariegos
 *
 * Created on 10 de febrero de 2016, 08:28 PM
 */

#ifndef INICIO_H
#define	INICIO_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "lista.h"
void waitInst();
void verificarComando(Lista *l);
void iniVars();
void menu(char comando[]);

#ifdef	__cplusplus
}
#endif

#endif	/* INICIO_H */

