#include <stdio.h>
#include <stdlib.h>
#include "Lab.h"
#include "ListAdj.h"


void F_alloca_struttura_gestione_grafo(GrafoLista *G){
    (*G)=(struct struttura_gestione_grafi*)malloc(sizeof(struct struttura_gestione_grafi));
    if(F_struttura_vuota(*G)) exit(-1);
    (*G)->strutturaPtr=NULL;
    (*G)->numeroNodi=0;
    (*G)->gradoEntrante=0;
    (*G)->gradoUscente=0;
}


void F_aggiungi_nodo_grafo_lista(GrafoLista *G, int valoreDaInserire){
    ListaAdj L=(*G)->strutturaPtr;
    F_alloca_nodo_grafo_lista(&L,valoreDaInserire);

    (*G)->numeroNodi++;
    (*G)->strutturaPtr=L;
}

void F_aggiungi_arco_grafo_lista(GrafoLista *G, int valoreNodoPartenza, int valoreNodoArrivo){
    ListaAdj L=(*G)->strutturaPtr;
    ListaAdj nodoPartenza=F_cerca_nodo_grafo_lista(&L,valoreNodoPartenza);

    if(!F_struttura_vuota(nodoPartenza)){

        ListaAdj nodoArrivo=F_cerca_nodo_grafo_lista(&L,valoreNodoArrivo);

        if(!F_struttura_vuota(nodoArrivo)){
            F_inserisci_arco_grafo_lista(&nodoPartenza->arcoPtr,nodoArrivo->nodo);

        }else printf("Nodo (%d) di arrivo non e' presente nel grafo.\n",valoreNodoPartenza);

    }else printf("Nodo (%d) di partenza non e' presente nel grafo.\n",valoreNodoArrivo);
}



ListaAdj F_cerca_nodo_grafo_lista(ListaAdj *L, int valoreNodoDaTrovare){
    if(F_struttura_vuota(*L)) return NULL;
    if((*L)->nodo==valoreNodoDaTrovare) return (*L);
    return F_cerca_nodo_grafo_lista((&(*L)->nextPtr),valoreNodoDaTrovare);
}

void F_inserisci_arco_grafo_lista(ListaAdj *L, int valoreDaInserire){
    if(F_struttura_vuota(*L)) {
        F_alloca_nodo_grafo_lista(L,valoreDaInserire);
    }
    else{
        if((*L)->nodo==valoreDaInserire)  { printf("Arco con (%d) gia' presente.\n",valoreDaInserire); return;}
        else F_inserisci_arco_grafo_lista((&(*L)->arcoPtr),valoreDaInserire);
    }
}


void F_stampa_grafo(ListaAdj *L){
    if(!F_struttura_vuota(*L)){
        printf("(%d)",(*L)->nodo);
        F_stampa_grafo_arco(&(*L)->arcoPtr);
        puts("");
        F_stampa_grafo(&(*L)->nextPtr);
    }
}

void F_stampa_grafo_arco(ListaAdj *L){
    if(!F_struttura_vuota(*L)){
        printf("->(%d)",(*L)->nodo);
        F_stampa_grafo_arco(&(*L)->arcoPtr);
    }
}

void F_dealloca_struttura_grafo_lista(ListaAdj *L){
    if(!F_struttura_vuota(*L)){
        F_dealloca_struttura_grafo_lista((&(*L)->nextPtr));
        if((*L)->arcoPtr) F_dealloca_archi_grafo_lista(&(*L)->arcoPtr);
        free(*L);
    }
}

void F_dealloca_archi_grafo_lista(ListaAdj *L){
    if (!F_struttura_vuota(*L)) {
        F_dealloca_archi_grafo_lista((&(*L)->arcoPtr));
        free(*L);
        *L=NULL;
    }
}

void F_alloca_nodo_grafo_lista(ListaAdj *L, int valoreDaInserire){
    if(F_struttura_vuota(*L)) {
        (*L)=(struct struttura_grafo_lista_adiacenza*)malloc(sizeof(struct struttura_grafo_lista_adiacenza));
        if(F_struttura_vuota(*L)) exit(2);
        (*L)->nodo=valoreDaInserire;
        (*L)->nextPtr=NULL;
        (*L)->arcoPtr=NULL;
    } else F_alloca_nodo_grafo_lista((&(*L)->nextPtr),valoreDaInserire);
}
