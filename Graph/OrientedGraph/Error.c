#include <stdio.h>
#include <stdlib.h>
#include "Error.h"

void F_error(int e){
    printf("\nERRORE:");
    switch(e){
        default:
            puts(" errore generico.");
            break;
        case 1:
            puts(" errore allocazione struttura principale grafo.");
            break;
        case 2:
            puts(" errore allocazione intero");
            break;
        case 3:
            puts(" errore allocazione nodo grafo.");
            break;
        case 4:
            puts(" errore allocazione colore.");
            break;
        case 5:
            puts(" errore allocazione matrice.");
            break;
        case 6:
            puts(" errore allocazione vettore nodi matrice.");
            break;
    }
    exit(e);
}
