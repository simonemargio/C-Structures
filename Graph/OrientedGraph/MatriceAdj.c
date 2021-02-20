#include "stdio.h"
#include <stdlib.h>
#include "Grafo.h"
#include "Error.h"
#include "MatriceAdj.h"

void F_stampa_grafo_matrice(Grafo *G){
    int i=0,j=0; MatrAdj M = (*G)->strutturaPtr; float **matrice=M->matrice; ArrMatr A = M->nodo;

    printf("Nodi presenti:\n");
    for(i=0;i<(*G)->numeroNodi;i++) printf("[%d]",A[i].nodo);

    puts("\n\nMatrice di riferimento:");
    for(i=0;i<(*G)->numeroNodi;i++) {
        printf("[%d]:\t",A[i].nodo);

        for (j = 0; j < (*G)->numeroNodi; j++) {
            if(matrice[i][j]>0 || matrice[i][j]<0) printf("|1|\t");
            else printf("|0|\t");
        }
        puts("");
    }
    puts("\n");
}

void F_aggiungi_arco_grafo_matrice(Grafo *G){
    MatrAdj M=(*G)->strutturaPtr; float **matrice=M->matrice;
    F_stampa_grafo_matrice(G);


    int elementoNodoPartenza=F_chiedi_intero("Inserisci il nodo di partenza:",2,'0','9');
    int nodoPatenza=F_cerca_nodo_grafo_matrice(G,elementoNodoPartenza);

    if(nodoPatenza!=-1){
        int elementoNodoArrivo=F_chiedi_intero("Inserisci il nodo di arrivo:",2,'0','9');
        int nodoArrivo=F_cerca_nodo_grafo_matrice(G,elementoNodoArrivo);

        if(nodoArrivo!=-1) F_inserisci_arco_grafo_matrice(matrice,nodoPatenza,nodoArrivo);

        else printf("\n Il nodo di arrivo (%d) non e' presente.\n",elementoNodoArrivo);

    }else printf("\n Il nodo di partenza (%d) non e' presente.\n",elementoNodoPartenza);

}

void F_elimina_arco_grafo_matrice(Grafo *G){
    MatrAdj M=(*G)->strutturaPtr; float **matrice=M->matrice;
    F_stampa_grafo_matrice(G);


    int elementoNodoPartenza=F_chiedi_intero("Inserisci il nodo di partenza da eliminare:",2,'0','9');
    int nodoPatenza=F_cerca_nodo_grafo_matrice(G,elementoNodoPartenza);

    if(nodoPatenza!=-1){
        int elementoNodoArrivo=F_chiedi_intero("Inserisci il nodo di arrivo da eliminare:",2,'0','9');
        int nodoArrivo=F_cerca_nodo_grafo_matrice(G,elementoNodoArrivo);

        if(nodoArrivo!=-1) F_dealloca_arco_grafo_matrice(matrice,nodoPatenza,nodoArrivo);

        else printf("\n Il nodo di arrivo (%d) non e' presente.\n",elementoNodoArrivo);

    }else printf("\n Il nodo di partenza (%d) non e' presente.\n",elementoNodoPartenza);
}

void F_inserisci_arco_grafo_matrice(float **M, int nodoPartenza, int nodoArrivo){
    M[nodoPartenza][nodoArrivo]=1;
}


void F_dealloca_arco_grafo_matrice(float **M, int nodoPartenza, int nodoArrivo){
    M[nodoPartenza][nodoArrivo]=0;
}


int F_cerca_nodo_grafo_matrice(Grafo *G, int nodoDaTrovare){
    int i=0; MatrAdj M = (*G)->strutturaPtr; ArrMatr A = M->nodo;

    for(i=0;i<(*G)->numeroNodi;i++) if(A[i].nodo==nodoDaTrovare) return i;

    return -1;
}

void F_aggiungi_nodo_grafo_matrice(Grafo *G){
    MatrAdj M=(*G)->strutturaPtr;
    if(F_struttura_vuota(M)){
        (*G)->numeroNodi=F_chiedi_intero("Numero di nodi da inserire nella matrice:",2,'0','9');
        F_alloca_struttura_grafo_matrice(G);
    } else F_alloca_nodo_grafo_matrice(G);
}




void F_alloca_nodo_grafo_matrice(Grafo *G)
{
    int i=0; MatrAdj M = (*G)->strutturaPtr; float **matrice=M->matrice; ArrMatr A = M->nodo;
    (*G)->numeroNodi++;


    float **nuovaMatrice =(float **)malloc((*G)->numeroNodi* sizeof(float *));
    for(i=0;i<(*G)->numeroNodi;i++)
        nuovaMatrice[i]=(float *)malloc((*G)->numeroNodi* sizeof(float *));

    /* Copia delle informazioni della vecchia matrice */
    F_copia_grafo_matrice(matrice,nuovaMatrice,(*G)->numeroNodi-1);
    ArrMatr nuovoArrayNodiMatrice= (struct struttura_elemento_array_nodo_matrice *)realloc(A,(*G)->numeroNodi* sizeof(struct struttura_elemento_array_nodo_matrice));
    nuovoArrayNodiMatrice->visitaPtr=NULL;
    nuovoArrayNodiMatrice[(*G)->numeroNodi-1].nodo=F_chiedi_intero("Inserisci il valore del nodo:",2,'0','9');

    /* Deallocazione matrice */
    for(i=0;i<(*G)->numeroNodi-1;i++)
        free(matrice[i]);
    free(matrice);

    /* Inserimento della nuova matrice nella struttura principale */
    M->nodo=nuovoArrayNodiMatrice;
    M->matrice=nuovaMatrice;
    (*G)->strutturaPtr=M;
}

void F_copia_grafo_matrice(float ** matricePartenza, float ** matriceDestinazione, int dim)
{
    int i=0,j=0;

    for(i=0;i<dim+1;i++)
        for(j=0;j<dim+1;j++)
            matriceDestinazione[i][j]=0;

    for(i=0;i<dim;i++)
        for(j=0;j<dim;j++)
            matriceDestinazione[i][j] = matricePartenza[i][j];
}



void F_alloca_struttura_grafo_matrice(Grafo *G){
    MatrAdj M = (struct struttura_elemento_matrice *)malloc(sizeof(struct struttura_elemento_matrice));
    ArrMatr A = (struct struttura_elemento_array_nodo_matrice *)malloc((*G)->numeroNodi*sizeof(struct struttura_elemento_array_nodo_matrice));
    if(F_struttura_vuota(M)) F_error(5);
    if(F_struttura_vuota(A)) F_error(6);
    M->matrice=NULL; A->visitaPtr=NULL;  int i=0;

    for(i=0;i<(*G)->numeroNodi;i++){
        int nodoDaInserire=F_chiedi_intero("Inserisci il valore del nodo:",2,'0','9');
        A[i].nodo=nodoDaInserire;
    }

    float **matrice =(float **)malloc((*G)->numeroNodi* sizeof(float *));
    for(i=0;i<(*G)->numeroNodi;i++)
        matrice[i]=(float *)malloc((*G)->numeroNodi* sizeof(float *));

    M->nodo=A;
    M->matrice=matrice;
    (*G)->strutturaPtr=M;
    F_inizializza_grafo_matrice(G);
}

void F_inizializza_grafo_matrice(Grafo *G){
    int i=0,j=0; MatrAdj M = (*G)->strutturaPtr;
    float **matrice=M->matrice;

    for(i=0;i<(*G)->numeroNodi;i++)
        for(j=0;j<(*G)->numeroNodi;j++) {
            matrice[i][j]=0;
        }
}

