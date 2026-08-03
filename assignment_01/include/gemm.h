#ifndef GEMM_H
#define GEMM_H

#include <vector>

using namespace std;

// Matrix type
typedef vector<vector<int>> Matrix;

// Read matrices from input file
bool readMatrices(const char* filename,
                  Matrix &A,
                  Matrix &B,
                  int &M,
                  int &K,
                  int &N);

// Simple GEMM
Matrix gemmSimple(const Matrix &A,
                  const Matrix &B,
                  int M,
                  int K,
                  int N);

// Blocking GEMM
Matrix gemmBlocking(const Matrix &A,
                    const Matrix &B,
                    int M,
                    int K,
                    int N,
                    int blockSize);

// Print matrix
void printMatrix(const Matrix &C);

#endif
