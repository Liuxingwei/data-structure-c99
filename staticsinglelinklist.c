/**
 * 静态链表实现示例
 * 数据元素为整型
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define OK true
#define ERROR false

/**
 * 线性表所能存储的元素的最大值（数组的定义长度）
 * 为方便测试边界情况，暂定义为较小的值
 */
#define MAXSIZE 10

#define OUTFAIL(PARAM)                                                         \
    printf("Function \"%s\" test fail. line is %d.\n", functionName,           \
           __LINE__);                                                          \
    return PARAM;
#define OUTSUCCESS(PARAM)                                                      \
    printf("Function \"%s\" test success.\n", functionName);                   \
    return PARAM;

/**
 * 定义线性表所存储的元素类型
 */
typedef int ElementType;

/**
 * 定义需要同时获取「执行是否成功」标志类型
 */
typedef bool Status;

/**
 * 节点类型
 */
typedef struct {
    ElementType value;
    int next;
} Node;

/**
 * 静态链表类型
 */
typedef struct {
    Node nodes[MAXSIZE];
    int length;
} StaticSingleLinkList;

/**
 * 初始化 listPointer 指向的静态链表
 */
Status initList(StaticSingleLinkList *listPointer);

/**
 * 为节点分配空间，返回新空间的位置索引
 */
int mallocSsll(StaticSingleLinkList *listPointer);

/**
 * 释放指定索引的节点空间
 */
Status freeSsll(StaticSingleLinkList *listPointer, int index);

/**
 * 判断线性表 list 是否为空。为空返回 true，不为空返回 false
 */
bool isEmpty(StaticSingleLinkList list);

/**
 * 清空 listPointer 指针指向的线性表。执行成功返回 OK，失败返回 ERROR
 */
Status clearList(StaticSingleLinkList *listPointer);

/**
 * 删除 listPointer 指针指向的线性表的第 index 个元素，并将删除的元素值放在
 * elementPointer 指针指向的变量中 执行成功返回 OK，失败返回 ERROR
 */
Status deleteElement(StaticSingleLinkList *listPointer, int index,
                     ElementType *elementPointer);
/**
 * 计算线性表 list 的长度
 */
int listLen(StaticSingleLinkList list);
/**
 * 使用连续 count 个整数填 listPointer 指针指向的线性表，起始数值为 3。
 * 用于在测试时初始化线性表
 */
void setup(StaticSingleLinkList *listPointer, int count);

/**
 * listPointer 函数的测试函数
 */
void testInitList();

/**
 * mallocSsll 函数的测试函数
 */
void testMallocSsll();

/**
 * freeSsll 函数的测试函数
 */
void testFreeSsll();

/**
 * isEmpty 函数的测试函数
 */
void testIsEmpty();

/**
 * deleteElement 函数的测试函数
 */
void testDeleteElement();

/**
 * clearList 函数的测试函数
 */
void testClearList();

/**
 * listLen 函数的测试函数
 */
void testListLen();

Status initList(StaticSingleLinkList *listPointer) {
    int i;
    for (i = 0; i < MAXSIZE - 1; ++i) {
        listPointer->nodes[i].value = 0;
        listPointer->nodes[i].next = i + 1;
    }
    listPointer->nodes[i].value = 0;
    listPointer->nodes[i].next = 0;
    listPointer->length = 0;
    return OK;
}

int mallocSsll(StaticSingleLinkList *listPointer) {
    if (listPointer->nodes[0].next >= MAXSIZE - 1) {
        return 0;
    }
    int i = listPointer->nodes[0].next;
    listPointer->nodes[0].next = listPointer->nodes[i].next;
    return i;
}

Status freeSsll(StaticSingleLinkList *listPointer, int index) {
    if (index < 1 || index >= MAXSIZE - 1) {
        return ERROR;
    }
    Node node = listPointer->nodes[0];
    while (MAXSIZE - 1 != node.next) {
        if (node.next == index) {
            return OK;
        }
        node = listPointer->nodes[node.next];
    }
    listPointer->nodes[index].next = listPointer->nodes[0].next;
    listPointer->nodes[0].next = index;
    listPointer->nodes[index].value = 0;
    return OK;
}

bool isEmpty(StaticSingleLinkList list) { return 0 == list.length; }

Status clearList(StaticSingleLinkList *listPointer) {
    return initList(listPointer);
}

Status deleteElement(StaticSingleLinkList *listPointer, int index,
                     ElementType *valuePointer) {
    if (index < 1 || index > listLen(*listPointer)) {
        return ERROR;
    }
    int t, i;
    Node *n = &(listPointer->nodes[MAXSIZE - 1]);
    for (i = 1; i < index; ++i) {
        n = &(listPointer->nodes[n->next]);
    }
    t = n->next;
    n->next = listPointer->nodes[t].next;
    *valuePointer = listPointer->nodes[t].value;
    freeSsll(listPointer, t);
    return OK;
}

int listLen(StaticSingleLinkList list) { return list.length; }

void main() {
    testInitList();
    testMallocSsll();
    testFreeSsll();
    testIsEmpty();
    testClearList();
    testDeleteElement();
    testListLen();
}

void setup(StaticSingleLinkList *listPointer, int count) {
    int i;
    for (i = 0; i < MAXSIZE - 1; ++i) {
        listPointer->nodes[i].value = 0;
        listPointer->nodes[i].next = i + 1;
    }
    listPointer->nodes[i].value = 0;
    listPointer->nodes[i].next = 0;
    for (i = 1; i <= count; ++i) {
        listPointer->nodes[i].value = i + 2;
    }
    if (count > 0) {
        listPointer->nodes[MAXSIZE - 1].next = 1;
        listPointer->nodes[count].next = 0;
    }
    listPointer->nodes[0].next = i;
    listPointer->length = count;
}

void testInitList() {
    char functionName[] = "initList";
    StaticSingleLinkList list;
    if (!initList(&list)) {
        OUTFAIL();
    }
    if (0 != list.length) {
        OUTFAIL();
    }
    int i;
    for (i = 1; i < MAXSIZE - 1; ++i) {
        if (i + 1 != list.nodes[i].next || 0 != list.nodes[i].value) {
            OUTFAIL();
        }
    }
    if (0 != list.nodes[i].next || 0 != list.nodes[i].value) {
        OUTFAIL();
    }
    OUTSUCCESS();
}

void testMallocSsll() {
    char functionName[] = "mallocSsll";
    StaticSingleLinkList list;
    setup(&list, 0);
    int newIndex = mallocSsll(&list);
    if (1 != newIndex) {
        OUTFAIL();
    }
    if (2 != list.nodes[0].next) {
        OUTFAIL();
    }
    setup(&list, 5);
    newIndex = mallocSsll(&list);
    if (6 != newIndex) {
        OUTFAIL();
    }
    if (7 != list.nodes[0].next) {
        OUTFAIL();
    }
    setup(&list, 8);
    newIndex = mallocSsll(&list);
    if (0 != newIndex) {
        OUTFAIL();
    }
    if (9 != list.nodes[0].next) {
        OUTFAIL();
    }
    OUTSUCCESS();
}

void testFreeSsll() {
    char functionName[] = "freeSsll";
    StaticSingleLinkList list;
    setup(&list, 0);
    if (freeSsll(&list, 0)) {
        OUTFAIL();
    }
    if (freeSsll(&list, 9)) {
        OUTFAIL();
    }
    if (!freeSsll(&list, 3) || 1 != list.nodes[0].next) {
        OUTFAIL();
    }
    setup(&list, 5);
    if (!freeSsll(&list, 3) || 3 != list.nodes[0].next ||
        6 != list.nodes[3].next) {
        OUTFAIL();
    }
    OUTSUCCESS();
}

void testIsEmpty() {
    char functionName[] = "isEmpty";
    StaticSingleLinkList list;
    list.length = 0;
    if (!isEmpty(list)) {
        OUTFAIL();
    }
    list.length = 3;
    if (isEmpty(list)) {
        OUTFAIL();
    }
    OUTSUCCESS();
}

void testClearList() {
    char functionName[] = "clearList";
    StaticSingleLinkList list;
    int i;
    setup(&list, 0);
    if (!clearList(&list)) {
        OUTFAIL();
    }
    if (0 != list.length) {
        OUTFAIL();
    }
    for (i = 0; i < MAXSIZE - 1; ++i) {
        if (i + 1 != list.nodes[i].next) {
            OUTFAIL();
        }
    }
    if (0 != list.nodes[i].next) { 
        OUTFAIL();
    }
    setup(&list, 6);
    if (!clearList(&list)) {
        OUTFAIL();
    }
    if (0 != list.length) {
        OUTFAIL();
    }
    for (i = 0; i < MAXSIZE - 1; ++i) {
        if (i + 1 != list.nodes[i].next) {
            OUTFAIL();
        }
    }
    if (0 != list.nodes[i].next) {
        OUTFAIL();
    }
    OUTSUCCESS();
}

void testDeleteElement() {
    char functionName[] = "deleteElement";
    StaticSingleLinkList list;
    ElementType value;
    setup(&list, 5);
    if (deleteElement(&list, 0, &value)) {
        OUTFAIL();
    }
    if (deleteElement(&list, 6, &value)) {
        OUTFAIL();
    }
    if (!deleteElement(&list, 3, &value)) {
        OUTFAIL();
    }
    if (5 != value) {
        OUTFAIL();
    }
    if (1 != list.nodes[MAXSIZE - 1].next || 2 != list.nodes[1].next ||
        4 != list.nodes[2].next || 5 != list.nodes[4].next ||
        0 != list.nodes[5].next) {
        OUTFAIL();
    }
    if (3 != list.nodes[0].next || 6 != list.nodes[3].next ||
        7 != list.nodes[6].next || 8 != list.nodes[7].next ||
        9 != list.nodes[8].next) {
        OUTFAIL();
    }
    if (3 != list.nodes[1].value || 4 != list.nodes[2].value ||
        6 != list.nodes[4].value || 7 != list.nodes[5].value) {
        OUTFAIL();
    }
    OUTSUCCESS();
}

void testListLen() {
    char functionName[] = "listLen";
    StaticSingleLinkList list;
    list.length = 0;
    if (0 != listLen(list)) {
        OUTFAIL();
    }
    list.length = 5;
    if (5 != listLen(list)) {
        OUTFAIL();
    }
    OUTSUCCESS();
}