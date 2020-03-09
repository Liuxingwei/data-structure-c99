#include <stdio.h>
#include <stdbool.h>

#define MAXSIZE 20
#define OK 1
#define ERROR 0

typedef int ElementType;
typedef struct {
    ElementType data[MAXSIZE];
    int length;
} SqList;
typedef bool Status;

Status initList(SqList *listPointer);
bool isEmpty(SqList list);
Status clearList(SqList *listPointer);
Status getElement(SqList list, int index, ElementType *elementPointer);
int locateElement(SqList list, ElementType elem);
Status insertElement(SqList *listPointer, int index, ElementType element);
Status appendElement(SqList *listPointer, ElementType element);
Status deleteElement(SqList *listPointer, int index, ElementType *elementPointer);
int listLen(SqList list);

Status initList(SqList *listPointer) {
    listPointer->length = 0;
}

bool isEmpty(SqList list) {
    return 0 == list.length;
}

Status clearList(SqList *listPointer) {
    int i;
    for (i = 1; i <= listPointer->length; i++) {
        listPointer->data[i - 1] = 0;
    }
    listPointer->length = 0;
}

Status getElement(SqList list, int index, ElementType *elementPointer) {
    if (index < 1 || index > list.length) {
        return ERROR;
    }
    *elementPointer = list.data[index - 1];
    return OK;
}

int locateElement(SqList list, ElementType element) {
    int i;
    for (i = 1; i <= list.length; i++) {
        if (list.data[i - 1] == element) {
            return i;
        }
    }
    return 0;
}

Status insertElement(SqList *listPointer, int index, ElementType element) {
    int i;
    if (listPointer->length == MAXSIZE || index < 1 || index > listPointer->length + 1) {
        return ERROR;
    }
    for (i = listPointer->length - 1; i >=  index - 1; i--) {
        listPointer->data[i + 1] = listPointer->data[i];
    }
    listPointer->data[index - 1] = element;
    listPointer->length++;
    return OK;
}

Status appendElement(SqList *listPointer, ElementType element) {
    return insertElement(listPointer, listPointer->length + 1, element);
}

Status deleteElement(SqList *listPointer, int index, ElementType *elementPointer) {
    int i;
    if (index < 1 || index > listPointer->length) {
        return ERROR;
    }
    *elementPointer = listPointer->data[index - 1];
    for (i = index; i < listPointer->length; i++) {
        listPointer->data[i - 1] = listPointer->data[i];
    }
    listPointer->data[listPointer->length - 1] = 0;
    listPointer->length--;
    return OK;
}

int listLen(SqList list) {
    return list.length;
}


int main() {
    int i;
    ElementType element;
    SqList list;
    initList(&list);
    if (isEmpty(list)) {
        printf("List is empty.\n");
    }
    insertElement(&list, 1, 3);
    insertElement(&list, 2, 5);
    insertElement(&list, 2, 4);
    for (i = 1; i <= listLen(list); i++) {
        getElement(list, i, &element);
        printf("%d\n", element);
    }
    printf("%d\n", locateElement(list, 4));
    printf("%d\n", locateElement(list, 9));
    deleteElement(&list, 2, &element);
    printf("%d %d %d %d %d\n", element, list.length, list.data[0], list.data[1], list.data[2]);
    appendElement(&list, 6);
    getElement(list, 3, &element);
    printf("%d %d\n", list.length, element);
    clearList(&list);
    printf("%d\n", list.data[2]);
    printf("%d\n", listLen(list));
    return 0;
}