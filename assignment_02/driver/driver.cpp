#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <iomanip>

#include "../include/bf_runner.hpp"
#include "../include/fw_runner.hpp"
#include "../include/test_utils.hpp"

using namespace std;
namespace fs = std::filesystem;

// =====================================================
// Utility: timestamp for output files
// =====================================================

string timestamp() {
    auto now = chrono::system_clock::now();
    time_t t = chrono::system_clock::to_time_t(now);

    tm tm_now{};
    localtime_r(&t, &tm_now);

    char buf[32];
    strftime(buf, sizeof(buf), "%Y%m%d_%H%M%S", &tm_now);

    return string(buf);
}

// =====================================================
// Recording helpers
// =====================================================

void recordAllBF() {
    fs::create_directories("outputs");

    string outFile = "outputs/bf_all_" + timestamp() + ".txt";
    ofstream out(outFile);

    auto files = collectTests("tests/bellman_ford");

    if (files.empty()) {
        cout << "No Bellman-Ford test files found.\\n";
        return;
    }

    cout << "Recording Bellman-Ford results to: " << outFile << "\\n";

    for (const auto& f : files) {
        cout << "Running: " << f << "\\n";
        out  << "Running: " << f << "\\n";

        // Redirect cout temporarily
        streambuf* oldBuf = cout.rdbuf();
        cout.rdbuf(out.rdbuf());

        runBellmanFord(f);

        cout.rdbuf(oldBuf);

        // Also show on terminal
        runBellmanFord(f);

        out << "\\n----------------------------------------\\n";
    }

    cout << "Saved to " << outFile << "\\n";
}

void recordAllFW() {
    fs::create_directories("outputs");

    string outFile = "outputs/fw_all_" + timestamp() + ".txt";
    ofstream out(outFile);

    auto files = collectTests("tests/floyd_warshall");

    if (files.empty()) {
        cout << "No Floyd-Warshall test files found.\\n";
        return;
    }

    cout << "Recording Floyd-Warshall results to: " << outFile << "\\n";

    for (const auto& f : files) {
        cout << "Running: " << f << "\\n";
        out  << "Running: " << f << "\\n";

        streambuf* oldBuf = cout.rdbuf();
        cout.rdbuf(out.rdbuf());

        runFloydWarshall(f);

        cout.rdbuf(oldBuf);

        runFloydWarshall(f);

        out << "\\n----------------------------------------\\n";
    }

    cout << "Saved to " << outFile << "\\n";
}

// =====================================================
// Menu
// =====================================================

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        cout << "\\n===== Assignment 02 Driver =====\\n";
        cout << "1. Run Bellman-Ford (one file)\\n";
        cout << "2. Run Floyd-Warshall (one file)\\n";
        cout << "3. Run all Bellman-Ford tests\\n";
        cout << "4. Run all Floyd-Warshall tests\\n";
        cout << "5. Run and RECORD all Bellman-Ford tests\\n";
        cout << "6. Run and RECORD all Floyd-Warshall tests\\n";
        cout << "0. Exit\\n";
        cout << "Choice: ";

        int choice;
        if (!(cin >> choice))
            break;

        if (choice == 0)
            break;

        if (choice == 1) {
            string file;
            cout << "Enter Bellman-Ford file name (e.g., bf_10.txt): ";
            cin >> file;
            runBellmanFord("tests/bellman_ford/" + file);
        }
        else if (choice == 2) {
            string file;
            cout << "Enter Floyd-Warshall file name (e.g., fw_10.txt): ";
            cin >> file;
            runFloydWarshall("tests/floyd_warshall/" + file);
        }
        else if (choice == 3) {
            for (const auto& f : collectTests("tests/bellman_ford"))
                runBellmanFord(f);
        }
        else if (choice == 4) {
            for (const auto& f : collectTests("tests/floyd_warshall"))
                runFloydWarshall(f);
        }
        else if (choice == 5) {
            recordAllBF();
        }
        else if (choice == 6) {
            recordAllFW();
        }
        else {
            cout << "Invalid choice\\n";
        }
    }

    return 0;
}
