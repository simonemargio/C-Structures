#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"


void F_start_libreria_lista(){
    int scelta=0,uscitaMenu=-1,listaVuota=0,valoreDaCercare=0, indiceInserimentoValore=0;
    Lista L=NULL;
    Lista prossimo=NULL, precedente=NULL;

    do{
        scelta=F_stampa_menu_principale_lista();
        switch (scelta){
            case 0:
                uscitaMenu=0;
                break;
            case 1: // Iniziallizza lista
                F_inizializza_lista(L);
                break;
            case 2: // Inserimento in testa
                L=F_instimento_in_testa(L);
                break;
            case 3: // Inserimento in coda
                L=F_inserimento_in_coda(L);
                break;
            case 4: // Inserimento all'interno
                if(!F_verifica_lista_vuota(L)){
                    F_stampa_lista(L);
                    printf("\nInserisci il valore dell'indice (0,2,3...n) dove inserire il valore:");
                    indiceInserimentoValore=F_chiedi_valore_intero();
                    L=F_inserisci_elemento_interno_con_indice(L,indiceInserimentoValore,0);
                }else puts("\nLista vuota. Eseguire almeno un inserimento in testa o in coda.");
                break;
            case 5: // Check lista vuota
                listaVuota=F_verifica_lista_vuota(L);
                if(listaVuota) puts("Lista vuota");
                else puts("La lista contiene almeno un elemento");
                break;
            case 6: // Cerca elemento
                valoreDaCercare=F_chiedi_valore_intero();
                valoreDaCercare=F_cerca_elemento_lista(L,valoreDaCercare);
                 printf("\n!!%d!!\n",valoreDaCercare);
                 if(!valoreDaCercare) puts("Valore non presente");
                 else puts("Valore presente");
                break;
            case 7: // Stampa
                F_stampa_lista(L);
                break;
            case 8: // Elimina elemento lista
                if(!F_verifica_lista_vuota(L)){
                    valoreDaCercare=F_chiedi_valore_intero();
                    L=F_elimina_elemento(L,valoreDaCercare);
                } puts("\nLista vuota");
                break;
            default:
                puts("\nScelta non valida!");
                break;
        }
        puts("\n");
    }while (uscitaMenu!=0);
    F_dealloca_lista(L);
}

Lista F_elimina_elemento(Lista L, int valoreDaEliminare){
    if(L){
        if(L->valore==valoreDaEliminare){
            Lista salvaNextPtr=L->nextPtr;
            free(L);
            return salvaNextPtr;
        } else L->nextPtr=F_elimina_elemento(L->nextPtr,valoreDaEliminare);
    }
    return L;
}


Lista F_inserisci_elemento_interno_con_indice(Lista L, int indiceDoveInserireValore, int indiceCorrente){
    if(indiceCorrente==indiceDoveInserireValore){
        Lista nuovoElemento=F_alloca_nuovo_elemento_lista();
        nuovoElemento->nextPtr=L;
        return nuovoElemento;
    } else L->nextPtr=F_inserisci_elemento_interno_con_indice(L->nextPtr,indiceDoveInserireValore,indiceCorrente+1);
    return L;
}

int F_cerca_elemento_lista(Lista L,int valoreDaCercare){
  if(L==NULL) return 0;
  if(L->valore==valoreDaCercare) return 1;
  return F_cerca_elemento_lista(L->nextPtr,valoreDaCercare);
}

int F_verifica_lista_vuota(Lista L){
    return (L==NULL);
}

void F_inizializza_lista(Lista L){
    if(!L) puts("\nLista inizializzata");
    else{
        L->valore=0;
        F_inizializza_lista(L->nextPtr);
    }
}

Lista F_instimento_in_testa(Lista L){
    Lista nuovoElementoLista=F_alloca_nuovo_elemento_lista();
    if(L) nuovoElementoLista->nextPtr=L;
    return nuovoElementoLista;
}


Lista F_inserimento_in_coda(Lista L){
    if(!L){
        Lista nuovoElementoLista=F_alloca_nuovo_elemento_lista();
        return nuovoElementoLista;
    } else{
        L->nextPtr=F_inserimento_in_coda(L->nextPtr);
        return L;
    }
}

Lista F_alloca_nuovo_elemento_lista(){
    Lista nuovoElementoLista=(struct struttura_elemento_lista *)malloc(sizeof(struct struttura_elemento_lista));
    int valoreDaInserire=F_chiedi_valore_intero();
    nuovoElementoLista->valore=valoreDaInserire;
    nuovoElementoLista->nextPtr=NULL;
    return nuovoElementoLista;
}

void F_stampa_lista(Lista L){
    if(L){
        printf("|%d|",L->valore);
        F_stampa_lista(L->nextPtr);
    }
}

void F_dealloca_lista(Lista L){
    if(L){
        L->valore=0;
        F_dealloca_lista(L->nextPtr);
        free(L);
    }
}

int F_chiedi_valore_intero(){
    int scelta=0;
    printf("\nInserisci il valore:");
    scanf("%d",&scelta);
    return scelta;
}

int F_stampa_menu_principale_lista(){
    int scelta=0;
    puts("1] Inizializza lista");
    puts("2] Inserimento in testa");
    puts("3] Inserimento in coda");
    puts("4] Inserimento all'interno");
    puts("5] Verifica lista vuota");
    puts("6] Cerca elemento");
    puts("7] Stampa lista");
    puts("8] Cancella elemento lista");
    puts("\n0] Esci");
    printf("\nSeleziona:");
    scanf("%d",&scelta);
    return scelta;
}