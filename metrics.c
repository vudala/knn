#include "metrics.h"


float accuracy(Sample** samples, short int* predicted, unsigned int size)
{
    unsigned int hit = 0;
    for (unsigned int i = 0; i < size; i++)
    {
        if (samples[i]->label == predicted[i])
            hit++;
    }

    return (float) hit / (float) size;
}