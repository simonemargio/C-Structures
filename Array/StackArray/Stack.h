#ifndef STACKARRAY_STACK_H
#define STACKARRAY_STACK_H

void F_start_libreria_stack();
void F_setta_cella_iniziale_stack(int *S,int dim);
int F_stampa_menu_stack();
void F_stampa_stack(int *S, int dim);
void F_push(int *S,int elemento);
int F_pop(int *S);
void F_elimina_elemento_stack(int *S);
int F_empty_stack(int *S);
int F_full_stack(int *S);
int F_chiedi_nuovo_elemento();
void F_togli_da_stack(int *S,int nuovoElemento);

#endif //STACKARRAY_STACK_H
