#include <stdbool.h>
#include <stdio.h>

#define MAXSIZE 20
#define OK 1
#define ERROR 0
#define OUTFAIL(PARAM)                                                         \
    printf("%s test fail. line is %d.\n", functionName, __LINE__);             \
    return PARAM;
#define OUTSUCCESS(PARAM)                                                      \
    printf("%s test success.\n", functionName);                                \
    return PARAM;

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
Status deleteElement(SqList *listPointer, int index,
                     ElementType *elementPointer);
int listLen(SqList list);
Status createListHead(SqList *listPointer, ElementType *valuesPointer,
                      int valueCounter);
Status createListTail(SqList *listPointer, ElementType *valuesPointer,
                      int valueCounter);

void testInitList();
void testIsEmpty();
void testClearList();
void testGetElement();
void testLocateElement();
void testInsertElement();
void testAppendElement();
void testDeleteElement();
void testListLen();
void testCreateListHead();
void testCreateListTail();

Status initList(SqList *listPointer) {
    listPointer->length = 0;
    return OK;
}

bool isEmpty(SqList list) { return 0 == list.length; }

Status clearList(SqList *listPointer) {
    int i;
    for (i = 1; i <= listPointer->length; i++) {
        listPointer->data[i - 1] = 0;
    }
    listPointer->length = 0;
    return OK;
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
    if (listPointer->length == MAXSIZE || index < 1 ||
        index > listPointer->length + 1) {
        return ERROR;
    }
    for (i = listPointer->length - 1; i >= index - 1; i--) {
        listPointer->data[i + 1] = listPointer->data[i];
    }
    listPointer->data[index - 1] = element;
    listPointer->length++;
    return OK;
}

Status appendElement(SqList *listPointer, ElementType element) {
    return insertElement(listPointer, listPointer->length + 1, element);
}

Status deleteElement(SqList *listPointer, int index,
                     ElementType *elementPointer) {
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

int listLen(SqList list) { return list.length; }

int main() {
    testInitList();
    testIsEmpty();
    testClearList();
    // testGetElement();
    // testLocateElement();
    // testInsertElement();
    // testAppendElement();
    // testDeleteElement();
    // testListLen();
    // testCreateListHead();
    // testCreateListTail();
}

void testInitList() {
    SqList list;
    char *functionName = "initList";
    if (!initList(&list)) {
        OUTFAIL();
    }
    if (0 != list.length) {
        OUTFAIL();
        return;
    }
    OUTSUCCESS();
}

void testIsEmpty() {
    SqList list;
    char *functionName = "isEmpty";
    initList(&list);
    if (!isEmpty(list)) {
        OUTFAIL();
        return;
    }
    appendElement(&list, 3);
    if (isEmpty(list)) {
        OUTFAIL();
        return;
    }
    OUTSUCCESS();
}

void testClearList() {
    char *functionName = "clearList";
    SqList list;
    initList(&list);
    appendElement(&list, 3);
    if (!clearList(&list)) {
        OUTFAIL();
    }
    if (!isEmpty(list)) {
        OUTFAIL();
    }
    OUTSUCCESS();
}