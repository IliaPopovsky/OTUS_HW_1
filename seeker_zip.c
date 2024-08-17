#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define SIZE 500

int main(void)
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    char *source_string = (char *)calloc(SIZE, sizeof(char));
    char name_target[SIZE] = {0};
    char name_source[SIZE] = {0};
    FILE *fs;
    FILE *ft;
    int counter;
    int read;
    int read_symbol;
    unsigned char source_symbol;
    int counter_symbol = 0;
    const char Local_file_headers_signature[5] = "\x50\x4b\x03\x04";
    const char Central_directory_file_header_signature[5] = "\x50\x4b\x01\x02";
    const char End_of_central_directory_record_signature[5] = "\x50\x4b\x05\x06";
    int x50x4bx03x04 = 0;
    int x50x4bx01x02 = 0;
    int x50x4bx05x06 = 0;
    int File_name_length = 0;
    int File_name_length_1 = 0;
    int zero_byte_offset = 0;
    int first_byte_offset = 0;
    int second_byte_offset = 0;
    int third_byte_offset = 0;
    int counter_Local_file_headers_signature = 0;
    int counter_Central_directory_file_header_signature = 0;
    int counter_End_of_central_directory_record_signature = 0;
    int flag_zip = 0;

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
        sprintf(name_target, "%s_bytes_list", name_source);
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
           #if 15
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
              if(flag_zip == 0)
              {
                  printf("Этот файл содержит ZIP-архив. Файлы входящие в данный ZIP-архив:\n");
                  flag_zip = 1;
              }
              printf("%s\n", name_target);
              memset(name_target, 0, SIZE);
              counter_Local_file_headers_signature++;
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
              if(flag_zip == 0)
              {
                  printf("Этот файл содержит ZIP-архив. Файлы входящие в данный ZIP-архив:\n");
                  flag_zip = 1;
              }
              printf("%s\n", name_target);
              memset(name_target, 0, SIZE);
              counter_Central_directory_file_header_signature++;

           }
           #endif // 0
           if(x50x4bx05x06 == 4)
           {
              counter = 12;
              while(counter > 0)
              {
                  getc(fs);
                  counter--;
              }
              zero_byte_offset = getc(fs);
              first_byte_offset = getc(fs);
              second_byte_offset = getc(fs);
              third_byte_offset = getc(fs);
              if(flag_zip == 0)
              {
                  printf("Этот файл содержит ZIP-архив. Файлы входящие в данный ZIP-архив:\n");
                  flag_zip = 1;
              }
              counter_End_of_central_directory_record_signature++;
           }
        }
        if(counter_Local_file_headers_signature == 0 &&
           counter_Central_directory_file_header_signature == 0 &&
           counter_End_of_central_directory_record_signature == 0)
        {
           printf("Этот файл не содержит ни одного из признаков ZIP-архива:\n");
           printf("1) Сигнатура Local file headers \"\\x50\\x4b\\x03\\x04\" отсутствует.\n");
           printf("2) Сигнатура Central directory file header \"\\x50\\x4b\\x01\\x02\" отсутствует.\n");
           printf("3) Сигнатура End of central directory record \"\\x50\\x4b\\x05\\x06\" отсутствует.\n");

        }

        end_circle:
        memset(name_source, 0, SIZE);
        counter_symbol = 0;
        //fprintf(stdout, "Введите имя исходного файла (или пустую строку для завершения):\n");
        fprintf(stdout, "Enter a name for the source file (or empty text to complete):\n");
        for (counter = 0; (read_symbol = getc(stdin)) != '\n'; counter++)
            name_source[counter] = read_symbol;
    }

    printf("Hello world!\n");
    return 0;
}
