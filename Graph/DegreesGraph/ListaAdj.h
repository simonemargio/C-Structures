#ifndef LISTAADJ_H
#define LISTAADJ_H

#include "Degrees.h"

struct struttura_grafo_lista_adiacenza
{
    int nodo;

    struct struttura_grafo_lista_adiacenza *arcoPtr; /*  Puntatore all'arco del nodo */
    struct struttura_grafo_lista_adiacenza *nextPtr; /*  Puntatore al nodo successivo */
};

typedef struct struttura_gestione_grafi *Grafo;
typedef struct struttura_grafo_lista_adiacenza *ListaAdj;


void F_alloca_nodo_grafo_lista(ListaAdj *L, int valoreNodo);
void F_aggiungi_nodo_grafo_lista(Grafo *G, int valoreNodoDaAggiungere);
void F_stampa_grafo_lista(ListaAdj *L);
void F_stampa_grafo_lista_arco(ListaAdj *A);
void F_inserisci_arco_grafo_lista(ListaAdj *L, int nodo);
ListaAdj F_cerca_nodo_grafo_lista(ListaAdj *L, int nodoDaTrovare);
void F_aggiungi_arco_grafo_lista(Grafo *G, int nodoPartenza, int nodoArrivo);



#endif
