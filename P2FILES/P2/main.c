/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Jose Manuel Amestoy Lopez LOGIN 1: manuel.amestoy@udc.es
 * AUTHOR 2: Xabier Dieguez Gomez LOGIN 2: xabier.diguezg@udc.es
 * GROUP: 4.1
 * DATE: 28 / 04 / 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "product_list.h"
#include "bid_stack.h"

#define MAX_BUFFER 255

/*
 * Objetivo: Transformar la categoria de un producto en un string para poder imprimirla
 * Entradas:
 * tIteml: El producto
 * Precondiciones: El producto existe y tiene una categoria asignada
 * Salida: Un string para representa la categoria del producto
 */
char * Categoria(tItemL producto) {
    if (producto.productCategory == book)
        return "book";
    return "painting";
}

/*
 * Objetivo: Añadir un nuevo elemento a la lista de tipo tList
 * Entradas:
 *          tList: La lista en la que se va a almacenar el producto
 *          tProductId: Nombre del producto
 *          tUserId: El vendedor del producto
 *          tProductCategory: La categoria del producto
 *          tProductPrice: El precio del producto
 * Postcondiciones: La lista tiene un nuevo elemento en su ultima posicion
 */
void New(tList *L, tProductId product, tUserId seller, tProductCategory category, tProductPrice price) {
    if (findItem(product, *L) == LNULL) {                                                       //Si el elemento no esta en la lista devuelve error
        tItemL productL;                                                                              //Creamos el producto y le asignamos nombre, vendedor, categoria y precio
        tStack pila;
        strcpy(productL.productId, product);
        strcpy(productL.seller, seller);
        productL.productCategory = category;
        productL.productPrice = price;
        productL.bidCounter = 0;                                                                     //Inicializamos el numero de pujas a 0
        createEmptyStack(&pila);
        productL.bidStack = pila;
        if (insertItem(productL, L)) {                                                                     //Introduce el producto en la lista de productos
            printf("* New: product %s seller %s category %s price %.2f\n", product, seller, Categoria(productL), price);
        }else{
            printf("+ Error: New not possible\n");
        }
    }else{
        printf("+ Error: New not possible\n");
    }
}
/*
 * Objetivo: Printear todos los elementos de la lista y una tabla con el total de cada categoria y el precio medio de esta
 * Entradas:
 *          tList: La lista a printear
 * Salida: Una tabla con la informacion total de la lista en la que se recopila la cantidad de cada producto y se calcula el producto con el precio mas incrementado
 */
void Stats(tList L) {
    if (isEmptyList(L)) {                                                                                    //Comprueba si la lista esta vacia, en ese caso da error
        printf("+ Error: Stats not possible\n");
    } else {
        tItemL producto, tItemIncremented;
        tPosL pos;
        int cntlibros = 0, cntcuadros = 0, cntbids = 0;                                                                //Contadores de libros y cuadros
        float precioLibros = 0, precioPromedioLibros = 0;
        float precioCuadros = 0, precioPromedioCuadros = 0;
        pos = first(L);                                                                                         //Empezamos en el primer elemento de la lista
        tItemIncremented = getItem(pos, L);
        while (pos != LNULL) {                                                                                   //Mientras la posicion no sea nula ejecuta
            producto = getItem(pos, L);
            if (producto.productCategory == book) {
                precioLibros += producto.productPrice;
                cntlibros++;
            } else {
                precioCuadros += producto.productPrice;
                cntcuadros++;
            }
            if (producto.bidCounter == 0) {
                printf("Product %s seller %s category %s price %.2f. No bids\n",
                       producto.productId, producto.seller, Categoria(producto), producto.productPrice);
            } else {
                printf("Product %s seller %s category %s price %.2f bids %d top bidder %s\n",
                       producto.productId, producto.seller, Categoria(producto), producto.productPrice, producto.bidCounter, peek(producto.bidStack).bidder);
                cntbids++;
                if (peek(producto.bidStack).productPrice/producto.productPrice > peek(tItemIncremented.bidStack).productPrice/tItemIncremented.productPrice){
                    tItemIncremented = producto;
                }
            }
            cntlibros != 0 ? (precioPromedioLibros = (float)precioLibros/(float)cntlibros) : (precioPromedioLibros = 0);
            cntcuadros != 0 ? (precioPromedioCuadros = (float)precioCuadros/(float)cntcuadros) : (precioPromedioCuadros = 0);
            pos = next(pos, L);                                                                           //Pasa al siguiente elemento de la lista
        }                                                                                                        //Cuando acabe de recorrer la lista, imprime una tabla con los datos de esta
        printf("\nCategory  Products    Price  Average\n");
        printf("Book      %8d %8.2f %8.2f\n", cntlibros, precioLibros, precioPromedioLibros);
        printf("Painting  %8d %8.2f %8.2f\n", cntcuadros, precioCuadros, precioPromedioCuadros);
        if (cntbids == 0) {
            printf("Top bid not possible\n");
        } else {
            printf("Top bid: Product %s seller %s category %s price %.2f bidder %s top price %.2f increase %.2f%%\n",
                   tItemIncremented.productId, tItemIncremented.seller, Categoria(tItemIncremented),tItemIncremented.productPrice, peek(tItemIncremented.bidStack).bidder, peek(tItemIncremented.bidStack).productPrice,
                   (peek(tItemIncremented.bidStack).productPrice/tItemIncremented.productPrice-1)*100);
        }
    }
}

/*
 *Objetivo: Pujar por un productor de la lista, cambiando su precio
 *Entradas:
 *          tList: La lista en la que esta el producto a pujar
 *          tProductId: El nombre del producto
 *          tUserId: El nombre del usuario que puja
 *          tProductPrice: El precio por el que se puja
 *Postcondicion: El precio del elemento y el numero de pujas por este aumenta
 */
void Bid(tList *L, tProductId productId, tUserId bidder ,tProductPrice price) {
    tPosL pos = findItem(productId, *L);
    if (pos == LNULL) {                                                                                         //Si el elemento no esta en la lista da error
        printf("+ Error: Bid not possible\n");
    }  else {
        tItemL producto;
        tItemS p;                                                                                               //Busca el elemento en la lista por su nombre
        float precio = price;
        producto = getItem(pos, *L);                                                                      //Asigna al producto los datos proporcionados
        if (producto.productPrice >= precio || (strcmp(producto.seller, bidder) == 0)) {                        //Comprueba que el vendedor no sea el comprador y que el precio no sea menor o igual al original
            printf("+ Error: Bid not possible\n");
        } else {
            strcpy(p.bidder, bidder);
            p.productPrice = price;
            push(p, &producto.bidStack);
            producto.bidCounter++;                                                                              //Aumenta en uno el contador de pujas del producto
            updateItem(producto, pos, L);
            printf("* Bid: product %s bidder %s category %s price %.2f bids  %d\n",
                   producto.productId, peek(producto.bidStack).bidder, Categoria(producto), peek(producto.bidStack).productPrice, producto.bidCounter); //Imprime el resultado de pujar
        }
    }
}

/*
 *Objetivo: Eliminar un producto de la lista
 *Entradas:
 *          tList: La lista en la que se quiere borrar un producto
 *          tProductId: El nombre del producto a eliminar
 *          bool: Booleano para imprimir la operacion del delete, se usa para aprovechar el delete en remove
 *Postcondicion: El producto eliminado desaparece de la lista
 */
void Delete(tList *L, tProductId productId, bool printDelete) {
    tPosL pos = findItem(productId,*L);                                                                     //Busca el elemento en la lista, si no esta da error
    if (pos == LNULL) {
        printf("+ Error: Delete not possible\n");
    } else {
        tItemL producto;
        producto = getItem(pos, *L);
        while (!isEmptyStack(producto.bidStack)) {
            pop(&producto.bidStack);
        }
        deleteAtPosition(pos, L);                                                                        //Elimina el elemento de la lista
        if (printDelete) {
            printf("* Delete: product %s seller %s category %s price %.2f bids %d\n",
                   producto.productId, producto.seller, Categoria(producto), producto.productPrice, producto.bidCounter);
        }
    }
}

/*
 * Objetivo: Buscar el ganador de una puja y eliminarlo de la lista
 * Entradas:
 *          tList: La lista en la que esta el producto
 *          tProductId: El nombre del producto
 * Salida: La lista sin el elemento
 */
void Award(tList *L, tProductId productId) {
    tPosL pos = findItem(productId, *L);
    if (pos == LNULL) {
        printf("+ Error: Award not possible\n");
    } else {
        tItemL producto;
        producto = getItem(pos, *L);
        if (isEmptyStack(producto.bidStack)) {
            printf("+ Error: Award not possible\n");
        } else {
            printf("* Award: product %s bidder %s category %s price %.2f\n",
                   producto.productId, peek(producto.bidStack).bidder, Categoria(producto), peek(producto.bidStack).productPrice);
            Delete(L, productId, false);
        }
    }
}

/*
 * Objetivo: Eliminar la mejor puja actual del producto introducido
 * Entradas:
 *          tList: La lista en la que esta el producto
 *          tProductId: El nombre del producto del que se quiere eliminar la mejor puja actual
 *          tUserId: El nombre del usuario que va a hacer withdraw
 * Salida: La pila del elemento introducido pierde el elemento de su cima y el contador de pujas de la pila se decrementa
 */
void Withdraw(tList *L, tProductId productId, tUserId userId) {
    tPosL pos = findItem(productId, *L);
    if (pos == LNULL) {
        printf("+ Error: Withdraw not possible\n");
    } else {
        tItemL producto;
        producto = getItem(pos, *L);
        if ((isEmptyStack(producto.bidStack)) || strcmp(userId, peek(producto.bidStack).bidder) != 0) {
            printf("+ Error: Withdraw not possible\n");
        } else {
            printf("* Withdraw: product %s bidder %s category %s price %.2f bids  %d\n",
                   producto.productId, peek(producto.bidStack).bidder, Categoria(producto), peek(producto.bidStack).productPrice,
                   producto.bidCounter);
            pop(&producto.bidStack);
            producto.bidCounter--;
            updateItem(producto, pos, L);
        }
    }
}

/*
 * Objetivo: Eliminar de la lista los elementos que no tengan pujas
 * Entrada:
 *          tList: La lista de la que se quieren eliminar los elementos que no tengan pujas
 * Salida: La lista sin los productos que tengan 0 pujas
 * Precondicion: La lista no esta vacia
 */
void Remove (tList *L) {
    tItemL producto;
    tPosL pos = first(*L);
    int cnt = 0;
    while (pos != LNULL) {
        producto = getItem(pos, *L);
        if (isEmptyStack(producto.bidStack)) {
            printf("Removing product %s seller %s category %s price %.2f bids %d\n",
                   producto.productId, producto.seller, Categoria(producto), producto.productPrice, producto.bidCounter);
            Delete(L, producto.productId, false);
            cnt++;
        }
        pos = next(pos, *L);
    }
    if (cnt == 0) {
        printf("+ Error: Remove not possible\n");
    }
}

float averageBids(tList L) {
    tPosL pos = first(L);
    tItemL product;
    float avg, n = 1, bids = 0;
    while (pos != NULL) {
        product = getItem(pos, L);
        bids += (float) product.bidCounter;
        pos = next(pos, L);
        n++;
    }
    avg = bids/n;
    return avg;
}

void InvalidateBids (tList *L) {
    if (isEmptyList(*L)) {
        printf("+ Error: InvalidateBids not possible\n");
    } else {
        tItemL producto;
        tPosL pos = first(*L);
        float avg = averageBids(*L);
        int productsInvalidated = 0;
        while (pos != NULL) {
            producto = getItem(pos, *L);
            if ((float)producto.bidCounter >= (avg+2)) {
                printf("Removing product %s seller %s category %s price %.2f bids %d average bids %f\n",
                       producto.productId, producto.seller, Categoria(producto), producto.productPrice, producto.bidCounter, avg);
                productsInvalidated++;
                while (!isEmptyStack(producto.bidStack)) {
                    pop(&producto.bidStack);
                }
            }
            pos = next(pos, *L);
        }
        if (productsInvalidated == 0) {
            printf("+ Error: InvalidateBids not possible\n");
        }
    }
}
void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4, tList *L) {
    printf("********************\n");
    switch (command) {
        case 'N':
            printf("%s %c: product %s seller %s category %s price %s\n", commandNumber, command, param1, param2, param3, param4);
            strcmp(param3, "book") ? New(L, param1, param2, painting, atof(param4)) :
                                     New(L, param1, param2, book, atof(param4));
            break;
        case 'S':
            printf("%s %c\n", commandNumber, command);
            Stats(*L);
            break;
        case 'B':
            printf("%s %c: product %s bidder %s price %s\n", commandNumber, command, param1, param2, param3);
            Bid(L, param1, param2, atof(param3));
            break;
        case 'D':
            printf("%s %c: product %s\n", commandNumber, command, param1);
            Delete(L, param1, true);
            break;
        case 'A':
            printf("%s %c: product %s\n", commandNumber, command, param1);
            Award(L, param1);
            break;
        case 'W':
            printf("%s %c: product %s bidder %s\n", commandNumber, command, param1, param2);
            Withdraw(L, param1, param2);
            break;
        case 'R':
            printf("%s %c\n", commandNumber, command);
            Remove(L);
            break;
        case 'I':
            printf("%s %c\n", commandNumber, command);
            InvalidateBids(L);
        default:
            break;
    }
}

void readTasks(char *filename) {
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3, *param4;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];
    tList L;
    createEmptyList(&L);

    f = fopen(filename, "r");

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);
            param4 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, param3, param4, &L);
        }
        fclose(f);
    } else {
        printf("Cannot open file %s.\n", filename);
    }
}

int main(int nargs, char **args) {

    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
        file_name = INPUT_FILE;
        #endif
    }

    readTasks(file_name);

    return 0;
}