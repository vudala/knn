#include "metrics.h"
#include "utils.h"

#include <stdlib.h>

float accuracy(Sample** samples, short int* predicted, unsigned int size)
{
    unsigned int hit = 0;
    for (unsigned int i = 0; i < size; i++)
        if (samples[i]->label == predicted[i])
            hit++;

    return (float) hit / (float) size;
}

//Retorna o indice de EL se presente em V, caso contrário retorna -1
// short int find(short int* v, short int el,  unsigned int size)
// {
//     for (unsigned int i = 0; i < size; i++)
//         if (v[i] == el)
//             return i;
//     return -1;
// }


void confusion_matrix(Sample** test_samples, short int* predicted, unsigned int size)
{
    unsigned int** mat = malloc(sizeof(int*));
    must_alloc(mat, __func__);

    mat[0] = calloc(size, sizeof(int) * size);
    must_alloc(mat[0], __func__);

    for (unsigned int i = 1; i < size; i++)
        mat[i] = mat[0] + size * i * sizeof(int);

    // short int pos = 0;
    for (int i = 0; i < size; i++)
    {
        mat[predicted[i]][test_samples[i]->label]++;
    }

    free(mat[0]);
    free(mat);
}