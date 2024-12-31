#ifdef _WIN32
#pragma execution_character_set("utf-8")
#endif // _WIN32

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void printHelp()
{
    cout << "\nKomandų sąrašas:\n\n";

    cout << "Pagrindinės komandos:\n";
    cout << "   input, i       Įvesti vienos ląstelės reikšmę\n";
    cout << "   fastinput, fi  Įvesti lentelės reikšmes\n";
    cout << "   print, p       Atspausdinti lentelę\n";
    cout << "   rowsum, r      Apskaičiuoti kiekvienos eilutės sumą\n";
    cout << "   colsum, c      Apskaičiuoti kiekvieno stulpelio sumą\n";
    cout << "   max, m         Rasti didžiausią reikšmę lentelėje\n\n";

    cout << "Pagalbinės komandos:\n";
    cout << "   help, h   Pamatyti komandų sąraša\n";
    cout << "   quit, q   Išeiti iš programos\n";
}

int strToInt(const string &str)
{
    stringstream ss;
    int result = 0;
    ss << str;
    ss >> result;
    return result;
}

int real_cell(const int i, const int j, const int cols) { return i * cols + j; }

void flip_axis(int &axis, const int size) { axis = size - axis + 1; }

int getCharsInNumber(int number)
{
    if (number == 0) {
        return 1;
    }

    bool result = 0;
    if (number < 0) {
        result = 1;
    }

    number = abs(number);
    return static_cast<int>(log10(number)) + 1 + (int)result;
}

void printArr(int *arr, int rows, int cols)
{
    cout << '\n' << '+';
    for (int x = 0; x < cols; x++) {
        cout << "---+";
    }
    cout << '\n';

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << "| ";
            int elem = real_cell(i, j, cols);
            cout << arr[elem] << " ";
        }
        cout << '|' << '\n' << '+';
        for (int x = 0; x < cols; x++) {
            cout << "---+";
        }
        cout << '\n';
    }
}

int main()
{
#ifdef _WIN32
    system("chcp 65001"); // utf-8
#endif // _WIN32

    int rows = 0;
    int cols = 0;
    int size = 0;
    int *arr = nullptr;

    string cmd;

    int max = 0;

    while (true) {
        cout << "\nĮveskite lentelės dydį (X, Y): ";
        cin >> cols >> rows; // Y, X

        if (rows > 0 && cols > 0)
            break;

        // else
        cout << "[KLAIDA] Lentelės dydis turi būti sudarytas iš teigiamų skaičių\n";
    }

    size = rows * cols;
    arr = new int[size];

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int elem = real_cell(i, j, cols);
            arr[elem] = 0;
        }
    }

    bool keepRunning = true;
    while (keepRunning) {
        cout << "\nJūsų komandą: ";
        cin >> cmd;

        if (cmd == "input" || cmd == "i") {
            int x = 0;
            int y = 0;
            int val = 0;

            cout << "\nĮveskite ląstelės koordinates (X, Y): ";
            cin >> y >> x;
            flip_axis(x, rows);

            if (x >= 1 && x <= rows && y >= 0 && y <= cols) {
                int elem = real_cell(x - 1, y - 1, cols);

                cout << "Įveskite reikšmę: ";
                cin >> val;

                arr[elem] = val;
            } else {
                cout << "\n[KLAIDA] Įvestos klaidingos koordinatės\n";
            }
        } else if (cmd == "fastinput" || cmd == "fi") {
            string fi_val;
            int val = 0;

            cout << "\nĮveskite " << size << " reikšmes\n";
            cout << "Jei norite išeiti, įveskite: q\n";
            cout << "\n---- Įvedimo pradžia ----\n";

            for (int i = 0; i < size; i++) {
                cin >> fi_val;
                if (fi_val == "q")
                    break;
                val = strToInt(fi_val);
                arr[i] = val;
            }

            cout << "---- Įvedimo pabaiga ----\n";
        } else if (cmd == "print" || cmd == "p") {
            printArr(arr, rows, cols);
        } else if (cmd == "rowsum" || cmd == "r") {
            for (int i = 0; i < rows; i++) {
                int rowSum = 0;

                for (int j = 0; j < cols; j++) {
                    int elem = real_cell(i, j, cols);
                    rowSum += arr[elem];
                }

                cout << "Eilutes nr. " << i + 1 << " suma: " << rowSum << '\n';
            }
        } else if (cmd == "colsum" || cmd == "c") {
            for (int j = 0; j < cols; j++) {
                int colSum = 0;

                for (int i = 0; i < rows; i++) {
                    int elem = real_cell(i, j, cols);
                    colSum += arr[elem];
                }
                
                cout << "Stulpelio nr. " << j + 1 << " suma: " << colSum << '\n';
            }
        } else if (cmd == "max" || cmd == "m") {
            for (int i = 0; i < size; i++) {
                if (arr[i] > max) {
                    max = arr[i];
                }
            }
            cout << "Didžiausia reikšmė lentelėje: " << max << '\n';
        } else if (cmd == "help" || cmd == "h") {
            printHelp();
        } else if (cmd == "quit" || cmd == "q") {
            cout << "\nIšeinama...\n";
            keepRunning = false;
        } else {
            cout << "\n[KLAIDA] Nežinoma komanda: " << cmd << '\n';
            cout << "[INFO] Jei norite pamatyti komandų sąrašą, pasakykite: help\n";
        }
    }

    delete[] arr;

    return 0;
}
