#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Grafo.h"
#include "ListaAdj.h"
#include "MatriceAdj.h"
#include "Error.h"



void F_start_libreria_grafi(){
    Grafo G=NULL;
    F_alloca_struttura_gestione_grafo(&G);
    F_scelta_tipo_di_grafo(&G);
    F_scelta_grafo_pesato(&G);
    F_engine_grafo_orientato(G);
    F_dealloca_grafo_orientato(G);
}


void F_alloca_struttura_gestione_grafo(Grafo *G){
    (*G)=(struct struttura_gestione_grafi*)malloc(sizeof(struct struttura_gestione_grafi));
    if(F_struttura_vuota(*G)) F_error(1);
    (*G)->strutturaPtr=NULL;
    (*G)->numeroNodi=0;
    (*G)->ciclico=0;
    (*G)->listaMatriceAdj=0;
    (*G)->pesatoNonPesato=0;
}


void F_engine_grafo_orientato(Grafo G){
    int sceltaMenu=0, uscitaMenu=-1;

    do{
        F_stampa_menu_principale_grafo();
        sceltaMenu=F_chiedi_intero("Inserisci il numero dell'operazione da effetturare:",1,'0','9');
        switch(sceltaMenu){
            default:
                puts("Scelta non valida!");
                break;
            case 0:
                uscitaMenu=0;
                break;
            case 1: /* Aggiungi nodo */
                if(G->listaMatriceAdj) F_aggiungi_nodo_grafo_lista(&G);
                else F_aggiungi_nodo_grafo_matrice(&G);
                break;
            case 2: /* Aggiungi arco */
                if(F_struttura_vuota(G->strutturaPtr)) { puts("Grafo vuoto"); break;}
                if(G->listaMatriceAdj) F_aggiungi_arco_grafo_lista(&G);
                else F_aggiungi_arco_grafo_matrice(&G);
                break;
            case 3: /* Stampa grafo Va poi messa la visita in ampiezza e in profondita' */
                if(F_struttura_vuota(G->strutturaPtr)) { puts("Grafo vuoto"); break;}
                if(G->listaMatriceAdj) {ListaAdj L=G->strutturaPtr; F_stampa_grafo_lista(&L);}
                else F_stampa_grafo_matrice(&G);
                break;
            case 4: /* Elimina nodo */
                if(F_struttura_vuota(G->strutturaPtr)) { puts("Grafo vuoto"); break;}
                if(G->listaMatriceAdj) F_elimina_nodo_grafo_lista(&G);
                /*else F_elimina_nodo_grafo_matrice(&G); */
                break;
            case 5: /* Elimina arco */
                if(F_struttura_vuota(G->strutturaPtr)) { puts("Grafo vuoto"); break;}
                if(G->listaMatriceAdj) F_elimina_arco_grafo_lista(&G);
                else F_elimina_arco_grafo_matrice(&G);
                break;
            case 6:
                printf("\nNumero totale di nodi: |%d|\n",G->numeroNodi);
                break;
            case 7: /* Visita in profondita' (DFS)*/
                if(F_struttura_vuota(G->strutturaPtr)) { puts("Grafo vuoto"); break;}
                if(G->listaMatriceAdj) F_visita_in_profondita_lista(&G);
                break;
            case 8: /* Visita in profondita' (BFS)*/
                if(F_struttura_vuota(G->strutturaPtr)) { puts("Grafo vuoto"); break;}
                if(G->listaMatriceAdj) F_visita_in_ampiezza_lista(&G);
                break;
            case 9: /* Aciclicita' */
                if(F_struttura_vuota(G->strutturaPtr)) { puts("Grafo vuoto"); break;}
                if(G->ciclico) puts("Il grafo presenta almeno un ciclio");
                else puts("Il grafo non presenta alcun ciclo");
                break;

        }
    }while(uscitaMenu!=0);
}


void F_dealloca_grafo_orientato(Grafo G){

}


void F_scelta_tipo_di_grafo(Grafo *G){
    int sceltaMenu=0;
    F_stampa_menu_scelta_tipo_di_grafo();
    F_chiedi_intero("Scegli il tipo di grafo su cui lavorare:",1,'0','2');
    switch (sceltaMenu){
        default:
            exit(0);
        case 1:
            (*G)->listaMatriceAdj=0;
            break;
        case 2:
            (*G)->listaMatriceAdj=1;
            break;
    }
}

void F_scelta_grafo_pesato(Grafo *G){
    int sceltaMenu=0;
    F_stampa_menu_scelta_tipo_di_grafo_pesato();
    F_chiedi_intero("Scegli se vuoi un grafo pesato o meno:",1,'0','2');
    switch (sceltaMenu){
        default:
            exit(0);
        case 1: /* Pesato */
            (*G)->pesatoNonPesato=1;
            break;
        case 2: /* Non pesato */
            (*G)->pesatoNonPesato=0;
            break;
    }
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
    if(F_struttura_vuota(elemento)) F_error(2);
    memcpy(elemento,&intero_preso,sizeof(int));
    return intero_preso;
}

int F_struttura_vuota(void *S){
    return (!S);
}

void F_stampa_menu_scelta_tipo_di_grafo(){
    puts("---------------------------------------------");
    puts("\nScelta grafo\n");
    puts("1] Crea grafo matrice adiacenza");
    puts("2] Crea grafo lista di adiacenza");
    puts("\n0] Esci");
    puts("---------------------------------------------");
}

void F_stampa_menu_scelta_tipo_di_grafo_pesato(){
    puts("---------------------------------------------");
    puts("\nScelta grafo\n");
    puts("1] Grafo pesato");
    puts("2] Grafo NON pesato");
    puts("\n0] Esci");
    puts("---------------------------------------------");
}

void F_stampa_menu_principale_grafo(){
    puts("---------------------------------------------");
    puts("\nMenu grafo\n");
    puts("1] Aggiungi nodo");
    puts("2] Aggiungi arco");
    puts("3] Stampa grafo");
    puts("4] Elimina nodo");
    puts("5] Elimina arco");
    puts("6] Numero nodi grafo");
    puts("7] Visita in profondita' (DFS)");
    puts("8] Visista in ampiezza (BFS)");
    puts("9] Verifica aciclicita'");
    puts("\n0] Esci");
    puts("---------------------------------------------");
}