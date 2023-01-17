/*

*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
//删除字符串两边的空格
char *DelBlankSE(char *arr, int len)
{
    char *p1;
    char *p2;
    p1 = arr;
    p2 = arr + len - 1;
    while (p1 <= p2 && *p1 == ' ') //去除左边空格
    {
        p1++;
    }
    while (p1 <= p2 && *p2 == ' ') //去除右边空格
    {
        p2--;
    }
    *(++p2) = '\0'; //字符串末尾为'\0'
    return p1;
}
//删除字符串两边的空格，中间的连续空格若存在则保留一个
char *DeleteBlankspace(char *arr, int len)
{

    int i;
    int count = 0;
    char *s = arr;                //
    arr = DelBlankSE(arr, len);   //去除字符串两边的空格
    for (i = 0; arr[i] != 0; i++) //
    {
        if (arr[i] != ' ')
        {
            s[count++] = arr[i];
        }
        else if (arr[i + 1] == ' ')
        {
            s[count] = ' ';
        }
        else
        {
            s[count++] = ' ';
        }
    }
    s[count] = '\0';
    return s;
}

int main()
{
    char s[50] = "          Green          Street    ";
    printf("|%s|\n", s);
    printf("|%s|\n", DeleteBlankspace(s, strlen(s)));
    printf("%d", strlen(DeleteBlankspace(s, strlen(s))));
    return 0;
}