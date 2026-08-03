#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    int choice;
    string filename;

    while (true)
    {
        cout << "\n=====================================\n";
        cout << "      CS509 Common Wrapper\n";
        cout << "=====================================\n";
        cout << "1. Run Assignment 1 (GEMM)\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Enter input file path: ";
                cin >> filename;

#ifdef _WIN32
                system(("~\\assignment_01\\driver\\driver.exe " + filename).c_str());
#else
                system(("./assignment_01/driver/driver " + filename).c_str());
#endif
                break;

            case 2:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice.\n";
        }
    }

    return 0;
}
