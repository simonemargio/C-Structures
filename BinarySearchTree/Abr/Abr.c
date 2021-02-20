#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Abr.h"

void F_start_libreria_abr(){
    Albero T=NULL;
    int sceltaMenu=0, uscitaMenu=-1, valoreNodo=0;

    do{
        F_stampa_menu_principale_abr();
        sceltaMenu=F_chiedi_intero("Scegli:");
        switch (sceltaMenu){
            case 0:
                uscitaMenu=0;
                break;
            case 1: // Inserisci elemento
                valoreNodo=F_chiedi_intero("Valore nodo:");
                F_inserisci_elemento_abr(&T,valoreNodo);
                break;
            case 2: // Stampa
                if(!(F_abr_vuoto(T))){
                    F_stampa_menu_visita_abr();
                    sceltaMenu=F_chiedi_intero("Seleziona la visita:");
                    switch (sceltaMenu){
                        case 1: // Order
                            F_stampa_abr_order(T);
                            break;
                        case 2: // PreOrder
                            F_stampa_abr_preorder(T);
                            break;
                        case 3: // PostOrder
                            F_stampa_abr_postorder(T);
                            break;
                        default:
                            puts("Scelta non valida");
                            break;
                    }
                } else puts("\nAlbero vuoto");
                break;
            case 3: // Ricerca elemento
                if(!(F_abr_vuoto(T))){
                    valoreNodo=F_chiedi_intero("Valore nodo da cercare:");
                    if(F_cerca_elemento_abr(T,valoreNodo)) printf("\nElemento |%d| presente",valoreNodo);
                    else printf("\nElemento |%d| NON presente",valoreNodo);
                }else puts("\nAlbero vuoto");
                break;
            case 4: // Verifica Abr
                if(!(F_abr_vuoto(T))){
                    if(F_verifica_abr(T, INT_MIN, INT_MAX)) puts("\nAlbero Abr");
                    else puts("\nAlbero NON Abr");
                }else puts("\nAlbero vuoto");
                break;
            case 5: // Cerca il minimo
                if(!(F_abr_vuoto(T))){
                    valoreNodo=F_cerca_minimo_abr(T);
                    printf("\nValore minimo:|%d|",valoreNodo);
                }else puts("\nAlbero vuoto");
                break;
            case 6:
                if(!(F_abr_vuoto(T))){
                    valoreNodo=F_chiedi_intero("Valore nodo da elimianre:");
                    F_cancella_nodo_abr(&T,valoreNodo);
                }else puts("\nALbero vuoto");
                break;
            default:
                puts("Valore non corretto");
                break;
        }
     puts("\n");
    }while (uscitaMenu!=0);
}

void F_cancella_nodo_abr(Albero *T, int elementoDaCancellare){
    Albero *aux=T;
    if(!(F_abr_vuoto(*T))){
        if(elementoDaCancellare<(*T)->valore) F_cancella_nodo_abr(&(*T)->sxPtr,elementoDaCancellare);
        else if(elementoDaCancellare>(*T)->valore) F_cancella_nodo_abr(&(*T)->dxPtr,elementoDaCancellare);
        else{
            // Il nodo da eliminare e' una foglia
            if(F_abr_vuoto((*T)->sxPtr) && F_abr_vuoto((*T)->dxPtr)){ free(*T); T=NULL;}
            else{
                // Il nodo da eliminare ha solo un sottoalbero sinistro
                if(!F_abr_vuoto((*T)->sxPtr) && F_abr_vuoto((*T)->dxPtr)) (*T)=(*aux)->sxPtr;
                // Il nodo da eliminare ha solo un sottoalbero destro
                if(F_abr_vuoto((*T)->sxPtr) && !F_abr_vuoto((*T)->dxPtr)) (*T)=(*aux)->dxPtr;
                // Elimino il nodo se si e' verificato uno dei duei if precedenti
                if(F_abr_vuoto((*aux)->sxPtr) || F_abr_vuoto((*aux)->dxPtr)){ free(*aux); return;}
                // Il nodo da eliminare ha due sottoalberi destro e sinistro
                if(!F_abr_vuoto((*T)->sxPtr) && !F_abr_vuoto((*T)->dxPtr)){
                    (*T)->valore=F_cerca_minimo_abr((*T)->dxPtr);
                    F_cancella_nodo_abr(&(*T)->dxPtr,(*T)->valore);
                }
            }
        }
    }
}

int F_abr_vuoto(Albero T){
    return (!T);
}

int F_cerca_minimo_abr(Albero T){
    if(!(F_abr_vuoto(T))){
        if(!T->sxPtr) return T->valore;
        return F_cerca_minimo_abr(T->sxPtr);
    }
    return -1;
}

int F_verifica_abr(Albero T, int min, int max){
    if(F_abr_vuoto(T)) return 1;
    if(  (T->valore > min) && (T->valore < max) && F_verifica_abr(T->sxPtr, min, T->valore) && F_verifica_abr(T->dxPtr, T->valore, max))
        return 1;
    else
        return 0;
}

int F_cerca_elemento_abr(Albero T, int valoreDaCercare){
    if(F_abr_vuoto(T)) return 0;
    else{
        if(T->valore==valoreDaCercare) return 1;
        if(valoreDaCercare<T->valore) return F_cerca_elemento_abr(T->sxPtr,valoreDaCercare);
        else return F_cerca_elemento_abr(T->dxPtr,valoreDaCercare);
    }
}

void F_inserisci_elemento_abr(Albero *T, int valore){
    if((F_abr_vuoto(*T))) *T=F_alloca_nuovo_elemento_albero(*T, valore);
    else{
        if(valore<(*T)->valore) F_inserisci_elemento_abr((&(*T)->sxPtr),valore);
        else F_inserisci_elemento_abr((&(*T)->dxPtr),valore);
    }
}

Albero F_alloca_nuovo_elemento_albero(Albero T, int valore){
    Albero nuovoElemento=(struct struttura_elemento_albero*)malloc(sizeof(struct struttura_elemento_albero));
    if(!nuovoElemento){puts("Allocazione nodo fallita!"); exit(-1);}
    nuovoElemento->valore=valore;
    nuovoElemento->dxPtr=NULL;
    nuovoElemento->sxPtr=NULL;

    return nuovoElemento;
}

void F_stampa_abr_order(Albero T){
    if(!(F_abr_vuoto(T))){
        F_stampa_abr_order(T->sxPtr);
        printf("|%d|",T->valore);
        F_stampa_abr_order(T->dxPtr);
    }
}

void F_stampa_abr_preorder(Albero T){
    if(!(F_abr_vuoto(T))){
        printf("|%d|",T->valore);
        F_stampa_abr_order(T->sxPtr);
        F_stampa_abr_order(T->dxPtr);
    }
}

void F_stampa_abr_postorder(Albero T){
    if(!(F_abr_vuoto(T))){
        F_stampa_abr_order(T->sxPtr);
        F_stampa_abr_order(T->dxPtr);
        printf("|%d|",T->valore);
    }
}

void F_stampa_menu_visita_abr(){
    puts("1] Visita in Order");
    puts("2] Visita in PreOrder");
    puts("3] Visita in PostOrder");
}

void F_stampa_menu_principale_abr(){
    puts("1] Aggiungi elemento");
    puts("2] Stampa");
    puts("3] Cerca elemento");
    puts("4] Verifica Abr");
    puts("5] Cerca minimo");
    puts("6] Cancella nodo");
}

int F_chiedi_intero(char *s){
    int intero=0;
    printf("%s",s);
    scanf("%d",&intero);
    return intero;
}