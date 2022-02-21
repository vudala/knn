#ifndef METRICS_INCLUDED
#define METRICS_INCLUDED

#include "sample.h"

// Retorna a acurácia
float accuracy(Sample** samples, short int* predicted, unsigned int size);

// Imprime a matriz de confusão
void confusion_matrix(Sample** test_samples, short int* predicted, unsigned int size, short int* labels_tracker, short int labels_found);

#endif