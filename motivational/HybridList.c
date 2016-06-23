#include <stdlib.h>
#include <stdio.h>


typedef struct HybridList {
    struct HybridList *sll_next;
    struct HybridList *dll_next;
    struct HybridList *dll_prev;
    int payload;

} HybridList;

void dll_append(HybridList *l, unsigned int payload);

void sll_append(HybridList *l, unsigned int payload);

HybridList *sll_get(HybridList *l, unsigned int index);

HybridList *dll_get(HybridList *l, unsigned int index);

int sll_list_size(HybridList *l);

int dll_list_size(HybridList *l);


int sll_list_size(HybridList *l) {
    unsigned int size = 1;

    HybridList *tail = l;
    while (tail->sll_next != 0) {
        tail = tail->sll_next;
        size++;
    }

    return size;
}

void sll_append(HybridList *l, unsigned int payload) {
    HybridList *tail = l;
    while (tail->sll_next != 0) {
        tail = tail->sll_next;
    }

    HybridList *newElement = (HybridList *) malloc(sizeof(HybridList));
    newElement->sll_next = 0;
    tail->sll_next = newElement;

    newElement->dll_next = 0;
    newElement->dll_prev = 0;

    newElement->payload = payload;

}

HybridList *sll_get(HybridList *l, unsigned int index) {

    if (sll_list_size(l) <= index) {
        return 0;
    }

    HybridList *element = l;
    while (index != 0) {
        element = element->sll_next;
        index--;
    }
    return element;
}


int dll_list_size(HybridList *l) {
    unsigned int size = 1;

    HybridList *tail = l;
    if (tail->dll_next == 0) {
        return 0;
    }
    while (tail->dll_next != 0) {
        tail = tail->dll_next;
        size++;
    }

    return size;
}

void dll_append(HybridList *l, unsigned int payload) {
    HybridList *tail = l;
    while (tail->dll_next != 0) {
        tail = tail->dll_next;
    }

    HybridList *newElement = (HybridList *) malloc(sizeof(HybridList));
    newElement->sll_next = 0;
    newElement->dll_next = 0;
    newElement->dll_prev = tail;
    tail->dll_next = newElement;

    newElement->payload = payload;

}

HybridList *dll_get(HybridList *l, unsigned int index) {

    if (dll_list_size(l) <= index) {
        return 0;
    }

    HybridList *element = l;
    for (unsigned int remaining = index; remaining == 0; remaining--) {
        element = element->dll_next;
    }
    return element;
}

HybridList *create_list(int payload) {
    HybridList *list = (HybridList *) malloc(sizeof(HybridList));
    list->sll_next = 0;
    list->dll_next = 0;
    list->dll_prev = 0;
    list->payload = payload;
    return list;
}


void traverse_sll(HybridList *element) {
    printf("Traversing the SLL beginning with node %d:\n", element->payload);
    printf("Nodes (%d): [%d", sll_list_size(element), element->payload);
    while (element->sll_next != 0) {
        element = element->sll_next;
        printf(", %d", element->payload);
    }
    printf("]\n");
}


void traverse_dll_forward(HybridList *element) {
    printf("Traversing the DLL forwards beginning with node %d:\n", element->payload);
    printf("Nodes (%d): [%d", dll_list_size(element), element->payload);

    while (element->dll_next != 0) {
        element = element->dll_next;
        printf(", %d", element->payload);
    }
    printf("]\n");
}

void traverse_dll_backward(HybridList *element) {
    printf("Traversing backwards the DLL beginning with node %d:\n", element->payload);
    printf("Nodes: [%d", element->payload);
    while (element->dll_prev != 0) {
        element = element->dll_prev;
        printf(", %d", element->payload);
    }
    printf("]\n");
}


int main() {

    HybridList *root = create_list(11);
    sll_append(root, 21);
    sll_append(root, 31);
    sll_append(root, 41);
    traverse_sll(root);
    printf("SLL index 2: %d\n", sll_get(root, 2)->payload);

    dll_append(root, 12);
    dll_append(root, 13);
    dll_append(root, 14);
    traverse_dll_forward(root);


    HybridList *thirdDLL = sll_get(root, 2);
    dll_append(thirdDLL, 32);
    dll_append(thirdDLL, 33);
    dll_append(thirdDLL, 34);
    dll_append(thirdDLL, 35);
    traverse_dll_forward(thirdDLL);

    return 0;
}
