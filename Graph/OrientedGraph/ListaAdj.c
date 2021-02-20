#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"
#include "ListaAdj.h"
#include "Coda.h"
#include "Error.h"


void F_visita_in_ampiezza_lista(Grafo *G){
    /*
     * Si gestisce con una coda
     * Colori 0: bianco vertice mai incontrato, 1: grigio vertice mai visista ma presente nelle coda, 2: nero vertice visitato e uscito dalla coda
     * Quindi il bianco va in coda, grigio sta in coda ed è pronto per la visita, nero già visitato
     *
     * */
    ListaAdj L=(*G)->strutturaPtr; ListaAdj nodoDaCuiPartire=NULL;
    F_stampa_grafo_lista(&L);
    int valoreNodoPartenza=F_chiedi_intero("Inserisci il valore del nodo da cui iniziare la visita:",2,'0','9');
    nodoDaCuiPartire=F_cerca_nodo_grafo_lista(&L,valoreNodoPartenza);

    if(nodoDaCuiPartire){
        F_inizializza_visita_ampiezza_lista(G,valoreNodoPartenza);
        printf("\nI nodi raggiungibili da nodo (%d) nella visita in ampiezza sono:\n",valoreNodoPartenza);

        /* Versione iterativa: F_esegui_visita_in_ampiezza_lista(G,nodoDaCuiPartire); */
        F_esegui_visita_in_ampiezza_lista_ricorsiva(G,nodoDaCuiPartire); /* Versione ricorsiva */

        printf("\nFine nodi.\n");
    }else printf("\n Il nodo da cui partire (%d) non e' presente.\n",valoreNodoPartenza);
}

void F_esegui_visita_in_ampiezza_lista_ricorsiva(Grafo *G, ListaAdj nodoDiPartenza){
    Coda C=NULL;
    F_enqueue(&C,nodoDiPartenza);
    F_visita_in_ampiezza_cerca_e_stampa_vertici_adiacenti_lista(G,&C);
    free(C);
    /* Eliminare le strutture dei colori */
}

void F_visita_in_ampiezza_cerca_e_stampa_vertici_adiacenti_lista(Grafo *G, Coda *C){
    if(!F_struttura_vuota(*C)){
        ListaAdj uVertice=F_restituisci_top_coda(C);
        ListaAdj vVerticeAdiacente=F_restituisci_vertice_adiacente_grafo_lista(G,uVertice,NULL);
        F_visita_in_ampiezza_stampa_vertici_adiacenti_lista(G,C,vVerticeAdiacente,uVertice);
        F_dequeue(C);
        F_cambia_colore_vertice_lista(G,uVertice,2);
        F_visita_in_ampiezza_cerca_e_stampa_vertici_adiacenti_lista(G,C);
    }
}

void F_visita_in_ampiezza_stampa_vertici_adiacenti_lista(Grafo *G,Coda *C,ListaAdj vVerticeAdiacente,ListaAdj uVertice){
    if(!F_struttura_vuota(vVerticeAdiacente)){
        int controlloColore=F_controllo_colore_vertice_lista(G,vVerticeAdiacente);

        if(controlloColore==0){ /* Colore bianco */
            F_cambia_colore_vertice_lista(G,vVerticeAdiacente,1); /* Cambio colore in grigio */
            printf("|%d|",vVerticeAdiacente->nodo);
            F_enqueue(C,vVerticeAdiacente); /* Lo inserisco nella coda */
        }
        vVerticeAdiacente=F_restituisci_vertice_adiacente_grafo_lista(G,uVertice,vVerticeAdiacente);
        F_visita_in_ampiezza_stampa_vertici_adiacenti_lista(G,C,vVerticeAdiacente,uVertice);
    }
}

void F_esegui_visita_in_ampiezza_lista(Grafo *G, ListaAdj nodoDiPartenza){
    Coda C=NULL;
    F_enqueue(&C,nodoDiPartenza);

    while(C){
        ListaAdj uVertice=F_restituisci_top_coda(&C);
        ListaAdj vVerticeAdiacente=F_restituisci_vertice_adiacente_grafo_lista(G,uVertice,NULL);

        while(vVerticeAdiacente){
            int controlloColore=F_controllo_colore_vertice_lista(G,vVerticeAdiacente);

            if(controlloColore==0){ /* Colore bianco */
                F_cambia_colore_vertice_lista(G,vVerticeAdiacente,1); /* Cambio colore in grigio */
                printf("|%d|",vVerticeAdiacente->nodo);
                F_enqueue(&C,vVerticeAdiacente); /* Lo inserisco nella coda */
            }
            vVerticeAdiacente=F_restituisci_vertice_adiacente_grafo_lista(G,uVertice,vVerticeAdiacente);
        }

        F_dequeue(&C);
        F_cambia_colore_vertice_lista(G,uVertice,2); /* Ho visitato tutti i vertici adj e quindi metto colore nero */
    }
}

int F_controllo_colore_vertice_lista(Grafo *G,ListaAdj vertice){
    ListaAdj L=(*G)->strutturaPtr;
    ListaAdj nodoDaTrovare=F_cerca_nodo_grafo_lista(&L,vertice->nodo);
    return ((nodoDaTrovare->visitaPtr)->colore);
}

void F_cambia_colore_vertice_lista(Grafo *G, ListaAdj vertice, int nuovoColore){
    ListaAdj L=(*G)->strutturaPtr;
    ListaAdj nodoDaTrovare=F_cerca_nodo_grafo_lista(&L,vertice->nodo);
    if(nodoDaTrovare) ((nodoDaTrovare->visitaPtr)->colore)=nuovoColore;
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

void F_inizializza_visita_ampiezza_lista(Grafo *G, int nodoSorgente){
    ListaAdj L=(*G)->strutturaPtr;

    while(L){
        Colore nuovoColore=F_alloca_struttura_colore();
        if(nodoSorgente==L->nodo) nuovoColore->colore=1; /* Metto grigio al nodo sorgente */
        else nuovoColore->colore=0;

        L->visitaPtr=nuovoColore;
        L=L->nextPtr;
    }
}

Colore  F_alloca_struttura_colore(){
    Colore nuovoColore=(struct struttra_extra_colore *)malloc(sizeof(struct struttra_extra_colore));
    if(F_struttura_vuota(nuovoColore)) F_error(4);
    nuovoColore->colore=0;
    return nuovoColore;
}


void F_visita_in_profondita_lista(Grafo *G){
    F_inizializza_visita_in_profondita_ampiezza_lista(G);
    printf("\nStampa della visita in profondita':\n");

    ListaAdj L=(*G)->strutturaPtr;
    (*G)->ciclico=0;
    while (L){
        if(L->visitaPtr->colore==0) F_esegui_visita_in_profondita_lista(G,L);
        L=L->nextPtr;
    }
}

void F_esegui_visita_in_profondita_lista(Grafo *G, ListaAdj u){
    F_cambia_colore_vertice_lista(G,u,1);
    printf("|%d|",u->nodo);
    puts("");

    ListaAdj vVerticeAdiacente=F_restituisci_vertice_adiacente_grafo_lista(G,u,NULL);

    while(vVerticeAdiacente)
    {
        int controlloColore=F_controllo_colore_vertice_lista(G,vVerticeAdiacente);
        if(controlloColore==1) (*G)->ciclico=1;

        if(controlloColore==0){
            F_esegui_visita_in_profondita_lista(G,vVerticeAdiacente);
        }
        vVerticeAdiacente=F_restituisci_vertice_adiacente_grafo_lista(G,u,vVerticeAdiacente);
    }

    F_cambia_colore_vertice_lista(G,u,2);

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

void F_stampa_grafo_lista(ListaAdj *L){
    if(!F_struttura_vuota(*L)){
        printf("|%d|",(*L)->nodo);
        F_stampa_grafo_lista_arco((&(*L)->arcoPtr));
        puts("");
        F_stampa_grafo_lista(&(*L)->nextPtr);
    }
}

void F_stampa_grafo_lista_arco(ListaAdj *A){
    if(!F_struttura_vuota(*A)){
        printf("->|%d|",(*A)->nodo);
        F_stampa_grafo_lista_arco(&(*A)->arcoPtr);
    }
}

void F_elimina_nodo_grafo_lista(Grafo *G){
    ListaAdj L=(*G)->strutturaPtr, nodoDaEliminare=NULL; int valoreNodoDaEliminare=0;

    valoreNodoDaEliminare=F_chiedi_intero("Inserisci il valore del nodo da eliminare:",2,'0','9');
    nodoDaEliminare=F_cerca_nodo_grafo_lista(&L,valoreNodoDaEliminare);

    if(nodoDaEliminare){
        if(nodoDaEliminare->arcoPtr) F_dealloca_archi_grafo_lista(&nodoDaEliminare->arcoPtr);
        F_dealloca_nodo_grafo_lista(&L,nodoDaEliminare->nodo);
        (*G)->numeroNodi--;
        (*G)->strutturaPtr=L;
    }else  printf("\n Il nodo da eliminare (%d) non e' presente.\n",valoreNodoDaEliminare);
}


void F_dealloca_archi_grafo_lista(ListaAdj *L) {
    if (!F_struttura_vuota(*L)) {
        F_dealloca_archi_grafo_lista((&(*L)->arcoPtr));
        free(*L);
        *L=NULL;
    }
}

void F_dealloca_nodo_grafo_lista(ListaAdj *L, int valoreDaEliminare){
    ListaAdj aux=(*L);
    if(*L){
        if((*L)->nodo==valoreDaEliminare){
            (*L)=(aux)->nextPtr;
            free(aux);
        } else F_dealloca_nodo_grafo_lista((&(*L)->nextPtr),valoreDaEliminare);
    }
}

void F_elimina_arco_grafo_lista(Grafo *G){
    ListaAdj L=(*G)->strutturaPtr, nodoPatenza=NULL, nodoArrivo=NULL;
    int elementoNodoPartenza=0, elementoNodoArrivo=0;

    elementoNodoPartenza=F_chiedi_intero("Inserisci il nodo di partenza da eliminare:",2,'0','9');
    nodoPatenza=F_cerca_nodo_grafo_lista(&L,elementoNodoPartenza);

    if(nodoPatenza){
        elementoNodoArrivo=F_chiedi_intero("Inserisci il nodo di arrivo da eliminare:",2,'0','9');
        nodoArrivo=F_cerca_nodo_grafo_lista(&L,elementoNodoArrivo);

        if(nodoArrivo)F_dealloca_arco_grafo_lista(&nodoPatenza->arcoPtr,nodoArrivo->nodo);
        else printf("\n Il nodo di arrivo (%d) non e' presente.\n",elementoNodoArrivo);

    }else printf("\n Il nodo di partenza (%d) non e' presente.\n",elementoNodoPartenza);
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

void F_aggiungi_nodo_grafo_lista(Grafo *G){
    ListaAdj L=(*G)->strutturaPtr; int valoreNodoDaAddiungere=0;
    valoreNodoDaAddiungere=F_chiedi_intero("Inserisci il valore del nodo:",2,'0','9');
    F_alloca_nodo_grafo_lista(&L,valoreNodoDaAddiungere);

    (*G)->numeroNodi++;
    (*G)->strutturaPtr=L;
}

void F_aggiungi_arco_grafo_lista(Grafo *G){
    ListaAdj L=(*G)->strutturaPtr, nodoPatenza=NULL, nodoArrivo=NULL;
    int elementoNodoPartenza=0, elementoNodoArrivo=0;

    elementoNodoPartenza=F_chiedi_intero("Inserisci il nodo di partenza:",2,'0','9');
    nodoPatenza=F_cerca_nodo_grafo_lista(&L,elementoNodoPartenza);

    if(nodoPatenza){
        elementoNodoArrivo=F_chiedi_intero("Inserisci il nodo di arrivo:",2,'0','9');
        nodoArrivo=F_cerca_nodo_grafo_lista(&L,elementoNodoArrivo);

        if(nodoArrivo){
           F_inserisci_arco_grafo_lista(&nodoPatenza->arcoPtr, nodoArrivo->nodo);
        }else printf("\n Il nodo di arrivo (%d) non e' presente.\n",elementoNodoArrivo);
    }else printf("\n Il nodo di partenza (%d) non e' presente.\n",elementoNodoPartenza);
}

void F_inserisci_arco_grafo_lista(ListaAdj *L, int nodo){
    if(F_struttura_vuota(*L)) F_alloca_nodo_grafo_lista(L,nodo);
    else{
        if((*L)->nodo==nodo) { printf("Nodo (%d) gia' presente\n",nodo); return;}
        else F_inserisci_arco_grafo_lista((&(*L)->arcoPtr),nodo);
    }
}

ListaAdj F_cerca_nodo_grafo_lista(ListaAdj *L, int nodoDaTrovare){
    if(F_struttura_vuota(*L)) return NULL;
    if(nodoDaTrovare==(*L)->nodo) return (*L);
    return F_cerca_nodo_grafo_lista((&(*L)->nextPtr),nodoDaTrovare);
}

void F_alloca_nodo_grafo_lista(ListaAdj *L, int valoreNodo){
    if(F_struttura_vuota(*L)){
        (*L)=(struct struttura_grafo_lista_adiacenza*)malloc(sizeof(struct struttura_grafo_lista_adiacenza));
        if(F_struttura_vuota(*L)) F_error(3);
        (*L)->nodo=valoreNodo;
        (*L)->visitaPtr=NULL;
        (*L)->nextPtr=NULL;
        (*L)->arcoPtr=NULL;
        (*L)->pesoPtr=NULL;
    } else F_alloca_nodo_grafo_lista((&(*L)->nextPtr),valoreNodo);
}
