#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <ctime>

using namespace std; // 0_0 Ну тут иначе никак

vector<int> inputFromKeyboard() {
    vector<int> data;
    int num;
    cout << "Введите числа:\n";
    while (cin >> num) {
        data.push_back(num);
        if (cin.peek() == '\n') break;
    }
    cin.clear();
    cin.ignore();
    return data;
}

vector<int> generateRandomData(int count) {
    vector<int> data;
    srand(time(0));
    for (int i = 0; i < count; ++i) {
        data.push_back(rand() % 100);
    }

    cout << "Сгенерированные данные:\n";
    for (int n : data) cout << n << " ";
    cout << endl;
    return data;
}

vector<int> readFromFile(const string& filename) {
    vector<int> data;
    ifstream fin("../"+filename);
    if (!fin) {
        cout << "Ошибка открытия файла!\n";
        return data;
    }
    int num;
    while (fin >> num) {
        data.push_back(num);
    }
    return data;
}

vector<int> chooseInputMethod() {
    cout << "Выберите способ ввода данных:\n"
         << "1. С клавиатуры\n"
         << "2. Случайные числа\n"
         << "3. Из файла\n";
    int choice;
    cin >> choice;
    cin.ignore();

    switch (choice) {
        case 1:
            return inputFromKeyboard();
        case 2:
            int count;
            cout << "Введите количество случайных чисел: ";
            cin >> count;
            return generateRandomData(count);
        case 3:
            string filename;
            cout << "Введите имя файла: ";
            cin >> filename;
            return readFromFile(filename);
    }
}

void task1() {
    list<int> L;
    vector<int> temp = chooseInputMethod();

    if (temp.size() % 3 != 0) {
        cout << "Ошибка: количество чисел не делится на 3\n";
        return;
    }

    L.assign(temp.begin(), temp.end());
    auto it = L.begin();
    advance(it, L.size() / 3);

    cout << "Результат:\n";
    for (auto i = L.begin(); i != it; ++i)
        cout << *i << " ";

    auto mid = it;
    advance(mid, L.size() / 3);
    for (auto i = mid; i != it;)
        cout << *(--i) << " ";

    auto end = L.end();
    for (auto i = end; i != mid;)
        cout << *(--i) << " ";

    cout << endl;
}

void task2() {
    vector<int> V = chooseInputMethod();

    if (V.size() % 2 != 0) {
        cout << "Ошибка: количество элементов нечетное\n";
        return;
    }

    auto pos = V.begin() + V.size() / 2;
    V.insert(pos, 5, 0);

    cout << "Результат:\n";
    for (int n : V) cout << n << " ";
    cout << endl;
}

void task3() {
    list<int> L1, L2;

    cout << "Введите данные для L1:\n";
    vector<int> temp1 = chooseInputMethod();

    cout << "Введите данные для L2:\n";
    vector<int> temp2 = chooseInputMethod();

    if (temp1.size() != temp2.size()) {
        cout << "Ошибка: списки разной длины\n";
        return;
    }

    L1.assign(temp1.begin(), temp1.end());
    L2.assign(temp2.begin(), temp2.end());

    auto i1 = L1.begin();
    auto i2 = L2.begin();
    int N = L1.size();

    for (int i = 0; i < N; ++i) {
        L2.splice(next(i2), L1, i1++);
        advance(i2, 2);
    }

    cout << "Результат L2:\n";
    for (int n : L2) cout << n << " ";
    cout << endl;
}

void task4() {
    int K;
    string name1 = "../task4In.txt", name2 = "../task4Out.txt";

    cout << "Введите K: "; cin >> K;

    ifstream fin(name1);
    ofstream fout(name2);

    remove_copy_if(
        istream_iterator<string>(fin),
        istream_iterator<string>(),
        ostream_iterator<string>(fout, "\n"),
        [K](const string& s) { return s.length() > K; }
    );

    cout << "Файл записан\n";
}

int main() {
    setlocale(LC_ALL, "Russian");

    int choice;
    do {
        cout << "\nВыберите задание:\n"
             << "1. Task1\n"
             << "2. Task2\n"
             << "3. Task3\n"
             << "4. Task4\n"
             << "0. Выход\n> ";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1: task1(); break;
            case 2: task2(); break;
            case 3: task3(); break;
            case 4: task4(); break;
            case 0: break;
            default: cout << "Неверный выбор\n";
        }
    } while(choice != 0);

    return 0;
}