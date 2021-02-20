#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Array.h"

void F_crea_array(int *array,int dim){
    srand(time(NULL));
    int i=1;
    for(i=1;i<=dim;i++){
        array[i]=F_genera_numero_casuale();
    }
}

int F_genera_numero_casuale(){
    return rand() % (100 + 1 - 0) + 0;
}