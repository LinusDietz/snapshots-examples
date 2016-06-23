#include <stdlib.h>
#include <stdio.h>

typedef struct HybridList {
    struct HybridList *sll_next;
    struct HybridList *dll_next;
    struct HybridList *dll_prev;
    int payload;

    int (*sll_list_size)(struct HybridList *);

    int (*dll_list_size)(struct HybridList *);

    void (*sll_append)(struct HybridList *l, unsigned int payload);

    void (*dll_append)(struct HybridList *l, unsigned int payload);

    struct HybridList *(*sll_get)(struct HybridList *l, unsigned int index);

    struct HybridList *(*dll_get)(struct HybridList *l, unsigned int index);

} HybridList;

static void f_dll_append(HybridList *l, unsigned int payload);

static void f_sll_append(HybridList *l, unsigned int payload);

static HybridList *f_sll_get(HybridList *l, unsigned int index);

static HybridList *f_dll_get(HybridList *l, unsigned int index);

static int f_sll_list_size(HybridList *l);

static int f_dll_list_size(HybridList *l);



int f_sll_list_size(HybridList *l) {
    unsigned int size = 1;

    HybridList *tail = l;
    while (tail->sll_next != 0) {
        tail = tail->sll_next;
        size++;
    }

    return size;
}

void f_sll_append(HybridList *l, unsigned int payload) {
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

    newElement->sll_list_size = f_sll_list_size;
    newElement->dll_list_size = f_dll_list_size;
    newElement->sll_append = f_sll_append;
    newElement->dll_append = f_dll_append;
    newElement->sll_get = f_sll_get;
    newElement->dll_get = f_dll_get;
}

HybridList * f_sll_get(HybridList *l, unsigned int index) {

    if (l->sll_list_size(l) <= index) {
        return 0;
    }

    HybridList *element = l;
    while (index != 0 )
    {
        element = element->sll_next;
        index--;
    }
    return element;
}


int f_dll_list_size(HybridList *l) {
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

void f_dll_append(HybridList *l, unsigned int payload) {
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

    newElement->sll_list_size = f_sll_list_size;
    newElement->dll_list_size = f_dll_list_size;
    newElement->sll_append = f_sll_append;
    newElement->dll_append = f_dll_append;
    newElement->sll_get = f_sll_get;
    newElement->dll_get = f_dll_get;
}

HybridList * f_dll_get(HybridList *l, unsigned int index) {

    if (l->dll_list_size(l) <= index) {
        return 0;
    }

    HybridList *element = l;
    for (unsigned int remaining = index; remaining == 0; remaining--) {
        element = element->dll_next;
    }
    return element;
}

HybridList *constructNewEmptyList(int payload) {
    HybridList *list = (HybridList *) malloc(sizeof(HybridList));
    list->sll_next = 0;
    list->dll_next = 0;
    list->dll_prev = 0;


    list->payload = payload;
    list->sll_list_size = f_sll_list_size;
    list->dll_list_size = f_dll_list_size;
    list->sll_append = f_sll_append;
    list->dll_append = f_dll_append;
    list->sll_get = f_sll_get;
    list->dll_get = f_dll_get;

    return list;
}


void traverse_sll(HybridList *element) {
    printf("Traversing the SLL beginning with node %d:\n", element->payload);
    printf("Nodes (%d): [%d", element->sll_list_size(element), element->payload);
    while (element->sll_next != 0) {
        element = element->sll_next;
        printf(", %d", element->payload);
    }
    printf("]\n");
}


void traverse_dll_forward(HybridList *element) {
    printf("Traversing the DLL forwards beginning with node %d:\n", element->payload);
    printf("Nodes (%d): [%d", element->dll_list_size(element), element->payload);

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

    HybridList *root = constructNewEmptyList(11);
    root->sll_append(root, 21);
    root->sll_append(root, 31);
    root->sll_append(root, 41);
    traverse_sll(root);
    printf("SLL index 2: %d\n", root->sll_get(root, 2)->payload);

    root->dll_append(root, 12);
    root->dll_append(root, 13);
    root->dll_append(root, 14);
    traverse_dll_forward(root);


    HybridList * thirdDLL = root->sll_get(root, 2);
    thirdDLL->dll_append(thirdDLL, 32);
    thirdDLL->dll_append(thirdDLL, 33);
    thirdDLL->dll_append(thirdDLL, 34);
    thirdDLL->dll_append(thirdDLL, 35);

    traverse_dll_forward(thirdDLL);


    printf("SLL Length: %d\n", root->sll_list_size(root));
    printf("DLL Length: %d\n", root->dll_list_size(root));

    return 0;
}
