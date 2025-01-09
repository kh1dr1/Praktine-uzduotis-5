#ifdef _WIN32
#pragma execution_character_set("utf-8")
#endif // _WIN32

#include <algorithm>
#include <cmath>
#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

using namespace std;
using sv = string_view;

const size_t INIT_CONTACT_COUNT = 10;
const string TAB = "  ";

void print(sv info, sv text, size_t LF_count = 1)
{
    cout << "\n[" << info << "] " << text;
    for (size_t i = 0; i < LF_count; i++) {
        cout << '\n';
    }
}

void printTableHelp()
{
    cout << "\nKomandų sąrašas:\n\n";

    cout << "Pagrindinės komandos:\n";
    cout << "  input, i       Įvesti vienos ląstelės reikšmę\n";
    cout << "  fastinput, fi  Įvesti lentelės reikšmes\n";
    cout << "  print, p       Atspausdinti lentelę\n";
    cout << "  rowsum, r      Apskaičiuoti kiekvienos eilutės sumą\n";
    cout << "  colsum, c      Apskaičiuoti kiekvieno stulpelio sumą\n";
    cout << "  max, m         Rasti didžiausią reikšmę lentelėje\n\n";

    cout << "Pagalbinės komandos:\n";
    cout << "  help, h   Pamatyti komandų sąraša\n";
    cout << "  quit, q   Išeiti iš programos\n";
}

void printContactsHelp()
{
    cout << "\nKomandų sąrašas:\n\n";

    cout << "Pagrindinės komandos:\n";
    cout << "  add, new, create  Sukurti naują kontaktą\n";
    cout << "  list, ls          Pamatyti kontaktų sąrašą\n";
    cout << "  edit              Keisti kontakto duomenis\n";
    cout << "  delete, del       Ištrinti kontaktą\n\n";

    cout << "Pagalbinės komandos:\n";
    cout << "  help, h   Pamatyti komandų sąraša\n";
    cout << "  quit, q   Išeiti iš programos\n";
}

void printOptHelp()
{
    cout << "\nPasirinkite opciją:\n";
    cout << "  -l, --lentele     Pamatyti komandų sąraša\n";
    cout << "  -k, --kontaktai   Išeiti iš programos\n";
}

int strToInt(const string& str)
{
    stringstream ss;
    int result = 0;
    ss << str;
    ss >> result;
    return result;
}

int real_cell(const int i, const int j, const int cols) { return i * cols + j; }

void flip_axis(int& axis, const int size) { axis = size - axis + 1; }

void printArr(int* arr, int rows, int cols)
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
    int phone_number{};
    int birth_year{}; // yyyy
    int birth_month{}; // MM
    int birth_day{}; // dd
};

string toDateString(int year, int month, int day)
{
    ostringstream oss;
    oss << year << '-' << month << '-' << day;
    return oss.str();
}

void printContact(const Contact& contact, size_t ID)
{
    cout << "\n--- Kontakto nr. " << ID << " duomenys ---\n";
    cout << TAB << "Vardas: " << contact.name << '\n';
    cout << TAB << "Pavardė: " << contact.surname << '\n';
    cout << TAB << "Telefono num.: " << contact.phone_number << '\n';
    cout << TAB << "Gimimo data: " << toDateString(contact.birth_year, contact.birth_month, contact.birth_day) << '\n';
}

bool intInRange(int number, int min, int max) { return number >= min && number <= max; }

size_t resizeContactList(Contact*& list, const size_t& size)
{
    if (list == nullptr) {
        list = new Contact[INIT_CONTACT_COUNT];
        return INIT_CONTACT_COUNT;
    }

    size_t newSize = size * 2;
    Contact* newList = new Contact[newSize];

    copy(list, list + size, newList);
    delete[] list;

    list = newList;
    return newSize;
}

Contact* removeElem(Contact* arr, size_t& size, size_t elemNum)
{
    // if (list == nullptr) { // ??
    // ....

    if (elemNum < 0 || elemNum >= size)
    {
        print("error", "elemNum out of range");
        return arr;
    }

    Contact* newArr = new Contact[size - 1];

    for (size_t i = 0; i < elemNum; i++) {
        newArr[i] = arr[i];
    }

    for (size_t i = elemNum + 1; i < size; i++) {
        newArr[i - 1] = arr[i]; // C6385
    }

    size--;
    delete[] arr;

    return newArr;
}

void addContactToList(Contact*& list, size_t& size, size_t& lastIndex, Contact& contact)
{
    if (lastIndex >= size) {
        size = resizeContactList(list, size);
    }

    list[lastIndex] = contact;
    lastIndex++;
}

void printContactList(Contact* list, size_t size)
{
    cout << "\nKontaktai:\n";
    for (size_t i = 0; i < size; i++) {
        printContact(list[i], i + 1);
    }
}

int getValidIntInput(int min, int max, string_view msg)
{
    int input = 0;

    while (true) {
        cout << TAB << msg << " (nuo " << min << " iki " << max << "): ";
        cin >> input;

        if (intInRange(input, min, max)) {
            break;
        }

        print("klaida", "Įvestas neteisingas skaičius", 2);
    }

    return input;
}

int getMaxDaysInMonth(int yearNum, int monthNum)
{
    using namespace std::chrono;

    unsigned int month_num = static_cast<unsigned int>(monthNum);

    year_month ym{year{yearNum}, month{month_num}};
    auto last_day = year_month_day{ym / last};

    return static_cast<unsigned>(last_day.day());
}

Contact getContactInput(sv msg = "")
{
    string name, surname;
    int phoneNum;

    cout << "\nĮveskite " << msg << " kontakto duomenis:\n";

    cout << TAB << "Vardas: ";
    cin >> name;

    cout << TAB << "Pavardė: ";
    cin >> surname;

    cout << TAB << "Telefono numeris: ";
    cin >> phoneNum;

    int year = getValidIntInput(1900, 2100, "Gimimo metai");
    int month = getValidIntInput(1, 12, "Gimimo mėnesis");

    int maxDay = getMaxDaysInMonth(year, month);
    int day = getValidIntInput(1, maxDay, "Gimimo diena");

    return Contact{name, surname, phoneNum, year, month, day};
}

void createContact(Contact*& arr, size_t& size, size_t& last)
{
    Contact newContact = getContactInput("naujo");
    addContactToList(arr, size, last, newContact);
}

Contact* deleteContact(Contact* arr, size_t& size, size_t& last)
{
    int contactId = 0;
    cout << "\nĮveskite kontakto ID: ";
    cin >> contactId;

    if (contactId < 1 || contactId > last) {
        print("klaida", "Neteisingas kontakto ID");
        return arr;
    }

    contactId--;

    size--;
    last--;
    
    return removeElem(arr, size, contactId);
}

void editContact(Contact* arr, size_t size, size_t last) { 
    int contactId = 0;

    cout << "\nĮveskite kontakto ID: ";
    cin >> contactId;

    if (contactId < 1 || contactId > last) {
        print("klaida", "Neteisingas kontakto ID");
        return;
    }

    Contact newData = getContactInput();
    contactId--;

    arr[contactId] = newData;
}

void prog_contacts()
{
    string cmd;
    size_t numContacts = 0;
    size_t lastContactNum = 0;
    Contact* contactList = nullptr;

    while (true) {
        cout << "\nJūsų komandą: ";
        cin >> cmd;

        if (cmd == "list" || cmd == "ls") {
            printContactList(contactList, lastContactNum);
        } else if (cmd == "new" || cmd == "create" || cmd == "add") {
            createContact(contactList, numContacts, lastContactNum);
        } else if (cmd == "delete" || cmd == "del") {
            contactList = deleteContact(contactList, numContacts, lastContactNum);
        } else if (cmd == "edit") {
            editContact(contactList, numContacts, lastContactNum);
        } else if (cmd == "help" || cmd == "h") {
            printContactsHelp();
        } else if (cmd == "quit" || cmd == "q") {
            cout << "\nIšeinama...\n";
            break;
        } else {
            cout << "\n[KLAIDA] Nežinoma komanda: " << cmd << '\n';
            cout << "[INFO] Jei norite pamatyti komandų sąrašą, pasakykite: help\n";
        }
    }

    delete[] contactList;
}

void prog_table()
{
    int rows = 0;
    int cols = 0;
    int size = 0;
    int* arr = nullptr;

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
            printTableHelp();
        } else if (cmd == "quit" || cmd == "q") {
            cout << "\nIšeinama...\n";
            keepRunning = false;
        } else {
            cout << "\n[KLAIDA] Nežinoma komanda: " << cmd << '\n';
            cout << "[INFO] Jei norite pamatyti komandų sąrašą, pasakykite: help\n";
        }
    }

    delete[] arr;
}

int main(int argc, char* argv[])
{
#ifdef _WIN32
    system("chcp 65001"); // utf-8
#endif // _WIN32

    if (argv[1] == nullptr) {
        print("klaida", "Pasirinkite opciją");
        printOptHelp();
        return 1;
    }

    string opt = argv[1];

    if (opt == "-l" || opt == "--lentele") {
        prog_table();
    } else if (opt == "-k" || opt == "--kontaktai") {
        prog_contacts();
    } else {
        print("klaida", "Neteisingas pasirinkimas");
        printOptHelp();
        return 1;
    }

    return 0;
}
