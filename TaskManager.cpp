#include <iostream>
#include <string>
using namespace std;

const int MAX_TASKS = 10;

struct Task
{
    string title;
    int priority;
    string description;
    string datetime;
};

int taskCount = 0;
Task taskList[MAX_TASKS];

int Search(const char* text, const char* target, int startingIndex = 0)
{
    int textLength = strlen(text);
    int targetLength = strlen(target);

    if (startingIndex >= textLength)
    {
        return -1;
    }

    for (int i = startingIndex; i <= textLength - targetLength; ++i)
    {
        bool targetFound = true;
        for (int j = 0; j < targetLength; ++j)
        {
            if (text[i + j] != target[j])
            {
                targetFound = false;
                break;
            }
        }
        if (targetFound)
        {
            return i;
        }
    }
    return -1;
}

void addTask()
{
    if (taskCount < MAX_TASKS)
    {
        Task task;
        cin.ignore(); // Очистка буфера перед вводом строки
        cout << "Введите название дела: ";
        getline(cin, task.title);
        cout << "Введите приоритет (1 - низкий, 2 - средний, 3 - высокий): ";
        cin >> task.priority;
        cin.ignore(); // Очистка буфера после ввода числа
        cout << "Введите описание дела: ";
        getline(cin, task.description);
        cout << "Введите дату и время исполнения (гггг-мм-дд чч:мм): ";
        getline(cin, task.datetime);
        taskList[taskCount++] = task;
        cout << "\n\nДело добавлено в список\n\n";
    }
    else
    {
        cout << "Список дел полон, нельзя добавить больше задач" << '\n';
    }
}

void removeTask()
{
    if (taskCount > 0)
    {
        int index;
        cout << "Введите номер дела для удаления: ";
        cin >> index;
        if (index >= 1 && index <= taskCount)
        {
            for (int i = index - 1; i < taskCount - 1; i++)
            {
                taskList[i] = taskList[i + 1];
            }
            taskCount--;
            cout << "Дело удалено из списка" << '\n';
        }
        else
        {
            cout << "Неверный номер дела" << '\n';
        }
    }
    else
    {
        cout << "Список дел пуст" << '\n';
    }
}

void editTask()
{
    if (taskCount > 0)
    {
        int index;
        cout << "Введите номер дела для редактирования: \n";
        cin >> index;
        if (index >= 1 && index <= taskCount)
        {
            Task& task = taskList[index - 1];
            cout << "Введите новое название дела: \n";
            cin.ignore();
            getline(cin, task.title);
            cout << "Введите новый приоритет (1 - низкий, 2 - средний, 3 - высокий): \n";
            cin >> task.priority;
            cin.ignore();
            cout << "Введите новое описание дела: \n";
            getline(cin, task.description);
            cout << "Введите новую дату и время исполнения (гггг-мм-дд чч:мм): \n";
            getline(cin, task.datetime);
            cout << "Дело отредактировано" << '\n';
        }
        else
        {
            cout << "Неверный номер дела" << '\n';
        }
    }
    else
    {
        cout << "\n\nСписок дел пуст\n\n";
    }
}

void searchByTitle()
{
    string searchTerm;
    cout << "Введите название для поиска: \n";
    cin.ignore();
    getline(cin, searchTerm);

    bool found = false;

    for (int i = 0; i < taskCount; i++)
    {
        //c_str -  для преобразования string(taskList[i].description и searchTerm) в char. Зачем? Потому что string не работает с strlen
        if (Search(taskList[i].title.c_str(), searchTerm.c_str()) != -1)
        {
            cout << "Найдено дело #" << (i + 1) << ": " << taskList[i].title << '\n';
            found = true;
        }
    }

    if (!found)
    {
        cout << "Дела с таким названием не найдены" << '\n';
    }
}

void searchByPriority()
{
    int searchPriority;
    cout << "Введите приоритет для поиска (1 - низкий, 2 - средний, 3 - высокий): ";
    cin >> searchPriority;

    bool found = false;

    for (int i = 0; i < taskCount; i++)
    {
        if (taskList[i].priority == searchPriority)
        {
            cout << "Найдено дело #" << (i + 1) << " " << taskList[i].title << '\n';
            found = true;
        }
    }

    if (!found)
    {
        cout << "Дела с выбранным приоритетом не найдены" << '\n';
    }
}

void searchByDescription()
{
    string searchDescription;
    cout << "Введите описание для поиска: \n";
    cin.ignore();
    getline(cin, searchDescription);

    bool found = false;

    for (int i = 0; i < taskCount; i++)
    {
        
        if (Search(taskList[i].description.c_str(), searchDescription.c_str()) != -1)
        {
            cout << "Найдено дело #" << (i + 1) << " " << taskList[i].title << '\n';
            found = true;
        }
    }

    if (!found)
    {
        cout << "Дела с таким описанием не найдены" << '\n';
    }
}

void displayTasks()
{
    if (taskCount > 0)
    {
        cout << "Список дел:" << '\n';;
        for (int i = 0; i < taskCount; i++)
        {
            cout << "\nДело #" << (i + 1) << "\n";
            cout << "Название: " << taskList[i].title << "\n";
            cout << "Приоритет: " << taskList[i].priority << "\n";
            cout << "Описание: " << taskList[i].description << "\n";
            cout << "Дата и время исполнения: " << taskList[i].datetime << "\n";
            cout << "---------------\n";
        }
    }
    else
    {
        cout << "\n\nСписок дел пуст\n\n";
    }
}

void displayTasksOnDay(const string& date)
{
    cout << "Список дел на " << date << ":\n";
    for (int i = 0; i < taskCount; i++)
    {
        if (Search(taskList[i].datetime.c_str(), date.c_str()) != -1)
        {
            cout << "\nДело #" << (i + 1) << "\n";
            cout << "Название: " << taskList[i].title << "\n";
            cout << "Приоритет: " << taskList[i].priority << "\n";
            cout << "Описание: " << taskList[i].description << "\n";
            cout << "Дата и время исполнения: " << taskList[i].datetime << "\n";
            cout << "---------------\n";
        }
    }
}

void displayTasksInWeek(const string& startDate, const string& endDate)
{
    cout << "Список дел с " << startDate << " по " << endDate << ":\n";
    for (int i = 0; i < taskCount; i++)
    {
        if (Search(taskList[i].datetime.c_str(), startDate.c_str()) != -1 &&
            Search(taskList[i].datetime.c_str(), endDate.c_str()) != -1)
        {
            cout << "\nДело #" << (i + 1) << "\n";
            cout << "Название: " << taskList[i].title << "\n";
            cout << "Приоритет: " << taskList[i].priority << "\n";
            cout << "Описание: " << taskList[i].description << "\n";
            cout << "Дата и время исполнения: " << taskList[i].datetime << "\n";
            cout << "---------------\n";
        }
    }
}

void displayTasksInMonth(const string& month)
{
    cout << "Список дел на " << month << ":\n";
    for (int i = 0; i < taskCount; i++)
    {
        if (Search(taskList[i].datetime.c_str(), month.c_str()) != -1)
        {
            cout << "\nДело #" << (i + 1) << "\n";
            cout << "Название: " << taskList[i].title << "\n";
            cout << "Приоритет: " << taskList[i].priority << "\n";
            cout << "Описание: " << taskList[i].description << "\n";
            cout << "Дата и время исполнения: " << taskList[i].datetime << "\n";
            cout << "---------------\n";
        }
    }
}

void sortByPriority()
{
    for (int i = 0; i < taskCount - 1; i++)
    {
        for (int j = 0; j < taskCount - i - 1; j++)
        {
            if (taskList[j].priority > taskList[j + 1].priority)
            {
                Task temp = taskList[j];
                taskList[j] = taskList[j + 1];
                taskList[j + 1] = temp;
            }
        }
    }
}

//(пузырьковая сортировка)
void sortByDatetime()
{
    for (int i = 0; i < taskCount - 1; i++)
    {
        for (int j = 0; j < taskCount - i - 1; j++)
        {
            if (taskList[j].datetime > taskList[j + 1].datetime)
            {
                Task temp = taskList[j];
                taskList[j] = taskList[j + 1];
                taskList[j + 1] = temp;
            }
        }
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    int choice;

    while (true)
    {
        cout << "Выберите действие:" << '\n';
        cout << "1. Добавить дело" << '\n';
        cout << "2. Удалить дело" << '\n';
        cout << "3. Редактировать дело" << '\n';
        cout << "4. Поиск по названию" << '\n';
        cout << "5. Поиск по приоритету" << '\n';
        cout << "6. Поиск по описанию" << '\n';
        cout << "7. Отобразить список дел" << '\n';
        cout << "8. Отобразить список дел на день" << '\n';
        cout << "9. Отобразить список дел на неделю" << '\n';
        cout << "10. Отобразить список дел на месяц" << '\n';
        cout << "11. Сортировать по приоритету" << '\n';
        cout << "12. Сортировать по дате и времени" << '\n';
        cout << "13. Выйти" << "\n\n";
        cout << "Введите номер действия: \n\n";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addTask();
            break;
        case 2:
            removeTask();
            break;
        case 3:
            editTask();
            break;
        case 4:
            searchByTitle();
            break;
        case 5:
            searchByPriority();
            break;
        case 6:
            searchByDescription();
            break;
        case 7:
            displayTasks();
            break;
        case 8:
        {
            string date;
            cout << "Введите дату для отображения списка дел на день (гггг-мм-дд): ";
            cin.ignore();
            getline(cin, date);
            displayTasksOnDay(date);
        }
        break;
        case 9:
        {
            string startDate, endDate;
            cout << "Введите начальную дату для отображения списка дел на неделю (гггг-мм-дд): ";
            cin.ignore();
            getline(cin, startDate);
            cout << "Введите конечную дату для отображения списка дел на неделю (гггг-мм-дд): ";
            getline(cin, endDate);
            displayTasksInWeek(startDate, endDate);
        }
        break;
        case 10:
        {
            string month;
            cout << "Введите месяц для отображения списка дел на месяц (гггг-мм): ";
            cin.ignore();
            getline(cin, month);
            displayTasksInMonth(month);
        }
        break;
        case 11:
            sortByPriority();
            cout << "Список отсортирован по приоритету." << '\n';
            break;
        case 12:
            sortByDatetime();
            cout << "Список отсортирован по дате и времени исполнения." << '\n';
            break;
        case 13:
            return 0;
        default:
            cout << "Неверный выбор. Попробуйте снова." << '\n';
        }
    }
}
