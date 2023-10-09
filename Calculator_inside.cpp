#include "calc_header.h"
#include <iostream>
using namespace std;

int Prioritet(char op)
{
    if (op == '*' || op == '/')         // �������� ������������
    {
        return 2;
    }
    else if (op == '+' || op == '-')    // ����� ������������
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
    return op == '+' || op == '-' || op == '*' || op == '/';  // �������� �� ��������
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
            cout << "������!\n ������� �� 0\n";
        }
        return num1 / num2;
    default: 
        return 0;
    }
}

int Calculator::evaluateExpression(const string& task) // evaluateExpression ����������� Calculator(���������)
{
    int i = 0;

    int length = task.length();      // ����� ���������
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
                num = num * 10 + (task[i] - '0');     /* ��� ������ ����� �������� num, �������� ��� �� 10, 
                                                               ����� ��������� � ����� ���������� ������� ����� 
                                                               ASCII-����� task[i] � '0'
                                                               ������ - �� ����������� ������ ����� �� ������ task � 
                                                               ����� �����! � ��������� ��� � num*/                         
                i++;
            }
            values[valIndex++] = num;
        }
        else if (task[i] == '(')              // ������ ������
        {
            operators[opIndex++] = task[i];
            i++;
        }
        else if (task[i] == ')')              // ������ ������
        {
            while (opIndex > 0 && operators[opIndex - 1] != '(')        /*���� opIndex ������ ����,
                                                                       ��� ���� �������������� ���������*/ 
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
            /*��������� �������, ������� �����������, ��� � ��� ���� ��������� � ��� ������� �������� task[i] ����� ������� ���������*/
            while (opIndex > 0 && Prioritet(operators[opIndex - 1]) > Prioritet(task[i]))
            {
                // ��������� �������� � ����� ������� ����������� � ��������� ��� � ���������� op
                char op = operators[--opIndex];    
                //�� ��������� valIndex �� 1, ����� �������� ������ ���������� �������� values, ��������� ���� ������� � ���//
                //������ ����������, � �� �����������? ����� ����� ������ � ��� �� ��������, � ��  � ���� ��������
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