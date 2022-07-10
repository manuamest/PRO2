#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define MAX_BUFFER 255

#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef STATIC_LIST
#include "static_list.h"
#endif

/*
 *Objetivo: Añadir un nuevo elemento a la lista
 *Entradas: La lista, el nombre del producto, el vendedor, la categoria y el precio
 *Postcondiciones: La lista tiene un nuevo elemento
 */
void New(tList *L, char *product, char *seller, char *category, char *price) {
    tItemL productL;                                                                                               //Creamos el producto y le asignamos nombre, vendedor, categoria y precio
    strcpy(productL.productId, product);
    strcpy(productL.seller, seller);
    productL.bidCounter = 0;                                                                                       //Inicializamos el numero de pujas a 0
    if (strcmp(category, "book") == 0) {
        productL.productCategory = book;
    } else {
        productL.productCategory = painting;
    }
    productL.productPrice = atof(price);

    if (findItem(product, *L) == LNULL) {                                                                    //Si el elemento no esta en la lista devuelve error
        insertItem(productL, L);                                                                     //Introduce el producto en la lista de productos
        printf("* New: product %s seller %s category %s price %s\n", product, seller, category, price);
    }else{
        printf("+ Error: New not possible\n");
    }
}

/*Objetivo: Printear todos los elementos de la lista y una tabla con el total de cada categoria y el precio medio de esta
 *Entradas: La lista a printear
 */
void Stats(tList *L) {
    tItemL producto;
    tPosL pos;
    char categoria[9];
    int cntlibros = 0, cntcuadros = 0;                                                                           //Contadores de libros y cuadros
    float precioLibros = 0, precioPromedioLibros = 0;
    float precioCuadros = 0, precioPromedioCuadros = 0;

    if (isEmptyList(*L)) {                                                                                    //Comprueba si la lista esta vacia, en ese caso da error
        printf("+ Error: Stats not possible\n");
    } else {
        pos = first(*L);                                                                                      //Empezamos en el primer elemento de la lista
        while (pos != LNULL) {                                                                                   //Mientras la posicion no sea nula ejecuta
            producto = getItem(pos, *L);
            if (producto.productCategory == book) {
                precioLibros += producto.productPrice;
                strcpy(categoria, "book");
                cntlibros++;
            } else {
                precioCuadros += producto.productPrice;
                strcpy(categoria, "painting");
                cntcuadros++;
            }
            printf("Product %s seller %s category %s price %.2f bids %d\n",
                   producto.productId, producto.seller, categoria, producto.productPrice, producto.bidCounter);
            if (cntlibros != 0) {
                precioPromedioLibros = (float)precioLibros/(float)cntlibros;                                     //Calcula el precio promedio de los libros
            }else{
                precioPromedioLibros = 0;
            }
            if (cntcuadros != 0) {
                precioPromedioCuadros = (float)precioCuadros/(float)cntcuadros;                                  //Calcula el precio promedio de los cuadros
            }else{
                precioPromedioCuadros = 0;
            }
            pos = next(pos, *L);                                                                           //Pasa al siguiente elemento de la lista
        }                                                                                                        //Cuando acabe de recorrer la lista, imprime una tabla con los datos de esta
        printf("\nCategory  Products    Price  Average\n");
        printf("Book      %8d %8.2f %8.2f\n", cntlibros, precioLibros, precioPromedioLibros);
        printf("Painting  %8d %8.2f %8.2f\n", cntcuadros, precioCuadros, precioPromedioCuadros);
    }
}

/*
 *Objetivo: Pujar por un productor de la lista, cambiando su precio
 *Entradas: La lista, el producto y el precio
 *Postcondicion: El precio del elemento y el numero de pujas por este aumenta
 */
void Bid(tList *L, char *productId, char *seller ,char *price) {
    tItemL producto;
    tPosL pos;
    pos = findItem(productId, *L);                                                                         //Busca el elemento en la lista por su nombre
    char categoria[9];
    float precio = atof(price);
    if (pos == LNULL) {                                                                                         //Si el elemento no esta en la lista da error
        printf("+ Error: Bid not possible\n");
    }  else {
        producto = getItem(pos, *L);                                                                      //Asigna al producto los datos proporcionados
        if (producto.productPrice >= precio || (strcmp(producto.seller, seller) == 0)) {                        //Comprueba que el vendedor no sea el comprador y que el precio no sea menor o igual al original
            printf("+ Error: Bid not possible\n");
        } else {
            if (producto.productCategory == book) {
                strcpy(categoria, "book");
            } else {
                strcpy(categoria, "painting");
            }
            producto.productPrice = precio;                                                                     //Asigna el nuevo precio
            producto.bidCounter++;                                                                              //Aumenta en uno el contador de pujas del producto
            updateItem(producto, pos, L);
            printf("* Bid: product %s seller %s category %s price %.2f bids %d\n",
                   producto.productId, producto.seller, categoria, producto.productPrice, producto.bidCounter); //Imprime el resultado de pujar
        }
    }
}

/*
 *Objetivo: Eliminar un producto de la lista
 *Entradas: La lista y el elemento a eliminar
 *Postcondicion: El producto eliminado desaparece de la lista
 */
void Delete(tList *L, char *productId) {
    tItemL producto;
    tPosL pos;
    char categoria[9];
    pos = findItem(productId, *L);                                                                     //Busca el elemento en la lista, si no esta da error

    if (pos == LNULL) {
        printf("+ Error: Delete not possible\n");
    } else {
        producto = getItem(pos, *L);
        if (producto.productCategory == book) {
            strcpy(categoria, "book");
        } else {
            strcpy(categoria, "painting");
        }
        deleteAtPosition(pos, L);                                                                        //Elimina el elemento de la lista
        printf("* Delete: product %s seller %s category %s price %.2f bids %d\n",
               producto.productId, producto.seller, categoria, producto.productPrice, producto.bidCounter);
    }
}

/*
 *Objetivo: Realizar la operacion asignada a la letra que se le pasa
 *Entradas: El numero del comando, el comando y los atributos que corresponden a los datos asignados a la operacion
 */
void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4, tList *L) {
    printf("********************\n");
    switch (command) {                                                                                      //Elige la operacion correspondiente a la pasada y la ejecuta deacuerdo a la funcion que le corresponda
        case 'N':
            printf("%s %c: product %s seller %s category %s price %s\n", commandNumber, command, param1, param2, param3, param4);
            New(L, param1, param2, param3, param4);
            break;
        case 'S':
            printf("%s %c\n", commandNumber, command);
            Stats(L);
            break;
        case 'B':
            printf("%s %c: product %s bidder %s price %s\n", commandNumber, command, param1, param2, param3);
            Bid(L, param1, param2, param3);
            break;
        case 'D':
            printf("%s %c: product %s\n", commandNumber, command, param1);
            Delete(L, param1);
            break;
        default:
            break;
    }
}

/*
 *Objetivo: Leer las tareas de un fichero
 *Entrada: El nombre del fichero a leer
 */
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
