/* 
 * File:   main.c
 * Author: Wendy Mazariegos
 *
 * Created on 10 de febrero de 2016, 10:56 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "inicio.h"
#include <string.h>
#include "plantillaParticion.h"

/*mkdisk -size=30 -unit=m -path=/home/clnx/Escritorio/dis.dsk
 rmdisk -path=/home/clnx/Escritorio/dis.dsk
 * rmDisk -path=/home/ghosth_32/Documentos/disk/dis2.dsk
 * fdisk -size=500 -unit=k -path=/home/ghosth_32/Documentos/disk/dis2.dsk -name=linux
 * fdisk -size=500 -unit=k -path=/home/clnx/Escritorio/dis.dsk -name=linux
// * mkfs -path=/home/clnx/Escritorio/dis.dsk -type=full -name=linux1
 * mount -path=/home/clnx/Escritorio/dis.dsk -name=linux
 * unmount -id=vda2
 * rep -name=mbr -path=/home/clnx/Escritorio/mbr.jpg -id=vda1
 * rep -name=disk -path=/home/clnx/Escritorio/disk.jpg -id=vda1
 * rep -name=sb -path=/home/clnx/Escritorio/sb.jpg -id=vda1
 * rep -name=bm_inode -path=/home/clnx/Escritorio/bmInode.jpg -id=vda1
 * rep -name=bm_block -path=/home/clnx/Escritorio/bmBlock.jpg -id=vda1
 */
void main(int argc, char** argv) {
    printf("\n******* PRÁCTICA MANEJO E IMPLEMENTACIÓN DE ARCHIVOS ******* \n");
    iniList(); //inicializo lista de particiones montadas
    while(1){
        waitInst();
    }
}

