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

    fclose(f_train);
    fclose(f_test);

    short int* predicted = predict(train_samples, train_size, test_samples, test_size, k_neighbors);

    unsigned int labels_found = 0;
    short int* tracker = extract_metadata(test_samples, test_size, &labels_found);

    float acc = accuracy(test_samples, predicted, test_size);
    printf("Acurácia: %f\n", acc);
    
    printf("Matriz de confusão: \n");
    confusion_matrix(test_samples, predicted, test_size, tracker, labels_found);

    free_sample_array(train_samples, train_size);
    free_sample_array(test_samples, test_size);
    free(predicted);
    free(tracker);

    return 0;
}