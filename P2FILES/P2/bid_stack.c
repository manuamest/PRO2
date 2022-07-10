/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Jose Manuel Amestoy Lopez LOGIN 1: manuel.amestoy@udc.es
 * AUTHOR 2: Xabier Dieguez Gomez LOGIN 2: xabier.diguezg@udc.es
 * GROUP: 4.1
 * DATE: 28 / 04 / 2022
 */

#include "bid_stack.h"

void createEmptyStack(tStack *s) {
    s->top = SNULL;
}

bool push(tItemS d, tStack *s) {
    if (s->top == SMAX - 1) {
        return false;
    } else {
        s->top++;
        s->data[s->top] = d;
    }
    return true;
}

void pop (tStack *s) {
    s->top--;
}

tItemS peek (tStack s) {
    return s.data[s.top];
}
bool isEmptyStack (tStack s) {
    return (s.top == SNULL);
}
