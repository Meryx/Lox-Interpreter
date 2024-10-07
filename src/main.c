#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

char *read_file_to_string(const char *filepath)
{
    FILE *fptr = fopen(filepath, "rb");
    if (fptr == NULL)
    {
        perror("Error opening file");
        return NULL;
    }

    if (ferror(fptr))
    {
        fclose(fptr);
        perror("Error reading file");
        return NULL;
    }

    char *data = NULL, *temp;
    size_t READALL_CHUNK = 2097152;
    size_t used = 0;
    size_t size = 0;
    size_t n;

    while (1)
    {
        if (used + READALL_CHUNK + 1 > size)
        {
            size = used + READALL_CHUNK + 1;

            if (size <= used)
            {
                free(data);
                return NULL;
            }

            temp = realloc(data, size);
            if (temp == NULL)
            {
                free(data);
                return NULL;
            }
            data = temp;
        }

        n = fread(data + used, 1, READALL_CHUNK, fptr);
        if (n == 0)
            break;

        used += n;
    }

    if (ferror(fptr))
    {
        fclose(fptr);
        perror("Error reading file");
        free(data);
        return NULL;
    }

    temp = realloc(data, used + 1);
    if (temp == NULL)
    {
        free(data);
        return NULL;
    }

    data = temp;
    data[used] = '\0';
    return data;
}

void run(char *source)
{
    printf(source);
}

void runFile(char *path)
{
    char *data = read_file_to_string(path);
    if (data == NULL)
    {
        return;
    }

    run(data);
    free(data);
}

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        printf("Usage: jlox [script]\n");
        exit(64);
    }

    if (argc == 2)
    {
        runFile(argv[1]);
    }
    else
    {
        // runPrompt();
    }
    return 0;
}