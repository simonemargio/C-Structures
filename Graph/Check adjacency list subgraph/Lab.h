#ifndef INC_1_LAB_H
#define INC_1_LAB_H

#include "ListAdj.h"

void F_Start();
int F_struttura_vuota(void *S);
void F_genera_grafo_G_lista_adj(Grafo G);
void F_genera_grafo_H_lista_adj(Grafo H);
int F_chiedi_intero(char *s,int dim,char minimo,char massimo);
void F_dealloca_grafo(Grafo G);
void F_engine(Grafo G, Grafo H);
void F_stampa_menu();
void F_aggiungi_nodo(Grafo G);
void F_aggiungi_arco(Grafo G);
int F_verifica_sottografo(Grafo G, Grafo H);
int F_verifica_nodi_sottografo_H_sottoinsieme_grafo_G(ListaAdj G, ListaAdj H);
int F_verifica_archi_multipli(ListaAdj G, ListaAdj H);

#endif //INC_1_LAB_H
