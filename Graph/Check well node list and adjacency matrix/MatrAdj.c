#include <stdio.h>
#include <stdlib.h>
#include "MatrAdj.h"
#include "Lab.h"

void F_alloca_struttura_gestione_matrice(GrafoMatrice *M){
    (*M)=(struct struttura_elemento_matrice*)malloc(sizeof(struct struttura_elemento_matrice));
    if(F_struttura_vuota(*M)) exit(-1);
    (*M)->matrice=NULL;
    (*M)->strutturaPtr=NULL;
    (*M)->numeroNodi=0;
}

void F_aggiungi_nodo_grafo_matrice(GrafoMatrice *M, int valoreDaInserire){
    MatrAdj Madj=(*M)->strutturaPtr;
    (*M)->numeroNodi++;
    F_alloca_nodo_grafo_matrice(M,&Madj,valoreDaInserire);
    (*M)->strutturaPtr=Madj;
}

void F_alloca_nodo_grafo_matrice(GrafoMatrice *GM, MatrAdj *M, int valoreDaInserire){
    /*
     * Viene allocato l'array contentente i nodi della matrice. Se tale array è già presente
     * si effettua una realloc di questo per inserire il nuovo elemento.
     */
    if(F_struttura_vuota(*M)) (*M) = (struct struttura_elemento_array_nodo_matrice *)malloc((*GM)->numeroNodi*sizeof(struct struttura_elemento_array_nodo_matrice));
    else (*M) = (struct struttura_elemento_array_nodo_matrice *)realloc((*M),(*GM)->numeroNodi*sizeof(struct struttura_elemento_array_nodo_matrice));
    (*M)[(*GM)->numeroNodi-1].nodo=valoreDaInserire;

    int i=0;

    int **matriceNuova=(int **)malloc((*GM)->numeroNodi* sizeof(int *));
    for(i=0;i<(*GM)->numeroNodi;i++)
        matriceNuova[i]=(int *)malloc((*GM)->numeroNodi* sizeof(int *));

    /*
    * Se la matrice non è mai stata allocata viene semplicemente inizalizzata a 0 (else).
    * Se è già presente si procede a copiare i valori della vecchia matrice nella nuova.
    */
    if(!F_struttura_vuota((*GM)->matrice)){
        int **matriceVecchia=(*GM)->matrice;
        F_copia_matrice(matriceNuova,matriceVecchia,(*GM)->numeroNodi);
    }else{
        int j=0;
        for(i=0;i<(*GM)->numeroNodi;i++)
            for(j=0;j<(*GM)->numeroNodi;j++)
                matriceNuova[i][j]=0;
    }
    (*GM)->matrice=matriceNuova;
}

void F_copia_matrice(int **matriceNuova, int **matriceVecchia, int numeroNodi){
    int i=0,j=0;

    for(i=0;i<numeroNodi;i++)
        for(j=0;j<numeroNodi;j++)
            matriceNuova[i][j]=0;

    for(i=0;i<numeroNodi-1;i++)
        for(j=0;j<numeroNodi-1;j++)
            matriceNuova[i][j] = matriceVecchia[i][j];
}

void F_stampa_grafo_matrice(GrafoMatrice *M){
    int i=0,j=0; int **matrice=(*M)->matrice;  MatrAdj A = (*M)->strutturaPtr;

    printf("\n\nNodi presenti nella matrice:\n");
    for(i=0;i<(*M)->numeroNodi;i++) printf("[%d]",A[i].nodo);

    puts("\n\nMatrice di riferimento:");
    for(i=0;i<(*M)->numeroNodi;i++) {
        printf("[%d]:\t",A[i].nodo);

        for (j = 0; j < (*M)->numeroNodi; j++) {
            if(matrice[i][j]>0 || matrice[i][j]<0) printf("|1|\t");
            else printf("|0|\t");
        }
        puts("");
    }
    puts("\n");
}

MatrAdj F_cerca_nodo_grafo_matrice(MatrAdj *M, int valoreNodoDaTrovare, int indicePartenza, int numeroTotaleNodi){
    if(indicePartenza>=numeroTotaleNodi || F_struttura_vuota(*M)) return NULL;
    if((*M)[indicePartenza].nodo==valoreNodoDaTrovare) return (*M);
    return F_cerca_nodo_grafo_matrice(M,valoreNodoDaTrovare,indicePartenza+1,numeroTotaleNodi);
}

int F_cerca_indice_grafo_matrice(MatrAdj *M, int valoreNodoDaTrovare, int indicePartenza, int numeroTotaleNodi){
    if(indicePartenza>=numeroTotaleNodi || F_struttura_vuota(*M)) return -1;
    if((*M)[indicePartenza].nodo==valoreNodoDaTrovare) return indicePartenza;
    return F_cerca_indice_grafo_matrice(M,valoreNodoDaTrovare,indicePartenza+1,numeroTotaleNodi);
}

void F_aggiungi_arco_grafo_matrice(GrafoMatrice *GM, int nodoPartenza, int nodoArrivo){
    int **matrice=(*GM)->matrice; MatrAdj M=(*GM)->strutturaPtr;

    int indicePartenza=F_cerca_indice_grafo_matrice(&M,nodoPartenza,0,(*GM)->numeroNodi);

    if(indicePartenza>=0){
        int indiceArrivo=F_cerca_indice_grafo_matrice(&M,nodoArrivo,0,(*GM)->numeroNodi);

        if(indiceArrivo>=0){
            F_inserisci_arco_grafo_matrice(matrice,indicePartenza,indiceArrivo);
        }else printf("Nodo (%d) di arrivo non e' presente nel grafo..\n",nodoArrivo);

    }else printf("Nodo (%d) di partenza non e' presente nel grafo..\n",nodoPartenza);
}

void F_inserisci_arco_grafo_matrice(int **M, int nodoPartenza, int nodoArrivo){
    M[nodoPartenza][nodoArrivo]=1;
}

void F_dealloca_struttura_grafo_matrice(GrafoMatrice GM){
    if(GM){
        int **matrice=GM->matrice;
        MatrAdj nodi=GM->strutturaPtr;

        if(!F_struttura_vuota(matrice))F_dealloca_matrice(matrice,GM->numeroNodi);
        if(!F_struttura_vuota(nodi)) free(nodi);
    }
}

void F_dealloca_matrice(int **matrice, int numeroNodi){
    int i=0;

    for (; i < numeroNodi; i++){
        int* currentIntPtr = matrice[i];
        free(currentIntPtr);
    }

}