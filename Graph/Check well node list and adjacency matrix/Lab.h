#ifndef INC_1_LAB_H
#define INC_1_LAB_H

#include "ListAdj.h"
#include "MatrAdj.h"

void F_Start();
int F_struttura_vuota(void *S);
void F_genera_grafo_lista_adj(GrafoLista GL);
void F_genera_grafo_matrice_adj(GrafoMatrice GM);
void F_engine(GrafoLista GL, GrafoMatrice GM);
void F_stampa_menu();
int F_chiedi_intero(char *s,int dim,char minimo,char massimo);
void F_aggiungi_arco_lista(GrafoLista G);
void F_aggiungi_nodo_lista(GrafoLista GL);
void F_aggiungi_nodo_matrice(GrafoMatrice GM);
void F_aggiungi_arco_matrice(GrafoMatrice GM);
void F_verifica_presenza_nodo_pozzo_lista(GrafoLista GL);
void F_cerca_nodo_pozzo_lista(GrafoLista GL,ListaAdj *L, ListaAdj *possibileNodoPozzo);
void F_inizalizza_array(int *array, int numeroNodi);
void F_calcolo_grado_entrante_lista(ListaAdj *L, ListaAdj *ListaScorrimento, int *arrayNodiLista, int numeroNodi);
void F_calcolo_numero_archi_lista(ListaAdj *L, ListaAdj *ArcoLista, int *arrayNodiLista, int numeroNodi);
int F_ritorna_indice_posizione_nodo_lista(ListaAdj *ListaScorrimento, int valoreDatrovare, int indiceNodoTrovato);
int F_verifica_nodo_pozzo(ListaAdj *L, int valoreNodoDaTrovare, int *array, int numeroNodi);
int F_conferma_nodo_pozzo(GrafoLista GL, ListaAdj *possibileNodoPozzo);
void F_verifica_presenza_nodo_pozzo_matrice(GrafoMatrice GM);
int F_calcolo_grado_uscente_matrice(int **matrice, int numeroNodi);
int F_calcola_grado_uscente_riga_matrice(int **matrice, int riga, int numeroNodi);
int F_conferma_nodo_pozzo_matrice(int **matrice,int numeroNodi, int rigaPresuntoNodoPozzo);

#endif //INC_1_LAB_H
