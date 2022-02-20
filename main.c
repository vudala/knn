#include <stdio.h>
#include <stdlib.h>

#include "sample.h"
#include "knn.h"
#include "metrics.h"
#include "utils.h"

int main(int argc, char** argv){

    if (argc < 4)
    {
        fprintf(stderr, "Parâmetros insuficientes\n");
        fprintf(stderr, "Uso:\n%s <train filepath> <test filepath> <k-neighbors>\n", argv[0]);
        exit(1);
    }

    FILE* f_train = fopen(argv[1], "r");
    must_open(f_train, argv[1]);
        
    FILE* f_test = fopen(argv[2], "r");
    must_open(f_test, argv[2]);

    unsigned int k_neighbors = atoi(argv[3]);

    unsigned int train_size = 0;
    Sample** train_samples = read_samples(f_train, &train_size);

    unsigned int test_size = 0;
    Sample** test_samples = read_samples(f_test, &test_size);

    short int* predicted = predict(train_samples, train_size, test_samples, test_size, k_neighbors);

    float acc = accuracy(test_samples, predicted, test_size);

    printf("%f\n", acc);

    // free_sample_array(train_samples, train_size);
    // free_sample_array(test_samples, test_size);
    free(predicted);
    fclose(f_train);
    fclose(f_test);

    return 0;
}