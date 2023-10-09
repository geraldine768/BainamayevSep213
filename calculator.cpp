#include <iostream>
#include <windows.h>
#include "calc_header.h"

using namespace std;


int main()
{
    setlocale(LC_ALL, "RUS");
    string task;

    cout << "Введите арифметическое выражение: \n";
    getline(cin, task);

    Calculator calculator;
    int result = calculator.calculate(task);

    cout << "Результат: " << result << endl;

    return 0;
}