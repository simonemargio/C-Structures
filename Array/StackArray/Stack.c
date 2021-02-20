#include <stdio.h>
#include "Array.h"
#include "Stack.h"
#define NUMERO_ELEMENTI_STACK 10
#define ELEMENTO_VUOTO -1

void F_start_libreria_stack(){
    int S[NUMERO_ELEMENTI_STACK+1], scelta=0, uscitaMenu=0,nuovoElemento=0;

    F_crea_array(S,NUMERO_ELEMENTI_STACK);
    F_setta_cella_iniziale_stack(S,NUMERO_ELEMENTI_STACK);

   do{
       scelta=F_stampa_menu_stack();
       switch(scelta){
           case 0:
               uscitaMenu=-1;
               break;
           case 1:
               F_stampa_stack(S,NUMERO_ELEMENTI_STACK);
               break;
           case 2:
               if(!F_full_stack(S)){
                   nuovoElemento=F_chiedi_nuovo_elemento();
                   F_push(S,nuovoElemento);
               }else puts("\nStack pieno!");
               break;
           case 3:
               if(!F_empty_stack(S)){
                   nuovoElemento=F_pop(S);
                   F_elimina_elemento_stack(S);
                   printf("\nElemento in cima allo stack:|%d|\n",nuovoElemento);
               }else puts("\nStack vuoto!");
               break;
           case 4:
               if(!F_empty_stack(S)){
                   nuovoElemento=F_chiedi_nuovo_elemento();
                   F_togli_da_stack(S,nuovoElemento);
               }else  puts("\nStack vuoto!");
               break;
           default:
               puts("Scelta non valida!");
       }
       puts("\n");
   }while(uscitaMenu!=-1);
}

void F_togli_da_stack(int *S,int nuovoElemento){
    if(F_empty_stack(S)) return;
    else{
       int elementoArray=F_pop(S);
       if(elementoArray==nuovoElemento) F_elimina_elemento_stack(S);
       F_togli_da_stack(S,nuovoElemento);
    }
}

void F_push(int *S,int elemento){
    if(!F_full_stack(S)){
        S[0]=S[0]+1;
        S[S[0]]=elemento;
    }
}

int F_pop(int *S){
    if(!F_empty_stack(S)){
        S[0]=S[0]-1;
        return S[S[0]+1];
    }
}

int F_empty_stack(int *S){
    return S[0]==0;
}

int F_full_stack(int *S){
    return S[0]==NUMERO_ELEMENTI_STACK;
}

void F_elimina_elemento_stack(int *S){
    S[S[0]+1]=ELEMENTO_VUOTO;
}


int F_chiedi_nuovo_elemento(){
    int elemento=0;
    printf("Inserisci l'elemento da inserire nello stack:");
    scanf("%d",&elemento);
    return elemento;
}

void F_setta_cella_iniziale_stack(int *S,int dim){
    S[0]=dim;
}

int F_stampa_menu_stack(){
    int scelta=0;
    puts("1] Stampa Stack");
    puts("2] Inserisci elemento (Push)");
    puts("3] Cancella elemento in testa (Pop)");
    puts("4] Togli elemento da stack mantenendo l'ordine");
    puts("\n0] Esci");
    printf("Inserisci scelta:");
    scanf("%d",&scelta);
    puts("\n");
    return scelta;
}

void F_stampa_stack(int *S, int dim){
    int i=1;
    puts("Stampa dello stack");
    for(i=1;i<=dim;i++){
        printf("|%d|",S[i]);
    }
}