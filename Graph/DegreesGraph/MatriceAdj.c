#include <stdio.h>
#include <stdlib.h>
#include "Degrees.h"
#include "MatriceAdj.h"

void F_stampa_grafo_matrice(Grafo *G){
    int i=0,j=0; MatrAdj M = (*G)->GrafoMatriceAdj; float **matrice=M->matrice; ArrMatr A = M->nodo;

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

void F_alloca_struttura_grafo_matrice(Grafo *G){
    MatrAdj M = (struct struttura_elemento_matrice *)malloc(sizeof(struct struttura_elemento_matrice));
    ArrMatr A = (struct struttura_elemento_array_nodo_matrice *)malloc((*G)->numeroNodi*sizeof(struct struttura_elemento_array_nodo_matrice));
    if(F_struttura_vuota(M)) exit(4);
    if(F_struttura_vuota(A)) exit(5);
    M->matrice=NULL; A->visitaPtr=NULL;  int i=0;
    int nodoDaInserire=0;

    for(i=0;i<(*G)->numeroNodi;i++){

        switch(i){
            case 0:
                nodoDaInserire=5;
                break;
            case 1:
                nodoDaInserire=7;
                break;
            case 2:
                nodoDaInserire=1;
                break;
            case 4:
                nodoDaInserire=3;
                break;
            default:
                break;
        }

        A[i].nodo=nodoDaInserire;
    }

    float **matrice =(float **)malloc((*G)->numeroNodi* sizeof(float *));
    for(i=0;i<(*G)->numeroNodi;i++)
        matrice[i]=(float *)malloc((*G)->numeroNodi* sizeof(float *));

    M->nodo=A;
    M->matrice=matrice;
    (*G)->GrafoMatriceAdj=M;
    F_inizializza_grafo_matrice(G);
}

void F_inizializza_grafo_matrice(Grafo *G){
    int i=0,j=0; MatrAdj M = (*G)->GrafoMatriceAdj;
    float **matrice=M->matrice;

    for(i=0;i<(*G)->numeroNodi;i++)
        for(j=0;j<(*G)->numeroNodi;j++) {
            matrice[i][j]=0;
        }
}

void F_aggiungi_arco_grafo_matrice(Grafo *G, int nodoPartenza, int nodoArrivo){
    MatrAdj M=(*G)->GrafoMatriceAdj; float **matrice=M->matrice;
    F_inserisci_arco_grafo_matrice(matrice,nodoPartenza,nodoArrivo);

}

void F_inserisci_arco_grafo_matrice(float **M, int nodoPartenza, int nodoArrivo){
    M[nodoPartenza][nodoArrivo]=1;
}