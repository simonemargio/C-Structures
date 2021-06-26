#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lab.h"
#include "ListAdj.h"


void F_Start(){
    Grafo G=NULL;

    F_alloca_struttura_gestione_grafo(&G);
    F_genera_grafo_lista_adj(G);
    F_engine(G);
    F_dealloca_grafo(G);
}

void F_engine(Grafo G){
    int sceltaMenu=0, uscitaMenu=-1;
    ListaAdj L=G->strutturaPtr;

    printf("\nLe strutture sono state gia' allocate.\n\nGrafo di riferimento:\n(Nodo)-arco->(nodo)\n");
    F_stampa_grafo(&L);

    do{
        F_stampa_menu();
        sceltaMenu=F_chiedi_intero("Inserisci il numero dell'operazione da effetturare:",1,'0','4');
        switch (sceltaMenu){
            default:
                puts("Scelta non valida.\n");
                break;
            case 0:
                uscitaMenu=0;
                break;
            case 1: /* Stampa grafo */
                printf("[Nodo]-arco->(nodo)\n");
                F_stampa_grafo(&L);
                break;
            case 2: /* Aggiungi nodo */
                F_aggiungi_nodo(G);
                break;
            case 3: /* Aggiungi arco */
                F_aggiungi_arco(G);
                break;
            case 4:  /* Ricerca ciclo */
                F_visita_in_profondita_lista(&G);
                if(G->ciclico) puts("\nIl grafo ha almeno un ciclo. L'arco che lo creava e' stato eliminato.\n");
                break;
        }
    }while (uscitaMenu!=0);

}

void F_aggiungi_nodo(Grafo G){
    ListaAdj L=G->strutturaPtr;
    int valoreNodoDaAggiungere=F_chiedi_intero("Inserisci il valore del nuovo nodo:",3,'0','9');

    ListaAdj nodoGiaPresente=F_cerca_nodo_grafo_lista(&L,valoreNodoDaAggiungere);

    if(F_struttura_vuota(nodoGiaPresente)){
        F_aggiungi_nodo_grafo_lista(&G,valoreNodoDaAggiungere);
    }else printf("\nNodo (%d) gia' presente.\n",valoreNodoDaAggiungere);
}


void F_aggiungi_arco(Grafo G){
    int valoreNodoPartenza=F_chiedi_intero("Inserisci il valore del nodo di partenza:",3,'0','9');
    int valoreNodoArrivo=F_chiedi_intero("Inserisci il valore del nodo di arrivo:",3,'0','9');
    F_aggiungi_arco_grafo_lista(&G,valoreNodoPartenza,valoreNodoArrivo);
}

void F_genera_grafo_lista_adj(Grafo G){
    F_aggiungi_nodo_grafo_lista(&G,5);
    F_aggiungi_nodo_grafo_lista(&G,8);
    F_aggiungi_nodo_grafo_lista(&G,4);
    F_aggiungi_nodo_grafo_lista(&G,2);
    F_aggiungi_arco_grafo_lista(&G,5,8);
    F_aggiungi_arco_grafo_lista(&G,4,2);
    F_aggiungi_arco_grafo_lista(&G,8,4);
    F_aggiungi_arco_grafo_lista(&G,2,5);
}

int F_struttura_vuota(void *S){
    return (!S);
}

int F_chiedi_intero(char *s,int dim,char minimo,char massimo){
    /*
     * Permette di prendere un interno dall'input. Vengono scartati tutti
     * i caratteri che non sono numeri. Informazioni sui parametri presi dalla
     * funzione in alto.
     * Si prendono valori numerici fin tanto che:
     * non si raggiunge un new line
     * non si supera il parametro dim
     * non si raggiunge end of file
     *
     */
    char tmp[dim],c='*',*ptr;
    int intero_preso=0,i=0,flag=0;

    printf("%s",s);
    do{
        while( (c= (char) getchar()) != '\n' && i<dim && c != EOF ){
            if(c>=minimo && c<=massimo){
                tmp[i]=c;
                i++;
            }
        }
        intero_preso = (int) strtol(tmp, &ptr, 10);

        if(!i){
            printf("Valore non corretto\nInserisci di nuovo:");

            /* Inizializzo vettore */
            for(i=0;i<dim;i++)
                tmp[i]='*';
            i=0;
        }else flag=1; /* Valore corretto */
    }while(flag==0);

    /*
     * Viene creato un elemento di tipo intero adibito
     * a contenere il valore preso in imput e restituito
     */
    int *elemento=malloc(sizeof(int));
    if(F_struttura_vuota(elemento)) exit(-4);
    memcpy(elemento,&intero_preso,sizeof(int));
    return intero_preso;
}

void F_dealloca_grafo(Grafo G){
    ListaAdj L=G->strutturaPtr;
    F_dealloca_struttura_grafo_lista(&L);
    free(G);
}

void F_stampa_menu(){
    puts("---------------------------------------------");
    puts("\nLab - Example 4\n");
    puts("1] Stampa grafo");
    puts("2] Aggiungi nodo");
    puts("3] Aggiungi arco");
    puts("4] Verifica presenza cicli");
    puts("\n0] Indietro");
    puts("---------------------------------------------");
}
