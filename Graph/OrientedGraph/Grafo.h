#ifndef GRAFI_GRAFO_H
#define GRAFI_GRAFO_H

struct struttura_gestione_grafi{
    void *strutturaPtr;  /* Può essere: struttura_grafo_lista_adiacenza oppure struttura_elemento_matrice */
    int numeroNodi;      /* Numero dei nodi del grafo */
    int pesatoNonPesato; /* Discriminante per stabilire se il grafo è pesato o meno (0=Non pesato, 1=Pesato) */
    int listaMatriceAdj; /* Discriminanete per stabilire se il grafo è lista o matrice adj (0=Matrice, 1=Lista) */
    int ciclico;
};

struct struttura_grafo_pesato
{
    float peso;
};

/* Informazione sul colore */
struct struttra_extra_colore
{
    int colore; // 0: bianco 1: grigio 2: nero
};

typedef struct struttura_gestione_grafi *Grafo;
typedef struct struttura_grafo_pesato *Peso;
typedef struct struttra_extra_colore *Colore;

void F_start_libreria_grafi();
void F_alloca_struttura_gestione_grafo(Grafo *G);
void F_engine_grafo_orientato(Grafo G);
void F_dealloca_grafo_orientato(Grafo G);
void F_stampa_menu_principale_grafo();
int F_chiedi_intero(char *s,int dim,char minimo,char massimo);
void F_stampa_menu_scelta_tipo_di_grafo_pesato();


int F_struttura_vuota(void *S);
void F_scelta_tipo_di_grafo(Grafo *G);
void F_stampa_menu_scelta_tipo_di_grafo();
void F_scelta_grafo_pesato(Grafo *G);




#endif //GRAFI_GRAFO_H
