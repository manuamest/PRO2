/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Jose Manuel Amestoy Lopez LOGIN 1: manuel.amestoy@udc.es
 * AUTHOR 2: Xabier Dieguez Gomez LOGIN 2: xabier.diguezg@udc.es
 * GROUP: 4.1
 * DATE: 28 / 04 / 2022
 */

#ifndef PRO2_2022_P2_TYPES_H
#define PRO2_2022_P2_TYPES_H


#define NAME_LENGTH_LIMIT 10


typedef char tUserId[NAME_LENGTH_LIMIT];

typedef char tProductId[NAME_LENGTH_LIMIT];

typedef enum {book, painting} tProductCategory;

typedef float tProductPrice;

typedef int tBidCounter;


#endif //PRO2_2022_P2_TYPES_H
