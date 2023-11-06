#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    char cad[]="tres tristes tigres trigaban trigo por culpa del bolivar";
    char *word[100];
    int word_count = 0;
    char *word1[100];
    char *word2[100];
    int cont1 = 0;
    int cont2 = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        MPI_Bcast(cad, sizeof(cad), MPI_CHAR, 0, MPI_COMM_WORLD);
    } else {
        if (rank == 1){ 
        MPI_Bcast(cad, sizeof(cad), MPI_CHAR, 0, MPI_COMM_WORLD);
        }
        if (rank == 2){
        MPI_Bcast(cad, sizeof(cad), MPI_CHAR, 0, MPI_COMM_WORLD);
        }
        if (rank == 3){
        MPI_Bcast(cad, sizeof(cad), MPI_CHAR, 0, MPI_COMM_WORLD);
        }
    }

    char *token = strtok(cad, " \t\n");

    while (token != NULL) {
        word[word_count++] = strdup(token);
        token = strtok(NULL, " \t\n");
    }
    for (int i = 0; i < word_count; i++) {
        if (i % 2 == 0) {
            word1[cont1++] = word[i];
        } else {
            word2[cont2++] = word[i];
        }
    }

    if (rank == 0) {
        printf("Palabras pares: ");
        for (int i = 0; i < cont1; i++) {
            printf("%s ", word1[i]);
            free(word1[i]);
        }

        printf("\nPalabras impares: ");
        for (int i = 0; i < cont2; i++) {
            printf("%s ", word2[i]);
            free(word2[i]);
        }

        printf("\n");
    }

    MPI_Finalize();

    return 0;
}
