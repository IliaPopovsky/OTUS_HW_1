#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define SIZE 1000

int main(void)
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    char *source_string = (char *)calloc(SIZE, sizeof(char));
    char *name_source = (char*)calloc(SIZE, sizeof(char));
    char *name_target = (char*)calloc(SIZE, sizeof(char));
    FILE *fs;
    FILE *ft;
    int counter;
    int read;
    char read_symbol;
    unsigned char source_symbol;
    int counter_symbol = 0;
    const char Local_file_headers_signature[5] = "\x50\x4b\x03\x04";
    const char Central_directory_file_header[5] = "\x50\x4b\x01\x02";
    const char End_of_central_directory_record[5] = "\x50\x4b\x05\x06";

    //fprintf(stdout, "Введите имя исходного файла (или пустую строку для завершения):\n");
    fprintf(stdout, "Enter a name for the source file (or empty text to complete):\n");
    for (counter = 0; (read_symbol = getc(stdin)) != '\n'; counter++)
            *(name_source + counter) = read_symbol;

    while (*name_source != '\0')
    {
        sprintf(name_target, "%s_bytes_list", "zip_uchar");
        if ((fs = fopen(name_source, "rb")) == NULL)
        {
            fprintf(stderr, "Не удается открыть файл %s\n", name_source);
            goto end_circle;
        }
        if((ft = fopen(name_target, "ab+")) == NULL)
        {
            fprintf(stderr, "Не удается открыть файл %s\n", name_target);
            goto end_circle;
        }
        //fread(&read_symbol, sizeof(char), 1, fs);
        while((read = getc(fs)) != EOF)
        //while(read_symbol != EOF)
        {
          //if(read_symbol == source_symbol)
                   counter_symbol++;
           //fwrite(read_symbol, 1, 1, ft);
           source_symbol = read;

           if(source_symbol < 16)
               fprintf(ft, "0x0%x, ", source_symbol);
           else
               fprintf(ft, "0x%x, ", source_symbol);


           //fwrite(&read_symbol, sizeof(char), 1, ft);
           //fread(&read_symbol, sizeof(char), 1, fs);
        }

        //fprintf(stdout, "В файле %s символ %c встречается %d раз.\n", name_source, source_symbol, counter_symbol);
        fprintf(stdout, "%d\n", counter_symbol);
        end_circle:
        for (counter = 0; counter < SIZE; counter++)
            name_source[counter] = '\0';
        counter_symbol = 0;
        //fprintf(stdout, "Введите имя исходного файла (или пустую строку для завершения):\n");
        fprintf(stdout, "Enter a name for the source file (or empty text to complete):\n");
        for (counter = 0; (read_symbol = getc(stdin)) != '\n'; counter++)
            name_source[counter] = read_symbol;
    }

    printf("Hello world!\n");
    return 0;
}
