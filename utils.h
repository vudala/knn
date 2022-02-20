#ifndef UTILS_INCLUDED
#define UTILS_INCLUDED

#include <stdio.h>

// Verifica se PTR foi alocado, caso contrário dispara uma mensagem em stderr e termina a execução com código 1
void must_alloc(void* ptr, const char* label);

// Verifica se F foi aberto, caso contrário dispara uma mensagem em stderr e termina a execução com código 1
void must_open(FILE* f, const char* fname);

#endif