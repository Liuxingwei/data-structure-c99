#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define OK true
#define ERROR false

#define MAXSIZE 1000

typedef bool Status;
typedef int ElementType;
typedef struct {
    ElementType value;
    int next;
} Node;
typedef Node StaticSingleLinkList[MAXSIZE];

int malloc_ssll(StaticSingleLinkList list);
Status free_ssll(StaticSingleLinkList list, int index);
Status initList(StaticSingleLinkList list);
bool isEmpty(StaticSingleLinkList list);
Status clearList(StaticSingleLinkList list);
Status getElement(StaticSingleLinkList list, int index, ElementType values[1]);
int locateElement(StaticSingleLinkList list, ElementType value);
Status insertElement(StaticSingleLinkList list, int index, ElementType value);
Status appendElement(StaticSingleLinkList list, ElementType value);
Status deleteElement(StaticSingleLinkList list, int index,
                     ElementType values[1]);
int listLen(StaticSingleLinkList list);

int malloc_ssll(StaticSingleLinkList list) {
    if (MAXSIZE - 1 == list[0].next) {
        return false;
    }
    int used = list[0].next;
    list[0].next = list[used].next;
    return used;
}

Status free_ssll(StaticSingleLinkList list, int index) {
    list[index].next = list[0].next;
    list[0].next = index;
    return OK;
}

Status initList(StaticSingleLinkList list) {
    int i;
    for (i = 0; i < MAXSIZE - 1; i++) {
        list[i].next = i + 1;
    }
    list[MAXSIZE - 1].next = 0;
    return OK;
}

bool isEmpty(StaticSingleLinkList list) { return 0 == list[MAXSIZE - 1].next; }

Status clearList(StaticSingleLinkList list) { return initList(list); }

Status getElement(StaticSingleLinkList list, int index, ElementType values[1]) {
    if (isEmpty(list) || index < 1 || index >= MAXSIZE - 1) {
        return ERROR;
    }
    int i;
    Node node = list[MAXSIZE - 1];
    for (i = 1; i <= index; i++) {
        if (0 == node.next) {
            return ERROR;
        }
        node = list[node.next];
    }
    values[0] = node.value;
    return OK;
}

int locateElement(StaticSingleLinkList list, ElementType value) {
    if (isEmpty(list)) {
        return ERROR;
    }
    int i = 1;
    Node node = list[list[MAXSIZE - 1].next];
    while (value != node.value) {
        if (0 == node.next) {
            return ERROR;
        }
        node = list[node.next];
        i++;
    }
    return i;
}

Status insertElement(StaticSingleLinkList list, int index, ElementType value) {
    int len = listLen(list);
    if (MAXSIZE - 2 == len || index < 1 || index > len + 1) {
        return ERROR;
    }
    int i = 1;
    int newNodeIndex = malloc_ssll(list);
    if (0 == newNodeIndex) {
        return ERROR;
    }
    list[newNodeIndex].value = value;
    Node node = list[list[MAXSIZE - 1].next];
    while (value != node.value) {
        if (0 == node.next) {
            return ERROR;
        }
        node = list[node.next];
        i++;
    }
    list[newNodeIndex].next = node.next;
    node.next = newNodeIndex;
    return OK;
}

Status appendElement(StaticSingleLinkList list, ElementType value) {
    return insertList(list, listLen(list) + 1, value);
}

Status deleteElement(StaticSingleLinkList list, int index,
                     ElementType values[1]) {
    if (isEmpty(list) || index < 1 || index > listLen(list)) {
        return ERROR;
    }
    int i;
    Node node = list[MAXSIZE - 1];
    for (i = 1; i < index; i++) {
        node = list[node.next];
    }
    int freeIndex = node.next;
    node.next = list[node.next].next;
    values[0] = list[freeIndex].value;
    free_ssll(list, freeIndex);
    return OK;
}

int listLen(StaticSingleLinkList list) {
    if (0 == list[MAXSIZE - 1].next) {
        return 0;
    }
    int i = 1;
    Node node = list[list[MAXSIZE - 1].next];
    while (0 != node.next) {
        node = list[node.next];
        i++;
    }
    return i;
}