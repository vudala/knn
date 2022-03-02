#include "sample.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define KBYTE 1024
#define SAMPLES_MEMORY_CHUNK 500 // Quantos bytes alocar a mais num realloc
#define LABELS_MEMORY_CHUNK  10


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


// Remove o NÚMERO:VALOR das carcterísticas da amostra e o retorna o valor em float
float clean_attr(char* str, char delim)
{
    unsigned int i;
    for (i = 0; str[i] != delim; i++);

    // +1 pra compensar o indice
    unsigned int new_size = strlen(str) - i;
    char* new_str = malloc(new_size);
    must_alloc(new_str, __func__);

    for (int j = 0; j < new_size; j++)
        new_str[j] = str[i + j + 1];

    float r_value = atof(new_str);
    free(new_str);

    return r_value;
}


// Separa um string contendo a amostra e cria um novo struct Sample a partir da string
Sample* parse_sample(char* str, unsigned int attrs_n)
{
    short int label;
    label = atoi(strtok(str, " "));

    float* atts = calloc(attrs_n, sizeof(float));
    must_alloc(atts, __func__);

    unsigned int i = 0;
    char* tok = strtok(NULL, " ");
    while(tok != NULL)
    {
        atts[i++] = clean_attr(tok, ':');
        tok = strtok(NULL, " ");
    }

    return new_sample(label, atts, attrs_n);
}


// Extrai a quantidade de atributos das amostras
unsigned int extract_attributes_n(FILE* f)
{
    char* buff = malloc(KBYTE * 2);
    must_alloc(buff, __func__);

    char* aux = malloc(KBYTE );
    must_alloc(buff, __func__);

    unsigned int i, j = 0;
    if (!feof(f))
    {
        if (!fgets(buff, KBYTE * 2, f))
            throw_exception(__func__);
            
        for (i = strlen(buff); buff[i] != ':'; i--);
        i--;
        for (;buff[i] != ' '; i--)
        {
            aux[j] = buff[i];
            j++;
        }
    }

    rewind(f);
    unsigned int r_value = atoi(str_reverse(aux));

    free(buff);
    free(aux);

    return r_value;
}


// Lê a database e extrai as samples
Sample** read_samples(FILE* f, unsigned int* size)
{
    unsigned int attrs_n = extract_attributes_n(f);

    char* buff = malloc(KBYTE * 2);
    must_alloc(buff, __func__);

    unsigned int i = 0;
    unsigned int chunk_mult = 1;
    
    Sample** samples = malloc(sizeof(Sample*) * SAMPLES_MEMORY_CHUNK * chunk_mult);
    must_alloc(samples, __func__);

    while(fgets(buff, KBYTE * 2, f))
    {
        if (i >= SAMPLES_MEMORY_CHUNK * chunk_mult)
        {
            chunk_mult = chunk_mult << 2;
            samples = (Sample**) realloc(samples, SAMPLES_MEMORY_CHUNK * chunk_mult * sizeof(Sample*));
            must_alloc(samples, __func__);
        }

        remove_nl(buff);
        samples[i] = parse_sample(buff, attrs_n);
        
        i++;
    }

    free(buff);

    *size = i;
    return samples;
}


// Verifica se EL pertence a V
int search(short int* v, unsigned int v_size, short int el)
{
    for (unsigned int i = 0; i < v_size; i++)
        if (v[i] == el)
            return 1;
    return 0;
}


// Extrai quantos rótulos diferentes há e os retorna
short int* extract_metadata(Sample** samples, unsigned int size, unsigned int* labels_found)
{
    unsigned int chunk_mult = 1;
    short int* labels_tracker = malloc(sizeof(short int) * LABELS_MEMORY_CHUNK);
    must_alloc(labels_tracker, __func__);

    for (int i = 0; i < size; i++)
        if (!search(labels_tracker, *labels_found, samples[i]->label))
        {
            if (*labels_found >= LABELS_MEMORY_CHUNK * chunk_mult)
            {
                chunk_mult = chunk_mult << 2;
                labels_tracker = realloc(labels_tracker, LABELS_MEMORY_CHUNK * chunk_mult * sizeof(short int));
                must_alloc(labels_tracker, __func__);
            }
            labels_tracker[*labels_found] = samples[i]->label;
            *labels_found += 1;
        }

    return labels_tracker;
}
