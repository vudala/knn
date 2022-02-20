#ifndef KNN_INCLUDED
#define KNN_INCLUDED

#include "sample.h"

short int* predict(Sample** train_samples, unsigned int train_size, Sample** test_samples, unsigned int  test_size, unsigned int k_neighbors);

#endif