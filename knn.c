#include "knn.h"
#include "utils.h"

#include <stdlib.h>
#include <math.h>
#include <float.h>


// Retorna o índice da maior distância caso haja alguma maior que dist, se não houver retorna -1
int find_greater(float* distances, unsigned int size, float* dist)
{
    unsigned int greater = 0, found = 0;
    for (unsigned int i = 0; i < size; i++)
        if (distances[i] > *dist)
        {
            greater = i;
            found = 1;
        }

    if (!found)
        return -1;

    return greater;
}


// Calcula a distância entre dois pontos utilizado a distância euclidiana (sqrt omitido para otimizar)
float distance(Sample* train_s, Sample* test_s)
{
    float sum = 0.0f, diff;
    for (unsigned int i = 0; i < train_s->atts_size; i++)
    {
        diff = train_s->attributes[i] - test_s->attributes[i];
        sum = sum + diff * diff;
    }

    return sum;
}


// Retorna as K samples de train mais próximas de test
Sample** nearest(Sample** train_samples, unsigned int train_size, Sample* test, unsigned int k_neighbors)
{
    Sample** nearest = malloc(k_neighbors * sizeof(Sample*));
    must_alloc(nearest, __func__);

    float* distances = malloc(k_neighbors * sizeof(float));
    must_alloc(distances, __func__);

    for(unsigned int i = 0; i < k_neighbors; i++)
        distances[i] = FLT_MAX;

    float dist;
    int greater_index;
    for (unsigned int i = 0; i < train_size; i++)
    {
        dist = distance(train_samples[i], test);
        greater_index = find_greater(distances, k_neighbors, &dist);
        if (greater_index > -1)
        {
            nearest[greater_index] = train_samples[i];
            distances[greater_index] = dist;
        }
    }

    free(distances);

    return nearest;
}


//Retorna o indice de EL se presente em V, caso contrário retorna -1
short int find(short int* v, unsigned int size, short int el)
{
    for (unsigned int i = 0; i < size; i++)
        if (v[i] == el)
            return i;
    return -1;
}


// Retorna o índice do maior elemento em V
short int greater(short int* v, unsigned int size)
{
    short int greater = 0;
    for (unsigned int i = 0; i < size; i++)
        if (v[greater] < v[i])
            greater = i;
    return greater;
}


// Retorna a label predominante entre aquelas samples
short int predominant_label(Sample** samples, unsigned int size)
{
    short int* count = malloc(sizeof(short int) * size);
    must_alloc(count, __func__);

    short int* found = malloc(sizeof(short int) * size);
    must_alloc(found, __func__);

    unsigned int pos = 0;

    short int f;
    for (unsigned int i = 0; i < size; i++)
    {
        f = find(found, pos, samples[i]->label);

        if (f > -1)
            count[f]++;
        else
        {
            found[pos] = samples[i]->label;
            count[pos]++;
            pos++;
        }
    }
    
    short int r_value = found[greater(count, size)];

    free(count);
    free(found);

    return r_value;
}


short int* predict(Sample** train_samples, unsigned int train_size, Sample** test_samples, unsigned int  test_size, unsigned int k_neighbors)
{
    short int* predicted = malloc(sizeof(short int) * test_size);
    must_alloc(predicted, __func__);

    Sample** nrst = NULL;
    
    for (unsigned int i = 0; i < test_size; i++)
    {
        nrst = nearest(train_samples, train_size, test_samples[i], k_neighbors);
        predicted[i] = predominant_label(nrst, k_neighbors);
    }

    return predicted;
}