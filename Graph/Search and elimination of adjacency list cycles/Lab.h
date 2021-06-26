#ifndef INC_1_LAB_H
#define INC_1_LAB_H

#include "ListAdj.h"

void F_Start();
int F_struttura_vuota(void *S);
void F_genera_grafo_lista_adj(Grafo G);
void F_engine(Grafo G);
void F_stampa_menu();
int F_chiedi_intero(char *s,int dim,char minimo,char massimo);
void F_aggiungi_nodo(Grafo G);
void F_aggiungi_arco(Grafo G);
void F_dealloca_grafo(Grafo G);
void F_stampa_intestazione();

#endif //INC_1_LAB_H
