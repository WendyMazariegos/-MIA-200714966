#include "plantillaParticion.h"
#include "plantillaDiscos.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <math.h>

//Lista2 *list; //mantiene en memoria las particiones montadas
char fecha1[16];

void fechaAct1(){
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    strftime(fecha1,16,"%d/%m/%y-%H:%M",tlocal);
}

void iniList(){ //inicializa lista
    list=malloc(sizeof(Lista2));
}

char *limpiarCad(int i){
    int j;
    char *cadena;
    for(j=0;j<i;j++){
        cadena[j] = '\0';
    }
    return cadena;
}

int existeDisco(char path[]){
    FILE *ver;
    int r;
    r=0;
    ver=fopen(path,"r");
    if(ver!=NULL){
        fclose(ver);
        r=1;
    }else{
        printf("error el disco no se ha encontrado!!\n");
    }
    return r;
}

void actualizarMBR(char path[],mbr encontrado){
    FILE *ver;
    ver=fopen(path,"rb+");
    if(ver!=NULL){
        fwrite(&encontrado,sizeof(mbr),1,ver);
        fclose(ver);
    }
}

mbr recuperarMBR(char path[]){
    FILE *ver;
    mbr encontrado;
    ver=fopen(path,"rb+");
    if(ver!=NULL){
        fread(&encontrado,sizeof(mbr),1,ver);
        fclose(ver);
    }
    return encontrado;
}

void actualizarSB(char path[],sb actual,int pos){
    FILE *ver;
    ver=fopen(path,"rb+");
    if(ver!=NULL){
        fseek(ver,pos,SEEK_SET);
        fwrite(&actual,sizeof(sb),1,ver);
        fclose(ver);
    }
}

sb recuperarSB(char path[],int posPart){
    FILE *ver;
    sb actual;
    ver=fopen(path,"rb+");
    if(ver!=NULL){
        fseek(ver,posPart,SEEK_SET);
        fread(&actual,sizeof(sb),1,ver);
        fclose(ver);
    }
    return actual;
}

void actualizarINODO(char path[],inodo actual,int posIni){ //nuevo inodo o actualizado, posIni donde inicia bloq de inodos
    FILE *ver;
    ver=fopen(path,"rb+");
    if(ver!=NULL){
        fseek(ver,posIni,SEEK_SET);
        fwrite(&actual,sizeof(inodo),1,ver);
        fclose(ver);
    }
}

inodo recuperarINODO(char path[],int posIni,int idInodo){
    FILE *ver;
    inodo actual;
    ver=fopen(path,"rb+");
    if(ver!=NULL){
        fseek(ver,posIni+(idInodo*sizeof(inodo)),SEEK_SET);
        fread(&actual,sizeof(inodo),1,ver);
        fclose(ver);
    }
    return actual;
}

void actualizarBM(char path[],bitmap actual,int pos){ //actualiza bitmap
    FILE *ver;
    ver=fopen(path,"rb+");
    if(ver!=NULL){
        fseek(ver,pos,SEEK_SET);
        fwrite(&actual,sizeof(bitmap),1,ver);
        fclose(ver);
    }
}

bitmap recuperarBM(char path[],int pos){
    FILE *ver;
    bitmap actual;
    ver=fopen(path,"rb+");
    if(ver!=NULL){
        fseek(ver,pos,SEEK_SET);
        fread(&actual,sizeof(bitmap),1,ver);
        fclose(ver);
    }
    return actual;
}

void actualizarBC(char path[],bloqCarp actual,int pos){ //actualiza bloq de carpetas
    FILE *ver;
    ver=fopen(path,"rb+");
    if(ver!=NULL){
        fseek(ver,pos,SEEK_SET);
        fwrite(&actual,sizeof(bloqCarp),1,ver);
        fclose(ver);
    }
}

bloqCarp recuperarBC(char path[],int pos){ //recupera bloq de carpetas
    FILE *ver;
    bloqCarp actual;
    ver=fopen(path,"rb+");
    if(ver!=NULL){
        fseek(ver,pos,SEEK_SET);
        fread(&actual,sizeof(bloqCarp),1,ver);
        fclose(ver);
    }
    return actual;
}

void actualizarCA(char path[],contArch actual,int pos){ //actualiza struct que contiene 64 bytes de contenido de un archivo
    FILE *ver;
    ver=fopen(path,"rb+");
    if(ver!=NULL){
        fseek(ver,pos,SEEK_SET);
        fwrite(&actual,sizeof(contArch),1,ver);
        fclose(ver);
    }
}

contArch recuperarCA(char path[],int pos){ //recupera struct que contiene 64 bytes de contenido de un archivo
    FILE *ver;
    contArch actual;
    ver = fopen(path, "rb+");
    if (ver != NULL) {
        fseek(ver, pos, SEEK_SET);
        fread(&actual, sizeof (contArch), 1, ver);
        fclose(ver);
    }
    return actual;
}

void actualizarBA(char path[],apuntador actual,int pos){ //actualiza bloque de 16 apuntadores
    FILE *ver;
    ver=fopen(path,"rb+");
    if(ver!=NULL){
        fseek(ver,pos,SEEK_SET);
        fwrite(&actual,sizeof(apuntador),1,ver);
        fclose(ver);
    }
}

apuntador recuperarBA(char path[],int pos){ //recupera bloque de 16 apuntadores
    FILE *ver;
    apuntador actual;
    ver = fopen(path, "rb+");
    if (ver != NULL) {
        fseek(ver, pos, SEEK_SET);
        fread(&actual, sizeof (apuntador), 1, ver);
        fclose(ver);
    }
    return actual;
}

bloqCarp bloqCarpStd(){
    int j;
    bloqCarp aux;
    for(j=0;j<4;j++){
        aux.b_content[j].b_inodo=-1; //apt no usado
        strcpy(aux.b_content[j].b_name,"");
    }
    return aux;
}

inodo inodoStd(int i){
    int j;
    inodo aux;
    aux.i_id=i;
    aux.i_size=-1;
    strcpy(aux.i_atime,"");
    strcpy(aux.i_ctime,"");
    strcpy(aux.i_mtime,"");
    for(j=0;j<15;j++){
        aux.i_bloq[j]=-1;
    }
    aux.i_perm=664;
    return aux;
}

partition getPartition(char path[],char name[]){
    int i;
    mbr actual;
    partition encontrado;
    actual=recuperarMBR(path);
    for(i=0;i<4;i++){
        if(strcmp(actual.mbr_partition[i].part_name,name)==0){
            encontrado=actual.mbr_partition[i];
            break;
        }
    }
    return encontrado;
}

//CREAR PARTICIÓN PRIMARIA
void crearParticion(int size,char unit[],char path[],char type[],char fit[],char name[]){ //tamaño en bytes
    //printf("se creara una particion...\n");
    int i,estado,exnom,x,usado,tam; //x numero de particion a utilizar, usado numero de bytes usados del disco
    exnom=0;
    x=-1;
    usado=sizeof(mbr);
    if(existeDisco(path)){
        mbr miMBR;
        miMBR=recuperarMBR(path);
        if(strcmp(unit,"b")==0 || strcmp(unit,"B")==0 || strcmp(unit,"k")==0 || strcmp(unit,"K")==0 || strcmp(unit,"m")==0 || strcmp(unit,"M")==0){
            if(strcmp(unit,"b")==0 || strcmp(unit,"B")==0){
                tam=size;
            }else if(strcmp(unit,"k")==0 || strcmp(unit,"K")==0){
                tam=size*1024;
            }else if(strcmp(unit,"m")==0 || strcmp(unit,"M")==0){
                tam=size*1024*1024;
            }
            if(miMBR.mbr_espacio_libre>tam){ //si existe suficiente espacio en el disco 
                for(i=0;i<4;i++){ //si el nombre de partcion ya existe
                    if(strcmp(miMBR.mbr_partition[i].part_name,name)==0){
                        exnom=1;
                        break;
                    }
                }
                if(exnom==0){ //si no existe el nombre de particion
                    for(i=0;i<4;i++){
                        estado=miMBR.mbr_partition[i].part_status;
                        if(estado==0){ //si la particion ha sido eliminada 
                            if(miMBR.mbr_partition[i].part_size>=size){
                                x=i;
                                usado=usado+miMBR.mbr_partition[i].part_start; //donde inicia la nueva particion
                                break;
                            }else{
                                usado=usado+miMBR.mbr_partition[i].part_size;
                            }
                        }else if(estado==1){ //si la particion sigue activa
                            usado=usado+miMBR.mbr_partition[i].part_size;
                        }else{
                            x=i;
                            break;
                        }
                    }
                    if((miMBR.mbr_tamanio-usado-sizeof(mbr))>=tam){
                        if(miMBR.mbr_partition[x].part_status==0 || miMBR.mbr_partition[x].part_status==-1){
                            if(strcmp(type,"p")==0 || strcmp(type,"e")==0 || strcmp(type,"l")==0){
                                if(strcmp(fit,"bf")==0 || strcmp(fit,"ff")==0 || strcmp(fit,"wf")==0){
                                    if(strcmp(type,"p")==0){ //creando particion primaria
                                        strcpy(miMBR.mbr_partition[x].part_fit,fit);
                                        strcpy(miMBR.mbr_partition[x].part_name,name);
                                        miMBR.mbr_partition[x].part_size=tam;
                                        miMBR.mbr_partition[x].part_start=usado;
                                        miMBR.mbr_partition[x].part_status=1; //particion creada
                                        strcpy(miMBR.mbr_partition[x].part_type,type);
                                        actualizarMBR(path,miMBR);
                                        printf("la particion %s a sido creada exitosamente!!\n",name);
                                    }
                                }else{
                                    printf("error en el tipo de ajuste de la particion!!\n");
                                }
                            }else{
                                printf("error en el tipo de particion que se quiere crear!!\n");
                            }
                        }else{
                            printf("ya no es posible crear particiones!!\n");
                        }
                    }else{
                        printf("no se ha encontrado espacio continuo para la particion!!\n");
                    }
                }else{
                    printf("error el nombre de la particion ya existe!!\n");
                }
            }else{
                printf("no existe sufieciente espacio para crear la particion!!\n");
            }
        }else{
            printf("error la unidad %s no ha sido reconocida!!\n",unit);
        }
    }
}


//FORMATEAR PARTICION
void formatearParticion(char path[],char type[],char name[]){
    int i,iniPart;
    float n,m;
    char *cadena;
    partition encontrado;
    sb nuevoSB;
    if(existeDisco(path)){
        if(strcmp(type,"fast")==0 || strcmp(type,"full")==0){
            encontrado=getPartition(path,name);
            if(strcmp(encontrado.part_name,name)==0){
                iniPart=encontrado.part_start;
                n=((encontrado.part_size-sizeof(sb))/(4+sizeof(inodo)+3*sizeof(apuntador))); //64 tamaño del bloque  
                //n=floor(m);
                //printf("n es :%.1lf\n",n);
                nuevoSB.inodes_count=n;
                nuevoSB.blocks_count=3*n;
                nuevoSB.free_inodes_count=n-1;
                nuevoSB.free_blocks_count=(3*n)-1;
                strcpy(nuevoSB.mtime,"");
                strcpy(nuevoSB.umtime,"");
                nuevoSB.mnt_count=0;
                nuevoSB.magic= 2007-149666;
                nuevoSB.inode_size=sizeof(inodo);
                nuevoSB.block_size=sizeof(apuntador);
                nuevoSB.firs_ino=iniPart+sizeof(sb)+(4*n)+sizeof(inodo);
                nuevoSB.first_blo=iniPart+sizeof(sb)+(4*n)+(n*sizeof(inodo))+sizeof(apuntador);
                nuevoSB.bm_inode_start=iniPart+sizeof(sb);
                nuevoSB.bm_block_start=iniPart+sizeof(sb)+n;
                nuevoSB.inode_start=iniPart+sizeof(sb)+(4*n);
                nuevoSB.block_start=iniPart+sizeof(sb)+(4*n)+(n*sizeof(inodo));
                actualizarSB(path,nuevoSB,encontrado.part_start);
                if(strcmp(type,"full")==0){ //realiza formateo completo
                    for(i=0;i<(4*n);i++){
                        bitmap nuevo;
                        nuevo.valor='0';
                        actualizarBM(path,nuevo,nuevoSB.bm_inode_start+i);
                    }
                    bitmap a;
                    a.valor='1';
                    actualizarBM(path,a,nuevoSB.bm_inode_start);
                    actualizarBM(path,a,nuevoSB.bm_block_start);
                    inodo raiz;
                    raiz=inodoStd(0);
                    fechaAct1();
                    strcpy(raiz.i_ctime,fecha1);
                    strcpy(raiz.i_mtime,fecha1);
                    raiz.i_type='0';
                    actualizarINODO(path,raiz,nuevoSB.inode_start);
                    for(i=0;i<n-1;i++){
                        inodo aux;
                        aux=inodoStd(i+1);
                        actualizarINODO(path,aux,nuevoSB.inode_start+(i*sizeof(inodo)));
                    }
                    bloqCarp bloqrz;
                    bloqrz=bloqCarpStd();
                    bloqrz.b_content[0].b_inodo=0;
                    strcpy(bloqrz.b_content[0].b_name,".");
                    bloqrz.b_content[0].b_inodo=0;
                    strcpy(bloqrz.b_content[0].b_name,"..");
                    actualizarBC(path,bloqrz,nuevoSB.block_start);
                    cadena=limpiarCad(64);
                    for(i=0;i<(3*(n-1));i++){ //verificar como llenar tabla de bloques
                        contArch aux;
                        strcpy(aux.contenido,cadena);
                        actualizarCA(path,aux,nuevoSB.block_start+((i+1)*sizeof(contArch)));
                    }
                    printf("particion %s ha sido formateado como ext2!!\n",name);
                }
            }else{
                printf("error la particion %s no se ha encontrado!!\n",name);
            }
        }else{
            printf("error en el tipo de formateo!!\n");
        }   
    }  
}

void modificarParticion(int tam,char unit[],char path[],char name[]){
    
}

void eliminarParticion(char type[],char name[],char path[]){
    

}

//MONTAR LA PARTICIÓN
void montarParticion(char path[],char name[]){
    char id[4];
    int i=48,j;
    mbr miMBR;
    partition part;
    nodol2 *aux,*aux2;
    aux=buscar21(list,path,name);
    if(strcmp(aux->name,name)!=0 && strcmp(aux->path,path)!=0){
        if(existeDisco(path)){
            part=getPartition(path,name);
            if(strcmp(part.part_name,name)==0){
                if(vacia2(list)){
                   i=i+1; 
                }else{
                    aux2=list->primero;
                    while(aux2!=NULL){
                        if(strcmp(aux->path,path)==0){
                            i=i+1;
                        }
                        aux2=aux2->sig;
                    }
                }
                miMBR=recuperarMBR(path);
                j=strlen(miMBR.mbr_disk_signature);
                strcpy(id,"");
                strcat(id,miMBR.mbr_disk_signature);
                id[j]=i; //verificar convertir numero a string
                id[4]='\0';
                addLista2(list,path,name,id); //agrega a lista de particiones montadas
                //printf("se ha insertado un elmento\n");
                recLista2(list);
                printf("la particion %s ha sido montada con id %s !!\n",name,id);
            }else{
                printf("error la particion %s no se ha encontrado!!\n",name);
            }
        }
    }else{
        printf("error esta particion ya ha sido montada!!\n");
    }
}

//DESMONTAR LA PARTICIÓN
void desmontarParticion(char id[]){
    nodol2 *aux;
    char *r;
    if(list->primero!=NULL){
        aux=buscar2(list,id);
        if(aux!=NULL){
            r=strstr(aux->id,id);
            if(r!=NULL){
                if(eliminar(list,id)){
                    printf("la particion con id %s ha sido desmontada con exito!!\n",id);
                }else{
                    printf("error la particion %s no se pudo desmontar!!\n",aux->name);
                }
            }else{
                printf("error particion no encontrada o no ha sido montada!!\n");
            }
        }else{
            printf("la particion con id %s no se encontro !!\n",id);
        }
    }else{
        printf("error ninguna particion ha sido montada!!\n");
    }
}

//CREAR PARTICIÓN EXTENDIDA

/*  ACTUALIZAR EBR
 * void actualizarEBR(char path[],ebr encontrado){
    FILE *ver;
    ver=fopen(path,"rb+");
    if(ver!=NULL){
        fwrite(&encontrado,sizeof(ebr),1,ver);
        fclose(ver)
    }
}
 * RECUPERAR EBR
 * mbr recuperarEBR(char path[]){
    FILE *ver;
    ebr encontrado;
    ver=fopen(path,"rb+");
    if(ver!=NULL){
        fread(&encontrado,sizeof(ebr),1,ver);
        fclose(ver);
    }
    return encontrado;
}
 * 
 */
