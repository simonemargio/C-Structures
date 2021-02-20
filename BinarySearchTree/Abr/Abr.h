#ifndef ABR_ABR_H
#define ABR_ABR_H

struct struttura_elemento_albero{
    int valore;
    struct struttura_elemento_albero *sxPtr;
    struct struttura_elemento_albero *dxPtr;
};

typedef struct struttura_elemento_albero *Albero;

void F_start_libreria_abr();
void F_stampa_menu_principale_abr();
int F_chiedi_intero(char *s);
void F_stampa_menu_visita_abr();
void F_stampa_abr_order(Albero T);
void F_inserisci_elemento_abr(Albero *T, int valore);
Albero F_alloca_nuovo_elemento_albero(Albero T, int valore);
void F_stampa_abr_preorder(Albero T);
void F_stampa_abr_postorder(Albero T);
int F_cerca_elemento_abr(Albero T, int valoreDaCercare);
int F_verifica_abr(Albero T, int min, int max);
int F_cerca_minimo_abr(Albero T);
int F_abr_vuoto(Albero T);
void F_cancella_nodo_abr(Albero *T, int elementoDaCancellare);

#endif //ABR_ABR_H
