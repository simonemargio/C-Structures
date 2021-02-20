#ifndef ARRAY_CODAPRIORITA_H
#define ARRAY_CODAPRIORITA_H

/* Struttura generale per la gestione dello heap */
struct Struttura_gestione_heap{
    void *struttura;
    int heapsize;
};

/* Struttura dell'elemento dell'array */
struct Struttura_array{
    struct Struttura_elemento_array *coda;
};

/* Struttura delle informazioni contenute in una cella dell'array */
struct Struttura_elemento_array{
    int elemento;
    int priorita;
};

/* Alias */
typedef struct Struttura_gestione_heap *StructHeap;
typedef struct Struttura_array *Array;
typedef struct Struttura_elemento_array *ElemArray;

/* Funzioni */
void F_start(); // Funzione di partenza
int F_stampa_menu_principale();
int F_seleziona(int dim,char minimo,char massimo,int escludi);
StructHeap F_crea_struttura_generale(); // Allocazione e iniziallizzazione di Struttura_gestione_heap
void F_aggiungi_informazioni_struttura_generale(StructHeap G, Array Arr);
Array F_crea_vettore(); // Allocazione e inizializzazione di Struttura_array
ElemArray F_alloca_elemento_array(); // Allocazione e randomizzazione di priorita' e elemento di Struttura_elemento_array
int F_genera_numero_casuale();
void F_stampa_array(StructHeap G);
int F_richiedi_elemento();


#endif //ARRAY_CODAPRIORITA_H
