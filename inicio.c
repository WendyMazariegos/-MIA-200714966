#include "inicio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "plantillaDiscos.h"
#include "plantillaParticion.h"
#include "plantillaReporte.h"

int ope1,ope2,p,err,h; //p=1 si esta activo
char comando[8],tk[100],unit[3],path[100],type[6],fit[3],name[15],delete[5],add[8],id[5],content[100],dest[100],iddest[5],file[100],size[8];

void leerArchivo(char path[]){
    
}

void iniVars(){
    h=0;
    ope1=-1;
    ope2=-1;
    p=-1;
    err=0;
    strcpy(tk,"");
    strcpy(unit,"");
    strcpy(path,"");
    strcpy(type,"");
    strcpy(fit,"");
    strcpy(name,"");
    strcpy(delete,"");
    strcpy(add,"");
    strcpy(id,"");
    strcpy(content,"");
    strcpy(dest,"");
    strcpy(iddest,"");
    strcpy(file,"");
    strcpy(size,"");
    strcpy(comando,"");
}

void separarComando(char entrada[]){
    char *token;
    char contenido[100];
    Lista *l;
    l=malloc(sizeof(Lista));
    token=strtok(entrada," ");
    while(token!=NULL){
        h++;
        strcpy(contenido,"");
        strcat(contenido,token);
        addLista(l, contenido);
        token=strtok(NULL," ");
    }
    verificarComando(l);
    free(l);
}

void waitInst(){
    char entrada[200];
    int i;
    printf("\n");
    getchar();
    fflush(stdin);
    scanf("%[^\n]",entrada);
    i=strlen(entrada);
    if(i>0){
        if(strcmp(entrada,"0")==0){
            exit(0);
        }
        iniVars();
        //printf("capturado: %s\n",entrada);
        separarComando(entrada);
    }
}

void menu(char comando[]){
    int num = atoi(size);
    int tam = atoi(add);
    //printf("comando: %i, %s \n",ope1,comando);
    if(err==0){
        if(ope1==1 && strcmp(comando,"AC")==0){ //para crear discos
            crearDisco(num,"m",path);
        }else if(ope1==1 && strcmp(comando,"ABC")==0){
            crearDisco(num,unit,path);
        }else if(ope1==2 && strcmp(comando,"C")==0){ //eliminar disco;
            eliminarDisco(path);
        }else if(ope1==3 && ope2==-1){
            if(strcmp(comando,"ACF")==0){
                crearParticion(num,"k",path,"p","wf",name);
            }else if(strcmp(comando,"ACEF")==0){
                    crearParticion(num,"k",path,"p",fit,name);
            }else if(strcmp(comando,"ACDF")==0){
                crearParticion(num,"k",path,type,"wf",name);
            }else if(strcmp(comando,"ACDEF")==0){
                crearParticion(num,"k",path,type,fit,name);
            }else if(strcmp(comando,"ABCF")==0){
                crearParticion(num,unit,path,"p","wf",name);
            }else if(strcmp(comando,"ABCEF")==0){
                crearParticion(num,unit,path,"p",fit,name);
            }else if(strcmp(comando,"ABCDF")==0){
                crearParticion(num,unit,path,type,"wf",name);
            }else if(strcmp(comando,"ABCDEF")==0){
                crearParticion(num,unit,path,type,fit,name);
            }else{
                printf("error comando no reconocido!!\n");
            }
        }else if(ope1==3 && ope2==4){
            eliminarParticion(delete,name,path);
        }else if(ope1==3 && ope2==5){
            modificarParticion(tam,unit,path,name);
        }else if(ope1==6 && strcmp(comando,"CF")==0){
            formatearParticion(path,"full",name);
        }else if(ope1==6 && strcmp(comando,"CDF")==0){
            formatearParticion(path,type,name);
        }else if(ope1==7 && strcmp(comando,"CF")==0){
            montarParticion(path,name);
        }else if(ope1==8 && strcmp(comando,"I")==0){
            desmontarParticion(id);
        }else if(ope1==18 && strcmp(comando,"FCI")==0 && strcmp(name,"mbr")==0){
            reporteMBR(path,id);
        }else if(ope1==18 && strcmp(comando,"FCI")==0 && strcmp(name,"disk")==0){
            reporteMBRPART(path,id);
        }else if(ope1==18 && strcmp(comando,"FCI")==0 && strcmp(name,"sb")==0){
            reporteSB(path,id);
        }else if(ope1==18 && strcmp(comando,"FCI")==0 && strcmp(name,"bm_inode")==0){
            reporteBitmapInodos(path,id);
        }else if(ope1==18 && strcmp(comando,"FCI")==0 && strcmp(name,"bm_block")==0){
            reporteBitmapBloques(path,id);
        }else if(ope1==19 && strcmp(comando,"C")==0){
            leerArchivo(path);
        }else{
            printf("error comando no reconocido!!\n");
        }
    }else{
        printf("error comando no reconocido!!\n");
    }
}

void verificarComando(Lista *l){
    int k=0;
    char token[100];
    nodol *nodo;
    while(k<h){ 
        nodo=getLista(l);
        strcpy(token,"");
        strcat(token,nodo->contenido);
        if(strcmp(token,"mkdisk")==0 || strcmp(token,"Mkdisk")==0 ){
            ope1=1;
        }else if(strcmp(token,"rmdisk")==0){
            ope1=2;
        }else if(strcmp(token,"fdisk")==0){
            ope1=3;
        }else if(strcmp(token,"-delete")==0){
            ope2=4;
        }else if(strcmp(token,"-add")==0){
            ope2=5;
        }else if(strcmp(token,"mkfs")==0){
            ope1=6;
        }else if(strcmp(token,"mount")==0){
            ope1=7;
        }else if(strcmp(token,"unmount")==0){
            ope1=8;
        }else if(strcmp(token,"mkfile")==0){
            ope1=9;
        }else if(strcmp(token,"cat")==0){
            ope1=10;
        }else if(strcmp(token,"rmfile")==0){
            ope1=11;
        }else if(strcmp(token,"edit")==0){
            ope1=12;
        }else if(strcmp(token,"rename")==0){
            ope1=13;
        }else if(strcmp(token,"mkdir")==0){
            ope1=14;
        }else if(strcmp(token,"cp")==0){
            ope1=15;
        }else if(strcmp(token,"mv")==0){
            ope1=16;
        }else if(strcmp(token,"find")==0){
            ope1=17;
        }else if(strcmp(token,"rep")==0){
            ope1=18;
        }else if(strcmp(token,"exec")==0){
            ope1=19;
        }else if(strcmp(token,"-p")==0){
            p=1;
        }else{
            char *tok;
            tok=strtok(token,"=");
            if(strcmp(tok,"-size")==0){
                strcat(comando,"A");
                tok=strtok(NULL,"=");
                strcpy(size,tok);
            }else if(strcmp(tok,"-unit")==0){
                strcat(comando,"B");
                tok=strtok(NULL,"=");
                strcpy(unit,tok);
            }else if(strcmp(tok,"-path")==0 || strcmp(tok,"-Path")==0 || strcmp(tok,"-PAth")==0){
                strcat(comando,"C");
                tok=strtok(NULL,"=");
                strcpy(path,tok);
            }else if(strcmp(tok,"-type")==0){
                strcat(comando,"D");
                tok=strtok(NULL,"=");
                strcpy(type,tok);
            }else if(strcmp(tok,"-fit")==0){
                strcat(comando,"E");
                tok=strtok(NULL,"=");
                strcpy(fit,tok);
            }else if(strcmp(tok,"-name")==0){
                strcat(comando,"F");
                tok=strtok(NULL,"=");
                strcpy(name,tok);
            }else if(strcmp(tok,"-delete")==0){
                strcat(comando,"G");
                tok=strtok(NULL,"=");
                strcpy(delete,tok);
            }else if(strcmp(tok,"-add")==0){
                strcat(comando,"H");
                tok=strtok(NULL,"=");
                strcpy(add,tok);
            }else if(strcmp(tok,"-id")==0){
                strcat(comando,"I");
                tok=strtok(NULL,"=");
                strcpy(id,tok);
            }else if(strcmp(tok,"-content")==0){
                strcat(comando,"K");
                tok=strtok(NULL,"=");
                strcpy(content,tok);
            }else if(strcmp(tok,"-dest")==0){
                strcat(comando,"L");
                tok=strtok(NULL,"=");
                strcpy(dest,tok);
            }else if(strcmp(tok,"-iddest")==0){
                strcat(comando,"M");
                tok=strtok(NULL,"=");
                strcpy(iddest,tok);
            }else if(strcmp(tok,"-file")==0){
                strcat(comando,"N");
                tok=strtok(NULL,"=");
                strcpy(file,tok);
            }else{
                err=err+1;
                printf("#errores: %i\n",err);
            }
        }
        
        k++;
    } 
    menu(comando);
}
