#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lab.h"
#include "ListAdj.h"
#include "MatrAdj.h"


void F_Start(){
    GrafoLista GL=NULL; GrafoMatrice GM=NULL;

    F_alloca_struttura_gestione_grafo(&GL);
    F_alloca_struttura_gestione_matrice(&GM);
    F_genera_grafo_lista_adj(GL);
    F_genera_grafo_matrice_adj(GM);
    F_engine(GL,GM);

    ListaAdj L=GL->strutturaPtr;
    F_dealloca_struttura_grafo_lista(&L);
    F_dealloca_struttura_grafo_matrice(GM);

}

void F_engine(GrafoLista GL, GrafoMatrice GM){
    int sceltaMenu=0, uscitaMenu=-1;
    ListaAdj L=GL->strutturaPtr;

    printf("\nLe strutture sono state gia' allocate.\n\nGrafo di riferimento:\n(Nodo)-[peso arco]->(nodo)\n");
    F_stampa_grafo(&L);
    F_stampa_grafo_matrice(&GM);

    do{
        F_stampa_menu();
        sceltaMenu=F_chiedi_intero("Inserisci il numero dell'operazione da effetturare:",1,'0','7');

        switch (sceltaMenu){
            default:
                puts("Scelta non valida.\n");
                break;
            case 0:
                uscitaMenu=0;
                break;
            case 1:
                printf("\nGrafo di riferimento:\n(Nodo)-[peso arco]->(nodo)\n");
                F_stampa_grafo(&L);
                F_stampa_grafo_matrice(&GM);
                break;
            case 2: /* Aggiungi nodo lista */
                F_aggiungi_nodo_lista(GL);
                break;
            case 3: /* Aggiungi arco lista */
                F_aggiungi_arco_lista(GL);
                break;
            case 4: /* Aggiungi nodo matrice */
                F_aggiungi_nodo_matrice(GM);
                break;
            case 5: /* Aggiungi arco matrice */
                F_aggiungi_arco_matrice(GM);
                break;
            case 6: /* Verifica nodo pozzo lista */
                F_verifica_presenza_nodo_pozzo_lista(GL);
                break;
            case 7: /* Verifica nodo pozzo matrice */
                F_verifica_presenza_nodo_pozzo_matrice(GM);
                break;
        }
    }while (uscitaMenu!=0);

}

void F_verifica_presenza_nodo_pozzo_matrice(GrafoMatrice GM){
    /*
     * Per essere un nodo pozzo la riga deve contenere tutti valori 0, oppure
     * tutti valori 0 tranne il cappio sul nodo stesso.
     */
    int rigaPresutoNodoPozzo=F_calcolo_grado_uscente_matrice(GM->matrice,GM->numeroNodi);

    if(rigaPresutoNodoPozzo!=-1){
        int nodoPozzoConfermato=F_conferma_nodo_pozzo_matrice(GM->matrice,GM->numeroNodi,rigaPresutoNodoPozzo);

        if(nodoPozzoConfermato){
            int **matrice=GM->matrice; MatrAdj M=GM->strutturaPtr;
            matrice[rigaPresutoNodoPozzo][0]=1;
            printf("Il nodo (%d) e' un nodo pozzo. Lo elimino creando un arco da (%d) al (%d).\n",M[rigaPresutoNodoPozzo].nodo,M[rigaPresutoNodoPozzo].nodo,M[0].nodo);
        }

    } else puts("\nNon e' presente un nodo pozzo nella matrice.");
}

int F_conferma_nodo_pozzo_matrice(int **matrice,int numeroNodi, int rigaPresuntoNodoPozzo){
    int colonna=rigaPresuntoNodoPozzo, riga=0, nodoPozzoConfermato=1;

    for(;riga<numeroNodi;riga++){
        if(riga!=rigaPresuntoNodoPozzo){

            if(matrice[riga][colonna]==0){
                nodoPozzoConfermato=0;
                break;
            }
        }
    }
    return nodoPozzoConfermato;
}

int F_calcolo_grado_uscente_matrice(int **matrice, int numeroNodi){
    /*
     * Si legge ogni riga della matrice sommando i valori dove sono presenti
     * degli archi (indentidicati nella matrice del valore 1).
     */
    int riga=0;

    while (riga<numeroNodi){
        int gradoUscenteriga=F_calcola_grado_uscente_riga_matrice(matrice,riga,numeroNodi);

        if(gradoUscenteriga==numeroNodi || gradoUscenteriga==numeroNodi-1) return riga;

        riga++;
    }

    return -1;
}

int F_calcola_grado_uscente_riga_matrice(int **matrice, int riga, int numeroNodi){
    int colonna=0, gradoUscente=0;

    for(;colonna<numeroNodi;colonna++) {
        /*
         * Si elimina la lettura del nodo con se stesso in quanto che abbia un cappio
         * con se stesso oppure no resta sempre un possibile nodo pozzo.
         */
        if(riga!=colonna){
            if(matrice[riga][colonna]==0) gradoUscente++;
        }

    }

    return gradoUscente;
}

void F_verifica_presenza_nodo_pozzo_lista(GrafoLista GL){
    /*
     * Si cerca un possibile nodo pozzo andando ad esaminare i suoi archi.
     */
    ListaAdj L=GL->strutturaPtr; ListaAdj possibileNodoPozzo=NULL;

    F_cerca_nodo_pozzo_lista(GL,&L,&possibileNodoPozzo);

    if(possibileNodoPozzo){
        F_aggiungi_arco_grafo_lista(&GL,possibileNodoPozzo->nodo,L->nodo);
        printf("Il nodo (%d) e' un nodo pozzo. Lo elimino creando un arco da (%d) a (%d).\n",possibileNodoPozzo->nodo,possibileNodoPozzo->nodo,L->nodo);

    } else puts("\nNon e' presente un nodo pozzo nella lista.");

}

void F_cerca_nodo_pozzo_lista(GrafoLista GL,ListaAdj *L, ListaAdj *possibileNodoPozzo){
    if(!F_struttura_vuota(*L)){

        /*
         * Un possibile nodo pozzo può avere un cappio su se stesso ma non ha altri archi.
         */
        if((*L)->arcoPtr){
            if((*L)->nodo==(*L)->arcoPtr->nodo && (*L)->arcoPtr->arcoPtr==NULL){
                (*possibileNodoPozzo)=(*L);
                int confermaNodoPozzo=F_conferma_nodo_pozzo(GL,possibileNodoPozzo);

                if(confermaNodoPozzo==0){
                    *possibileNodoPozzo=NULL;
                    return;
                }
            }
        }

        /*
         * Se un nodo non ha alcun arco è candiato ad essere un possibile nodo pozzo.
         */
        if(!(*L)->arcoPtr){
            (*possibileNodoPozzo)=(*L);
            int confermaNodoPozzo=F_conferma_nodo_pozzo(GL,possibileNodoPozzo);

            if(confermaNodoPozzo==0){
                *possibileNodoPozzo=NULL;
                return;
            }
        }

        F_cerca_nodo_pozzo_lista(GL,&(*L)->nextPtr,possibileNodoPozzo);
    }

}

int F_conferma_nodo_pozzo(GrafoLista GL, ListaAdj *possibileNodoPozzo){
    ListaAdj Lista=GL->strutturaPtr;

    /*
     * Set di funzioni create in laboratorio esercizio 1.
     * Si va a verificare se nella cella di indice del nodo presunto pozzo siano presenti un numero di archi entranti pari
     * al numero dei nodi (quindi tutti i nodi puntanto al nodo pozzo compreso se stesso) oppure il numero di nodi -1 (tutti
     * i nodi puntano al nodo pozzo tranne se stesso oppure tutti i nodi (presunto pozzo compreso) puntano al presunto pozzo
     * tranne uno)
     */
    int arrayGradoEntranteLista[GL->numeroNodi];
    F_inizalizza_array(arrayGradoEntranteLista,GL->numeroNodi);
    F_calcolo_grado_entrante_lista(&Lista,&Lista, arrayGradoEntranteLista,GL->numeroNodi);
    int nodoPozzo=F_verifica_nodo_pozzo(&Lista,(*possibileNodoPozzo)->nodo,arrayGradoEntranteLista,GL->numeroNodi);


    return nodoPozzo;
}

int F_verifica_nodo_pozzo(ListaAdj *L, int valoreNodoDaTrovare, int *array, int numeroNodi){
    int indiceNodo= F_ritorna_indice_posizione_nodo_lista(L, valoreNodoDaTrovare, 0);

    if(array[indiceNodo]==numeroNodi) return 1;

    if(array[indiceNodo]==numeroNodi-1){
        /*
         * Se il numero di nodi è minore di una unità bisogna verificare che il presunto
         * noso pozzo abbia un unico arco e questo sarà necessariamente l'arco con se stesso.
         */
        while(*L){

            if((*L)->nodo==valoreNodoDaTrovare){
                if((*L)->arcoPtr) return 0;
                else return 1;
            }
            (*L)=(*L)->nextPtr;
        }

    }
    else return 0;
}

void F_calcolo_grado_entrante_lista(ListaAdj *L, ListaAdj *ListaScorrimento, int *arrayNodiLista, int numeroNodi){
    /*
     * L = lista usata per scorrere ogni singolo nodo dopo che sono stati visitati tutti gli archi del nodo stesso.
     * ListaScorrimento = lista adibita allo scorrimento dei nodi per ricercare gli indici da associare all'array.
     *
     * Si scorre la lista intera e per ogni nodo si verifica se sono presenti archi.
     */
    if(!F_struttura_vuota(*L)){

        if((*L)->arcoPtr) F_calcolo_numero_archi_lista(&(*ListaScorrimento),&(*L)->arcoPtr,arrayNodiLista,numeroNodi);
        F_calcolo_grado_entrante_lista(&(*L)->nextPtr,ListaScorrimento,arrayNodiLista,numeroNodi);
    }

}

void F_calcolo_numero_archi_lista(ListaAdj *L, ListaAdj *ArcoLista, int *arrayNodiLista, int numeroNodi){
    /*
     * L = lista principale
     * ArcoLista = è il nodo arco di riferimento. Lo si scorre tutto per leggere tutti gli archi.
     *
     * Per ogni valore nel nodo si ottiene il suo indice e si incrementa la variabile nell'array.
     */
    if(!F_struttura_vuota(*ArcoLista)){
        int indiceIncrementoNodo=0;
        indiceIncrementoNodo=F_ritorna_indice_posizione_nodo_lista(L,(*ArcoLista)->nodo, 0);

        arrayNodiLista[indiceIncrementoNodo]=arrayNodiLista[indiceIncrementoNodo]+1;

        F_calcolo_numero_archi_lista(L,&(*ArcoLista)->arcoPtr,arrayNodiLista,numeroNodi);
    }
}

int F_ritorna_indice_posizione_nodo_lista(ListaAdj *ListaScorrimento, int valoreDatrovare, int indiceNodoTrovato){
    if(!F_struttura_vuota(*ListaScorrimento)){
        if((*ListaScorrimento)->nodo==valoreDatrovare) return indiceNodoTrovato;
        return F_ritorna_indice_posizione_nodo_lista(&(*ListaScorrimento)->nextPtr,valoreDatrovare,indiceNodoTrovato+1);
    }
    return indiceNodoTrovato;
}

void F_inizalizza_array(int *array, int numeroNodi){
    int i=0;
    for(;i<numeroNodi;i++)
        array[i]=0;
}

void F_genera_grafo_lista_adj(GrafoLista GL){
    F_aggiungi_nodo_grafo_lista(&GL,5);
    F_aggiungi_nodo_grafo_lista(&GL,8);
    F_aggiungi_nodo_grafo_lista(&GL,4);
    F_aggiungi_nodo_grafo_lista(&GL,2);
    F_aggiungi_arco_grafo_lista(&GL,5,8);
    F_aggiungi_arco_grafo_lista(&GL,5,2);
    F_aggiungi_arco_grafo_lista(&GL,5,4);
    F_aggiungi_arco_grafo_lista(&GL,8,2);
    F_aggiungi_arco_grafo_lista(&GL,8,8);
    F_aggiungi_arco_grafo_lista(&GL,8,5);
    F_aggiungi_arco_grafo_lista(&GL,4,2);
}

void F_genera_grafo_matrice_adj(GrafoMatrice GM){
    F_aggiungi_nodo_grafo_matrice(&GM,5);
    F_aggiungi_nodo_grafo_matrice(&GM,8);
    F_aggiungi_nodo_grafo_matrice(&GM,4);
    F_aggiungi_nodo_grafo_matrice(&GM,2);
    F_aggiungi_arco_grafo_matrice(&GM,5,8);
    F_aggiungi_arco_grafo_matrice(&GM,5,2);
    F_aggiungi_arco_grafo_matrice(&GM,5,4);
    F_aggiungi_arco_grafo_matrice(&GM,8,2);
    F_aggiungi_arco_grafo_matrice(&GM,8,8);
    F_aggiungi_arco_grafo_matrice(&GM,8,5);
    F_aggiungi_arco_grafo_matrice(&GM,4,2);
}

void F_aggiungi_arco_matrice(GrafoMatrice GM){
    int valoreNodoPartenza=F_chiedi_intero("Inserisci il valore del nodo di partenza:",3,'0','9');
    int valoreNodoArrivo=F_chiedi_intero("Inserisci il valore del nodo di arrivo:",3,'0','9');

    F_aggiungi_arco_grafo_matrice(&GM,valoreNodoPartenza,valoreNodoArrivo);
}

void F_aggiungi_nodo_matrice(GrafoMatrice GM){
    MatrAdj M=GM->strutturaPtr;
    int valoreNodoDaAggiungere=F_chiedi_intero("Inserisci il valore del nuovo nodo:",3,'0','9');

    int nodoGiaPresente=F_cerca_indice_grafo_matrice(&M,valoreNodoDaAggiungere,0,GM->numeroNodi);

    if(nodoGiaPresente<=0){
        F_aggiungi_nodo_grafo_matrice(&GM,valoreNodoDaAggiungere);
    }else printf("\nNodo (%d) gia' presente.\n",valoreNodoDaAggiungere);
}

void F_aggiungi_nodo_lista(GrafoLista GL){
    ListaAdj L=GL->strutturaPtr;
    int valoreNodoDaAggiungere=F_chiedi_intero("Inserisci il valore del nuovo nodo:",3,'0','9');

    ListaAdj nodoGiaPresente=F_cerca_nodo_grafo_lista(&L,valoreNodoDaAggiungere);

    if(F_struttura_vuota(nodoGiaPresente)){
        F_aggiungi_nodo_grafo_lista(&GL,valoreNodoDaAggiungere);
    }else printf("\nNodo (%d) gia' presente.\n",valoreNodoDaAggiungere);
}

void F_aggiungi_arco_lista(GrafoLista G){
    int valoreNodoPartenza=F_chiedi_intero("Inserisci il valore del nodo di partenza:",3,'0','9');
    int valoreNodoArrivo=F_chiedi_intero("Inserisci il valore del nodo di arrivo:",3,'0','9');
    F_aggiungi_arco_grafo_lista(&G,valoreNodoPartenza,valoreNodoArrivo);
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

void F_stampa_menu(){
    puts("---------------------------------------------");
    puts("\nLab - Example 2\n");
    puts("1] Stampa grafi");
    puts("2] Aggiungi nodo grafo lista");
    puts("3] Aggiungi arco grafo lista");
    puts("4] Aggiungi nodo grafo matrice");
    puts("5] Aggiungi arco grafo matrice");
    puts("6] Verifica prezenza nodo posso lista");
    puts("7] Verifica prezenza nodo posso matrice");
    puts("\n0] Esci");
    puts("---------------------------------------------");
}
