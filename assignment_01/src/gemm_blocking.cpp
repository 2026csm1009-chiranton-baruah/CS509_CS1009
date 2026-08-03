#include "../include/gemm.h"

using namespace std;

/*
 * Blocked (Tiled) GEMM
 *
 * Improves cache locality by multiplying matrices in
 * smaller blocks instead of entire rows/columns.
 *
 * Time Complexity:
 * O(M × K × N)
 *
 * Space Complexity:
 * O(M × N)
 */

Matrix gemmBlocking(const Matrix &A,
                    const Matrix &B,
                    int M,
                    int K,
                    int N,
                    int blockSize)
{
    Matrix C(M, vector<int>(N, 0));

    // Iterate over blocks
    for (int ii = 0; ii < M; ii += blockSize)
    {
        for (int jj = 0; jj < N; jj += blockSize)
        {
            for (int kk = 0; kk < K; kk += blockSize)
            {
                // Multiply the current block
                for (int i = ii; i < min(ii + blockSize, M); i++)
                {
                    for (int j = jj; j < min(jj + blockSize, N); j++)
                    {
                        int sum = C[i][j];

                        for (int k = kk; k < min(kk + blockSize, K); k++)
                        {
                            sum += A[i][k] * B[k][j];
                        }

                        C[i][j] = sum;
                    }
                }
            }
        }
    }

    return C;
}
