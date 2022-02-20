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