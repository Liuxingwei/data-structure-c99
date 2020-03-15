/**
 * 线性表的单链存储结构实现示例
 * 数据单元为整数
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define OK true
#define ERROR false

#define OUTFAIL(PARAM)                                                         \
    printf("Function \"%s\" test fail. line is %d.\n", functionName,           \
           __LINE__);                                                          \
    return PARAM;
#define OUTSUCCESS(PARAM)                                                      \
    printf("Function \"%s\" test success.\n", functionName);                   \
    return PARAM

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
typedef struct Node {
    ElementType value;
    struct Node *next;
} Node;

/**
 * 单链表类型，其中指针指向头节点（不存储数据）
 */
typedef struct {
    Node *headNode;
    int length;
} SingleLinkList;

/**
 * 初始化 listPointer 指向的线性表。执行成功返回 OK，失败返回 ERROR
 */
Status initList(SingleLinkList *listPointer);

/**
 * 判断线性表 list 是否为空。为空返回 true，不为空返回 false
 */
bool isEmpty(SingleLinkList list);

/**
 * 清空 listPointer 指针指向的线性表。执行成功返回 OK，失败返回 ERROR
 */
Status clearList(SingleLinkList *listPointer);

/**
 * 获取线性表 list 的第 index 个元素的值，放在 elementPointer 指针指向的变量中
 * 执行成功返回 OK，失败返回 ERROR
 */
Status getElement(SingleLinkList list, int index, ElementType *valuePointer);

/**
 * 在线性表 list 中查找与 element 相等的元素。以整数形式返回其位置，查找失败返回
 * 0
 */
int locateElement(SingleLinkList list, ElementType value);

/**
 * 将 element 插入到 listPointer 指针指向的线性表的第 index 个位置
 * 执行成功返回 OK，执行失败返回 ERROR
 */
Status insertElement(SingleLinkList *listPointer, int index, ElementType value);

/**
 * 将 element 追加到 listPointer 指针指向的线性表的末尾
 * 执行成功返回 OK，执行失败返回 ERROR
 */
Status appendElement(SingleLinkList *listPointer, ElementType value);

/**
 * 删除 listPointer 指针指向的线性表的第 index 个元素，并将删除的元素值放在
 * elementPointer 指针指向的变量中 执行成功返回 OK，失败返回 ERROR
 */
Status deleteElement(SingleLinkList *listPointer, int index,
                     ElementType *valuePointer);

/**
 * 计算线性表 list 的长度
 */
int listLen(SingleLinkList list);

/**
 * 以头插的方式使用 valuesPointer 指向的数组的值，创建 listPointer
 * 指针指向的线性表，由于无法自动计算数组长度，需要提供第三个参数指定要填充的元素个数
 * 执行成功返回 OK，失败返回 ERROR
 */
Status createListHead(SingleLinkList *listPointer, ElementType *valuesPorinter,
                      int length);

/**
 * 以尾插的方式使用 valuesPointer 指向的数组的值，创建 listPointer
 * 指针指向的线性表，由于无法自动计算数组长度，需要提供第三个参数指定要填充的元素个数
 * 执行成功返回 OK，失败返回 ERROR
 */
Status createListTail(SingleLinkList *listPointer, ElementType *valuesPorinter,
                      int length);

/**
 * 使用连续 count 个整数填 listPointer 指针指向的线性表，起始数值为 3。
 * 用于在测试时初始化线性表
 */
void setup(SingleLinkList *listPointer, int count);

/**
 * initList 函数的测试函数
 */
void testInitList();

/**
 * isEmpty 函数的测试函数
 */
void testIsEmpty();

/**
 * clearList 函数的测试函数
 */
void testClearList();

/**
 * getElement 函数的测试函数
 */
void testGetElement();

/**
 * locateElement 函数的测试函数
 */
void testLocateElement();

/**
 * insertElement 函数的测试函数
 */
void testInsertElement();

/**
 * appendElement 函数的测试函数
 */
void testAppendElement();

/**
 * deleteElement 函数的测试函数
 */
void testDeleteElement();

/**
 * listLen 函数的测试函数
 */
void testListLen();

/**
 * createListHead 函数的测试函数
 */
void testCreateListHead();

/**
 * createListTail 函数的测试函数
 */
void testCreateListTail();

Status initList(SingleLinkList *listPointer) {
    listPointer->length = 0;
    listPointer->headNode = (Node *)malloc(sizeof(Node));
    listPointer->headNode->next = NULL;
    return OK;
}

bool isEmpty(SingleLinkList list) { return 0 == list.length; }

Status clearList(SingleLinkList *listPointer) {
    int i;
    Node *p, *n;
    if (0 != listPointer->length) {
        p = listPointer->headNode;
        for (i = 1; i <= listPointer->length; ++i) {
            n = p->next;
            p->next = n->next;
            free(n);
        }
    }
    listPointer->length = 0;
    return OK;
}

Status getElement(SingleLinkList list, int index, ElementType *valuePointer) {
    if (index < 1 || index > list.length) {
        return ERROR;
    }
    int i;
    Node *p = list.headNode;
    for (i = 1; i <= index; ++i) {
        p = p->next;
    }
    *valuePointer = p->value;
    return OK;
}

int locateElement(SingleLinkList list, ElementType value) {
    int i;
    Node *p = list.headNode;
    for (i = 1; i <= list.length; ++i) {
        if (p->next->value == value) {
            return i;
        }
        p = p->next;
    }
    return 0;
}

Status insertElement(SingleLinkList *listPointer, int index,
                     ElementType value) {
    if (index < 1 || index > listPointer->length + 1) {
        return ERROR;
    }
    int i;
    Node *p, *n;
    p = listPointer->headNode;
    for (i = 1; i < index; ++i) {
        p = p->next;
    }
    n = (Node *)malloc(sizeof(Node));
    n->value = value;
    n->next = p->next;
    p->next = n;
    ++listPointer->length;
    return OK;
}

Status appendElement(SingleLinkList *listPointer, ElementType value) {
    return insertElement(listPointer, listPointer->length + 1, value);
}

Status deleteElement(SingleLinkList *listPointer, int index,
                     ElementType *valuePointer) {
    if (index < 1 || index > listPointer->length) {
        return ERROR;
    }
    int i;
    Node *p, *n;
    p = listPointer->headNode;
    for (i = 1; i < index; ++i) {
        p = p->next;
    }
    n = p->next;
    p->next = n->next;
    *valuePointer = n->value;
    free(n);
    --listPointer->length;
    return OK;
}

int listLen(SingleLinkList list) { return list.length; }

Status createListHead(SingleLinkList *listPointer, ElementType *valuesPointer,
                      int count) {
    int i;
    initList(listPointer);
    for (i = 1; i <= count; ++i) {
        insertElement(listPointer, 1, valuesPointer[i - 1]);
    }
    return OK;
}

Status createListTail(SingleLinkList *listPointer, ElementType *valuesPointer,
                      int count) {
    int i;
    initList(listPointer);
    Node *p, *n;
    p = listPointer->headNode;
    for (i = 1; i <= count; ++i) {
        n = (Node *)malloc(sizeof(Node));
        n->value = valuesPointer[i - 1];
        n->next = NULL;
        p->next = n;
        p = p->next;
        ++listPointer->length;
    }
    return OK;
}

int main() {
    testInitList();
    testIsEmpty();
    testClearList();
    testGetElement();
    testLocateElement();
    testInsertElement();
    testAppendElement();
    testDeleteElement();
    testListLen();
    testCreateListHead();
    testCreateListTail();
}

void setup(SingleLinkList *listPointer, int count) {
    int i;
    Node *p, *n;
    listPointer->headNode = p = (Node *)malloc(sizeof(Node));
    p->next = NULL;
    for (i = 0; i < count; ++i) {
        n = (Node *)malloc(sizeof(Node));
        n->value = i + 3;
        n->next = NULL;
        p = p->next = n;
    }
    listPointer->length = count;
}

void testInitList() {
    char functionName[] = "initList";
    SingleLinkList list;
    if (!initList(&list)) {
        OUTFAIL()
    }
    if (0 != list.length) {
        OUTFAIL();
    }
    if (list.headNode->next != NULL) {
        OUTFAIL();
    }
    OUTSUCCESS();
}

void testIsEmpty() {
    char functionName[] = "isEmpty";
    SingleLinkList list;
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
    SingleLinkList list;
    setup(&list, 0);
    if (!clearList(&list)) {
        OUTFAIL();
    }
    if (0 != list.length) {
        OUTFAIL();
    }
    if (NULL != list.headNode->next) {
        OUTFAIL();
    }
    setup(&list, 3);
    if (!clearList(&list)) {
        OUTFAIL();
    }
    if (0 != list.length) {
        OUTFAIL();
    }
    OUTSUCCESS();
}

void testGetElement() {
    char functionName[] = "getElement";
    SingleLinkList list;
    ElementType value;
    setup(&list, 5);
    if (getElement(list, 0, &value)) {
        OUTFAIL();
    }
    if (getElement(list, 6, &value)) {
        OUTFAIL();
    }
    if (!getElement(list, 1, &value) || 3 != value) {
        OUTFAIL();
    }
    if (!getElement(list, 3, &value) || 5 != value) {
        OUTFAIL();
    }
    if (!getElement(list, 5, &value) || 7 != value) {
        OUTFAIL();
    }
    OUTSUCCESS();
}

void testLocateElement() {
    char functionName[] = "locateElement";
    SingleLinkList list;
    setup(&list, 5);
    if (0 != locateElement(list, 0)) {
        OUTFAIL();
    }
    if (0 != locateElement(list, 8)) {
        OUTFAIL();
    }
    if (1 != locateElement(list, 3)) {
        OUTFAIL();
    }
    if (3 != locateElement(list, 5)) {
        OUTFAIL();
    }
    if (5 != locateElement(list, 7)) {
        OUTFAIL();
    }
    OUTSUCCESS();
}

void testInsertElement() {
    char functionName[] = "insertElement";
    SingleLinkList list;
    ElementType value;
    int i;
    setup(&list, 5);
    if (insertElement(&list, 0, 2)) {
        OUTFAIL();
    }
    if (insertElement(&list, 7, 8)) {
        OUTFAIL();
    }
    if (!insertElement(&list, 1, 2) || 6 != list.length) {
        OUTFAIL()
    }
    for (i = 1; i <= 6; ++i) {
        if (!getElement(list, i, &value) || i + 1 != value) {
            OUTFAIL();
        }
    }
    if (!insertElement(&list, 7, 8) || 7 != list.length) {
        OUTFAIL();
    }
    for (i = 1; i <= 6; ++i) {
        if (!getElement(list, i, &value) || i + 1 != value) {
            OUTFAIL();
        }
    }
    if (!insertElement(&list, 4, 9) || 8 != list.length) {
        OUTFAIL();
    }
    for (i = 1; i <= 3; ++i) {
        if (!getElement(list, i, &value) || i + 1 != value) {
            OUTFAIL();
        }
    }

    if (!getElement(list, i, &value) || 9 != value) {
        OUTFAIL();
    }
    for (++i; i <= 8; ++i) {
        if (!getElement(list, i, &value) || i != value) {
            OUTFAIL();
        }
    }
    OUTSUCCESS();
}

void testAppendElement() {
    char functionName[] = "appendElement";
    SingleLinkList list;
    ElementType value;
    int i;
    setup(&list, 5);
    if (!appendElement(&list, 8) || 6 != list.length) {
        OUTFAIL();
    }
    for (i = 1; i <= 6; ++i) {
        if (!getElement(list, i, &value) || i + 2 != value) {
            OUTFAIL();
        }
    }
    OUTSUCCESS();
}

void testDeleteElement() {
    char functionName[] = "deleteElement";
    SingleLinkList list;
    int i;
    ElementType value;
    setup(&list, 5);
    if (deleteElement(&list, 0, &value)) {
        OUTFAIL();
    }
    if (deleteElement(&list, 6, &value)) {
        OUTFAIL();
    }
    if (!deleteElement(&list, 1, &value) || 4 != list.length) {
        OUTFAIL();
    }
    if (3 != value) {
        OUTFAIL();
    }
    for (i = 1; i <= 4; ++i) {
        if (!getElement(list, i, &value) || i + 3 != value) {
            OUTFAIL();
        }
    }
    if (!deleteElement(&list, 4, &value) || 3 != list.length) {
        OUTFAIL();
    }
    if (7 != value) {
        OUTFAIL();
    }
    for (i = 1; i <= 3; ++i) {
        if (!getElement(list, i, &value) || i + 3 != value) {
            OUTFAIL();
        }
    }
    if (!deleteElement(&list, 2, &value) || 2 != list.length) {
        OUTFAIL();
    }
    if (5 != value) {
        OUTFAIL();
    }
    if (!getElement(list, 1, &value) || 4 != value) {
        OUTFAIL();
    }
    if (!getElement(list, 2, &value) || 6 != value) {
        OUTFAIL();
    }
    OUTSUCCESS();
}

void testListLen() {
    char functionName[] = "listLen";
    SingleLinkList list;
    setup(&list, 3);
    if (3 != listLen(list)) {
        OUTFAIL();
    }
    SingleLinkList list1;
    setup(&list1, 8);
    if (8 != listLen(list1)) {
        OUTFAIL();
    }
    OUTSUCCESS();
}

void testCreateListHead() {
    char functionName[] = "createListHead";
    SingleLinkList list;
    ElementType value, values[] = {1, 3, 5, 7, 9, 11};
    int i;
    if (!createListHead(&list, values, 6)) {
        OUTFAIL();
    }
    if (6 != list.length) {
        OUTFAIL();
    }
    for (i = 1; i <= list.length; ++i) {
        if (!getElement(list, i, &value) || (6 - i) * 2 + 1 != value) {
            OUTFAIL();
        }
    }
    OUTSUCCESS();
}

void testCreateListTail() {
    char functionName[] = "createListTail";
    SingleLinkList list;
    ElementType value, values[] = {1, 3, 5, 7, 9, 11};
    int i;
    if (!createListTail(&list, values, 6)) {
        OUTFAIL();
    }
    if (6 != list.length) {
        OUTFAIL();
    }
    for (i = 1; i <= list.length; ++i) {
        if (!getElement(list, i, &value) || i * 2 - 1 != value) {
            OUTFAIL();
        }
    }
    OUTSUCCESS();
}