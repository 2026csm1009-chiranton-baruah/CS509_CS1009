#include "../include/gemm.h"
#include "../include/csr.h"

#include <chrono>
#include <filesystem>
#include <iostream>
#include <vector>

namespace fs = std::filesystem;
using namespace std;
using namespace std::chrono;

void runGEMM(const fs::path& testDir);
void runCSR(const fs::path& testDir);

int main(int argc, char* argv[])
{
    try
    {
        // Directory containing the executable
        fs::path exeDir = fs::canonical(argv[0]).parent_path();

        // Tests folder (assignment1 is built inside assignment_01/)
        fs::path testDir = exeDir / "tests";

        if (!fs::exists(testDir))
        {
            cerr << "Error: Test directory not found:\n"
                 << testDir << endl;
            return 1;
        }

        int choice;

        while (true)
        {
            cout << "\n======================================\n";
            cout << "      CS509 Assignment 1\n";
            cout << "======================================\n";
            cout << "1. GEMM (Simple + Blocking)\n";
            cout << "2. CSR Graph Conversion\n";
            cout << "0. Exit\n";
            cout << "\nEnter choice: ";

            cin >> choice;

            switch (choice)
            {
                case 1:
                    runGEMM(testDir);
                    break;

                case 2:
                    runCSR(testDir);
                    break;

                case 0:
                    cout << "\nGoodbye!\n";
                    return 0;

                default:
                    cout << "\nInvalid choice.\n";
            }
        }
    }
    catch (const exception& e)
    {
        cerr << "Fatal error: " << e.what() << endl;
        return 1;
    }
}

void runGEMM(const fs::path& testDir)
{
    string filename;

    cout << "\nEnter GEMM input filename: ";
    cin >> filename;

    fs::path fullPath = testDir / filename;

    if (!fs::exists(fullPath))
    {
        cerr << "Error: File not found:\n"
             << fullPath << endl;
        return;
    }

    Matrix A, B;
    int M, K, N;

    if (!readMatrices(fullPath.string().c_str(), A, B, M, K, N))
        return;

    auto start = high_resolution_clock::now();

    Matrix result1 = gemmSimple(A, B, M, K, N);

    auto stop = high_resolution_clock::now();

    cout << "\n===== GEMM Simple =====\n";
    printMatrix(result1);

    cout << "\nExecution Time: "
         << duration<double, milli>(stop - start).count()
         << " ms\n";

    constexpr int BLOCK_SIZE = 32;

    start = high_resolution_clock::now();

    Matrix result2 =
        gemmBlocking(A, B, M, K, N, BLOCK_SIZE);

    stop = high_resolution_clock::now();

    cout << "\n===== GEMM Blocking =====\n";
    printMatrix(result2);

    cout << "\nExecution Time: "
         << duration<double, milli>(stop - start).count()
         << " ms\n";
}

void runCSR(const fs::path& testDir)
{
    string filename;

    cout << "\nEnter CSR graph filename: ";
    cin >> filename;

    fs::path fullPath = testDir / filename;

    if (!fs::exists(fullPath))
    {
        cerr << "Error: File not found:\n"
             << fullPath << endl;
        return;
    }

    vector<vector<Edge>> adjacencyList;

    int V, E;
    bool weighted = false;

    if (!readAdjacencyList(fullPath.string(),
                           adjacencyList,
                           weighted,
                           V,
                           E))
        return;

    auto start = high_resolution_clock::now();

    CSRGraph graph =
        convertToCSR(adjacencyList, weighted);

    auto stop = high_resolution_clock::now();

    cout << "\n===== CSR Representation =====\n";
    printCSR(graph, weighted);

    cout << "\nConversion Time: "
         << duration<double, milli>(stop - start).count()
         << " ms\n";
}
