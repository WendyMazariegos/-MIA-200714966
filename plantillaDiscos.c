#include "plantillaDiscos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include <dirent.h>
#include <time.h>
        
//char nombre[20],extension[5],fecha[16],pathAct[150];
int actual=97;

void fechaAct(){
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    strftime(fecha,16,"%d/%m/%y-%H:%M",tlocal);
}

// CREAR DIRECTORIO
void verificarPath(int w,char path[]){
    DIR *carpeta;
    char dir[150];
    int bandera,j;
    char *ptr;
    bandera=0;
    strcpy(dir,"");
    strcat(dir,"/");
    ptr = strtok(path,"/");
    for(j=0;j<w-1;j++){
        strcat(dir,ptr);
        strcat(dir,"/");
        if((carpeta=opendir(dir))!=NULL){
            bandera=1;
            closedir(carpeta);
        }
        if(bandera==0){
            char terminal[150];
            sprintf(terminal,"%s%s","mkdir ",dir);
            system(terminal);
        }
        ptr=strtok(NULL,"/");
        bandera=0;
    }
    strcpy(pathAct,"");
    strcat(pathAct,dir);
    char *tok;
    tok=strtok(ptr,".");
    strcpy(nombre,"");
    strcat(nombre,tok); 
    tok=strtok(NULL,".");
    strcpy(extension,"");
    strcat(extension,tok);
    strcat(pathAct,nombre);
}         

int divPath(char path[]){
    int x=1;
    char *ptr;
    ptr = strtok(path,"/");    // Primera llamada => Primer token
    while( (ptr=strtok(NULL,"/"))!=NULL){    // Posteriores llamadas
        x++;
    }
    return x;
}

//CREAR DISCO
void crearDisco(int size, char unit[],char path[]){
    int tam,i;
    char pathVerif[150],direc[150];
    cont llenar;
    FILE *nuevoDisco;
    if(size>0){
        if(strcmp(unit,"k")==0 || strcmp(unit,"K")==0 || strcmp(unit,"m")==0 || strcmp(unit,"M")==0){ 
            if(strcmp(unit,"m")==0 || strcmp(unit,"M")==0){
                tam=size*1024*1024;
            }else{
                tam=size*1024;
            }
            strcpy(pathVerif,"");
            strcat(pathVerif,path);
            strcpy(direc,"");
            strcat(direc,path);
            verificarPath(divPath(path),pathVerif);
            if(strcmp(extension,"dsk")==0){
                nuevoDisco=fopen(direc,"w");
                if(nuevoDisco!=NULL){
                    mbr nuevo;
                    nuevo.mbr_tamanio=tam;
                    nuevo.mbr_espacio_libre=tam-sizeof(mbr);
                    fechaAct();
                    strcpy(nuevo.mbr_fecha_creacion,fecha);
                    for(i=0;i<4;i++){
                        nuevo.mbr_partition[i].part_status=-1;
                        strcpy(nuevo.mbr_partition[i].part_name,"");
                    }
                    strcpy(nuevo.mbr_disk_signature,"");
                    strcat(nuevo.mbr_disk_signature,"vd");
                    nuevo.mbr_disk_signature[2]=actual;
                    nuevo.mbr_disk_signature[3]='\0';
                    actual=actual+1;
                    for(i=0;i<1024;i++){
                        llenar.contenido[i]='\0';
                    }
                    for(i=0;i<((tam)/1024);i++){
                        fwrite(&llenar,sizeof(cont),1,nuevoDisco);
                    }
                    fseek(nuevoDisco,0,SEEK_SET);
                    fwrite(&nuevo,sizeof(mbr),1,nuevoDisco);
                    fclose(nuevoDisco);
                    printf("se creo el disco %s.dsk !!\n",nombre);
                }else{
                    printf("se produjo un error al intentar crear el disco!!\n");
                }
            }else{
                printf("error extension no reconocida!!\n");
            }
        }else{
            printf("error en la definicion de -unit=%s !!\n",unit);}
    }else{
        printf("error, el tamaño debe ser mayor a 0!!\n");
    }
}

//ELIMINAR DISCO
void eliminarDisco(char path[]){
    int r,resp;
    FILE *ver;
    ver=fopen(path,"r");
    if(ver!=NULL){
        fclose(ver);
        printf("Confirmar eliminar 1 --> eliminar : ");
        scanf("%i",&r);
        if(r==1){
            resp=remove(path);
            if(resp==0){
                printf("el disco ha sido eliminado !!\n");
            }else{
                printf("error al intentar eliminar el disco !!\n");
            }
        }else{
            printf("el disco no ha sido eliminado !!\n");
        }
    }else{
        printf("error el disco no ha sido encontrado!!\n");
    }
    
}
