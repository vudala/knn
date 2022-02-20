#include "utils.h"

#include <stdlib.h>
#include <stdio.h>

void must_alloc(void* ptr, const char* label)
{
    if (!ptr)
    {
        fprintf(stderr, "Falha a alocar memória em: %s", label);
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