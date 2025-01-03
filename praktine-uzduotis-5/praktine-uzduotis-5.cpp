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

struct Contact {
    string name;
    string surname;
    int phone_number;
    int birth_year; // yyyy
    int birth_month; // MM
    int birth_day; // dd
};

bool intInRange(int number, int min, int max)
{
    return number >= min && number <= max;
}

void program_2()
{
    string cmd;
    size_t numContacts = 5;
    size_t lastContactNum = 0;
    Contact* contactList = new Contact[numContacts];

    while (true) {
        cout << "\nJūsų komandą: ";
        cin >> cmd;

        if (cmd == "list" || cmd == "ls") {
            cout << "\nKontaktai:\n";

            for (size_t i = 0; i < numContacts; i++) {
                Contact& contact = contactList[i];
                cout << "\nKontaktas #" << i + 1 << '\n';
                cout << "\tName: " << contactList[i].name << '\n';
                cout << "\tSurname: " << contactList[i].surname << '\n';
                cout << "\tPhone number: " << contactList[i].phone_number << '\n';
                cout << "\tBirth date: " << contactList[i].birth_year << '\n';
            }
        } else if (cmd == "add") {
            string name;
            string surname;
            int phone_number;
            int birth_year;
            int birth_month;
            int birth_day;

            cout << "Iveskite naujo kontakto duomenis:\n";
            cout << "\tVardas: "; cin >> name;
            cout << "\tPavarde: "; cin >> surname;
            cout << "\tTelefono numeris: "; cin >> phone_number;

            while (true) {
                cout << "\tGimimo metai (1900-2100): ";
                cin >> birth_year;

                if (intInRange(birth_year, 1900, 2100)) {
                    break;
                }

                cout << "\n[KLAIDA] Gimimo metai turi buti tarp 1900 ir 2100 metu\n\n";
            }

            while (true) {
                cout << "\tGimimo menesis (1-12): ";
                cin >> birth_month;

                if (intInRange(birth_month, 1, 12)) {
                    break;
                }

                cout << "\n[KLAIDA] Gimimo menesis turi buti skaiciu tarp 1 ir 12\n\n";
            }

            while (true) {
                cout << "\tGimimo diena (1-31 | 1-28): ";
                cin >> birth_day;

                int maxDay = 31;

                if (birth_month == 2) {
                    maxDay = 28;
                }

                if (intInRange(birth_day, 1, maxDay)) {
                    break;
                }

                cout << "\n[KLAIDA] Gimimo diena turi buti skaiciu tarp 1 ir " << maxDay << "\n\n";
            }

            // to do: if (lastContactNum == numContacts + 1)

            contactList[lastContactNum] = Contact{name, surname, phone_number, birth_year, birth_month, birth_day};
            lastContactNum++;
        } else if (cmd == "delete" || cmd == "del") {
            cout << "INFO: to do\n";
        } else if (cmd == "quit" || cmd == "q") {
            cout << "\nIšeinama...\n";
            delete[] contactList;
            return;
        } else {
            cout << "\n[KLAIDA] Nežinoma komanda: " << cmd << '\n';
            cout << "[INFO] Jei norite pamatyti komandų sąrašą, pasakykite: help\n";
        }
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
