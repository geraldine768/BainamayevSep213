#include "calc_header.h"
#include <iostream>
using namespace std;

int Prioritet(char op)
{
    if (op == '*' || op == '/')         // íàèáîëåå ïðèîðèòåòíûå
    {
        return 2;
    }
    else if (op == '+' || op == '-')    // ìåíåå ïðèîðèòåòíûå
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
    return op == '+' || op == '-' || op == '*' || op == '/';  // ïðîâåðêà íà îïåðàòîð
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
            cout << "Îøèáêà!\n äåëåíèå íà 0\n";
        }
        return num1 / num2;
    default: 
        return 0;
    }
}

int Calculator::evaluateExpression(const string& task) // evaluateExpression ïðèíàäëåæèò Calculator(ñòðóêòóðà)
{
    int i = 0;

    int length = task.length();      // äëèíà âûðàæåíèÿ
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
                num = num * 10 + (task[i] - '0');     /* ýòà ñòðîêà áåðåò çíà÷åíèå num, óìíîæàåò åãî íà 10, 
                                                               çàòåì äîáàâëÿåò ê ýòîìó ðåçóëüòàòó ðàçíèöó ìåæäó 
                                                               ASCII-êîäîì task[i] è '0'
                                                               êîðî÷å - ìû ïðåîáðàçóåì ñèìâîë öèôðû èç ñòðîêè task â 
                                                               öåëîå ÷èñëî! è äîáàâëÿåì åãî ê num*/                         
                i++;
            }
            values[valIndex++] = num;
        }
        else if (task[i] == '(')              // ïåðâàÿ ñêîáêà
        {
            operators[opIndex++] = task[i];
            i++;
        }
        else if (task[i] == ')')              // âòîðàÿ ñêîáêà
        {
            while (opIndex > 0 && operators[opIndex - 1] != '(')        /*Åñëè opIndex áîëüøå íóëÿ,
                                                                       åùå åñòü íåîáðàáîòàííûå îïåðàòîðû*/ 
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
            /*ïðîâåðÿåì óñëîâèå, êîòîðîå ãàðàíòèðóåò, ÷òî ó íàñ åñòü îïåðàòîðû è ÷òî òåêóùèé îïåðàòîð task[i] èìååò ìåíüøèé ïðèîðèòåò*/
            while (opIndex > 0 && Prioritet(operators[opIndex - 1]) > Prioritet(task[i]))
            {
                // èçâëåêàåì îïåðàòîð ñ áîëåå âûñîêèì ïðèîðèòåòîì è ñîõðàíÿåì åãî â ïåðåìåííóþ op
                char op = operators[--opIndex];    
                //Ìû óìåíüøàåì valIndex íà 1, ÷òîáû ïîëó÷èòü èíäåêñ ïîñëåäíåãî ýëåìåíòà values, ñîõðàíÿåì ýòîò ýëåìåíò â íóì//
                //ïî÷åìó ïðåôèêñíîå, à íå ïîñòôèêñíîå? ÷òîáû ñðàçó îòíÿòü è òóò æå ïîëó÷èòü, à íå  â ñëåä èòåðàöèè
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
