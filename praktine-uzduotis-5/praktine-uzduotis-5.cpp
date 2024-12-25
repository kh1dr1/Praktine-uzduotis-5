#pragma execution_character_set("utf-8")

#include <iostream>

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

int to_real_index(int x, int y, int cols) {
    return x * cols + y; // i * cols + j
}

void printArr(int *arr, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int elem = to_real_index(i, j, cols);
            cout << arr[elem] << " ";
        }
        cout << '\n';
    }
}

int main() {
    system("chcp 65001"); // utf-8

    int rows = 0;
    int cols = 0;
    int *arr = nullptr;

    char cmd = 0;
    int x = 0;
    int y = 0;
    int val = 0;

    cout << "\nĮveskite lentelės dydį (X, Y):\n";
    cin >> cols >> rows; // Y, X

    if (rows < 1 || cols < 1) {
        cout << "Klaida: lentelės dydis turi būti sudarytas iš teigiamų "
                "skaičių\n";
        exit(1);
    }

    arr = new int[rows * cols];

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int elem = to_real_index(i, j, cols);
            arr[elem] = 0;
        }
    }

    while (cmd != 'q') {
        cout << "\nJūsų komandą: ";
        cin >> cmd;

        switch (cmd) {
            case 'i':
                cout << "\nĮveskite ląstelės koordinates\n";
                cin >> x >> y;

                if (x >= 0 && x < rows && y >= 0 && y < cols) {
                    int elem = to_real_index(x, y, cols);

                    cout << "\nĮveskite reikšmę\n";
                    cin >> val;

                    arr[elem] = val;
                } else {
                    cout << "Klaida: \n";
                }
                break;
            case 'f':

                break;
            case 'p':
                printArr(arr, rows, cols);
                break;
            case 'r':

                break;
            case 'c':

                break;
            case 'm':

                break;
            case 'h':
                printHelp();
                break;
            case 'q':
                cout << "Išeinama...\n";
                break;
            default:
                cout << "Klaida: nežinoma komanda '" << cmd << "'\n";
                break;
        }
    }

    delete[] arr;

    return 0;
}
