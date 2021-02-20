#include <stdlib.h>
#include "Grafo.h"
#include "Error.h"
#include "Coda.h"



void F_alloca_elemento_coda(Coda *C){
    (*C)=(struct struttura_elemento_coda*)malloc(sizeof(struct struttura_elemento_coda));
    if(F_struttura_vuota(*C)) F_error(9);
    (*C)->elemento=NULL;
    (*C)->nextPtr=NULL;
}


void F_enqueue(Coda *C, void *elementoDaInserire){
    if(F_struttura_vuota(*C)) {
        F_alloca_elemento_coda(C);
        (*C)->elemento=elementoDaInserire;
    }else{
        F_enqueue((&(*C)->nextPtr),elementoDaInserire);
    }
}

void *F_restituisci_top_coda(Coda *C){
    if(!F_struttura_vuota(*C)) return (*C)->elemento;
    else return NULL;
}

void F_dequeue(Coda *C){
    if(!F_struttura_vuota(*C)){
        Coda elementoDaEliminare = *C;
        *C = elementoDaEliminare->nextPtr;
        free(elementoDaEliminare);
    }
}

