/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Jose Manuel Amestoy Lopez LOGIN 1: manuel.amestoy@udc.es
 * AUTHOR 2: Xabier Dieguez Gomez LOGIN 2: xabier.diguezg@udc.es
 * GROUP: 4.1
 * DATE: 28 / 04 / 2022
 */

#include "product_list.h"



/*Codigo*/

void createEmptyList (tList* L){
    *L = LNULL;                                                 //Crea una lista usando la variable que defina a esta como un puntero a nulo
}

bool insertItem(tItemL i, tList * L){
    tPosL q = malloc(sizeof(struct tNode)), s = malloc(sizeof(struct tNode));

    if (q == LNULL) {
        return false;
    } else {
        q->data = i; //Actualiza q
        q->next = LNULL;
        if (*L == LNULL) //Verifica que la lista está vacía
            *L = q;
        else if (strcmp(i.productId, (*L)->data.productId) < 0) { //Inserta al final de la lista
            q->next = *L;
            *L = q;
        } else {
            if (s == LNULL) { //Inserta en el principio de la lista
                return false;
            } else { //Inserta en una posición intermedia de la lista
                s = *L;
                while (s->next != NULL && strcmp(i.productId, s->next->data.productId) > 0){
                    s = s->next;
                }
                q ->next = s->next;
                s->next = q;
            }
            return true;
        }
    }
}

tPosL first(tList L){
    return L;                                       //Devuelve el primer elemento de la lista que corresponde a la variable apuntada por la lista
}

tPosL next(tPosL p, tList L){
    return p->next;                                 //Usando el campo next devuelve el siguiente elemento al dado
}

tPosL last(tList L){
    tPosL p;                                        //Variable para determinar la posicion del ultimo elemento de la lista

    for(p=L; p->next != LNULL ; p=p->next);         //Recorre la lista hasta no encontrar mas elementos y devuelve el ultimo que encontro
    return p;
}

tPosL previous(tPosL p, tList L){
    tPosL q;                                        //Variable para determinar la posicion del anterior elemento al dado

    if(p==L)                                        //Si la posicion correponde al primer elemento de la lista devuelve nulo
        return LNULL;
    else{
        for(q=L; q->next != p ; q = q->next);       //Recorre la lista buscando el elemento dado y devuelve la posicion del elemento al que le corresponde el mismo next con el elemento que damos
        return q;
    }
}

bool isEmptyList(tList L){
    return L == LNULL;                              //Comprueba si el primer elemento de la lista es nulo para determinar si esta vacia
}

tItemL getItem(tPosL p, tList L){
    return p->data;                                 //Devuelve el elemento de la posicion dada
}

tPosL findItem (tProductId d, tList L){
    tPosL p;                                        //Variable para determinar la posicion del elemento dado en la lista

    for (p = L ; (p != LNULL) && (strcmp(p->data.productId, d) != 0); p = p ->next);    //Recorre la lista comparando cada elemento con el dado
    return p;
}

void updateItem(tItemL d, tPosL p, tList*L){
    p->data = d;                                    //Cambia el elemento de la posicion dada con el elemento dado en la cabecera
}

void deleteAtPosition(tPosL p, tList* L) {
    tPosL q;                                        //Variable auxiliar que usaremos para recorrer la lista
    if (p == *L) {                                     //Si la posicion coincide con el primer elemento de la lisa elimina el siguiente
        *L = (*L)->next;
    } else if (p->next == LNULL) {                      //Si el siguiente elemento no tiene continuidad entra en el if
        for (q = *L; q->next != p; q = q->next);       //Recorre la lista en busca de la posicion dada
        q->next = LNULL;                            //Elimina el elemento de la posicion dada a trave de su anterior elemento
    } else {
        q = p->next;                                //Intercambia los elementos p q para asi borrar q y luego p
        p->data = q->data;
        p->next = q->next;
        p = q;
    }
    free(p);
}
void borrarUltimo(tList *L) {
    tPosL p;
    if (*L != NULL) {
        if ((*L)->next == NULL) {
            *L = NULL;
            free(*L);
        } else {
            p = *L;
            while (p->next->next != NULL) {
                p = p->next;
            }
            p->next = NULL;
            free(p->next);
        }
    }
}

void RotaAtras (tList *L) {//Primer fallo
    tPosL temp, ini, prev;

    if (*L != NULL) {//Segundo fallo
        if ((*L)->next != NULL) {
            temp = *L;
            while (temp->next->next != NULL)
                temp = temp->next;
            ini = (*L)->next;
            temp->next->next = *L;
            (*L) -> prev = temp->next;//Ultimo elemento previo del ex ultimo
            (*L) ->next = NULL;//Primer elemento nuevo ultimo, no tiene siguiente
            (*L) = ini;//Nuevo primero
        }
    }
}