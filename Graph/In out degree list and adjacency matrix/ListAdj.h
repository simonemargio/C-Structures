#ifndef INC_1_LISTADJ_H
#define INC_1_LISTADJ_H

struct struttura_gestione_grafi{
    void *strutturaPtr;             /* Puntatore a struttura_grafo_lista_adiacenza che indentidica l'insieme dei nodi del grafo */
    int numeroNodi;
    int gradoEntrante;
    int gradoUscente;
};

struct struttura_grafo_lista_adiacenza{
    int nodo;

    /*
     *  nextPtr scorre tra i nodi del grafo.
     *  arcoPtr scorre tra gli archi di un nodo.
     */
    struct struttura_grafo_lista_adiacenza *arcoPtr; /*  Puntatore all'arco del nodo */
    struct struttura_grafo_lista_adiacenza *nextPtr; /*  Puntatore al nodo successivo */

};

typedef struct struttura_grafo_lista_adiacenza *ListaAdj;
typedef struct struttura_gestione_grafi *GrafoLista;


void F_alloca_struttura_gestione_grafo(GrafoLista *G);
void F_aggiungi_nodo_grafo_lista(GrafoLista *G, int valoreDaInserire);
void F_alloca_nodo_grafo_lista(ListaAdj *L, int valoreDaInserire);
void F_aggiungi_arco_grafo_lista(GrafoLista *G, int valoreNodoPartenza, int valoreNodoArrivo);
ListaAdj F_cerca_nodo_grafo_lista(ListaAdj *L, int valoreNodoDaTrovare);
void F_inserisci_arco_grafo_lista(ListaAdj *L, int valoreDaInserire);
void F_stampa_grafo(ListaAdj *L);
void F_stampa_grafo_arco(ListaAdj *L);
void F_dealloca_struttura_grafo_lista(ListaAdj *L);
void F_dealloca_archi_grafo_lista(ListaAdj *L);

#endif //INC_1_LISTADJ_H
