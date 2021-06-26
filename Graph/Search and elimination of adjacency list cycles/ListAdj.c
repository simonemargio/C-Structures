#include <stdio.h>
#include <stdlib.h>
#include "ListAdj.h"
#include "Lab.h"

void F_visita_in_profondita_lista(Grafo *G){
    /*
     * Tutti i colori dei nodi vengono inzializzati a 0 (non visitati).
     * Ogni nodo viene agganciato alla struttura del colore in quanto
     * avere un'informazione nel nodo che identifica il colore non è una
     * informazione del nodo stesso.
     * Si è preferito quindi associare un puntatore alla struttura del colore
     * ed eliminarlo quando non serve più.
     */
    F_inizializza_visita_in_profondita_ampiezza_lista(G);

    ListaAdj L=(*G)->strutturaPtr;
    (*G)->ciclico=0;
    while (L){
        if(L->visitaPtr->colore==0) F_esegui_visita_in_profondita_lista(G,L);
        L=L->nextPtr;
    }
}

void F_esegui_visita_in_profondita_lista(Grafo *G, ListaAdj u){
    /*
     * Il nodo u preso viene messo come colore grigio pari a 1, ovvero il vertice
     * è visitato ma non sono ancora stati visitati i suoi adiacenti.
     */
    F_cambia_colore_vertice_lista(G,u,1);
    ListaAdj vVerticeAdiacente=F_restituisci_vertice_adiacente_grafo_lista(G,u,NULL);

    while(vVerticeAdiacente)
    {
        int controlloColore=F_controllo_colore_vertice_lista(G,vVerticeAdiacente);
        /*
         * Nodo già "visto" e quindi identifica un ciclo
         */
        if(controlloColore==1){
            (*G)->ciclico=1;
            ListaAdj L=(*G)->strutturaPtr;
            ListaAdj nodoCuiEliminareArco=F_cerca_nodo_grafo_lista(&L,u->nodo);
            /*
             * Si elimina l'arco che crea il ciclo
             */
            F_dealloca_arco_grafo_lista(&nodoCuiEliminareArco->arcoPtr,vVerticeAdiacente->nodo);
            return;
        }

        if(controlloColore==0){
            F_esegui_visita_in_profondita_lista(G,vVerticeAdiacente);
        }
        vVerticeAdiacente=F_restituisci_vertice_adiacente_grafo_lista(G,u,vVerticeAdiacente);
    }

    /*
     * Il nodo viene messo come colore nero pari a 2, ovver il vertice e TUTTI i suoi
     * adiacenti sono stati visitati.
     */
    F_cambia_colore_vertice_lista(G,u,2);
}

int F_controllo_colore_vertice_lista(Grafo *G,ListaAdj vertice){
    ListaAdj L=(*G)->strutturaPtr;
    ListaAdj nodoDaTrovare=F_cerca_nodo_grafo_lista(&L,vertice->nodo);
    return ((nodoDaTrovare->visitaPtr)->colore);
}

ListaAdj F_restituisci_vertice_adiacente_grafo_lista(Grafo *G, ListaAdj u, ListaAdj ultimo){
    /*
    *
    * Ultimo rappresenta l'ultimo nodo che e' stato passato come vertice adiacente.
    * La prima volta ultimo risulta=NULL e la funzione restituisce il primo vertice,
    * i successivi ultimo saranno uguali all'utlimo vertice ritornato dalla funzione.
    * In questo modo viene cercato il successivo vertice adiacente partendo dall'informazione
    * in ultimo.
    *
    */
    ListaAdj L=(*G)->strutturaPtr;

    while(L){
        if(u->nodo==L->nodo) break;
        L=L->nextPtr;
    }

    u=L;

    if(u && u->arcoPtr){

        if(ultimo){

            while (u){

                if(u->nodo==ultimo->nodo){
                    if(u->arcoPtr) ultimo=u->arcoPtr;
                    else ultimo=NULL;
                    break;
                }
                u=u->arcoPtr;
            }

        }else ultimo=u->arcoPtr;
    }

    return ultimo;
}

void F_cambia_colore_vertice_lista(Grafo *G, ListaAdj vertice, int nuovoColore){
    ListaAdj L=(*G)->strutturaPtr;
    ListaAdj nodoDaTrovare=F_cerca_nodo_grafo_lista(&L,vertice->nodo);
    if(nodoDaTrovare) ((nodoDaTrovare->visitaPtr)->colore)=nuovoColore;
}

void F_inizializza_visita_in_profondita_ampiezza_lista(Grafo *G){
    ListaAdj L=(*G)->strutturaPtr;

    while(L){
        Colore nuovoColore=F_alloca_struttura_colore();
        nuovoColore->colore=0;
        L->visitaPtr=nuovoColore;
        L=L->nextPtr;
    }
}

Colore F_alloca_struttura_colore(){
    Colore nuovoColore=(struct struttra_extra_colore *)malloc(sizeof(struct struttra_extra_colore));
    if(F_struttura_vuota(nuovoColore)) exit(-2);
    nuovoColore->colore=0;
    return nuovoColore;
}


void F_aggiungi_nodo_grafo_lista(Grafo *G, int valoreDaInserire){
    ListaAdj L=(*G)->strutturaPtr;
    F_alloca_nodo_grafo_lista(&L,valoreDaInserire);

    (*G)->numeroNodi++;
    (*G)->strutturaPtr=L;
}


void F_alloca_nodo_grafo_lista(ListaAdj *L, int valoreDaInserire){
    if(F_struttura_vuota(*L)) {
        (*L)=(struct struttura_grafo_lista_adiacenza*)malloc(sizeof(struct struttura_grafo_lista_adiacenza));
        if(F_struttura_vuota(*L)) exit(2);
        (*L)->nodo=valoreDaInserire;
        (*L)->nextPtr=NULL;
        (*L)->arcoPtr=NULL;
        (*L)->visitaPtr=NULL;

    } else F_alloca_nodo_grafo_lista((&(*L)->nextPtr),valoreDaInserire);
}


void F_aggiungi_arco_grafo_lista(Grafo *G, int valoreNodoPartenza, int valoreNodoArrivo){
    ListaAdj L=(*G)->strutturaPtr;
    ListaAdj nodoPartenza=F_cerca_nodo_grafo_lista(&L,valoreNodoPartenza);

    if(!F_struttura_vuota(nodoPartenza)){

        ListaAdj nodoArrivo=F_cerca_nodo_grafo_lista(&L,valoreNodoArrivo);

        if(!F_struttura_vuota(nodoArrivo)){
            F_inserisci_arco_grafo_lista(&nodoPartenza->arcoPtr,nodoArrivo->nodo);

        }else printf("Nodo (%d) di arrivo non e' presente nel grafo.\n",valoreNodoPartenza);

    }else printf("Nodo (%d) di partenza non e' presente nel grafo.\n",valoreNodoArrivo);
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


ListaAdj F_cerca_nodo_grafo_lista(ListaAdj *L, int valoreNodoDaTrovare){
    if(F_struttura_vuota(*L)) return NULL;
    if((*L)->nodo==valoreNodoDaTrovare) return (*L);
    return F_cerca_nodo_grafo_lista((&(*L)->nextPtr),valoreNodoDaTrovare);
}


void F_alloca_struttura_gestione_grafo(Grafo *G){
    (*G)=(struct struttura_gestione_grafi*)malloc(sizeof(struct struttura_gestione_grafi));
    if(F_struttura_vuota(*G)) exit(-1);
    (*G)->strutturaPtr=NULL;
    (*G)->numeroNodi=0;
    (*G)->ciclico=0;
}

void F_dealloca_arco_grafo_lista(ListaAdj *L, int valoreDaEliminare){
    ListaAdj aux=(*L);
    if(*L){
        if((*L)->nodo==valoreDaEliminare){
            (*L)=(aux)->arcoPtr;
            free(aux);
        } else F_dealloca_arco_grafo_lista((&(*L)->arcoPtr),valoreDaEliminare);
    }
}

void F_stampa_grafo(ListaAdj *L){
    if(!F_struttura_vuota(*L)){
        printf("[%d]",(*L)->nodo);
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