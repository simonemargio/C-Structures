#ifndef INC_1_LISTADJ_H
#define INC_1_LISTADJ_H

struct struttura_gestione_grafi{
    void *strutturaPtr;
    int numeroNodi;
};

struct struttura_grafo_pesato{
    int peso;
};


struct struttura_grafo_lista_adiacenza{
    int nodo;

    struct struttura_grafo_lista_adiacenza *arcoPtr; /*  Puntatore all'arco del nodo */
    struct struttura_grafo_lista_adiacenza *nextPtr; /*  Puntatore al nodo successivo */
    struct struttura_grafo_pesato *pesoPtr;
};


typedef struct struttura_grafo_lista_adiacenza *ListaAdj;
typedef struct struttura_gestione_grafi *Grafo;
typedef struct struttura_grafo_pesato *Peso;


void F_alloca_struttura_gestione_grafo(Grafo *G);
void F_aggiungi_nodo_grafo_lista(Grafo *G, int valoreDaInserire);
void F_alloca_nodo_grafo_lista(ListaAdj *L, int valoreDaInserire);
void F_aggiungi_arco_grafo_lista(Grafo *G, int valoreNodoPartenza, int valoreNodoArrivo, int peso);
ListaAdj F_cerca_nodo_grafo_lista(ListaAdj *L, int valoreNodoDaTrovare);
void F_inserisci_arco_grafo_lista(ListaAdj *L, int valoreDaInserire, int peso);
void F_alloca_struttura_peso(Peso *P);
void F_stampa_grafo(ListaAdj *L);
void F_stampa_grafo_arco(ListaAdj *L);
void F_dealloca_struttura_grafo_lista(ListaAdj *L);
void F_dealloca_archi_grafo_lista(ListaAdj *L);
ListaAdj F_cerca_arco_grafo_lista(ListaAdj *L, int valoreNodoDaTrovare);

#endif //INC_1_LISTADJ_H
