#include "knn.h"

#include <stdlib.h>
#include <math.h>
#include <float.h>


// Retorna o índice da maior distância caso haja alguma maior que dist, se não houver retorna -1
int find_greater(float* distances, unsigned int size, float* dist)
{
    unsigned int smaller = 0, found = 0;
    for (int i = 0; i < size; i++)
        if (distances[smaller] > *dist)
        {
            smaller = i;
            found = 1;
        }

    if (!found)
        return -1;

    return smaller;
}


// Calcula a distância entre dois pontos utilizado a distância euclidiana (sqrt omitido para otimizar)
float distance(Sample* train_s, Sample* test_s)
{
    float sum = 0.0f;
    for (int i = 0; train_s->atts_size; i++)
        sum += powf(train_s->attributes[i] - test_s->attributes[i], 2.0f);
    return sum;
}

void predict(Sample** train_samples, unsigned int train_size, unsigned int k_neighbors, Sample* test)
{
    Sample** closest = malloc(k_neighbors * sizeof(Sample*));
    float* distances = malloc(k_neighbors * sizeof(float));
    for(int i = 0; i < k_neighbors; i++)
        distances[i] = FLT_MAX;

    float dist;
    int greater_index = -1;
    for (int i = 0; i < train_size; i++)
    {
        dist = distance(train_samples[i], test);
        greater_index = find_greater(distances, k_neighbors, &dist);
        if (greater_index > -1)
        {
            closest[greater_index] = train_samples[i];
            distances[greater_index] = dist;
        }
    }
}