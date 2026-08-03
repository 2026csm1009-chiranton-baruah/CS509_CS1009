#include "../include/gemm.h"

#include <iostream>
#include <fstream>

using namespace std;

/*
 * Reads matrices from the input file.
 * Format:
 * M K N
 * A matrix (M x K)
 * B matrix (K x N)
 */
bool readMatrices(const char* filename,
                  Matrix &A,
                  Matrix &B,
                  int &M,
                  int &K,
                  int &N)
{
    ifstream fin(filename);

    if (!fin.is_open())
    {
        cerr << "Error: Cannot open input file." << endl;
        return false;
    }

    fin >> M >> K >> N;

    A.assign(M, vector<int>(K));
    B.assign(K, vector<int>(N));

    // Read Matrix A
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < K; j++)
        {
            fin >> A[i][j];
        }
    }

    // Read Matrix B
    for (int i = 0; i < K; i++)
    {
        for (int j = 0; j < N; j++)
        {
            fin >> B[i][j];
        }
    }

    fin.close();
    return true;
}

/*
 * Prints a matrix.
 */
void printMatrix(const Matrix &C)
{
    for (size_t i = 0; i < C.size(); i++)
    {
        for (size_t j = 0; j < C[i].size(); j++)
        {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }
}

/*
 * Standard GEMM
 * Time Complexity:
 * O(M × K × N)
 */
Matrix gemmSimple(const Matrix &A,
                  const Matrix &B,
                  int M,
                  int K,
                  int N)
{
    Matrix C(M, vector<int>(N, 0));

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int sum = 0;

            for (int k = 0; k < K; k++)
            {
                sum += A[i][k] * B[k][j];
            }

            C[i][j] = sum;
        }
    }

    return C;
}
