#include "sample.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define KBYTE 1024
#define MEMORY_CHUNK 500 // Quantos bytes alocar a mais num realloc


Sample* new_sample(short int label, float* attributes, unsigned int size)
{
    Sample* s = (Sample*) malloc(sizeof(Sample));
    must_alloc(s, __func__);
    s->label = label;
    s->attributes = attributes;
    s->atts_size = size;
    return s;
}

void free_sample(Sample* s)
{
    free(s->attributes);
    free(s);
}

void free_sample_array(Sample** s, unsigned int size)
{
    for (unsigned int i = 0; i < size; i++)
        free_sample(s[i]);
    free(s);
}


// Remove o NÚMERO: das carcterísticas da amostra e o retorna o valor em float
float clean_attr(char* str, char delim)
{
    unsigned int i;
    for (i = 0; str[i] != delim; i++);

    // +1 pra compensar o indice
    unsigned int new_size = strlen(str) - (i + 1);
    char* new_str = malloc(new_size);
    must_alloc(new_str, __func__);

    for (int j = 0; j < new_size; j++)
        new_str[j] = str[i + j + 1];

    float r_value = atof(new_str);
    free(new_str);

    return r_value;
}


Sample* parse_sample(char* str)
{
    short int label;
    label = atoi(strtok(str, " "));

    float* atts = malloc(sizeof(float) * 132);
    must_alloc(atts, __func__);

    unsigned int i = 0;
    char* tok = strtok(NULL, " ");
    while(tok != NULL)
    {
        atts[i++] = clean_attr(tok, ':');
        tok = strtok(NULL, " ");
    }

    return new_sample(label, atts, 132);
}


void remove_nl(char* str)
{
    str[strlen(str) - 2] = '\0';
}


Sample** read_samples(FILE* f, unsigned int* size)
{
    char* buff = malloc(KBYTE * 2);
    must_alloc(buff, __func__);

    unsigned int i = 0;
    unsigned int chunk_mult = 1;
    
    Sample** samples = malloc(sizeof(Sample*) * MEMORY_CHUNK * chunk_mult);
    must_alloc(samples, __func__);

    while(!feof(f))
    {
        if (i >= MEMORY_CHUNK * chunk_mult)
        {
            chunk_mult = chunk_mult << 2;
            samples = (Sample**) realloc(samples, MEMORY_CHUNK * chunk_mult * sizeof(Sample*));
            must_alloc(samples, __func__);
        }
        
        fgets(buff, KBYTE * 2, f);
        remove_nl(buff);
        samples[i] = parse_sample(buff);
        i++;
    }

    free(buff);

    *size = i - 1;
    return samples;
}