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
        sceltaMenu=F_chiedi_intero("Inserisci il numero dell'operazione da effetturare:",1,'0','6');
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
            case 6: /* Calcolo grado entrante e uscente */
                F_calcolo_grado_entrante_uescente_lista_matrice(GL,GM);
                printf("\nGrado entrante lista:(%d)\nGrado uscente lista:(%d)",GL->gradoEntrante,GL->gradoUscente);
                printf("\nGrado entrante matrice:(%d)\nGrado uscente matrice:(%d)\n\n",GM->gradoEntrante,GM->gradoUscente);
                break;
        }
    }while (uscitaMenu!=0);

}

void F_calcolo_grado_entrante_uescente_lista_matrice(GrafoLista GL, GrafoMatrice GM){

    /*
     * Grado uscente lista
     */
    ListaAdj L=GL->strutturaPtr;
    GL->gradoUscente=F_calcolo_grado_uscente_lista(&L, 0);


    /* Grando entrante lista
     * Ogni elemento della lista è associato all'indice dell'array. Esempio:
     * Indice array - Nodo
     *     0        -  5
     *     1        -  8
     *     2        -  4
     * e così via.
     * Ogni cella dell'array viene incrementata di una unità quando si trova il valore del nodo in un arco.
     * Successivemente si cerca il massimo valore all'interno dell'array che rappresenta il grado entrante.
     */
    int arrayGradoEntranteLista[GL->numeroNodi];
    F_inizalizza_array(arrayGradoEntranteLista,GL->numeroNodi);
    F_calcolo_grado_entrante_lista(&L,&L, arrayGradoEntranteLista,GL->numeroNodi);
    GL->gradoEntrante=F_trova_grado_entrante_lista(arrayGradoEntranteLista,GL->numeroNodi);

    /*
     * Grado uscente matrice
     */
    GM->gradoUscente=F_calcolo_grado_uscente_matrice(GM->matrice,GM->numeroNodi);

    /*
     * Grando entrante matrice
     */
    GM->gradoEntrante=F_calcolo_grado_entrante_matrice(GM->matrice,GM->numeroNodi);
}

int F_calcolo_grado_uscente_matrice(int **matrice, int numeroNodi){
    /*
     * Si legge ogni riga della matrice sommando i valori dove sono presenti
     * degli archi (indentidicati nella matrice del valore 1).
     */
    int riga=0, gradoUscente=0;

    while (riga<numeroNodi){
        int gradoUscenteriga=F_calcola_grado_uscente_riga_matrice(matrice,riga,numeroNodi);

        if(gradoUscente<gradoUscenteriga) gradoUscente=gradoUscenteriga;

        riga++;
    }

    return gradoUscente;
}

int F_calcola_grado_uscente_riga_matrice(int **matrice, int riga, int numeroNodi){
    int colonna=0, gradoUscente=0;

    for(;colonna<numeroNodi;colonna++) if(matrice[riga][colonna]==1) gradoUscente++;

    return gradoUscente;
}

int F_calcolo_grado_entrante_matrice(int **matrice, int numeroNodi){
    /*
    * Si legge ogni colonnna della matrice sommando i valori dove sono presenti
    * degli archi (indentidicati nella matrice del valore 1).
    */
    int colonna=0, gradoEntrante=0;

    while (colonna<numeroNodi){
        int gradoUscenteriga=F_calcola_grado_entrante_riga_matrice(matrice,colonna,numeroNodi);

        if(gradoEntrante<gradoUscenteriga) gradoEntrante=gradoUscenteriga;

        colonna++;
    }

    return gradoEntrante;
}

int F_calcola_grado_entrante_riga_matrice(int **matrice, int colonna, int numeroNodi){
    int riga=0, gradoEntrante=0;

    for(;riga<numeroNodi;riga++) if(matrice[riga][colonna]==1) gradoEntrante++;

    return gradoEntrante;
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

int F_trova_grado_entrante_lista(int *array, int numeroNodi){
    int i=0, gradoEntranteLista=0;

    for(i=0;i<numeroNodi;i++){
        if(gradoEntranteLista<array[i]){
            gradoEntranteLista=array[i];
        }
    }
    return gradoEntranteLista;
}

void F_inizalizza_array(int *array, int numeroNodi){
    int i=0;
    for(;i<numeroNodi;i++)
        array[i]=0;
}

int F_calcolo_grado_uscente_lista(ListaAdj *L, int gradoUscente){
    /*
     * Per ogni nodo viene verificato se ha un arco. Se presente allora si contano il numero di archi (numeroArchiUscenti)
     * e si salva (gradoUscente) il valore di archi maggiore.
     */
    if(!F_struttura_vuota(*L)){

        if((*L)->arcoPtr){
            int numeroAchiUscenti=0;
            numeroAchiUscenti=F_calcola_grado_uscente_arco_lista(&(*L)->arcoPtr,numeroAchiUscenti);
            if(numeroAchiUscenti>gradoUscente) gradoUscente=numeroAchiUscenti;
        }
        return F_calcolo_grado_uscente_lista((&(*L)->nextPtr), gradoUscente);
    }
    return gradoUscente;
}

int F_calcola_grado_uscente_arco_lista(ListaAdj *L, int numeroArchiUscenti){
    if(!F_struttura_vuota(*L)) return F_calcola_grado_uscente_arco_lista((&(*L)->arcoPtr), numeroArchiUscenti+1);
    return numeroArchiUscenti;
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

void F_genera_grafo_lista_adj(GrafoLista GL){
    F_aggiungi_nodo_grafo_lista(&GL,5);
    F_aggiungi_nodo_grafo_lista(&GL,8);
    F_aggiungi_nodo_grafo_lista(&GL,4);
    F_aggiungi_nodo_grafo_lista(&GL,2);
    F_aggiungi_arco_grafo_lista(&GL,5,8);
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
    F_aggiungi_arco_grafo_matrice(&GM,5,4);
    F_aggiungi_arco_grafo_matrice(&GM,8,2);
    F_aggiungi_arco_grafo_matrice(&GM,8,8);
    F_aggiungi_arco_grafo_matrice(&GM,8,5);
    F_aggiungi_arco_grafo_matrice(&GM,4,2);
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
    puts("\nLab - Example 1\n");
    puts("1] Stampa grafi");
    puts("2] Aggiungi nodo grafo lista");
    puts("3] Aggiungi arco grafo lista");
    puts("4] Aggiungi nodo grafo matrice");
    puts("5] Aggiungi arco grafo matrice");
    puts("6] Calcola grado entrante e uscente");
    puts("\n0] Indietro");
    puts("---------------------------------------------");
}

