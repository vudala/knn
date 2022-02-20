// Descrição das amostras
#include <stdio.h>
struct sample {
    short int label;
    float* attributes;
    unsigned int atts_size;
};
typedef struct sample Sample; 

Sample* new_sample(short int label, float* attributes, unsigned int atts_size);

Sample** read_samples(FILE* f, unsigned int* size);