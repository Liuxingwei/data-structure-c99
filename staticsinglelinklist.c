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
    return OK;
}

void main() {
    testInitList();
    testMallocSsll();
    testFreeSsll();
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