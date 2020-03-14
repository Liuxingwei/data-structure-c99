/**
 * 线性表的顺序存储结构实现示例
 * 数据单元为整数，以整数数组实现
 */
#include <stdbool.h>
#include <stdio.h>

/**
 * 线性表所能存储的元素的最大值（数组的定义长度）
 * 为方便测试边界情况，暂定义为较小的值
 */
#define MAXSIZE 6

#define OK true
#define ERROR false

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
 * 定义线性表结构。使用数组存储数据；使用整数任长度计数
 */
typedef struct {
    ElementType data[MAXSIZE];
    int length;
} SqList;

/**
 * 定义需要同时获取「执行是否成功」标志类型
 */
typedef bool Status;

/**
 * 初始化 listPointer 指向的线性表。执行成功返回 OK，失败返回 ERROR
 */
Status initList(SqList *listPointer);

/**
 * 判断线性表 list 是否为空。为空返回 true，不为空返回 false
 */
bool isEmpty(SqList list);

/**
 * 清空 listPointer 指针指向的线性表。执行成功返回 OK，失败返回 ERROR
 */
Status clearList(SqList *listPointer);

/**
 * 获取线性表 list 的第 index 个元素的值，放在 elementPointer 指针指向的变量中
 * 执行成功返回 OK，失败返回 ERROR
 */
Status getElement(SqList list, int index, ElementType *elementPointer);

/**
 * 在线性表 list 中查找与 element 相等的元素。以整数形式返回其位置，查找失败返回
 * 0
 */
int locateElement(SqList list, ElementType element);

/**
 * 将 element 插入到 listPointer 指针指向的线性表的第 index 个位置
 * 执行成功返回 OK，执行失败返回 ERROR
 */
Status insertElement(SqList *listPointer, int index, ElementType element);

/**
 * 将 element 追加到 listPointer 指针指向的线性表的末尾
 * 执行成功返回 OK，执行失败返回 ERROR
 */
Status appendElement(SqList *listPointer, ElementType element);

/**
 * 删除 listPointer 指针指向的线性表的第 index 个元素，并将删除的元素值放在
 * elementPointer 指针指向的变量中 执行成功返回 OK，失败返回 ERROR
 */
Status deleteElement(SqList *listPointer, int index,
                     ElementType *elementPointer);

/**
 * 计算线性表 list 的长度
 */
int listLen(SqList list);

/**
 * 以头插的方式使用 valuesPointer 指向的数组的值，创建 listPointer
 * 指针指向的线性表，由于无法自动计算数组长度，需要提供第三个参数指定要填充的元素个数
 * 执行成功返回 OK，失败返回 ERROR
 */
Status createListHead(SqList *listPointer, ElementType *valuesPointer,
                      int valueCounter);

/**
 * 以尾插的方式使用 valuesPointer 指向的数组的值，创建 listPointer
 * 指针指向的线性表，由于无法自动计算数组长度，需要提供第三个参数指定要填充的元素个数
 * 执行成功返回 OK，失败返回 ERROR
 */
Status createListTail(SqList *listPointer, ElementType *valuesPointer,
                      int valueCounter);

/**
 * 使用连续 count 个整数填 listPointer 指针指向的线性表，起始数值为 3。
 * 用于在测试时初始化线性表
 */
void setup(SqList *listPointer, int count);

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

Status initList(SqList *listPointer) {
    int i;
    for (i = 0; i < MAXSIZE; ++i) {
        listPointer->data[i] = 0;
    }
    listPointer->length = 0;
    return OK;
}

bool isEmpty(SqList list) { return 0 == list.length; }

Status clearList(SqList *listPointer) {
    if (listPointer->length < 0) {
        return initList(listPointer);
    }
    int i;
    for (i = 1; i <= listPointer->length; ++i) {
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
    for (i = 1; i <= list.length; ++i) {
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
    ++listPointer->length;
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
    for (i = index; i < listPointer->length; ++i) {
        listPointer->data[i - 1] = listPointer->data[i];
    }
    listPointer->data[listPointer->length - 1] = 0;
    listPointer->length--;
    return OK;
}

int listLen(SqList list) { return list.length; }

Status createListHead(SqList *listPointer, ElementType *valuesPointer,
                      int valueCounter) {
    int i;
    initList(listPointer);
    for (i = 1; i <= valueCounter; ++i) {
        if (!insertElement(listPointer, 1, valuesPointer[i - 1])) {
            return ERROR;
        };
    }
    return OK;
}

Status createListTail(SqList *listPointer, ElementType *valuesPointer,
                      int valueCounter) {
    int i;
    initList(listPointer);
    for (i = 1; i <= valueCounter; ++i) {
        if (!insertElement(listPointer, i, valuesPointer[i - 1])) {
            return ERROR;
        };
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

void setup(SqList *list, int count) {
    int i;
    for (i = 0; i < MAXSIZE; ++i) {
        if (i < count) {
            list->data[i] = i + 3;
        } else {
            list->data[i] = 0;
        }
    }
    list->length = count;
}

void testInitList() {
    SqList list;
    int i;
    char functionName[] = "initList";
    if (!initList(&list)) {
        OUTFAIL();
    }
    if (0 != list.length) {
        OUTFAIL();
    }
    for (i = 0; i < MAXSIZE; ++i) {
        if (0 != list.data[i]) {
            OUTFAIL();
        }
    }
    OUTSUCCESS();
}

void testIsEmpty() {
    SqList list;
    char functionName[] = "isEmpty";
    list.length = 0;
    if (!isEmpty(list)) {
        OUTFAIL();
    }
    list.length = 1;
    if (isEmpty(list)) {
        OUTFAIL();
    }
    OUTSUCCESS();
}

void testClearList() {
    char functionName[] = "clearList";
    SqList list;
    int i;
    if (!clearList(&list)) {
        OUTFAIL();
    }
    if (0 != list.length) {
        OUTFAIL();
    }
    for (i = 0; i < MAXSIZE; ++i) {
        if (0 != list.data[i]) {
            OUTFAIL();
        }
    }
    setup(&list, 3);
    if (!clearList(&list)) {
        OUTFAIL();
    }
    if (0 != list.length) {
        OUTFAIL();
    }
    for (i = 0; i < MAXSIZE; ++i) {
        if (0 != list.data[i]) {
            OUTFAIL();
        }
    }
    OUTSUCCESS();
}

void testGetElement() {
    char functionName[] = "getElement";
    SqList list;
    ElementType res;
    setup(&list, 3);
    if (!getElement(list, 2, &res)) {
        OUTSUCCESS();
    }
    if (4 != res) {
        OUTFAIL();
    }
    if (getElement(list, 0, &res)) {
        OUTFAIL();
    }
    if (getElement(list, 4, &res)) {
        OUTFAIL();
    }
    if (!getElement(list, 1, &res) || 3 != res) {
        OUTFAIL();
    }
    if (!getElement(list, 3, &res) || 5 != res) {
        OUTFAIL();
    }
    OUTSUCCESS();
}

void testLocateElement() {
    char functionName[] = "locateElement";
    SqList list;
    setup(&list, 3);
    if (locateElement(list, 7)) {
        OUTFAIL();
    }
    if (locateElement(list, 3) != 1) {
        OUTFAIL();
    }
    if (locateElement(list, 4) != 2) {
        OUTFAIL();
    }
    if (locateElement(list, 5) != 3) {
        OUTFAIL();
    }
    OUTSUCCESS();
}

void testInsertElement() {
    char functionName[] = "insertElement";
    SqList list;
    ElementType res;
    setup(&list, 3);
    if (insertElement(&list, 0, 2)) {
        OUTFAIL();
    }
    if (insertElement(&list, 5, 6)) {
        OUTFAIL();
    }
    if (!insertElement(&list, 1, 2)) {
        OUTFAIL();
    }
    if (2 != list.data[0]) {
        OUTFAIL();
    }
    if (5 != list.data[3]) {
        OUTFAIL();
    }
    if (4 != list.length) {
        OUTFAIL();
    }
    if (!insertElement(&list, 5, 6)) {
        OUTFAIL();
    }
    if (5 != list.data[3]) {
        OUTFAIL();
    }
    if (6 != list.data[4]) {
        OUTFAIL();
    }
    if (5 != list.length) {
        OUTFAIL();
    }
    if (!insertElement(&list, 3, 9)) {
        OUTFAIL();
    }
    if (9 != list.data[2]) {
        OUTFAIL();
    }
    if (3 != list.data[1]) {
        OUTFAIL();
    }
    if (4 != list.data[3]) {
        OUTFAIL();
    }
    if (6 != list.length) {
        OUTFAIL();
    }
    if (insertElement(&list, 3, 5)) {
        OUTFAIL();
    }
    if (6 != list.length) {
        OUTFAIL();
    }
    OUTSUCCESS();
}

void testAppendElement() {
    char functionName[] = "appendElement";
    SqList list;
    ElementType res;
    int i;
    setup(&list, 3);
    if (!appendElement(&list, 6)) {
        OUTFAIL();
    }
    for (i = 0; i < 4; ++i) {
        if (i + 3 != list.data[i]) {
            OUTFAIL();
        }
    }
    if (4 != list.length) {
        OUTFAIL();
    }
    appendElement(&list, 7);
    appendElement(&list, 8);
    if (appendElement(&list, 9)) {
        OUTFAIL();
    }
    if (6 != list.length) {
        OUTFAIL();
    }
    OUTSUCCESS();
}

void testDeleteElement() {
    char functionName[] = "deleteElement";
    SqList list;
    ElementType value;
    int i;
    setup(&list, 4);
    if (deleteElement(&list, 0, &value)) {
        OUTFAIL();
    }
    if (deleteElement(&list, 5, &value)) {
        OUTFAIL();
    }
    if (!deleteElement(&list, 4, &value)) {
        OUTFAIL();
    }
    if (6 != value) {
        OUTFAIL();
    }
    if (3 != list.length) {
        OUTFAIL();
    }
    for (i = 0; i < 3; ++i) {
        if (i + 3 != list.data[i]) {
            OUTFAIL();
        }
    }
    for (; i < MAXSIZE; ++i) {
        if (0 != list.data[i]) {
            OUTFAIL();
        }
    }
    if (!deleteElement(&list, 2, &value)) {
        OUTFAIL();
    }
    if (2 != list.length) {
        OUTFAIL();
    }
    if (4 != value) {
        OUTFAIL();
    }
    if (3 != list.data[0] || 5 != list.data[1]) {
        OUTFAIL();
    }
    for (i = 2; i < MAXSIZE; i++) {
        if (0 != list.data[i]) {
            OUTFAIL();
        }
    }
    OUTSUCCESS();
}

void testListLen() {
    char functionName[] = "listLen";
    SqList list;
    list.length = 0;
    if (0 != listLen(list)) {
        OUTFAIL();
    }
    list.length = 2;
    if (2 != listLen(list)) {
        OUTFAIL();
    }
    list.length = 6;
    if (6 != listLen(list)) {
        OUTFAIL();
    }
    OUTSUCCESS();
}

void testCreateListHead() {
    char functionName[] = "createListHead";
    SqList list;
    int i;
    ElementType values[10] = {6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    if (createListHead(&list, values, 10)) {
        OUTFAIL();
    }
    SqList list1;
    if (!createListHead(&list1, values, 0)) {
        OUTFAIL();
    }
    if (0 != list1.length) {
        OUTFAIL();
    }
    for (i = 0; i < MAXSIZE; ++i) {
        if (0 != list1.data[i]) {
            OUTFAIL();
        }
    }
    SqList list2;
    if (!createListHead(&list2, values, 5)) {
        OUTFAIL();
    }
    if (5 != list2.length) {
        OUTFAIL();
    }
    for (i = 0; i < 5; ++i) {
        if (10 - i != list2.data[i]) {
            OUTFAIL();
        }
    }
    for (; i < MAXSIZE; ++i) {
        if (0 != list2.data[i]) {
            OUTFAIL();
        }
    }
    OUTSUCCESS();
}

void testCreateListTail() {
    char functionName[] = "createListTail";
    int i;
    ElementType values[10] = {6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    SqList list;
    if (createListTail(&list, values, 10)) {
        OUTFAIL();
    }
    SqList list1;
    if (!createListTail(&list1, values, 0)) {
        OUTFAIL();
    }
    if (0 != list1.length) {
        OUTFAIL();
    }
    for (i = 0; i < MAXSIZE; ++i) {
        if (0 != list1.data[i]) {
            OUTFAIL();
        }
    }
    SqList list2;
    if (!createListTail(&list2, values, 5)) {
        OUTFAIL();
    }
    if (5 != list2.length) {
        OUTFAIL();
    }
    for (i = 0; i < 5; ++i) {
        if (i + 6 != list2.data[i]) {
            OUTFAIL();
        }
    }
    for (; i < MAXSIZE; ++i) {
        if (0 != list2.data[i]) {
            OUTFAIL();
        }
    }
    OUTSUCCESS();
}