#include <iostream>

#include "../include/bf_runner.hpp"
#include "../include/fw_runner.hpp"
#include "../include/test_utils.hpp"

using namespace std;

int main() {
    while (true) {
        cout << "\\n===== Assignment 02 Driver =====\\n";
        cout << "1. Run Bellman-Ford (one file)\\n";
        cout << "2. Run Floyd-Warshall (one file)\\n";
        cout << "3. Run all Bellman-Ford tests\\n";
        cout << "4. Run all Floyd-Warshall tests\\n";
        cout << "0. Exit\\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;

        if (choice == 0) break;

        if (choice == 1) {
            string path;
            cout << "Enter file path: ";
            cin >> path;
            runBellmanFord(path);
        }
        else if (choice == 2) {
            string path;
            cout << "Enter file path: ";
            cin >> path;
            runFloydWarshall(path);
        }
        else if (choice == 3) {
            for (const auto& f : collectTests("tests/bellman_ford"))
                runBellmanFord(f);
        }
        else if (choice == 4) {
            for (const auto& f : collectTests("tests/floyd_warshall"))
                runFloydWarshall(f);
        }
    }
}
