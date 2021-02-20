#ifndef DEGREES_H
#define DEGREES_H

#include "ListaAdj.h"

struct struttura_gestione_grafi{
  struct struttura_grafo_lista_adiacenza *GrafoListaAdj;
  struct struttura_elemento_matrice *GrafoMatriceAdj;
  struct struttura_gestione_grado *GradoPtr;
  int numeroNodi;
};

struct struttura_gestione_grado{
    int nodo;
    int grado;
    struct struttura_gestione_grado *nextPtr;
};


typedef struct struttura_gestione_grafi *Grafo;
typedef struct struttura_grafo_lista_adiacenza *ListaAdj;
typedef struct struttura_gestione_grado *Grado;

void F_esegui_Degrees();
void F_alloca_struttura_gestione_grafi(Grafo *G);
int F_struttura_vuota(void *S);
void F_costruisci_grafo_lista_adiacenza(Grafo *G);
void F_costruisci_grafo_matrice_adiacenza(Grafo *G);
void F_calcolo_grado_uscente_entrante_grafo_lista_adiacenza(Grafo *G);
void F_calcolo_grado_entrante_grafo_lista_adiacenza(Grafo *G,ListaAdj *L);
void F_arco_lista_adiacenza(Grafo *G,ListaAdj *L);

void F_salva_valore_grado(Grado *Grado, int valoreDaSalvare);
void F_alloca_elemento_grado(Grado *Grado);
void F_stampa_grado_entrante_grafo_lista_adiacenza(Grado *G);


void F_calcolo_grado_uscente_grafo_lista_adiacenza(Grafo *G,ListaAdj *L);

#endif
