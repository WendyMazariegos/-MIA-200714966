/* 
 * File:   plantillaDiscos.h
 * Author: Wendy Mazariegos
 *
 * Created on 12 de Julio de 2016, 08:02 AM
 */

#ifndef PLANTILLADISCOS_H
#define	PLANTILLADISCOS_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "lista.h"
    char nombre[20],extension[5],fecha[16],pathAct[150];
    typedef struct{
        int part_status; //indica si la particion esta activa o no 1=activa 0=eliminada -1=no creada
        char part_type[2]; //indica el tipo de particion "P" o "E"
        char part_fit[2]; //tipo de ajuste de la particion B,F,W
        int part_start; //indica en que byte del disco inicia la particion
        int part_size; //contiene el tamaño total de la particion en bytes
        char part_name[16]; //nombre de la particion
    }partition;    
    
    typedef struct{
        char mbr_disk_signature[5]; //numero random, que identifica de forma unica a cada disco
        int mbr_espacio_libre; //espacio libre en disco
        int mbr_tamanio; //tamaño total del disco en bytes
        char mbr_fecha_creacion[20]; //fecha y hora de creacion del disco
        partition mbr_partition[4]; //Estructura con info de la particion
    }mbr; 
    
    typedef struct{
        int part_status; //indica si la particion esta activa o no 1=activa 0=eliminada -1=no creada
         char part_fit[2]; //tipo de ajuste de la particion B,F,W
         int part_start; //indica en que byte del disco inicia la particion
         int part_size; //contiene el tamaño total de la particion en bytes
         int part_next; //byte en el que esta el proximo EBR. -1 si no hay siguiente
        char part_name[16]; //nombre de la particion  
    }ebr;  
    
    typedef struct{
        char contenido[1024];
    }cont;
    
    void inicializar();
    void verificarPath(int w,char path[]);
    int divPath(char path[]);
    void crearDisco(int size, char unit[],char path[]);
    void fechaAct();
    void eliminarDisco(char path[]);
    void iniList1();

#ifdef	__cplusplus
}
#endif

#endif	/* PLANTILLADISCOS_H */

