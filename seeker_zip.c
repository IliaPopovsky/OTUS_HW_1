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
    unsigned char read_symbol;
    unsigned char source_symbol;
    int counter_symbol = 0;
    const char Local_file_headers_signature[5] = "\x50\x4b\x03\x04";
    const char Central_directory_file_header[5] = "\x50\x4b\x01\x02";
    const char End_of_central_directory_record[5] = "\x50\x4b\x05\x06";
    int x50x4bx03x04 = 0;
    int x50x4bx01x02 = 0;
    int x50x4bx05x06 = 0;
    int File_name_length = 0;
    int File_name_length_1 = 0;

    //fprintf(stdout, "Введите имя исходного файла (или пустую строку для завершения):\n");
    fprintf(stdout, "Enter a name for the source file (or empty text to complete):\n");
    for (counter = 0; (read_symbol = getc(stdin)) != '\n'; counter++)
            *(name_source + counter) = read_symbol;

    while (*name_source != '\0')
    {
        if ((fs = fopen(name_source, "rb")) == NULL)
        {
            fprintf(stderr, "Не удается открыть файл %s\n", name_source);
            goto end_circle;
        }
        #if 0
        sprintf(name_target, "%s_bytes_list", "zip_uchar");
        if((ft = fopen(name_target, "ab+")) == NULL)
        {
            fprintf(stderr, "Не удается открыть файл %s\n", name_target);
            goto end_circle;
        }

        while((read = getc(fs)) != EOF)
        {
           counter_symbol++;
           source_symbol = read;
           if(source_symbol < 16)
               fprintf(ft, "0x0%x, ", source_symbol);
           else
               fprintf(ft, "0x%x, ", source_symbol);
        }
        //fprintf(stdout, "В файле %s символ %c встречается %d раз.\n", name_source, source_symbol, counter_symbol);
        fprintf(stdout, "%d\n", counter_symbol);
        #endif // For write in file Hx values
        while((read_symbol = getc(fs)) != EOF)
        {
           switch(read_symbol)
           {
               case '\x50': x50x4bx03x04 = 1;
                            x50x4bx01x02 = 1;
                            x50x4bx05x06 = 1;
                            break;
               case '\x4b': if(x50x4bx03x04 == 1) x50x4bx03x04 = 2;
                            if(x50x4bx01x02 == 1) x50x4bx01x02 = 2;
                            if(x50x4bx05x06 == 1) x50x4bx05x06 = 2;
                            break;
               case '\x03': if(x50x4bx03x04 == 2) x50x4bx03x04 = 3;
                            x50x4bx01x02 = 0;
                            x50x4bx05x06 = 0;
                            break;
               case '\x04': if(x50x4bx03x04 == 3) x50x4bx03x04 = 4;
                            x50x4bx01x02 = 0;
                            x50x4bx05x06 = 0;
                            break;
               case '\x01': if(x50x4bx01x02 == 2) x50x4bx01x02 = 3;
                            x50x4bx03x04 = 0;
                            x50x4bx05x06 = 0;
                            break;
               case '\x02': if(x50x4bx01x02 == 3) x50x4bx01x02 = 4;
                            x50x4bx03x04 = 0;
                            x50x4bx05x06 = 0;
                            break;
               case '\x05': if(x50x4bx05x06 == 2) x50x4bx05x06 = 3;
                            x50x4bx03x04 = 0;
                            x50x4bx01x02 = 0;
                            break;
               case '\x06': if(x50x4bx05x06 == 3) x50x4bx05x06 = 4;
                            x50x4bx03x04 = 0;
                            x50x4bx01x02 = 0;
                            break;
               default    : x50x4bx03x04 = 0;
                            x50x4bx01x02 = 0;
                            x50x4bx05x06 = 0;
           }
           #if 0
           if(x50x4bx03x04 == 4)
           {
              counter = 22;
              while(counter > 0)
              {
                  getc(fs);
                  counter--;
              }
              File_name_length = getc(fs);
              File_name_length_1 = getc(fs);
              if(File_name_length_1 != 0)
                File_name_length = File_name_length_1 + 255;
              getc(fs);
              getc(fs);
              counter = 0;
              while(counter < File_name_length)
              {
                  *(name_target + counter) = getc(fs);
                  counter++;
              }
              printf("%s\n", name_target);
              free(name_target);
              name_target = (char*)calloc(SIZE, sizeof(char));
           }
           #endif // 2
           #if 1
           if(x50x4bx01x02 == 4)
           {
              counter = 24;
              while(counter > 0)
              {
                  getc(fs);
                  counter--;
              }
              File_name_length = getc(fs);
              File_name_length_1 = getc(fs);
              if(File_name_length_1 != 0)
                File_name_length = File_name_length_1 + 255;


              counter = 16;
              while(counter > 0)
              {
                  getc(fs);
                  counter--;
              }
              counter = 0;
              while(counter < File_name_length)
              {
                  *(name_target + counter) = getc(fs);
                  counter++;
              }
              printf("%s\n", name_target);
              free(name_target);
              name_target = (char*)calloc(SIZE, sizeof(char));
           }
           #endif // 0
           if(x50x4bx05x06 == 4)
           {

           }
        }

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
