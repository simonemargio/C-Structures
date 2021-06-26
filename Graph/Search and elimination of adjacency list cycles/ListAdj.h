#ifndef INC_1_LISTADJ_H
#define INC_1_LISTADJ_H

struct struttura_gestione_grafi{
    void *strutturaPtr;
    int numeroNodi;
    int ciclico;  /* 0: nessun ciclo 1: altrimenti */
};

struct struttra_extra_colore{
    int colore;   /* 0: bianco 1:grigio 2: nero */
};

struct struttura_grafo_lista_adiacenza{
    int nodo;

    /*
    *  nextPtr scorre tra i nodi del grafo.
    *  arcoPtr scorre tra gli archi di un nodo.
    *  visitaPtr punta alla struttura che indentifica il colore del nodo.
    */
    struct struttura_grafo_lista_adiacenza *arcoPtr; /*  Puntatore all'arco del nodo */
    struct struttura_grafo_lista_adiacenza *nextPtr; /*  Puntatore al nodo successivo */
    struct struttra_extra_colore *visitaPtr;        /*  Puntatore alla struttura struttra_extra_colore */
};


typedef struct struttura_grafo_lista_adiacenza *ListaAdj;
typedef struct struttura_gestione_grafi *Grafo;
typedef struct struttra_extra_colore *Colore;

void F_alloca_struttura_gestione_grafo(Grafo *G);
void F_aggiungi_nodo_grafo_lista(Grafo *G, int valoreDaInserire);
void F_alloca_nodo_grafo_lista(ListaAdj *L, int valoreDaInserire);
void F_aggiungi_arco_grafo_lista(Grafo *G, int valoreNodoPartenza, int valoreNodoArrivo);
ListaAdj F_cerca_nodo_grafo_lista(ListaAdj *L, int valoreNodoDaTrovare);
void F_inserisci_arco_grafo_lista(ListaAdj *L, int valoreDaInserire);
void F_stampa_grafo(ListaAdj *L);
void F_stampa_grafo_arco(ListaAdj *L);
Colore F_alloca_struttura_colore();
void F_inizializza_visita_in_profondita_ampiezza_lista(Grafo *G);
void F_visita_in_profondita_lista(Grafo *G);
void F_esegui_visita_in_profondita_lista(Grafo *G, ListaAdj u);
void F_cambia_colore_vertice_lista(Grafo *G, ListaAdj vertice, int nuovoColore);
ListaAdj F_restituisci_vertice_adiacente_grafo_lista(Grafo *G, ListaAdj u, ListaAdj ultimo);
int F_controllo_colore_vertice_lista(Grafo *G,ListaAdj vertice);
void F_dealloca_arco_grafo_lista(ListaAdj *L, int valoreDaEliminare);
void F_dealloca_struttura_grafo_lista(ListaAdj *L);
void F_dealloca_archi_grafo_lista(ListaAdj *L);

#endif //INC_1_LISTADJ_H
