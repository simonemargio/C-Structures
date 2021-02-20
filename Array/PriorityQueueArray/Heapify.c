#include "Heapify.h"
#include <stdlib.h>
#include <stdio.h>

/* Costruzione di un heap */
void F_build_heap(StructHeap G){
    int n = (G->heapsize / 2 );
    while(n>=0){
        F_heapify(G,n);
        n--;
    }
}

/* Algoritmo per applicare le proprieta' dello heap */
void F_heapify(StructHeap G,int i){
    int sx=F_figlio_sinistro(i);
    int dx=F_figlio_destro(i);
    int max=F_confronto_sx_padre(G,sx,i);
    max=F_confronto_dx_max(G,dx, max);
    if(max!=i){
        F_effettua_scambio_max_i(G,i,max);
        F_heapify(G,max);
    }
}

/* Ritorna l'indice del figlio sinitro */
int F_figlio_sinistro(int i){
    return (2*i)+1;
}

/* Ritnorna l'indice del figlio destro */
int F_figlio_destro(int i){
    return (2*i)+2;
}

/* Primo confrontd tra chi ha priorita' maggiore tra figlio sx e padre */
int F_confronto_sx_padre(StructHeap G, int sx, int i){
    Array A=G->struttura;
    int res=i;
    if(sx<G->heapsize){
        if(A[sx].coda->priorita>A[i].coda->priorita) res=sx;
        else res=i;
    }
    return res;
}

/* Primo confrontd tra chi ha priorita' maggiore tra figlio dx e il presunto valore massimo */
int F_confronto_dx_max(StructHeap G, int dx, int max){
    Array A=G->struttura;

    if(dx<G->heapsize){
        if(A[dx].coda->priorita>A[max].coda->priorita) max=dx;
    }
    return max;
}

/* Effettua lo scambio se richiesto tra uno dei due figli e il padre */
void F_effettua_scambio_max_i(StructHeap G, int i, int max){
    Array A=G->struttura;
    int elementoTemp=0, prioritaTemp=0;

    elementoTemp=A[i].coda->elemento;
    prioritaTemp=A[i].coda->priorita;

    A[i].coda->priorita=A[max].coda->priorita;
    A[i].coda->elemento=A[max].coda->elemento;

    A[max].coda->priorita=prioritaTemp;
    A[max].coda->elemento=elementoTemp;
}

/* Algoritmo di ordinamento crescente della priorita' di uno heap */
void F_heap_sort(StructHeap G){
    int i=0, salva_dimensione_heap=G->heapsize;
    F_build_heap(G);

    for(i=G->heapsize-1;i>=1;i--){
        F_effettua_scambio_max_i(G,0,i);
        G->heapsize=G->heapsize-1;
        F_heapify(G,0);
    }
    G->heapsize=salva_dimensione_heap;
}

int F_ricerca_elemento_array(StructHeap G){
    F_stampa_array(G);
    int numeroScelto=F_richiedi_elemento();
    numeroScelto=F_cerca_elemento(G,numeroScelto);
    return numeroScelto;
}

int F_cerca_elemento(StructHeap G,int elementoDaCercare){
    Array A=G->struttura;
    for(int i=0;i<10;i++){
            if(elementoDaCercare==A[i].coda->elemento) return i;
        }
    return -1;
}

