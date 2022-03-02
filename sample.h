#ifndef SAMPLE_INCLUDED
#define SAMPLE_INCLUDED

// Descrição das amostras
#include <stdio.h>
struct sample {
    short int label;        // Rótulo da amostra
    float* attributes;      // Vetor de características
    unsigned int atts_size; // Quantas características diferentes há
};
typedef struct sample Sample; 


// Libera o espaço de memória ocupado por um array de samples
void free_sample_array(Sample** s, unsigned int size);

// Extrai as samples de um arquivo
Sample** read_samples(FILE* f, unsigned int* size);

// Extrai metadados do arquivo de amostra
short int* extract_metadata(Sample** samples, unsigned int size, unsigned int* labels_found);

#endif