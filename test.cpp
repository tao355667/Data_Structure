#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

#define LIST_INIT_SIZE 1   //线性表存储空间的初始分配量
#define LIST_INCREMENT 100 //线性表存储空间的分配增量

typedef struct
{
    int *elem;
    int length;
    int listsize;
} sqlist;
void initlist(sqlist &L)
{
    L.elem = (int *)malloc(LIST_INIT_SIZE * sizeof(int));
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
}

int main()
{
    sqlist L;
    initlist(L);
    int *newbase;
    newbase = (int *)realloc(L.elem, (LIST_INCREMENT + L.listsize) * sizeof(int));
    L.listsize += LIST_INCREMENT;
    printf("L.elem=%u,newbase=%u\n", L.elem, newbase);
    L.elem = newbase;
    newbase = (int *)realloc(L.elem, (LIST_INCREMENT + L.listsize) * sizeof(int));
    L.listsize += LIST_INCREMENT;
    printf("L.elem=%u,newbase=%u\n", L.elem, newbase);
    L.elem = newbase;
    newbase = (int *)realloc(L.elem, (LIST_INCREMENT + L.listsize) * sizeof(int));
    L.listsize += LIST_INCREMENT;
    printf("L.elem=%u,newbase=%u\n", L.elem, newbase);
    L.elem = newbase;
    newbase = (int *)realloc(L.elem, (LIST_INCREMENT + L.listsize) * sizeof(int));
    L.listsize += LIST_INCREMENT;
    printf("L.elem=%u,newbase=%u\n", L.elem, newbase);
    L.elem = newbase;
    L.elem[4] = 666;
    printf("%d", L.elem[4]);
    system("pause");
    return 0;
}