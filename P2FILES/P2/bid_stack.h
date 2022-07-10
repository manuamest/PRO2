/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Jose Manuel Amestoy Lopez LOGIN 1: manuel.amestoy@udc.es
 * AUTHOR 2: Xabier Dieguez Gomez LOGIN 2: xabier.diguezg@udc.es
 * GROUP: 4.1
 * DATE: 28 / 04 / 2022
 */

#ifndef BID_STACK_H
#define BID_STACK_H

#include <stdbool.h>
#include "types.h"
#include <string.h>

#define SNULL -1
#define SMAX 25

typedef struct tItemS {
    tUserId bidder;
    tProductPrice productPrice;
} tItemS;
typedef int tPosS;

typedef struct Stack {
    tItemS data[SMAX];
    tPosS top;
} tStack;

/*
 * Objetivo: Crear una pila vacia e inicializarla
 * Salida: La pila vacia de tipo tStack
 * Posconficion: La pila vacia
 */
void createEmptyStack(tStack *s);

/*
 * Objetivo: Mete un elemento en la cima de la pila
 * Entrada: El contenido del elemento a meter de tipo tItemS y la pila donde vamos a meter de tipo tStack
 * Salida: La pila con el elemento metido en la cima de la pila y true si lo metio, en caso contrario false
 */
bool push(tItemS d, tStack *s);

/*
 * Objetivo: Sacar el elemento de la cima de la pila
 * Entrada: La pila de donde vamos a sacar el elemento de tipo tStack
 * Salida: La pila sin el elemento en su cima
 * Precondicion: La pila no esta vacia
 */
void pop (tStack *s);

/*
 * Objetivo: Recuperar el elemento de la cima sin eliminarlo
 * Entrada: La pila de la que recuperar el elemento de tipo tStack
 * Salida: El contenido de la cima de la pila de tipo tItemS
 * Precondicion: La pila no esta vacia
 */
tItemS peek (tStack s);

/*
 * Objetivo: Determinar si una pila esta vacia o no
 * Entrada: La pila de tipo tStack
 * Salida: Verdadero si la lista esta vacia, falso en caso contrario
 */
bool isEmptyStack (tStack s);
#endif
