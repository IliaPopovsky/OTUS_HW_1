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
    FILE *fs;
    int counter;
    char read_symbol;
    char source_symbol;
    int counter_symbol = 0;
    const char Local_file_headers_signature[5] = "\x50\x4b\x03\x04";

    fprintf(stdout, "Введите имя исходного файла (или пустую строку для завершения):\n");
    for (counter = 0; (read_symbol = getc(stdin)) != '\n'; counter++)
            *(name_source + counter) = read_symbol;

    while (*name_source != '\0')
    {
        if ((fs = fopen(name_source, "rb")) == NULL)
        {
            fprintf(stderr, "Не удается открыть файл %s\n", name_source);
            goto end_circle;
        }
        while((read_symbol = getc(fs)) != EOF)
            if(read_symbol == source_symbol)
                   counter_symbol++;
        fprintf(stdout, "В файле %s символ %c встречается %d раз.\n", name_source, source_symbol, counter_symbol);

        end_circle:
        for (counter = 0; counter < SIZE; counter++)
            name_source[counter] = '\0';
        counter_symbol = 0;
        fprintf(stdout, "Введите имя исходного файла (или пустую строку для завершения):\n");
        for (counter = 0; (read_symbol = getc(stdin)) != '\n'; counter++)
            name_source[counter] = read_symbol;
    }

    printf("Hello world!\n");
    return 0;
}
