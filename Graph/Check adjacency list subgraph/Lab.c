#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListAdj.h"
#include "Lab.h"

void F_Start(){
    Grafo G=NULL, H=NULL;

    F_alloca_struttura_gestione_grafo(&G);
    F_alloca_struttura_gestione_grafo(&H);
    F_genera_grafo_G_lista_adj(G);
    F_genera_grafo_H_lista_adj(H);
    F_engine(G,H);
    F_dealloca_grafo(G);
}

void F_engine(Grafo G, Grafo H){
    int sceltaMenu=0, uscitaMenu=-1, verificaSottografo=0;
    ListaAdj LG=G->strutturaPtr;
    ListaAdj LH=H->strutturaPtr;

    do{
        F_stampa_menu();
        sceltaMenu=F_chiedi_intero("Inserisci il numero dell'operazione da effetturare:",1,'0','6');
        switch (sceltaMenu){
            default:
                puts("Scelta non valida.\n");
                break;
            case 0:
                uscitaMenu=0;
                break;
            case 1:
                printf("\nGrafo G\n(Nodo)-[peso arco]->(nodo)\n");
                F_stampa_grafo(&LG);
                printf("\nGrafo H\n(Nodo)-[peso arco]->(nodo)\n");
                F_stampa_grafo(&LH);
                break;
            case 2: /* Aggiungi nodo G */
                F_aggiungi_nodo(G);
                break;
            case 3: /* Aggiungi arco G */
                F_aggiungi_arco(G);
                break;
            case 4: /* Aggiungi nodo H */
                F_aggiungi_nodo(H);
                break;
            case 5:  /* Aggiungi arco H */
                F_aggiungi_arco(H);
                break;
            case 6: /* H sottografo G */
                verificaSottografo=F_verifica_sottografo(G,H);
                if(verificaSottografo) puts("\nH e' sottografo di G con archi multipli.");
                else puts("H NON e' sottografo di G con archi multipli.");
                break;
        }
    }while (uscitaMenu!=0);

}

int F_verifica_sottografo(Grafo G, Grafo H){
    int verificaHsottografodiG=0;

    /*
     * H per essere un sottografo di G deve avere un numero di nodi/vertici minori o uguali a quelli di G.
     */
    if(H->numeroNodi<=G->numeroNodi){
        verificaHsottografodiG=F_verifica_nodi_sottografo_H_sottoinsieme_grafo_G(G->strutturaPtr,H->strutturaPtr);
        printf("\nValore finale:|%d|\n",verificaHsottografodiG);



    }
    return verificaHsottografodiG;
}

int F_verifica_nodi_sottografo_H_sottoinsieme_grafo_G(ListaAdj G, ListaAdj H){
    /*
     * Verifica che ogni nodo presente in H sia presente necessariamente anche in G.
     * Se il nodo H è presente in G allora si procede a verificare se gli archi di H siano presenti in G e che siano multipli.
     * Un nodo di G può avere anche più archi del nodo di H, basta che gli archi di H siano gli stessi di G e che siano multipli.
     */
    if(!F_struttura_vuota(H)){
        ListaAdj nodoGpresente=F_cerca_nodo_grafo_lista(&G,H->nodo);

        if(nodoGpresente){

            if(nodoGpresente->arcoPtr && H->arcoPtr){
                int verificaArchiMultipli=F_verifica_archi_multipli(nodoGpresente->arcoPtr,H->arcoPtr);
                if(verificaArchiMultipli==0) return 0;
            }

            return F_verifica_nodi_sottografo_H_sottoinsieme_grafo_G(G,H->nextPtr);
        } else return 0;
    }
    return 1;
}



int F_verifica_archi_multipli(ListaAdj G, ListaAdj H){
    /*
     * Dato l'arco H si verifica che questo sia presente anche in G. Se è presente si verifica che l'arco in H sia un multiplo
     * dell'alrco presente in G.
     * Il calcolo del multiplo usa la divisione analizzando il resto. Se esso è 0 allora è un multiplo.
     *
     * Si verifica se il valore dell'arco in G <= arco in H, se è così c'è la possibilità che H sia un multiplo.
     * Altrimenti significa che il valore dell'arco G>H e quindi non è possibile che in H ci sia un multiplo, a patto che non sia 0.
     *
     */
    if(!F_struttura_vuota(H)){

        ListaAdj arcoGpresente=F_cerca_arco_grafo_lista(&G,H->nodo);

        if(arcoGpresente){

            if(arcoGpresente->pesoPtr->peso<=H->pesoPtr->peso){
                int controlloMultiplo=H->pesoPtr->peso%arcoGpresente->pesoPtr->peso;
                if(controlloMultiplo!=0) return 0;

            }else if(H->pesoPtr->peso!=0) return 0;


            return F_verifica_archi_multipli(G,H->arcoPtr);

        }else return 0;

    }
    return 1;
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
    ListaAdj L=G->strutturaPtr;
    int valoreNodoPartenza=F_chiedi_intero("Inserisci il valore del nodo di partenza:",3,'0','9');
    int valoreNodoArrivo=F_chiedi_intero("Inserisci il valore del nodo di arrivo:",3,'0','9');
    int peso=F_chiedi_intero("Inserisci il valore del nodo di arrivo:",3,'0','9');
    F_aggiungi_arco_grafo_lista(&G,valoreNodoPartenza,valoreNodoArrivo,peso);
}

void F_genera_grafo_G_lista_adj(Grafo G){
    F_aggiungi_nodo_grafo_lista(&G,5);
    F_aggiungi_nodo_grafo_lista(&G,8);
    F_aggiungi_nodo_grafo_lista(&G,4);
    F_aggiungi_nodo_grafo_lista(&G,2);
    F_aggiungi_arco_grafo_lista(&G,5,8,8);
    F_aggiungi_arco_grafo_lista(&G,4,2,16);
    F_aggiungi_arco_grafo_lista(&G,8,4,9);
    F_aggiungi_arco_grafo_lista(&G,2,5,1);
}

void F_genera_grafo_H_lista_adj(Grafo H){

    F_aggiungi_nodo_grafo_lista(&H,4);
    F_aggiungi_nodo_grafo_lista(&H,8);
    F_aggiungi_nodo_grafo_lista(&H,5);

    F_aggiungi_arco_grafo_lista(&H,5,8,24);
    F_aggiungi_arco_grafo_lista(&H,8,4,18);
}


int F_struttura_vuota(void *S){
    return (!S);
}


void F_dealloca_grafo(Grafo G){
    ListaAdj L=G->strutturaPtr;
    F_dealloca_struttura_grafo_lista(&L);
    free(G);
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

void F_stampa_menu(){
    puts("---------------------------------------------");
    puts("\nLab - Example 3\n");
    puts("1] Stampa grafi");
    puts("2] Aggiungi nodo grafo G");
    puts("3] Aggiungi arco grafo G");
    puts("4] Aggiungi nodo grafo H");
    puts("5] Aggiungi arco grafo H");
    puts("6] Verifica sottografo");
    puts("\n0] Indietro");
    puts("---------------------------------------------");
}