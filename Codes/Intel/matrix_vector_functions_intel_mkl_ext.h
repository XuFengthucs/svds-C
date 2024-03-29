#pragma once

#include "mkl.h"
#include "matrix_vector_functions_intel_mkl.h"

/* 
    The rows/cols fields use 1-based indexing. This is due to an undocumented 
    feature of MKL library: if you are trying to cooperate sparse matrix with 
    row-major layout dense matrices, then the interfaces assume the indexing 
    is 0-based. Otherwise if you use column major dense matrices, you should 
    use 1-based indexing.
*/
typedef struct {
    MKL_INT nrows, ncols;
    MKL_INT nnz; // number of non-zero element in the matrix.
    MKL_INT capacity; // number of possible nnzs.
    double *values;
    MKL_INT *rows, *cols;
} mat_coo;

typedef struct {
    MKL_INT nnz;
    MKL_INT nrows, ncols;
    double *values;
    MKL_INT *cols;
    MKL_INT *pointerB, *pointerE;
} mat_csr;




// initialize with sizes, the only interface that allocates space for coo struct
mat_coo* coo_matrix_new(int nrows, int ncols, int capacity);

// collect allocated space.
void coo_matrix_delete(mat_coo *M);

void set_coo_matrix_element(mat_coo *M, int row, int col, double val, int force_new);

void coo_matrix_print(mat_coo *M);

void coo_matrix_matrix_mult(mat_coo *A, mat *B, mat *C);

void coo_matrix_copy_to_dense(mat_coo *A, mat *B);

void gen_rand_coo_matrix(mat_coo *M, double density);

// return a pointer, but nothing inside.
mat_csr* csr_matrix_new();

// collect the space
void csr_matrix_delete(mat_csr *M);

void csr_matrix_print(mat_csr *M);

// the only interface that allocates space for mat_csr struct and initialize with M
void csr_init_from_coo(mat_csr *D, mat_coo *M);

void csr_matrix_matrix_mult(mat_csr *A, mat *B, mat *C);

void csr_matrix_transpose_matrix_mult(mat_csr *A, mat *B, mat *C);

void csr_matrix_vector_mult(mat_csr *A, vec *x, vec *y);

void csr_matrix_transpose_vector_mult(mat_csr *A, vec *x, vec *y);
