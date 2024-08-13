#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define SIZE 100

int main(void)
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    char *source_string = (char *)calloc(SIZE, sizeof(char));
    char *name_source = (char*)calloc(SIZE, sizeof(char));
    FILE *fp;
    int counter;
    char read_symbol;

    printf("Hello world!\n");
    return 0;
}
