#include <stdio.h>
#include <stdlib.h>

#include "sample.h"

int main(int argc, char** argv){

    FILE* f_train = fopen(argv[1], "r");
    if (!f_train)
        fprintf(stderr, "Falha ao abrir o arquivo %s\n", argv[1]);
        
    FILE* f_test = fopen(argv[2], "r");
    if (!f_test)
        fprintf(stderr, "Falha ao abrir o arquivo %s\n", argv[2]);

    unsigned int test_size = 0;
    Sample** test_samples = read_samples(f_test, &test_size);

    unsigned int train_size = 0;
    Sample** train_samples = read_samples(f_train, &train_size);

    fclose(f_train);
    fclose(f_test);

    return 0;
}