#ifndef LISTEDOPPIAMENTEPUNTATE_LISTADOPP_H
#define LISTEDOPPIAMENTEPUNTATE_LISTADOPP_H

struct struttura_elemento_lista{
    int elemento;
    struct struttura_elemento_lista *nextPtr;
    struct struttura_elemento_lista *predPtr;
};

typedef struct struttura_elemento_lista *Lista;

void F_start_libreria_lista_doppiamente_puntata();
int F_stampa_menu_liste_doppiamente_puntate();
Lista F_inserimento_in_testa(Lista L);
Lista F_alloca_nuovo_elemento_lista();
int F_chiedi_intero();
void F_stampa_lista(Lista L);
Lista F_inserimento_in_coda(Lista L);
void F_dealloca_lista(Lista L);
Lista F_elimina_elemento_lista(Lista L, int elemento);
int F_ricerca_elemento_lista(Lista L, int elemento);
void F_inizializza_lista(Lista L);
void F_inserisci_interno_lista(Lista L, int indiceArrivo, int indicePartenza);

#endif //LISTEDOPPIAMENTEPUNTATE_LISTADOPP_H
