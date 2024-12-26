#ifdef _WIN32
#pragma execution_character_set("utf-8")
#endif // _WIN32

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void printHelp() {
    cout << "\nKomandų sąrašas:\n\n";

    cout << "Pagrindinės komandos:\n";
    cout << "[i]: Įvesti vienos ląstelės reikšmę\n";
    cout << "[f]: Įvesti lentelės reikšmes\n";
    cout << "[p]: Atspausdinti lentelę\n";
    cout << "[r]: Apskaičiuoti kiekvienos eilutės sumą\n";
    cout << "[c]: Apskaičiuoti kiekvieno stulpelio sumą\n";
    cout << "[m]: Rasti didžiausią reikšmę lentelėje\n\n";

    cout << "Pagalbinės komandos:\n";
    cout << "[h]: Pamatyti komandų sąraša\n";
    cout << "[q]: Išeiti iš programos\n";
}

int strToInt(const string &str) {
    stringstream ss;
    int result = 0;
    ss << str;
    ss >> result;
    return result;
}

// R = i * cols + j
int real_index(int x, int y, int cols) { return x * cols + y; }

// v_inv = rows - v - 1
int inverseVerticalAxis(int v, int rows) { return rows - v - 1; }

int getCharsInNumber(int number) {
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

void printArr(int *arr, int rows, int cols) {
    cout << '\n' << '+';
    for (int x = 0; x < cols; x++) {
        cout << "---+";
    }
    cout << '\n';

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << "| ";
            int elem = real_index(i, j, cols);
            cout << arr[elem] << " ";
        }
        cout << '|' << '\n' << '+';
        for (int x = 0; x < cols; x++) {
            cout << "---+";
        }
        cout << '\n';
    }
}

int main() {
#ifdef _WIN32
    system("chcp 65001"); // utf-8
#endif // _WIN32

    int rows = 0;
    int cols = 0;
    int size = 0;
    int *arr = nullptr;

    char cmd = 0;
    int x = 0;
    int y = 0;
    int val = 0;
    string fi_val;

    int max = 0;

    cout << "\nĮveskite lentelės dydį (X, Y): ";
    cin >> cols >> rows; // Y, X

    if (rows < 1 || cols < 1) {
        cout << "Klaida: lentelės dydis turi būti sudarytas iš teigiamų "
                "skaičių\n";
        exit(1);
    }

    size = rows * cols;
    arr = new int[size];

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int elem = real_index(i, j, cols);
            arr[elem] = 0;
        }
    }

    while (cmd != 'q') {
        cout << "\nJūsų komandą: ";
        cin >> cmd;

        switch (cmd) {
            case 'i':
                cout << "\nĮveskite ląstelės koordinates (X, Y): ";
                cin >> y >> x;
                x = inverseVerticalAxis(x, rows);

                if (x >= 0 && x < rows && y >= 0 && y < cols) {
                    int elem = real_index(x, y, cols);

                    cout << "Įveskite reikšmę: ";
                    cin >> val;

                    arr[elem] = val;
                } else {
                    cout << "Klaida: įvestos per didelės koordinatės\n";
                }

                break;
            case 'f':
                cout << "\nĮveskite " << size << " reikšmes\n";
                cout << "Jei norite išeiti, įveskite \"q\"\n";
                cout << "\n---- Įvedimo pradžia ----\n";

                for (int i = 0; i < size; i++) {
                    cin >> fi_val;
                    if (fi_val == "q")
                        break;
                    val = strToInt(fi_val);
                    arr[i] = val;
                }

                cout << "---- Įvedimo pabaiga ----\n";
                break;
            case 'p':
                printArr(arr, rows, cols);
                break;
            case 'r':

                break;
            case 'c':

                break;
            case 'm':
                for (int i = 0; i < size; i++) {
                    if (arr[i] > max) {
                        max = arr[i];
                    }
                }
                cout << "Didžiausia reikšmė lentelėje: " << max << '\n';
                break;
            case 'h':
                printHelp();
                break;
            case 'q':
                cout << "Išeinama...\n";
                break;
            default:
                cout << "Klaida: nežinoma komanda '" << cmd << "'\n";
                cout << "Jei norite pamatyti komandų sąrašą, pasirinkite 'h'\n";
                break;
        }
    }

    delete[] arr;

    return 0;
}
