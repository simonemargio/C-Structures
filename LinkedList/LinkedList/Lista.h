#ifndef LISTESEMPLICI_LISTA_H
#define LISTESEMPLICI_LISTA_H

struct struttura_elemento_lista{
    int valore;
    struct struttura_elemento_lista *nextPtr;
};

typedef struct struttura_elemento_lista *Lista;


void F_start_libreria_lista();
int F_stampa_menu_principale_lista();
Lista F_inserimento_in_coda(Lista L);
int F_chiedi_valore_intero();
void F_stampa_lista(Lista L);
void F_dealloca_lista(Lista L);
Lista F_instimento_in_testa(Lista L);
Lista F_alloca_nuovo_elemento_lista();
void F_inizializza_lista(Lista L);
int F_verifica_lista_vuota(Lista L);
int F_cerca_elemento_lista(Lista L,int valoreDaCercare);
Lista F_elimina_elemento(Lista L, int valoreDaEliminare);
Lista F_inserisci_elemento_interno_con_indice(Lista L, int indiceDoveInserireValore, int indiceCorrente);
Lista F_inserisci_interno_lista(Lista L, int indiceDoveInserireValore, int indiceCorrente, Lista precedente, Lista prossimo);

#endif //LISTESEMPLICI_LISTA_H
