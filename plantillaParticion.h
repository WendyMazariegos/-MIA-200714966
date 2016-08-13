/* 
 * File:   plantillaParticion.h
 * Author: Wendy Mazariegos
 *
 * Created on 5 de agosto de 2016, 08:53 AM
 */

#ifndef PLANTILLAPARTICION_H
#define	PLANTILLAPARTICION_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "lista.h"
#include "plantillaDiscos.h"
    Lista2 *list;
    typedef struct{
        int inodes_count; //numero total de i-nodos en la tabla de i-nodos
        int blocks_count; //numero total de bloques de datos
        int free_blocks_count; //numero de bloques libres
        int free_inodes_count; //numero de i-nodos libres en la tabla de i-nodos
        char mtime[16]; //ultima fecha en que fue montado
        char umtime[16]; //ultima fecha en que desmontado
        int mnt_count; //numero de veces que ha sido montado
        int magic; //identificador del sistema de archivos 2007-14966        
        int inode_size; //tamaño de una estructura de un i-nodo
        int block_size; //tamaño de una estructura de un bloque de datos
        
      int firs_ino; //primer inodo libre
        int first_blo; //primer bloque libre
        int bm_inode_start; //inicio del bitmap de inodos
        int bm_block_start; //inicio del bitmap de bloques
        int inode_start; //inicio de la tabla de inodos
        int block_start; //inicio de la tabla de bloques
        
        /*
        int arbol_virtual_count; //numero de estructuras en el arbol virtual de directorio
        int detalle_directorio_count; //numero de estructuras en el detalle de directorio
        int free_arbol_virtual_count; //numero de estructuras en el arbol virtual de directorio libres
        int free_detalle_directorio_count; //numero de estructuras en el detalle de directorio libre
        int avd_size; //tamaño de una estructura de arbol virtual de directorio 
        int detalle_directorio_size; //tamaño de una estructura de un detalle de directorio
        int ap_avd; //apuntador al inicio del arbol virtual de directorio
        int ap_bitmat_avd; //apuntador al inicio del bitmap del arbol virtual de directorio
        int ap_detalle_directorio; //apuntador al inicio del detalle del directorio
        int ap_bitmap_detalle_directorio; //apuntador al inicio del bitmap de detalle del directorio
        int ap_tabla_inodo; //apuntador al inicio de la tabla de i-nodos
        int ap_bitmap_tabla_inodo; //apuntador al inicio del bitmap de la tabla de i-nodos
        int ap_bloque; // apuntador al inicio del bloque de datos
        int ap_bitmap_inodo; //apuntador al inicio del bitmap de bloque de datos
        int ap_log; //apuntador al inicio del log o bitácora
        int ap_copia_super_Bloque; //apuntador al inicio de la copia del superbloque
        int firts_free_bit_avd; //primer bit libre en el bitmap arbol de directorio
        int first_free_bit_detalle_directorio; //primer bit libre en el bitmap detalle de directorio
        int first_free_bit_tabla_inodo; //primer bit libre en el bitmap de i-nodo
        int first_free_bit_bloques; //primer bit libre en el bitmap de bloques de datos
        */
        
    }sb;
    
    typedef struct{
        int i_id; //id del inodo
        int i_size; //tamaño del archivo en bytes
        char i_atime[16]; //ultima fecha q se leyo el inodo sin modificar
        char i_ctime[16]; //fecha de creacion del inodo
        char i_mtime[16]; //ultima fecha que se modifico el inodo
        int i_bloq[15]; //1..12 bloq directos, 13 ind simple, 14 ind doble, 15 ind triple; si no se utilizan valor de -1
        char i_type; //indica si es archivo o carpeta 1=archivo 0=carpeta
        int i_perm; //guarda los permisos 664 para todos  
    }inodo;
    
    typedef struct{
        char b_name[12]; //nombre de la carpeta o archivo
        int b_inodo; //apuntador hacia un inodo asociado al archivo o carpeta
    }contenedor;
    
    typedef struct{
        contenedor b_content[4];
    }bloqCarp;
    
    typedef struct{
        char contenido[64]; //contenido del archivo tam 64 bytes
    }contArch;
    
    typedef struct{
        int b_pointers[16]; //array con los apuntadores hacia bloques(de archivo o carpeta) 
    }apuntador; 
    
    typedef struct{
        char valor; //0 ó 1
    }bitmap;
    
    sb recuperarSB(char path[],int posPart);
    void desmontarParticion(char id[]);
    mbr recuperarMBR(char path[]);
    void actualizarSB(char path[], sb actual, int pos);
    void actualizarMBR(char path[], mbr encontrado);
    int existeDisco(char path[]);
    void actualizarINODO(char path[], inodo actual, int posIni);
    inodo recuperarINODO(char path[], int posIni, int idInodo);
    void actualizarBM(char path[],bitmap actual,int pos);
    bitmap recuperarBM(char path[],int pos);
    void actualizarBC(char path[],bloqCarp actual,int pos);
    bloqCarp recuperarBC(char path[],int pos);
    void actualizarCA(char path[],contArch actual,int pos);
    contArch recuperarCA(char path[],int pos);
    void actualizarBA(char path[],apuntador actual,int pos);
    apuntador recuperarBA(char path[],int pos);
    bloqCarp bloqCarpStd();
    inodo inodoStd(int i);
    partition getPartition(char path[],char name[]);
#ifdef	__cplusplus
}
#endif

#endif	/* PLANTILLAPARTICION_H */

