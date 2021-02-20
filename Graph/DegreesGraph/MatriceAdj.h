#ifndef DEGREES_H
#define DEGREES_H

struct struttura_elemento_matrice
{
    void *nodo;       /* Puntatore all'array contenenti i nodi del grafo */
    float **matrice;  /* Puntatore alla matrice */

};

struct struttura_elemento_array_nodo_matrice
{
    int nodo;
    struct struttra_extra_colore *visitaPtr;
};

typedef struct struttura_elemento_matrice *MatrAdj;
typedef struct struttura_elemento_array_nodo_matrice *ArrMatr;


void F_inizializza_grafo_matrice(Grafo *G);
void F_alloca_struttura_grafo_matrice(Grafo *G);
void F_inserisci_arco_grafo_matrice(float **M, int nodoPartenza, int nodoArrivo);
void F_aggiungi_arco_grafo_matrice(Grafo *G, int nodoPartenza, int nodoArrivo);
void F_stampa_grafo_matrice(Grafo *G);

#endif 
