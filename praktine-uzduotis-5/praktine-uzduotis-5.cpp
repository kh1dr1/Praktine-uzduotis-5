#pragma execution_character_set("utf-8")

#include <iostream>
#include <string>

using namespace std;

void printHelp() {
    cout << "\nKomandų sąrašas:\n\n";

    cout << "Pagrindinės komandos:\n";
    cout << "input      Įvesti vienos ląstelės reikšmę\n";
    cout << "fastinput  Įvesti lentelės reikšmes\n";
    cout << "print      Atspausdinti lentelę\n";
    cout << "rowsum     Apskaičiuoti kiekvienos eilutės sumą\n";
    cout << "colsum     Apskaičiuoti kiekvieno stulpelio sumą\n";
    cout << "max        Rasti didžiausią reikšmę lentelėje\n\n";

    cout << "Pagalbinės komandos:\n";
    cout << "h, help  Pamatyti komandų sąraša\n";
    cout << "q, quit  Išeiti iš programos\n";
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
    int rows = 0;
    int cols = 0;
    int *arr = nullptr;

    string cmd;
    int x = 0;
    int y = 0;
    int val = 0;

    cout << "Įveskite lentelės dydį\n";
    cin >> rows >> cols;

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

    while (cmd != "quit" && cmd != "q") {
        cout << "Jūsų komandą: ";
        cin >> cmd;

        if (cmd == "q" || cmd == "quit") {
            cout << "Išeinama...\n";
        } else if (cmd == "h" || cmd == "help") {
            printHelp();
        } else if (cmd == "input") {
            cout << "Įveskite ląstelės koordinates\n";
            cin >> x >> y;

            if (x >= 0 && x < rows && y >= 0 && y < cols) {
                int elem = to_real_index(x, y, cols);

                cout << "Įveskite reikšmę\n";
                cin >> val;

                arr[elem] = val;
            } else {
                cout << "Klaida: \n";
            }
        } else if (cmd == "print") {
            printArr(arr, rows, cols);
        } else {
            cout << "Klaida: nežinoma komanda '" << cmd << "'\n";
        }
        
    }

    delete[] arr;

    return 0;
}
