#include <stdio.h>
#include <stdlib.h>
#include "ListaDopp.h"


void F_start_libreria_lista_doppiamente_puntata(){
    int menuPrincipale=-1, sceltaMenu=0, elementoListaScelto=0, indiceInserireElemento=0;
    Lista L=NULL;

    do{
        sceltaMenu=F_stampa_menu_liste_doppiamente_puntate();
        switch (sceltaMenu){
            case 0:
                menuPrincipale=0;
                break;
            case 1: // Inserimento in testa
                L=F_inserimento_in_testa(L);
                break;
            case 2: // Inserimento in coda
                L=F_inserimento_in_coda(L);
                break;
            case 3: // Stampa lista
                if(L) F_stampa_lista(L);
                else puts("\nLista vuota");
                break;
            case 4: // Elimina elemento
               if(L){
                   elementoListaScelto=F_chiedi_intero();
                   L=F_elimina_elemento_lista(L, elementoListaScelto);
                } else puts("\nLista vuota");
                break;
            case 5: // Ricerca elemento
                if(L){
                    elementoListaScelto=F_chiedi_intero();
                    if(F_ricerca_elemento_lista(L,elementoListaScelto)) puts("\nElemento presente");
                    else puts("\nElemento NON presente");
                } else puts("\nLista vuota");
                break;
            case 6: // Inserisci all'interno
                if(L){
                    printf("Inserisci l'indice dove inserire l'elemento");
                    indiceInserireElemento=F_chiedi_intero();
                    F_inserisci_interno_lista(L,indiceInserireElemento,0);
                } else puts("\nLista vuota");
                break;
            case 7: // Dealloca lista
                F_dealloca_lista(L);
                L=NULL;
                break;
            case 8: // Inizializza lista
                F_inizializza_lista(L);
                break;
            default:
                puts("\nScelta non valida!");
                break;

        }
        puts("\n");
    }while(menuPrincipale!=0);
    F_dealloca_lista(L);
}

void F_inizializza_lista(Lista L){
    if(L){
        L->elemento=0;
        F_inizializza_lista(L->nextPtr);
    }
}

void F_inserisci_interno_lista(Lista L, int indiceArrivo, int indicePartenza){
    if(L){
        if(indiceArrivo==indicePartenza){
            Lista nuovoElemento=F_alloca_nuovo_elemento_lista();
            if(L->nextPtr!=NULL){
                nuovoElemento->nextPtr=L->nextPtr;
                L->nextPtr->predPtr=nuovoElemento;
            }
            L->nextPtr=nuovoElemento;
            nuovoElemento->predPtr=L;

        }else F_inserisci_interno_lista(L->nextPtr,indiceArrivo,indicePartenza+1);
    }
}

int F_ricerca_elemento_lista(Lista L, int elemento){
    if(L){
        if(elemento==L->elemento) return 1;
        return F_ricerca_elemento_lista(L->nextPtr,elemento);
    }
    return 0;
}

Lista F_elimina_elemento_lista(Lista L, int elemento){
    if(L){
        if(elemento==L->elemento){
            Lista salvaNext=L->nextPtr;
            L->predPtr=L->nextPtr;
            L->nextPtr=L->predPtr;
            free(L);
            return salvaNext;
        }else L->nextPtr=F_elimina_elemento_lista(L->nextPtr,elemento);
    }
    return L;
}

Lista F_inserimento_in_testa(Lista L){
    Lista nuovoElemento=F_alloca_nuovo_elemento_lista();
    if(L){
        L->predPtr=nuovoElemento;
        nuovoElemento->nextPtr=L;
    }
    return nuovoElemento;
}

Lista F_inserimento_in_coda(Lista L){
    if(!L){
        Lista nuovoElemento=F_alloca_nuovo_elemento_lista();
        return nuovoElemento;
    }else {
         L->nextPtr=F_inserimento_in_coda(L->nextPtr);
         L->nextPtr->predPtr=L;
        return L;
    }
}

Lista F_alloca_nuovo_elemento_lista(){
    Lista nuovoElemento=(struct struttura_elemento_lista*)malloc(sizeof(struct struttura_elemento_lista));
    nuovoElemento->elemento=F_chiedi_intero();
    nuovoElemento->nextPtr=NULL;
    nuovoElemento->predPtr=NULL;
    return nuovoElemento;
}

void F_dealloca_lista(Lista L){
   if(L){
       F_dealloca_lista(L->nextPtr);
       L->predPtr=NULL;
       L->nextPtr=NULL;
       free(L);
   }
}

void F_stampa_lista(Lista L){
    if(L){
        printf("|%d|",L->elemento);
        F_stampa_lista(L->nextPtr);
    }
}

int F_chiedi_intero(){
    int valore=0;
    printf("\nValore da inserire:");
    scanf("%d",&valore);
    return valore;
}

int F_stampa_menu_liste_doppiamente_puntate(){
    int scelta=0;
    puts("1] Inserimento in testa");
    puts("2] Inserimento in coda");
    puts("3] Stampa lista");
    puts("4] Elimina elemento");
    puts("5] Cerca elemento");
    puts("6] Inserisci all'interno");
    puts("7] Dealloca lista");
    puts("8] Inizializza lista");
    printf("\nScegli:");
    scanf("%d",&scelta);
    return scelta;
}