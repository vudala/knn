#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void must_alloc(void* ptr, const char* label)
{
    if (!ptr)
    {
        fprintf(stderr, "Falha a alocar memória em: %s\n", label);
        exit(1);
    }
}


void must_open(FILE* f, const char* fname)
{
    if (!f)
    {
        fprintf(stderr, "Falha ao abrir o arquivo %s\n", fname);
        exit(1);
    }
}


void throw_exception(const char* func)
{
    fprintf(stderr, "Algum erro inesperado aconteceu durante a execução em %s\n", func);
    exit(1);
}


char* str_reverse(char* str)
{
    char aux;
    unsigned int len = strlen(str);
    int i, j;
    for (i = 0, j = len - 1; i < j; i++, j--)
    {
        aux = str[i];
        str[i] = str[j];
        str[j] = aux;
    }
    return str;
}


void remove_nl(char* str)
{
    unsigned int len = strlen(str);
    if ( len > 0 && str[len - 1] == '\n' )
        str[len - 1] = '\0';
}