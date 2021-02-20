#include <stdio.h>
#include <stdlib.h>
#include "Degrees.h"
#include "ListaAdj.h"
#include "MatriceAdj.h"


void F_esegui_Degrees(){
    Grafo G=NULL;
    F_alloca_struttura_gestione_grafi(&G);
    F_costruisci_grafo_lista_adiacenza(&G);
    F_costruisci_grafo_matrice_adiacenza(&G);
    F_calcolo_grado_uscente_entrante_grafo_lista_adiacenza(&G);


    ListaAdj L=G->GrafoListaAdj;
    F_stampa_grafo_lista(&L);
    puts("\n\n");
    F_stampa_grafo_matrice(&G);
}

void F_calcolo_grado_uscente_entrante_grafo_lista_adiacenza(Grafo *G){
    ListaAdj L=(*G)->GrafoListaAdj;
    F_calcolo_grado_entrante_grafo_lista_adiacenza(G,&L);
    F_stampa_grado_entrante_grafo_lista_adiacenza((&(*G)->GradoPtr));

    (*G)->GradoPtr=NULL;

    F_calcolo_grado_uscente_grafo_lista_adiacenza(G,&L);

}


void F_calcolo_grado_uscente_grafo_lista_adiacenza(Grafo *G,ListaAdj *L){

}


void F_stampa_grado_entrante_grafo_lista_adiacenza(Grado *G){
    if(!F_struttura_vuota(*G)){
        printf("Il grado entrante del nodo (%d) e': (%d)\n",(*G)->nodo,(*G)->grado);
        F_stampa_grado_entrante_grafo_lista_adiacenza((&(*G)->nextPtr));
    }
}

void F_calcolo_grado_entrante_grafo_lista_adiacenza(Grafo *G,ListaAdj *L){
    if(!F_struttura_vuota(*L)){
        F_arco_lista_adiacenza(G,(&(*L)->arcoPtr));
        F_calcolo_grado_entrante_grafo_lista_adiacenza(G,(&(*L)->nextPtr));
    }
}

void F_arco_lista_adiacenza(Grafo *G,ListaAdj *L){
    if(!F_struttura_vuota(*L)){
        F_salva_valore_grado((&(*G)->GradoPtr),((*L)->nodo));
        F_arco_lista_adiacenza(G,(&(*L)->arcoPtr));
    }
}

void F_salva_valore_grado(Grado *Grado, int valoreDaSalvare){
    if(F_struttura_vuota(*Grado)){
       F_alloca_elemento_grado(Grado);
        (*Grado)->nodo=valoreDaSalvare;
        (*Grado)->grado++;
    } else{
        if((*Grado)->nodo==valoreDaSalvare) (*Grado)->grado++;
        else F_salva_valore_grado((&(*Grado)->nextPtr),valoreDaSalvare);
    }
}

void F_alloca_elemento_grado(Grado *Grado){
    (*Grado)=(struct struttura_gestione_grado*)malloc(sizeof(struct struttura_gestione_grado));
    (*Grado)->nodo=0;
    (*Grado)->grado=0;
    (*Grado)->nextPtr=NULL;
}

void F_costruisci_grafo_lista_adiacenza(Grafo *G){
    F_aggiungi_nodo_grafo_lista(G,4);
    F_aggiungi_nodo_grafo_lista(G,8);
    F_aggiungi_nodo_grafo_lista(G,2);
    F_aggiungi_nodo_grafo_lista(G,5);
    F_aggiungi_arco_grafo_lista(G,4,8);
    F_aggiungi_arco_grafo_lista(G,4,2);
    F_aggiungi_arco_grafo_lista(G,8,4);
    F_aggiungi_arco_grafo_lista(G,8,5);
    F_aggiungi_arco_grafo_lista(G,8,2);
    F_aggiungi_arco_grafo_lista(G,2,5);
    F_aggiungi_arco_grafo_lista(G,5,2);
    F_aggiungi_arco_grafo_lista(G,5,8);
    F_aggiungi_arco_grafo_lista(G,5,4);
}

void F_costruisci_grafo_matrice_adiacenza(Grafo *G){
    F_alloca_struttura_grafo_matrice(G);
    F_aggiungi_arco_grafo_matrice(G,0,3);
    F_aggiungi_arco_grafo_matrice(G,1,0);
    F_aggiungi_arco_grafo_matrice(G,1,2);
    F_aggiungi_arco_grafo_matrice(G,1,3);
    F_aggiungi_arco_grafo_matrice(G,3,0);
    F_aggiungi_arco_grafo_matrice(G,3,1);
}


void F_alloca_struttura_gestione_grafi(Grafo *G){
    (*G)=(struct struttura_gestione_grafi*)malloc(sizeof(struct struttura_gestione_grafi));
    if(F_struttura_vuota(*G)) exit(1);
    (*G)->numeroNodi=0;
    (*G)->GradoPtr=NULL;
    (*G)->GrafoListaAdj=NULL;
    (*G)->GrafoMatriceAdj=NULL;
}

int F_struttura_vuota(void *S){
    return (!S);
}