#ifndef INC_1_MATRADJ_H
#define INC_1_MATRADJ_H

struct struttura_elemento_matrice
{
    void *strutturaPtr;       /* Puntatore all'array contenenti i nodi del grafo (struttura_elemento_array_nodo_matrice) */
    int **matrice;           /* Puntatore alla matrice */
    int numeroNodi;
    int gradoEntrante;
    int gradoUscente;
};

struct struttura_elemento_array_nodo_matrice
{
    int nodo;
};

typedef struct struttura_elemento_matrice *GrafoMatrice;
typedef struct struttura_elemento_array_nodo_matrice *MatrAdj;

void F_alloca_struttura_gestione_matrice(GrafoMatrice *M);
void F_inserisci_arco_grafo_matrice(int **M, int nodoPartenza, int nodoArrivo);
void F_aggiungi_arco_grafo_matrice(GrafoMatrice *GM, int nodoPartenza, int nodoArrivo);
void F_stampa_grafo_matrice(GrafoMatrice *M);
void F_aggiungi_nodo_grafo_matrice(GrafoMatrice *M, int valoreDaInserire);
void F_alloca_nodo_grafo_matrice(GrafoMatrice *GM, MatrAdj *M, int valoreDaInserire);
void F_copia_matrice(int **matriceNuova, int **matriceVecchia, int numeroNodi);
MatrAdj F_cerca_nodo_grafo_matrice(MatrAdj *M, int valoreNodoDaTrovare, int indicePartenza, int numeroTotaleNodi);
int F_cerca_indice_grafo_matrice(MatrAdj *M, int valoreNodoDaTrovare, int indicePartenza, int numeroTotaleNodi);
void F_dealloca_struttura_grafo_matrice(GrafoMatrice GM);
void F_dealloca_matrice(int **matrice, int numeroNodi);
void F_dealloca_nodi_matrice(MatrAdj *nodi, int numeroNodi);

#endif //INC_1_MATRADJ_H
