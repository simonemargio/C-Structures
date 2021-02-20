#ifndef GRAFI_CODA_H
#define GRAFI_CODA_H

struct struttura_elemento_coda{
    void *elemento;
    struct struttura_elemento_coda *nextPtr;
};

typedef struct struttura_elemento_coda *Coda;


void F_alloca_elemento_coda(Coda *C);
void F_enqueue(Coda *C, void *elementoDaInserire);
void F_dequeue(Coda *C);
void *F_restituisci_top_coda(Coda *C);


#endif //GRAFI_CODA_H
