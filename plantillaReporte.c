#include "plantillaReporte.h"
#include "plantillaParticion.h"
#include "plantillaDiscos.h" 
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include <dirent.h>
#include <time.h>

void reporteMBR(char pathRep[],char id[]){
    nodol2 *aux;
    mbr enc;
    int j;
    char dirRep[150],dirDisco[150],tam[6],status[2],start[10],bsize[10],dirImg[150],terminal[300];
    strcpy(dirRep,"");
    strcat(dirRep,pathRep);
    aux=buscar2(list,id);
    if(aux!=NULL){
        if(strcmp(aux->id,id)==0){
            verificarPath(divPath(pathRep),dirRep);
                strcpy(dirDisco,"");
                strcat(dirDisco,pathAct);
                strcat(dirDisco,".dot");
                strcpy(dirImg,"");
                strcat(dirImg,pathAct);
                strcat(dirImg,".");
                strcat(dirImg,extension);
            enc=recuperarMBR(aux->path);
            FILE *dot = fopen(dirDisco,"w");
            if(dot!=NULL){
                sprintf(tam, "%i",enc.mbr_tamanio);
                fprintf(dot,"digraph ReporteMBR { \n");
                fprintf(dot,"nodesep=.05; \n rankdir=\"TB\"; \n node [shape=record,width=.1,height=.1,color=blue,style=diagonals]; \n node [width = 1.5]; \n");
                fprintf(dot,"node1[label=\"{{NOMBRE |VALOR} |");
                
                fprintf(dot,"{ mbr_tamanio  | %s }|",tam);
                fprintf(dot,"{ mbr_fecha_creacion  | %s }|",enc.mbr_fecha_creacion);
                fprintf(dot,"{ mbr_disk_signature  | %s }|",enc.mbr_disk_signature);
                for(j=0;j<4;j++){
                    if(enc.mbr_partition[j].part_status!=-1){
                        sprintf(status, "%i",enc.mbr_partition[j].part_status);
                        sprintf(start, "%i",enc.mbr_partition[j].part_start);
                        sprintf(bsize, "%i",enc.mbr_partition[j].part_size);
                        fprintf(dot,"{ part_status_%i  | %s }|",j+1,status);
                        fprintf(dot,"{ part_type_%i  | %s }|",j+1,enc.mbr_partition[j].part_type);
                        fprintf(dot,"{ part_fit_%i  | %s }|",j+1,enc.mbr_partition[j].part_fit);
                        fprintf(dot,"{ part_start_%i  | %s }|",j+1,start);
                        fprintf(dot,"{ part_size_%i  | %s }|",j+1,bsize);
                        fprintf(dot,"{ part_name_%i  | %s }",j+1,enc.mbr_partition[j].part_name);
                    }
                }
                fprintf(dot,"}\"];\n");
                fprintf(dot,"}");
                fclose(dot);
                strcpy(terminal,"");
                strcat(terminal,"dot");
                if(strcmp(extension,"pdf")==0){
                    strcat(terminal," -Tpdf ");
                }else if(strcmp(extension,"png")==0){
                    strcat(terminal," -Tpng ");
                }else{
                    strcat(terminal," -Tjpg ");
                }
                strcat(terminal,dirDisco);
                strcat(terminal," -o ");
                strcat(terminal,dirImg);
                //system("dot -Tpng estructura.dot -o grafica.png");
                system(terminal);
                printf("se creo el reporte %s !!\n",dirImg);
            }else{
                printf("error al intentar crear el reporte de MBR!!\n");
            }    
        }else{
            printf("error el disco con id %s no ha sido montado !!\n",id);
        }
    }else{
        printf("error el disco con id %s no ha sido montado !!\n",id);
    }
}

void reporteMBRPART(char pathRep[],char id[]){
    nodol2 *aux;
    mbr enc;
    int j,i=3;
    char dirRep[150],dirDisco[150],particion[2],dirImg[150],terminal[300];
    strcpy(dirRep,"");
    strcat(dirRep,pathRep);
    aux=buscar2(list,id);
    if(aux!=NULL){
        if(strcmp(aux->id,id)==0){
            verificarPath(divPath(pathRep),dirRep);
            strcpy(dirDisco,"");
            strcat(dirDisco,pathAct);
            strcat(dirDisco,".dot");
            strcpy(dirImg,"");
            strcat(dirImg,pathAct);
            strcat(dirImg,".");
            strcat(dirImg,extension);
            enc=recuperarMBR(aux->path);
            FILE *dot = fopen(dirDisco,"w");
            if(dot!=NULL){
                fprintf(dot,"digraph MBRPART {node[ shape=box, style=filled]; rankdir=TB;\n");
                fprintf(dot,"subgraph cluster0 {color=blue;  node [color=white];\n");
                if(enc.mbr_espacio_libre>0){
                    fprintf(dot,"Nodo [label=\"LIBRE\"fillcolor=\"white\", shape=\"box\",color=blue];");
                }
                for(j=0;j<4;j++){
                    if(enc.mbr_partition[i].part_status==1){
                        if(strcmp(enc.mbr_partition[i].part_type,"p")==0){
                            strcpy(particion,"");
                            strcat(particion,"primaria");
                        }else{
                            strcpy(particion,"");
                            strcat(particion,"extendida");
                        }
                        fprintf(dot,"Nodo%i [label=\"%s\"fillcolor=\"white\", shape=\"box\",color=blue];",i,particion);
                    }
                    i--;
                }
                fprintf(dot,"Nodo%i [label=\"MBR\"fillcolor=\"white\", shape=\"box\",color=blue];",j+1);
                fprintf(dot,"}\n}\n");
                fclose(dot);
                strcpy(terminal,"");
                strcat(terminal,"dot");
                if(strcmp(extension,"pdf")==0){
                    strcat(terminal," -Tpdf ");
                }else if(strcmp(extension,"png")==0){
                    strcat(terminal," -Tpng ");
                }else{
                    strcat(terminal," -Tjpg ");
                }
                strcat(terminal,dirDisco);
                strcat(terminal," -o ");
                strcat(terminal,dirImg);
                //system("dot -Tpng estructura.dot -o grafica.png");
                system(terminal);
                printf("se creo el reporte %s !!\n",dirImg);
            }else{
                printf("error al intentar crear el reporte %s !!\n",dirImg);
            }
        }else{
            printf("error id %s no encontrado!!\n",id);
        }
    }else{
        printf("error la particion no ha sido montada!!\n");
    }
}

void reporteSB(char pathRep[],char id[]){
    nodol2 *aux;
    mbr enc;
    partition partEnc;
    sb sup;
    char a[10],b[10],c[10],d[10],f[10],e[10],g[10],h[10],i[10],j[10],k[10],l[10],m[10];
    char dirRep[150],dirDisco[150],tam[6],dirImg[150],terminal[300];
    strcpy(dirRep,"");
    strcat(dirRep,pathRep);
    aux=buscar2(list,id);
    if(aux!=NULL){
        if(strcmp(aux->id,id)==0){
            verificarPath(divPath(pathRep),dirRep);
                strcpy(dirDisco,"");
                strcat(dirDisco,pathAct);
                strcat(dirDisco,".dot");
                strcpy(dirImg,"");
                strcat(dirImg,pathAct);
                strcat(dirImg,".");
                strcat(dirImg,extension);
            enc=recuperarMBR(aux->path);
            partEnc=getPartition(aux->path,aux->name);
            FILE *dot = fopen(dirDisco,"w");
            if(dot!=NULL){
                sup=recuperarSB(aux->path,partEnc.part_start);
                sprintf(a, "%i",sup.inodes_count);
                sprintf(b, "%i",sup.blocks_count);
                sprintf(c, "%i",sup.free_blocks_count);
                sprintf(d, "%i",sup.free_inodes_count);
                sprintf(e, "%i",sup.mnt_count);
                sprintf(f, "%i",sup.inode_size);
                sprintf(g, "%i",sup.block_size);
                sprintf(h, "%i",sup.firs_ino);
                sprintf(i, "%i",sup.first_blo);
                sprintf(j, "%i",sup.bm_inode_start);
                sprintf(k, "%i",sup.bm_block_start);
                sprintf(l, "%i",sup.inode_start);
                sprintf(m, "%i",sup.block_start);
                fprintf(dot,"digraph ReporteSB { \n");
                fprintf(dot,"nodesep=.05; \n rankdir=\"TB\"; \n node [shape=record,width=.1,height=.1,color=blue,style=diagonals]; \n node [width = 1.5]; \n");
                fprintf(dot,"node1[label=\"{{NOMBRE |VALOR} |");
                fprintf(dot,"{ s_inodes_count | %s }|",a);
                fprintf(dot,"{ s_blocks_count | %s }|",b);
                fprintf(dot,"{ s_free_blocks_count | %s }|",c);
                fprintf(dot,"{ s_free_inodes_count | %s }|",d);
                fprintf(dot,"{ s_mtime | %s }|",sup.mtime);
                fprintf(dot,"{ s_umtime | %s }|",sup.umtime);
                fprintf(dot,"{ s_mnt_count | %s }|",e);
                fprintf(dot,"{ s_magic | 2007-14966 }|");
                fprintf(dot,"{ s_inode_size | %s }|",f);
                fprintf(dot,"{ s_block_size | %s }|",g);
                fprintf(dot,"{ s_first_inode_free | %s }|",h);
                fprintf(dot,"{ s_first_block_free | %s }|",i);
                fprintf(dot,"{ s_bm_inode_start | %s }|",j);
                fprintf(dot,"{ s_bm_block_start | %s }|",k);
                fprintf(dot,"{ s_inode_start | %s }|",l);
                fprintf(dot,"{ s_block_start | %s }",m);
                fprintf(dot,"}\"];\n");
                fprintf(dot,"}");
                fclose(dot);
                strcpy(terminal,"");
                strcat(terminal,"dot");
                if(strcmp(extension,"pdf")==0){
                    strcat(terminal," -Tpdf ");
                }else if(strcmp(extension,"png")==0){
                    strcat(terminal," -Tpng ");
                }else{
                    strcat(terminal," -Tjpg ");
                }
                strcat(terminal,dirDisco);
                strcat(terminal," -o ");
                strcat(terminal,dirImg);
                //system("dot -Tpng estructura.dot -o grafica.png");
                system(terminal);
                printf("se creo el reporte %s !!\n",dirImg);
            }else{
                printf("error al intentar crear el reporte de SuperBloque!!\n");
            }    
        }else{
            printf("error la particion con id %s no ha sido montado !!\n",id);
        }
    }else{
        printf("error la particion con id %s no ha sido montado !!\n",id);
    }
}

void reporteBitmapInodos(char pathRep[],char id[]){
    nodol2 *aux;
    mbr enc;
    partition partEnc;
    sb sup;
    char dirRep[150],dirDisco[150],tam[6],dirImg[150],terminal[300];
    int k,i;
    strcpy(dirRep,"");
    strcat(dirRep,pathRep);
    aux=buscar2(list,id);
    if(aux!=NULL){
        if(strcmp(aux->id,id)==0){
            verificarPath(divPath(pathRep),dirRep);
                strcpy(dirDisco,"");
                strcat(dirDisco,pathAct);
                strcat(dirDisco,".dot");
                strcpy(dirImg,"");
                strcat(dirImg,pathAct);
                strcat(dirImg,".");
                strcat(dirImg,extension);
            enc=recuperarMBR(aux->path);
            partEnc=getPartition(aux->path,aux->name);
            FILE *dot = fopen(dirDisco,"w");
            if(dot!=NULL){
                sup=recuperarSB(aux->path,partEnc.part_start);
                fprintf(dot,"digraph ReporteSB { \n");
                fprintf(dot,"nodesep=.05; \n rankdir=\"TB\"; \n node [shape=record,width=.1,height=.1,color=blue,style=diagonals]; \n node [width = 1.5]; \n");
                fprintf(dot,"node1[label=\"{{ID |ESTADO} |");
                i=sup.bm_inode_start;
                for(k=0;k<(sup.inodes_count-1);k++){
                    bitmap bm=recuperarBM(aux->path,i+k);
                    fprintf(dot,"{ %i | %c }|",k,bm.valor);
                }
                bitmap bm=recuperarBM(aux->path,i+k);
                fprintf(dot,"{ %i | %c }",k,bm.valor);
                fprintf(dot,"}\"];\n");
                fprintf(dot,"}");
//d [label="hello   jiji\nworld blabla",color=gray,fontsize=15,shape="box",fontcolor=white,style=filled];
                fclose(dot);
                strcpy(terminal,"");
                strcat(terminal,"dot");
                if(strcmp(extension,"pdf")==0){
                    strcat(terminal," -Tpdf ");
                }else if(strcmp(extension,"png")==0){
                    strcat(terminal," -Tpng ");
                }else{
                    strcat(terminal," -Tjpg ");
                }
                strcat(terminal,dirDisco);
                strcat(terminal," -o ");
                strcat(terminal,dirImg);
                //system("dot -Tpng estructura.dot -o grafica.png");
                system(terminal);
                printf("se creo el reporte %s !!\n",dirImg);
            }else{
                printf("error al intentar crear el reporte del bitmap de inodos!!\n");
            }    
        }else{
            printf("error la particion con id %s no ha sido montado !!\n",id);
        }
    }else{
        printf("error la particion con id %s no ha sido montado !!\n",id);
    }
}

void reporteBitmapBloques(char pathRep[],char id[]){
    nodol2 *aux;
    mbr enc;
    partition partEnc;
    sb sup;
    char dirRep[150],dirDisco[150],tam[6],dirImg[150],terminal[300];
    int k,i;
    strcpy(dirRep,"");
    strcat(dirRep,pathRep);
    aux=buscar2(list,id);
    if(aux!=NULL){
        if(strcmp(aux->id,id)==0){
            verificarPath(divPath(pathRep),dirRep);
                strcpy(dirDisco,"");
                strcat(dirDisco,pathAct);
                strcat(dirDisco,".dot");
                strcpy(dirImg,"");
                strcat(dirImg,pathAct);
                strcat(dirImg,".");
                strcat(dirImg,extension);
            enc=recuperarMBR(aux->path);
            partEnc=getPartition(aux->path,aux->name);
            FILE *dot = fopen(dirDisco,"w");
            if(dot!=NULL){
                sup=recuperarSB(aux->path,partEnc.part_start);
                fprintf(dot,"digraph ReporteSB { \n");
                fprintf(dot,"nodesep=.05; \n rankdir=\"TB\"; \n node [shape=record,width=.1,height=.1,color=blue,style=diagonals]; \n node [width = 1.5]; \n");
                fprintf(dot,"node1[label=\"{{ID |ESTADO} |");
                i=sup.bm_block_start;
                for(k=0;k<(sup.blocks_count-1);k++){
                    bitmap bm=recuperarBM(aux->path,i+k);
                    fprintf(dot,"{ %i | %c }|",k,bm.valor);
                }
                bitmap bm=recuperarBM(aux->path,i+k);
                fprintf(dot,"{ %i | %c }",k,bm.valor);
                fprintf(dot,"}\"];\n");
                fprintf(dot,"}");
//d [label="hello   jiji\nworld blabla",color=gray,fontsize=15,shape="box",fontcolor=white,style=filled];
                fclose(dot);
                strcpy(terminal,"");
                strcat(terminal,"dot");
                if(strcmp(extension,"pdf")==0){
                    strcat(terminal," -Tpdf ");
                }else if(strcmp(extension,"png")==0){
                    strcat(terminal," -Tpng ");
                }else{
                    strcat(terminal," -Tjpg ");
                }
                strcat(terminal,dirDisco);
                strcat(terminal," -o ");
                strcat(terminal,dirImg);
                //system("dot -Tpng estructura.dot -o grafica.png");
                system(terminal);
                printf("se creo el reporte %s !!\n",dirImg);
            }else{
                printf("error al intentar crear el reporte de bitmap de bloques!!\n");
            }    
        }else{
            printf("error la particion con id %s no ha sido montado !!\n",id);
        }
    }else{
        printf("error la particion con id %s no ha sido montado !!\n",id);
    }
}

void reporteInodo(char pathRep[],char id[]){
    nodol2 *aux;
    mbr enc;
    partition partEnc;
    sb sup;
    char dirRep[150],dirDisco[150],tam[6],dirImg[150],terminal[300];
    strcpy(dirRep,"");
    strcat(dirRep,pathRep);
    aux=buscar2(list,id);
    if(aux!=NULL){
        if(strcmp(aux->id,id)==0){
            verificarPath(divPath(pathRep),dirRep);
                strcpy(dirDisco,"");
                strcat(dirDisco,pathAct);
                strcat(dirDisco,".dot");
                strcpy(dirImg,"");
                strcat(dirImg,pathAct);
                strcat(dirImg,".");
                strcat(dirImg,extension);
            enc=recuperarMBR(aux->path);
            partEnc=getPartition(aux->path,aux->name);
            FILE *dot = fopen(dirDisco,"w");
            if(dot!=NULL){
                sup=recuperarSB(aux->path,partEnc.part_start);
                fprintf(dot,"digraph ReporteInodos { \n");
                fprintf(dot,"node[ shape=box, style=filled]; rankdir=BT \n");
                //inodo aux=recuperarINODO(char path[],int posIni,int idInodo);
//d [label="hello   jiji\nworld blabla",color=gray,fontsize=15,shape="box",fontcolor=white,style=filled];
                
                
                fclose(dot);
                strcpy(terminal,"");
                strcat(terminal,"dot");
                if(strcmp(extension,"pdf")==0){
                    strcat(terminal," -Tpdf ");
                }else if(strcmp(extension,"png")==0){
                    strcat(terminal," -Tpng ");
                }else{
                    strcat(terminal," -Tjpg ");
                }
                strcat(terminal,dirDisco);
                strcat(terminal," -o ");
                strcat(terminal,dirImg);
                //system("dot -Tpng estructura.dot -o grafica.png");
                system(terminal);
                printf("se creo el reporte %s !!\n",dirImg);
            }else{
                printf("error al intentar crear el reporte de SuperBloque!!\n");
            }    
        }else{
            printf("error la particion con id %s no ha sido montado !!\n",id);
        }
    }else{
        printf("error la particion con id %s no ha sido montado !!\n",id);
    }
}

/*
 void reporteMBR(char pathRep[],char id[]){
    nodol2 *aux;
    mbr enc;
    int j;
    char dirRep[150],dirDisco[150],tam[6],status[2],start[10],bsize[10],dirImg[150],terminal[300];
    strcpy(dirRep,"");
    strcat(dirRep,pathRep);
    aux=buscar2(list,id);
    if(aux!=NULL){
        if(strcmp(aux->id,id)==0){
            verificarPath(divPath(pathRep),dirRep);
                strcpy(dirDisco,"");
                strcat(dirDisco,pathAct);
                strcat(dirDisco,".dot");
                strcpy(dirImg,"");
                strcat(dirImg,pathAct);
                strcat(dirImg,".");
                strcat(dirImg,extension);
            enc=recuperarMBR(aux->path);
            FILE *dot = fopen(dirDisco,"w");
            if(dot!=NULL){
                sprintf(tam, "%i",enc.mbr_tamanio);
                fprintf(dot,"digraph ReporteMBR { \n");
                fprintf(dot,"nodesep=.05; \n rankdir=\"TB\"; \n node [shape=record,width=.1,height=.1,color=blue,style=diagonals]; \n node [width = 1.5]; \n");
                fprintf(dot,"node1[label=\"{{NOMBRE |VALOR} |");
                
                fprintf(dot,"{ mbr_tamanio  | %s }|",tam);
                fprintf(dot,"{ mbr_fecha_creacion  | %s }|",enc.mbr_fecha_creacion);
                fprintf(dot,"{ mbr_disk_signature  | %s }|",enc.mbr_disk_signature);
                for(j=0;j<4;j++){
                    if(enc.mbr_partition[j].part_status!=-1){
                        sprintf(status, "%i",enc.mbr_partition[j].part_status);
                        sprintf(start, "%i",enc.mbr_partition[j].part_start);
                        sprintf(bsize, "%i",enc.mbr_partition[j].part_size);
                        fprintf(dot,"{ part_status_%i  | %s }|",j+1,status);
                        fprintf(dot,"{ part_type_%i  | %s }|",j+1,enc.mbr_partition[j].part_type);
                        fprintf(dot,"{ part_fit_%i  | %s }|",j+1,enc.mbr_partition[j].part_fit);
                        fprintf(dot,"{ part_start_%i  | %s }|",j+1,start);
                        fprintf(dot,"{ part_size_%i  | %s }|",j+1,bsize);
                        fprintf(dot,"{ part_name_%i  | %s }",j+1,enc.mbr_partition[j].part_name);
                    }
                }
                fprintf(dot,"}\"];\n");
                fprintf(dot,"}");
                fclose(dot);
                strcpy(terminal,"");
                strcat(terminal,"dot");
                if(strcmp(extension,"pdf")==0){
                    strcat(terminal," -Tpdf ");
                }else if(strcmp(extension,"png")==0){
                    strcat(terminal," -Tpng ");
                }else{
                    strcat(terminal," -Tjpg ");
                }
                strcat(terminal,dirDisco);
                strcat(terminal," -o ");
                strcat(terminal,dirImg);
                //system("dot -Tpng estructura.dot -o grafica.png");
                system(terminal);
                printf("se creo el reporte %s !!\n",dirImg);
            }else{
                printf("error al intentar crear el reporte de MBR!!\n");
            }    
        }else{
            printf("error el disco con id %s no ha sido montado !!\n",id);
        }
    }else{
        printf("error el disco con id %s no ha sido montado !!\n",id);
    }
}
 */
