#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "CodaPriorita.h"
#include "Heapify.h"
#define NUMERO_ELEMENTI_VETTORE 10

void F_start(){
    int uscita_menu_principale=-1,scelta=0,numeroDaCercare=0;
    srand((unsigned)time(NULL));
    StructHeap G=F_crea_struttura_generale();
    Array Arr=F_crea_vettore();
    F_aggiungi_informazioni_struttura_generale(G,Arr);

    do{
        scelta=F_stampa_menu_principale();
        switch (scelta){
            case 0:
                uscita_menu_principale=0;
                break;
            case 1:
                F_build_heap(G);
                F_stampa_array(G);
                break;
            case 2:
                F_heap_sort(G);
                F_stampa_array(G);
                break;
            case 3:
                F_stampa_array(G);
                break;
            case 4:
                 numeroDaCercare=F_ricerca_elemento_array(G);
                 if(numeroDaCercare==-1) printf("\nValore non presente!\n");
                 else printf("\nIndice dove e' presente il valore:%d\n",numeroDaCercare);
              break;
            case 5:
                break;
            default:
                puts("\nScelta non valida! Riprovare");
                break;
        }

    }while(uscita_menu_principale!=0);

    /* Per eliminare un elemento una volta trovato, prendo una foglia (l'ultimo elemento dell'array)
     * e la metto al posto dell'elemento da eliminare, succedivamente eseguo una incrase key o decrease key.
     * Vedere poi come eliminare l'ultimo elemento dell'array e aggiustare heapsize
     *
     * Devo vedere che se lo heap e' ordinato allora incrase e decrease non serve, aletimenti li devo applicare!
     * */
}

int F_stampa_menu_principale(){
    int scelta = 0;
    puts("\n");
    puts("1] Costrusci haep");
    puts("2] Ordina heap");
    puts("3] Stampa heap ");
    puts("4] Cerca elemento");
    puts("5] Annulla lavoro");
    puts("");
    puts("0] Esci");
    printf("\nSeleziona tramite valore numerico:");
    scelta=F_seleziona(1,'0','6',0);

    return scelta;
}

int F_richiedi_elemento(){
    printf("\nInserisci il valore dell'elemento che vuoi trovare:");
    int elementoDaCercare=F_seleziona(1,'0','6',0);
    return elementoDaCercare;
}

int F_seleziona(int dim,char minimo,char massimo,int escludi){
    /* Variabili in ingresso:
     *
     * dim: dimensione del vettore che conterrà i valori numerici presi in inmput
     * minimo: valore piu' piccolo che puo' essere preso
     * massimo: valore massimo che puo' essere preso
     * escludi: il valore preso in input non deve essere minore uguale del valore escludi
     * */
    char tmp[dim],c='*',*ptr;
    int intero_preso=0,i=0,flag=0;

    do
    {
        while( (c= (char) getchar()) != '\n' && i<dim && c != EOF )
        {
            if(c>=minimo && c<=massimo)
            {
                tmp[i]=c;
                i++;
            }

        }
        intero_preso = (int) strtol(tmp, &ptr, 10);

        if(intero_preso<=escludi)
        {
            printf("Valore non corretto\nInserisci di nuovo:");

            /* Inizializzo vettore */
            for(i=0;i<dim;i++)
                tmp[i]='*';

            i=0;
        }
        else // Valore corretto
            flag=1;

    }while(flag==0);

    int *elemento=malloc(sizeof(int));
    memcpy(elemento,&intero_preso,sizeof(int));
    return intero_preso;
}

void F_aggiungi_informazioni_struttura_generale(StructHeap G, Array Arr){
    G->struttura=Arr;
    G->heapsize=NUMERO_ELEMENTI_VETTORE;
}

StructHeap F_crea_struttura_generale(){
    StructHeap G=(struct Struttura_gestione_heap*)malloc(sizeof(struct Struttura_gestione_heap));
    G->heapsize=0;
    G->struttura=NULL;
    return G;
}

Array F_crea_vettore(){
    Array A=(struct Struttura_array*)calloc(NUMERO_ELEMENTI_VETTORE, sizeof(struct Struttura_array));

    for(int i=0;i<NUMERO_ELEMENTI_VETTORE;i++){
        ElemArray Elem=F_alloca_elemento_array();
        A[i].coda=Elem;

    }
    return A;
}

/* Funzione per la generazione di priorita' e dell'elemento */
ElemArray F_alloca_elemento_array(){
    ElemArray Elem=(struct Struttura_elemento_array*)malloc(sizeof(struct Struttura_elemento_array));
    Elem->elemento=F_genera_numero_casuale();
    Elem->priorita=F_genera_numero_casuale();
    return Elem;
}

int F_genera_numero_casuale(){
    int numero_random = rand() % (100 + 1);

    return numero_random;
}

void F_stampa_array(StructHeap G){
    Array Arr=G->struttura;
    puts("\nLeggenda: |(Priorita')-[Valore]|");
    for(int i=0;i<NUMERO_ELEMENTI_VETTORE;i++){
        printf("|(%d)-[%d]| ",Arr[i].coda->priorita,Arr[i].coda->elemento);
    }
}