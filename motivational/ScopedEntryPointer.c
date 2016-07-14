#include <stdlib.h>
#include <stdio.h>

typedef struct DLL {
    int payload;

    struct DLL *next;
    struct DLL *previous;
} DLL;

DLL *create_list(int payload) {
    DLL *list = (DLL *) malloc(sizeof(DLL));
    list->next = NULL;
    list->previous = NULL;
    list->payload = payload;
    return list;
}


void append(DLL *l, unsigned int payload) {
    DLL *tail = l;
    while (tail->next != NULL) {
        tail = tail->next;
    }

    DLL *newElement = (DLL *) malloc(sizeof(DLL));
    newElement->next = NULL;
    newElement->previous = tail;
    tail->next = newElement;

    newElement->payload = payload;
}

unsigned int list_size(DLL *list) {
    unsigned int size = 1;

    DLL *tail = list;
    if (tail->next == NULL) {
        return 1;
    }
    while (tail->next != NULL) {
        tail = tail->next;
        size++;
    }

    return size;
}

void traverse(DLL *list) {
    printf("Traversing a DLL with length %d.\nNodes: [%d", list_size(list),  list->payload);
    DLL *element = list;
    while (element->next != NULL) {
        element = element->next;
        printf(", %d", element->payload);
    }
    printf("]\n");
}

int main() {

    DLL *alive = NULL;
    DLL *killed = create_list(1);
    append(killed, 2);
    append(killed, 3);
    traverse(killed);
    alive = killed;
    killed = NULL;

    append(alive, 4);
    append(alive, 5);
    append(alive, 6);
    traverse(alive);

    return 0;
}