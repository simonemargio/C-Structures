#ifndef GRAFI_LISTAADJ_H
#define GRAFI_LISTAADJ_H

#include "Coda.h"

struct struttura_grafo_lista_adiacenza
{
    int nodo;

    struct struttura_grafo_pesato *pesoPtr;          /* Puntatore al peso se presente */
    struct struttura_grafo_lista_adiacenza *arcoPtr; /*  Puntatore all'arco del nodo */
    struct struttura_grafo_lista_adiacenza *nextPtr; /*  Puntatore al nodo successivo */
    struct struttra_extra_colore *visitaPtr;
};


typedef struct struttura_grafo_lista_adiacenza *ListaAdj;

void F_stampa_grafo_lista(ListaAdj *L);
void F_aggiungi_nodo_grafo_lista(Grafo *G);
void F_alloca_nodo_grafo_lista(ListaAdj *L, int valoreNodo);
void F_stampa_grafo_lista_arco(ListaAdj *A);
void F_aggiungi_arco_grafo_lista(Grafo *G);
ListaAdj F_cerca_nodo_grafo_lista(ListaAdj *L, int nodoDaTrovare);
void F_inserisci_arco_grafo_lista(ListaAdj *nodoPartenza, int nodo);
void F_elimina_nodo_grafo_lista(Grafo *G);
void F_dealloca_archi_grafo_lista(ListaAdj *L);
void F_dealloca_nodo_grafo_lista(ListaAdj *L, int valoreDaEliminare);
void F_dealloca_arco_grafo_lista(ListaAdj *L, int valoreDaEliminare);
void F_elimina_arco_grafo_lista(Grafo *G);
void F_visita_in_profondita_lista(Grafo *G);
void F_inizializza_visita_in_profondita_ampiezza_lista(Grafo *G);
void F_visita_in_ampiezza_lista(Grafo *G);
void F_inizializza_visita_ampiezza_lista(Grafo *G, int nodoSorgente);
Colore  F_alloca_struttura_colore();
void F_esegui_visita_in_ampiezza_lista(Grafo *G, ListaAdj nodoDiPartenza);
ListaAdj F_restituisci_vertice_adiacente_grafo_lista(Grafo *G, ListaAdj u, ListaAdj ultimo);
int F_controllo_colore_vertice_lista(Grafo *G,ListaAdj vertice);
void F_cambia_colore_vertice_lista(Grafo *G, ListaAdj vertice, int nuovoColore);



void F_esegui_visita_in_ampiezza_lista_ricorsiva(Grafo *G, ListaAdj nodoDiPartenza);
void F_visita_in_ampiezza_cerca_e_stampa_vertici_adiacenti_lista(Grafo *G, Coda *C);
void F_visita_in_ampiezza_stampa_vertici_adiacenti_lista(Grafo *G,Coda *C,ListaAdj vVerticeAdiacente,ListaAdj uVertice);
void F_esegui_visita_in_profondita_lista(Grafo *G, ListaAdj u);


#endif //GRAFI_LISTAADJ_H
