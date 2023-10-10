#include "calc_header.h"
#include <iostream>
using namespace std;

int Prioritet(char op)
{
    if (op == '*' || op == '/')         // наиболее приоритетные
    {
        return 2;
    }
    else if (op == '+' || op == '-')    // менее приоритетные
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool isOperator(char op)
{
    return op == '+' || op == '-' || op == '*' || op == '/';  // проверка на оператор
}


int Calculate(int num1, int num2, char op)
{
    switch (op)
    {
    case '+': 
        return num1 + num2;
    case '-': 
        return num1 - num2;
    case '*': 
        return num1 * num2;
    case '/':
        if (num2 == 0)
        {
            cout << "Ошибка!\n деление на 0\n";
        }
        return num1 / num2;
    default: 
        return 0;
    }
}

int Calculator::calculate(const string& task) // calculate принадлежит Calculator(структура)
{
    int i = 0;

    int length = task.length();      // длина выражения
    char* operators = new char[length];
    int* values = new int[length];

    int valIndex = 0;
    int opIndex = 0;

    while (i < length)
    {
        if (task[i] == ' ') 
        {
            i++;
            continue;
        }

        if (isdigit(task[i])) 
        {
            int num = 0;
            while (i < length && isdigit(task[i])) 
            {
                num = num * 10 + (task[i] - '0');     /* берем num, умножаем его на 10, 
                                                               затем добавляем к этому результату разницу между 
                                                               ASCII-кодом task[i] и '0'
                                                               короче - мы преобразуем символ цифры из строки task в 
                                                               целое число! и добавляем его к num*/                         
                i++;
            }
            values[valIndex++] = num;
        }
        else if (task[i] == '(')              // первая скобка
        {
            operators[opIndex++] = task[i];
            i++;
        }
        else if (task[i] == ')')              // вторая скобка
        {
            while (opIndex > 0 && operators[opIndex - 1] != '(')        /*Если opIndex больше нуля,
                                                                       еще есть необработанные операторы*/ 
            {
                char op = operators[--opIndex];
                int num1 = values[--valIndex];
                int num2 = values[--valIndex];
                values[valIndex++] = Calculate(num1, num2, op);
            }
            opIndex--;
            i++;
        }
        else if (isOperator(task[i]))
        {
            /проверяем условие, которое гарантирует, что у нас есть операторы и что текущий оператор task[i] имеет меньший приоритет/
            while (opIndex > 0 && Prioritet(operators[opIndex - 1]) > Prioritet(task[i]))
            {
                // извлекаем оператор с более высоким приоритетом и сохраняем его в переменную op
                char op = operators[--opIndex];    
                //Мы уменьшаем valIndex на 1, чтобы получить индекс последнего элемента values, сохраняем этот элемент в нум//
                //почему префиксное, а не постфиксное? чтобы сразу отнять и тут же получить, а не  в след итерации
                int num1 = values[--valIndex];      
                int num2 = values[--valIndex];
                values[valIndex++] = Calculate(num1, num2, op);
            }
            operators[opIndex++] = task[i];
            i++;
        }
    }

    while (opIndex > 0) 
    {
        char op = operators[--opIndex];
        int num1 = values[--valIndex];
        int num2 = values[--valIndex];
        values[valIndex++] = Calculate(num1, num2, op);
    }

    int result = values[0];
    delete[] values;
    delete[] operators;


    return result;
}
