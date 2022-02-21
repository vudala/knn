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


void print_matrix(unsigned int** m, unsigned int n, short int* labels_tracker, short int labels_found)
{
    printf("      ");
    for (int i = 0; i < labels_found; i++)
        printf("%5d ", labels_tracker[i]);
    printf("\n");
    for (int i = 0; i < labels_found; i++)
        printf("_______");
    printf("\n");

    for (int i = 0; i < n; i++)
    {
        printf("%5d |", labels_tracker[i]);
        for (int j = 0; j < n; j++)
            printf("%5d ", m[i][j]);
        printf("\n");
    }
}


void confusion_matrix(Sample** test_samples, short int* predicted, unsigned int size, short int* labels_tracker, short int labels_found)
{
    unsigned int** mat = malloc(sizeof(unsigned int*) * labels_found);
    must_alloc(mat, __func__);

    mat[0] = calloc(labels_found * labels_found, sizeof(unsigned int));
    must_alloc(mat[0], __func__);

    for (unsigned int i = 1; i < labels_found; i++)
        mat[i] = mat[0] + i * labels_found;

    for (int i = 0; i < size; i++)
        mat[predicted[i]][test_samples[i]->label]++;

    print_matrix(mat, labels_found, labels_tracker, labels_found);

    free(mat[0]);
    free(mat);
}
