// Descrição das amostras
#include <stdio.h>
struct sample {
    short int label;        // Rótulo da amostra
    float* attributes;      // Vetor de características
    unsigned int atts_size; // Quantas características diferentes há
};
typedef struct sample Sample; 

Sample* new_sample(short int label, float* attributes, unsigned int atts_size);

Sample** read_samples(FILE* f, unsigned int* size);