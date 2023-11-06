#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <gmp.h>

int main(int argc, char** argv) {
    int rank, size;
    mpz_t term, n, x;
    mpz_init(term);  
    mpz_init(n);     
    mpz_init(x);     

    MPI_Init(&argc, &argv); 

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  
    MPI_Comm_size(MPI_COMM_WORLD, &size);  

    if (rank == 0) {  
        mpz_set_ui(n, 1); 
        mpz_set_ui(x, 1);  
        for (int i = 1; i <= 1000; i++) {  
            if (i % 2 == 0) {  
                mpz_mul_ui(term, x, 2); 
                mpz_add_ui(x, x, 1);    
            } else {  
                mpz_set_ui(term, (mpz_get_ui(n) * mpz_get_ui(n)) + 1);  
                mpz_add_ui(n, n, 1); 
            }
            gmp_printf("Término %d: %Zd\n", i, term);  
        }
    } else {  
        mpz_set_ui(n, rank);  
        mpz_set_ui(x, rank); 
        for (int i = rank; i <= 1000; i += size - 1) {  
            if (i % 2 == 0) {  
                mpz_mul_ui(term, x, 2);  
                mpz_add_ui(x, x, size - 1); 
            } else {  
                mpz_set_ui(term, (mpz_get_ui(n) * mpz_get_ui(n)) + 1);  
                mpz_add_ui(n, n, size - 1); 
            }
            MPI_Send(&term, sizeof(mpz_t), MPI_BYTE, 0, 0, MPI_COMM_WORLD);  
        }
    }

    mpz_clear(term); 
    mpz_clear(n);     
    mpz_clear(x);     
    MPI_Finalize();   

    return 0;  
}
