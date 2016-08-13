/* 
 * File:   lista.h
 * Author: Wendy Mazariegos
 *
 * Created on 11 de febrero de 2016, 06:16 AM
 */

#ifndef LISTA_H
#define	LISTA_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct nodo{
        char contenido[100];
        struct nodo *ant;
        struct nodo *sig;
    }nodol;

    typedef struct{
        nodol *primero;
        nodol *ultimo;
    }Lista;
    
    typedef struct nodo2{
        char id[5];
        char name[20];
        char path[100];
        struct nodo2 *ant;
        struct nodo2 *sig;
    }nodol2;
    
    typedef struct{
        nodol2 *primero;
        nodol2 *ultimo;
    }Lista2;
    
    void addLista(Lista *l, char nom[]);
    nodol* getLista(Lista *l);
    void recLista(Lista *l);
    int vacia(Lista *l);
    void freeLista(Lista *l);
    
    void addLista2(Lista2 *l, char path[],char name[],char id[]);
    nodol2* buscar2(Lista2 *l,char id[]);
    nodol2 *buscar21(Lista2 *l,char path[],char name[]);
    int eliminar(Lista2 *l,char id[]);
    int vacia2(Lista2 *l);
    void recLista2(Lista2 *l);

#ifdef	__cplusplus
}
#endif

#endif	/* LISTA_H */

