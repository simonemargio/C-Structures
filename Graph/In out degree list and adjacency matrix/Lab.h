#ifndef INC_1_LAB_H
#define INC_1_LAB_H

#include "ListAdj.h"
#include "MatrAdj.h"

void F_Start();
void F_engine(GrafoLista GL, GrafoMatrice GM);
int F_struttura_vuota(void *S);
void F_genera_grafo_lista_adj(GrafoLista G);
void F_genera_grafo_matrice_adj(GrafoMatrice M);
void F_stampa_menu();
int F_chiedi_intero(char *s,int dim,char minimo,char massimo);
void F_aggiungi_nodo_lista(GrafoLista GL);
void F_aggiungi_arco_lista(GrafoLista G);
void F_aggiungi_nodo_matrice(GrafoMatrice GM);
void F_aggiungi_arco_matrice(GrafoMatrice GM);
void F_calcolo_grado_entrante_uescente_lista_matrice(GrafoLista GL, GrafoMatrice GM);
int F_calcolo_grado_uscente_lista(ListaAdj *L,int gradoUscente);
int F_calcola_grado_uscente_arco_lista(ListaAdj *L,int numeroArchiUscenti);
void F_calcolo_grado_entrante_lista(ListaAdj *L, ListaAdj *ListaScorrimento, int *arrayNodiLista, int numeroNodi);
void F_inizalizza_array(int *array, int numeroNodi);
int F_trova_grado_entrante_lista(int *array, int numeroNodi);
void F_calcolo_numero_archi_lista(ListaAdj *L,ListaAdj *ArcoLista, int *arrayNodiLista, int numeroNodi);
int F_ritorna_indice_posizione_nodo_lista(ListaAdj *ListaScorrimento, int valoreDatrovare, int indiceNodoTrovato);

int F_calcolo_grado_uscente_matrice(int **matrice, int numeroNodi);
int F_calcola_grado_uscente_riga_matrice(int **matrice, int riga, int numeroNodi);
int F_calcolo_grado_entrante_matrice(int **matrice, int numeroNodi);
int F_calcola_grado_entrante_riga_matrice(int **matrice, int colonna, int numeroNodi);

#endif //INC_1_LAB_H
