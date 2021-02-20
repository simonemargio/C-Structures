#ifndef ARRAY_HEAPIFY_H
#define ARRAY_HEAPIFY_H
#include "CodaPriorita.h"


void F_build_heap(StructHeap G);
void F_heapify(StructHeap G, int i);
int F_figlio_sinistro(int i);
int F_figlio_destro(int i);
int F_confronto_sx_padre(StructHeap G, int sx, int i);
int F_confronto_dx_max(StructHeap G, int dx, int max);
void F_effettua_scambio_max_i(StructHeap G, int i, int max);
void F_heap_sort(StructHeap G);
int F_ricerca_elemento_array(StructHeap G);
int F_cerca_elemento(StructHeap G,int elementoDaCercare);

#endif //ARRAY_HEAPIFY_H
