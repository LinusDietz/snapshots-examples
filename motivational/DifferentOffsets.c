#include <stdlib.h>
#include <stdio.h>


typedef struct ListElem {
    int payload;
    struct ListElem *next;
    struct ListElem *prev;
} ListElem;


typedef struct ListHead {
    char headPayload;
    struct ListElem elem;
} ListHead;


ListHead *init_list(char outerPayLoad, unsigned int elemPayload) {
    ListHead *root = (ListHead *) malloc(sizeof(ListHead));
    root->headPayload = outerPayLoad;
    root->elem.payload = elemPayload;
    root->elem.next = 0;
    root->elem.prev = 0;
    return root;
}

void append(ListHead *l, unsigned int payload) {
    ListElem *tail = &l->elem;
    while (tail->next != 0) {
        tail = tail->next;
    }

    ListElem *newElement = (ListElem *) malloc(sizeof(ListElem));
    newElement->next = 0;
    newElement->prev = tail;
    tail->next = newElement;

    newElement->payload = payload;
}

unsigned int list_size(ListHead *l) {
    unsigned int size = 1;

    ListElem *tail = &l->elem;
    if (tail->next == 0) {
        return 1;
    }
    while (tail->next != 0) {
        tail = tail->next;
        size++;
    }

    return size;
}

void traverse(ListHead *head) {
    printf("Traversing the list '%c'; length is %d.\nNodes: [%d", head->headPayload, list_size(head),
           head->elem.payload);
    ListElem *element = &head->elem;
    while (element->next != 0) {
        element = element->next;
        printf(", %d", element->payload);
    }
    printf("]\n");
}

int main() {

    ListHead *root = init_list('a', 1);

    printf("Size of head payload: %d bytes\n", sizeof(root->headPayload));
    printf("Size of elem payload: %d bytes\n", sizeof(root->elem.payload));

    append(root, 2);
    traverse(root);
    return 0;
}