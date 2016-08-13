#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addLista(Lista *l, char nom[]){
    nodol *n=malloc(sizeof(nodol));
    strcpy(n->contenido,nom);
    if(l->primero==NULL){
        n->ant=NULL;
        n->sig=NULL;
        l->primero=n;
        l->ultimo=n;
    }else{
        l->ultimo->sig=n;
        n->ant=l->ultimo;
        l->ultimo=n;
    }
}

void freeLista(Lista *l){
    nodol *aux;
    aux=l->primero;
    if(aux!=NULL){
        while(aux!=NULL){
            aux=aux->sig;
            free(aux);
        }
    }
}

nodol *getLista(Lista *l){
    nodol *aux;
    aux=l->primero;
    if(aux!=NULL){
        if(aux->sig!=NULL){
            l->primero=aux->sig;
        }else{
            l->primero=NULL;
            l->ultimo=NULL;
        }
        //free(aux);
    }
    return aux;
}

void recLista(Lista *l){
    nodol *auxiliar;
    auxiliar=l->primero;
    while(auxiliar!=NULL){
        printf(" %s\n",auxiliar->contenido);
        auxiliar=auxiliar->sig;
    }
}

int vacia(Lista *l){
    if(l->primero!=NULL){
        return 1;
    }else{
        return 0;
    }
}

void addLista2(Lista2 *l, char path[],char name[],char id[]){
    nodol2 *n=malloc(sizeof(nodol2));
    strcpy(n->path,"");
    strcpy(n->name,"");
    strcpy(n->id,"");
    strcat(n->path,path);
    strcat(n->name,name);
    strcat(n->id,id);
    if(l->primero==NULL){
        n->ant=NULL;
        n->sig=NULL;
        l->primero=n;
        l->ultimo=n;
    }else{
        l->ultimo->sig=n;
        n->ant=l->ultimo;
        l->ultimo=n;
    }
}

nodol2 *buscar2(Lista2 *l,char id[]){
    nodol2 *auxiliar;
    auxiliar=l->primero;
    while(auxiliar!=NULL){
        if(strcmp(auxiliar->id,id)==0){
            break;
        }
        auxiliar=auxiliar->sig;
    }
    return auxiliar;
}

nodol2 *buscar21(Lista2 *l,char path[],char name[]){
    nodol2 *auxiliar;
    auxiliar=l->primero;
    while(auxiliar!=NULL){
        if(strcmp(auxiliar->name,name)==0 && strcmp(auxiliar->path,path)==0){
            break;
        }
        auxiliar=auxiliar->sig;
    }
    if(auxiliar==NULL){
        auxiliar=malloc(sizeof(nodol));
        strcmp(auxiliar->name,"");
        strcmp(auxiliar->path,"");
        strcmp(auxiliar->id,"");
    }
    return auxiliar;
}

int eliminar(Lista2 *l,char id[]){
    nodol2 *aux,*aux2;
    aux2=buscar2(l,id);
    aux=l->primero;
    if(strcmp(aux2->id,id)==0){
        while(aux!=NULL && strcmp(aux->id,id)!=0){
            aux=aux->sig;
        }
        if(aux->sig==NULL && aux->ant==NULL){
            l->primero=NULL;
        }else if(aux->ant==NULL){
            aux->sig->ant=NULL;
        }else if(aux->sig==NULL){
            aux->ant->sig=NULL;
        }else{
            aux->ant->sig=aux->sig;
            aux->sig->ant=aux->ant;
        }
        free(aux);
        return 1;
    }else{
        return 0;
    }
}

int vacia2(Lista2 *l){
    if(l->primero==NULL){
        return 1;
    }else{
        return 0;
    }
}

void recLista2(Lista2 *l){
    nodol2 *auxiliar;
    auxiliar=l->primero;
    while(auxiliar!=NULL){
        printf(" %s | %s | %s\n",auxiliar->id,auxiliar->name,auxiliar->path);
        auxiliar=auxiliar->sig;
    }
}
