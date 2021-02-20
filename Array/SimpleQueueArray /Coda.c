#include <stdio.h>
#include "Coda.h"

#define NUMERO_ELEMENTI_ARRAY 8
void F_start_coda_array(){
    int Q[NUMERO_ELEMENTI_ARRAY+2],uscitaMenu=-1,sceltaMenu=0,elementoInOut=0;
    F_inizializza_coda(Q);

    do{
        sceltaMenu=F_stampa_menu_coda();
        switch(sceltaMenu){
            case 0:
                uscitaMenu=0;
                break;
            case 1:
                if(!F_full_queue(Q)){
                    elementoInOut=F_richiedi_elemento();
                    F_enqueue(Q,elementoInOut);
                }else puts("\nCoda piena!\n");
                break;
            case 2:
                if(!F_empty_queue(Q)){
                    elementoInOut=F_dequeue(Q);
                    printf("\nElemento estratto:|%d|\n",elementoInOut);
                }else puts("\nCoda vuota!\n");
                break;
            case 3:
                F_stampa_coda(Q);
                F_rewerse(Q);
                puts("\n");
                break;
            default:
                puts("\nScelta non valida!");
                break;
        }
    }while(uscitaMenu!=0);

}

void F_inizializza_coda(int *Q){
    int i=0;
    for(i=1;i<NUMERO_ELEMENTI_ARRAY+1;i++) Q[i]=-1;
    Q[0]=0; // Indica che la coda e' vuota
    Q[NUMERO_ELEMENTI_ARRAY+1]=1; // Indica che il primo elemento viene messo in posizione 1
}

int F_richiedi_elemento(){
    int elemento=0;
    printf("\nInserisci il valore:");
    scanf("%d",&elemento);
    return elemento;
}

int F_empty_queue(int *Q){
    return Q[0]==0;
}

int F_full_queue(int *Q){
    return Q[0]==Q[NUMERO_ELEMENTI_ARRAY+1];
}

void F_enqueue(int *Q,int elemento){
    Q[Q[NUMERO_ELEMENTI_ARRAY+1]]=elemento;
    if(Q[0]==0) Q[0]=1;
    Q[NUMERO_ELEMENTI_ARRAY+1]=(Q[NUMERO_ELEMENTI_ARRAY+1]%NUMERO_ELEMENTI_ARRAY)+1;
}

int F_dequeue(int *Q){
    int elemento=Q[Q[0]];
    Q[Q[0]]=-1;
    Q[0]=(Q[0]%NUMERO_ELEMENTI_ARRAY)+1;
    if(Q[0]==Q[NUMERO_ELEMENTI_ARRAY+1]){
        Q[0]=0; Q[NUMERO_ELEMENTI_ARRAY+1]=1;
    }
    return elemento;
}

void F_stampa_coda(int *Q){
    int elemento=0;
    if(!F_empty_queue(Q)){
        elemento=F_dequeue(Q);
        printf("|%d| ",elemento);
        F_stampa_coda(Q);
        F_enqueue(Q,elemento);
    }
}

void F_rewerse(int *Q){
    int elemento=0;
    if(!F_empty_queue(Q)){
        elemento=F_dequeue(Q);
        F_rewerse(Q);
        F_enqueue(Q,elemento);
    }
}

int F_stampa_menu_coda(){
    int scelta=0;
    puts("1] Aggiungi elemento coda (Queue)");
    puts("2] Estrai elemento coda (Dequeue)");
    puts("3] Stampa coda");
    puts("");
    puts("0] Esci");
    printf("Inserisci scelta:");
    scanf("%d",&scelta);
    return scelta;
}