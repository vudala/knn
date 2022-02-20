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

void free_sample_array(Sample** s, unsigned int size);

Sample** read_samples(FILE* f, unsigned int* size);

short int* extract_metadata(Sample** samples, unsigned int size, unsigned int* labels_found);

#endif