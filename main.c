#include <stdio.h>
#include <stdlib.h>

#include "sample.h"

int main(int argc, char** argv){

    if (argc < 4)
    {
        fprintf(stderr, "Parâmetros insuficientes\n");
        fprintf(stderr, "Uso:\n%s <train filepath> <test filepath> <k-neighbors>\n", argv[0]);
        exit(1);
    }

    FILE* f_train = fopen(argv[1], "r");
    if (!f_train)
        fprintf(stderr, "Falha ao abrir o arquivo %s\n", argv[1]);
        
    FILE* f_test = fopen(argv[2], "r");
    if (!f_test)
        fprintf(stderr, "Falha ao abrir o arquivo %s\n", argv[2]);

    unsigned int k_neighbors = atoi(argv[3]);

    unsigned int train_size = 0;
    Sample** train_samples = read_samples(f_train, &train_size);

    unsigned int test_size = 0;
    Sample** test_samples = read_samples(f_test, &test_size);

    

    fclose(f_train);
    fclose(f_test);

    return 0;
}