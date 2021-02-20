#include <stdio.h>
#include <stdlib.h>
#include "ListaAdj.h"
#include "Degrees.h"

void F_aggiungi_nodo_grafo_lista(Grafo *G, int valoreNodoDaAggiungere){
    ListaAdj L=(*G)->GrafoListaAdj;
    F_alloca_nodo_grafo_lista(&L,valoreNodoDaAggiungere);

    (*G)->numeroNodi++;
    (*G)->GrafoListaAdj=L;
}

void F_alloca_nodo_grafo_lista(ListaAdj *L, int valoreNodo){
    if(F_struttura_vuota(*L)){
        (*L)=(struct struttura_grafo_lista_adiacenza*)malloc(sizeof(struct struttura_grafo_lista_adiacenza));
        if(F_struttura_vuota(*L)) exit(2);
        (*L)->nodo=valoreNodo;
        (*L)->nextPtr=NULL;
        (*L)->arcoPtr=NULL;
    } else F_alloca_nodo_grafo_lista((&(*L)->nextPtr),valoreNodo);
}

void F_stampa_grafo_lista(ListaAdj *L){
    if(!F_struttura_vuota(*L)){
        printf("|%d|",(*L)->nodo);
        F_stampa_grafo_lista_arco((&(*L)->arcoPtr));
        puts("");
        F_stampa_grafo_lista(&(*L)->nextPtr);
    }
}

void F_stampa_grafo_lista_arco(ListaAdj *A){
    if(!F_struttura_vuota(*A)){
        printf("->|%d|",(*A)->nodo);
        F_stampa_grafo_lista_arco(&(*A)->arcoPtr);
    }
}



void F_aggiungi_arco_grafo_lista(Grafo *G, int nodoPartenza, int nodoArrivo){
    ListaAdj L=(*G)->GrafoListaAdj;
    ListaAdj nodoPatenza=F_cerca_nodo_grafo_lista(&L,nodoPartenza);

    F_inserisci_arco_grafo_lista(&nodoPatenza->arcoPtr, nodoArrivo);

}

ListaAdj F_cerca_nodo_grafo_lista(ListaAdj *L, int nodoDaTrovare){
    if(F_struttura_vuota(*L)) return NULL;
    if(nodoDaTrovare==(*L)->nodo) return (*L);
    return F_cerca_nodo_grafo_lista((&(*L)->nextPtr),nodoDaTrovare);
}


void F_inserisci_arco_grafo_lista(ListaAdj *L, int nodo){
    if(F_struttura_vuota(*L)) F_alloca_nodo_grafo_lista(L,nodo);
    else{
        if((*L)->nodo==nodo) { printf("Nodo (%d) gia' presente\n",nodo); return;}
        else F_inserisci_arco_grafo_lista((&(*L)->arcoPtr),nodo);
    }
}