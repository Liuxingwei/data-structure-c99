#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef bool Status;

typedef int ElementType;

typedef struct Node {
    ElementType value;
    struct Node *next;
} Node;

typedef struct {
    Node *next;
    int length;
} SingleLinkList;

Status initList(SingleLinkList *listPointer);
bool isEmpty(SingleLinkList list);
Status clearList(SingleLinkList *listPointer);
Status getElement(SingleLinkList list, int index, ElementType *valuePointer);
int locateElement(SingleLinkList list, ElementType value);
Status insertElement(SingleLinkList *listPointer, int index, ElementType value);
Status appendElement(SingleLinkList *listPointer, ElementType value);
Status deleteElement(SingleLinkList *listPointer, int index,
                     ElementType *valuePointer);
int listLen(SingleLinkList list);
Status createListHead(SingleLinkList *listPointer, ElementType *valuesPorinter,
                      int length);
Status createListTail(SingleLinkList *listPointer, ElementType *valuesPorinter,
                      int length);
Status appendTo(Node *node, ElementType value);

Status initList(SingleLinkList *listPointer) {
    listPointer->length = 0;
    listPointer->next = NULL;
    return OK;
}

bool isEmpty(SingleLinkList list) { return 0 == list.length; }

Status clearList(SingleLinkList *listPointer) {
    Node *p, *n;
    if (0 == listPointer->length) {
        return OK;
    }
    n = listPointer->next->next;
    free(listPointer->next);
    listPointer->next = NULL;
    listPointer->length = 0;
    while (NULL != n->next) {
        p = n;
        n = p->next;
        free(p);
    }
    return OK;
}

Status getElement(SingleLinkList list, int index, ElementType *valuePointer) {
    Node *p = list.next;
    int i;
    if (index < 1 || index > list.length) {
        return ERROR;
    }
    for (i = 0; i <= index - 1; i++) {
        p = p->next;
    }
    *valuePointer = p->value;
    return OK;
}

int locateElement(SingleLinkList list, ElementType value) {
    Node *p = list.next;
    int i = 1;
    while (p != NULL) {
        if (p->value == value) {
            return i;
        }
        p = p->next;
        i++;
    }
    return 0;
}

Status insertElement(SingleLinkList *listPointer, int index,
                     ElementType element) {
    Node *p = listPointer->next;
    int i;
    for (i = 1; i < index; i++) {
        p = p->next;
    }
    if (ERROR == appendTo(p, element)) {
        return ERROR;
    }
    listPointer->length++;
    return OK;
}

Status appendElement(SingleLinkList *listPointer, ElementType value) {
    return insertElement(listPointer, listPointer->length + 1, value);
}

Status deleteElement(SingleLinkList *listPointer, int index,
                     ElementType *valuePointer) {
    Node *p = listPointer->next, *r;
    int i;
    for (i = 1; i < index; i++) {
        p = p->next;
    }
    *valuePointer = p->next->value;
    r = p->next;
    p->next = p->next->next;
    listPointer->length--;
    free(r);
    return OK;
}

int listLen(SingleLinkList list) { return list.length; }

Status createListHead(SingleLinkList *listPointer, ElementType *valuesPorinter,
                      int length) {
    if (listPointer->next != NULL || length <= 0) {
        return ERROR;
    }
    int i;
    for (i = 1; i <= length; i++) {
        if (ERROR == appendTo(listPointer, valuesPorinter[i - 1])) {
            return ERROR;
        }
    }
    listPointer->length = length;
    return OK;
}

Status createListTail(SingleLinkList *listPointer, ElementType *valuesPorinter,
                      int length) {
    if (listPointer->length != 0 || length <= 0) {
        return ERROR;
    }
    int i = 1;
    Node *p;
    p = (Node *)malloc(sizeof(Node));
    p->next = NULL;
    p->value = valuesPorinter[i - 1];
    listPointer->next = p;
    for (; i < length; i++) {
        if (ERROR == appendTo(p, valuesPorinter[i - 1])) {
            return ERROR;
        }
        p = p->next;
    }
    p->next = NULL;
    listPointer->length = length;
    return OK;
}

Status appendTo(Node *node, ElementType value) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (NULL == n) {
        return ERROR;
    }
    n->value = value;
    n->next = node->next;
    node->next = n;
    return OK;
}

int main() {
    SingleLinkList list;
    printf("%d\n", list.length);
    initList(&list);
    printf("%d\n", list.length);
    clearList(&list);
    printf("%d\n", isEmpty(list));
}
