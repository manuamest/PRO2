#include <stdbool.h>
#include "types.h"
/* Types definition */

#define LNULL NULL

typedef struct tNode* tPosL;  //Ptr to tNode

struct tNode {

    tItemL data;
    tPosL next;

};

typedef tPosL tList;

/* Function prototypes */

void createEmptyList(tList *L);
bool createNode(tPosL* p);
tPosL findPosition(tList L, tItemL d);
bool insertItem(tItemL d, tList *L);
void updateItem(tItemL d, tPosL p, tList* L);
tPosL findItem(tProductId d,tList L);
bool isEmptyList(tList L);
tItemL getItem(tPosL p, tList L);
tPosL first(tList L);
tPosL last(tList L);
tPosL previous(tPosL p, tList L);
tPosL next(tPosL p,tList L);
void deleteAtPosition(tPosL p , tList *L);
void deleteList(tList *L);
