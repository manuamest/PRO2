/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Jose Manuel Amestoy Lopez LOGIN 1: manuel.amestoy@udc.es
 * AUTHOR 2: Xabier Dieguez Gomez LOGIN 2: xabier.diguezg@udc.es
 * GROUP: 4.1
 * DATE: 28 / 04 / 2022
 */


#ifndef PRODUCT_LIST_H
#define PRODUCT_LIST_H

#include "types.h"
#include "bid_stack.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//Definicion de tipos
#define LNULL NULL


typedef struct tItemL {
    tUserId seller;
    tProductId productId;
    tProductCategory productCategory;
    tProductPrice productPrice;
    tBidCounter bidCounter;
    tStack bidStack;
} tItemL;

typedef struct tNode * tPosL;
struct tNode{
    tItemL data;
    tPosL next;
};

typedef tPosL tList;

// Prototipos de funciones

/*Objetivo: Crea una lista vacia y la inicializa
Salida: La lista vacía de tipo tList
Precondición: La lista esta vacía
*/
void createEmptyList(tList* L);

/*Objetivo: Insertar un elemento en una lista ordenada
Entrada: El ItemL, o dato a insertar, la lista donde se insertará el item
Salida: Lista con el elemento
Precondición: La posicion es valida o nula
Poscondición: Las posiciones de los elementos de la lista posteriores a la del elemento a insertar pueden variar
*/
bool insertItem(tItemL d, tList* L);

/*Objetivo: Encontrar el primer elemento de una lista
Entrada: Lista a usar de tipo tList
Salida: La posicion del primer elemento de la lista
Precondición: La lista no esta vacia
*/
tPosL first(tList L);

/*Objetivo: Encontrar la posicion siguiente a la del elemento introducido
Entrada: La posicion del elemento tPosL y la lista de tipo tList
Salida: La posicion del siguiente elemento o nulo si es el ultimo
Precondición:  Posicion valida de la lista
*/
tPosL next(tPosL p, tList L);

/*Objetivo: Encontrar el ultimo elemento de una lista
Entrada: Lista a usar de tipo tList
Salida: La posicion del ultimo elemento de la lista
Precondición: La lista no esta vacia
*/
tPosL last(tList L);

/*Objetivo: Encontrar La posicion previa a la del elemento introducido
Entrada: La posicion del elemento tPosL y la lista tList
Salida: La posicion previa a la introducida o nulo si es el primero
Precondición: Posicion valida de la lista
*/
tPosL previous(tPosL p, tList L);

/*Objetivo: Comprueba si la lista esta vacia
Entrada: La lista tList a comprobar
Salida: True si la lista esta vacia, si no false
*/
bool isEmptyList(tList L);

/*Objetivo: Obtiene el contenido de un elemento de la lista
Entrada: La posicion del elemento tPosL y la lista tList en la que esta
Salida: El elemento deseado
Precondición: Posicion valida en la lista
*/
tItemL getItem(tPosL p, tList L);

/*Objetivo: Encontrar el primer elemento con cierto nombre en la lista
Entrada: El nombre tProductId y la lista tList
Salida: La posicion del elemento con ese nombre o una posicion nula
*/
tPosL findItem(tProductId d, tList L);

/*Objetivo: Modificar un elemento de la lista
Entrada: El nuevo dato a asignar tItemL, la posicion tPosL para ese dato, la lista tList en la que se va a cambiar el dato
Salida: La nueva lista con el dato dado
Precondición: La posición es válida en la lista
*/
void updateItem(tItemL d, tPosL p, tList* L);

/*Objetivo: Eliminar un elemento en una posicion dada
Entrada: La posicion del elemento tPosL a eliminar y la lista tList de este
Salida: La lista sin el elemento de esa posicion
Precondición: La posicion es valida en la lista y el producto tiene una pila de pujas vacia
Poscondición: Las posiciones posteriores a la del elemento eliminado puden haber variado
*/
void deleteAtPosition(tPosL p, tList* L);
void borrarUltimo (tList *L);
#endif



