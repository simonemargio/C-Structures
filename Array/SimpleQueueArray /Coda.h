#ifndef CODAARRAY_CODA_H
#define CODAARRAY_CODA_H

void F_start_coda_array();
void F_inizializza_coda(int *Q);
int F_stampa_menu_coda();
void F_enqueue(int *Q,int elemento);
int F_richiedi_elemento();
int F_empty_queue(int *Q);
int F_full_queue(int *Q);
int F_dequeue(int *Q);
void F_stampa_coda(int *Q);
void F_rewerse(int *Q);

#endif //CODAARRAY_CODA_H
