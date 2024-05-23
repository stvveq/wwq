#include <iostream>
#include <fstream>
#include <cstring>
#include "file_reader.h"
#include "tele_cons.h"
#include "const.h"
#include "processing.h"
#include <string>
using namespace std;


void print_stuff(marafon* call[], int id)
{
    cout << call[id]->number << ' ';
    cout << call[id]->name << ' ';
    cout << call[id]->club << ' ';
    cout << call[id]->start_time.hours << ':';
    cout << call[id]->start_time.minutes << ':';
    cout << call[id]->start_time.seconds << ' ';
    cout << call[id]->finish_time.hours << ':';
    cout << call[id]->finish_time.minutes << ':';
    cout << call[id]->finish_time.seconds << ' ';
  '\n';
}



void only_spartak(marafon* subscriptions[], int size)//тока спартак
{


    for (int i = 0; i < size; i++)
    {
        if (strstr(subscriptions[i]->club, "Spartak") != NULL)
        {
            print_stuff(subscriptions, i);
        }
    }
}
void only_min_time(marafon* subscriptions[], int size)//<2 50 00
{


    for (int i = 0; i < size; i++)
    {
        if (((subscriptions[i]->finish_time.hours) * 3600 + (subscriptions[i]->finish_time.minutes) * 60 + (subscriptions[i]->finish_time.seconds) - (subscriptions[i]->start_time.hours) * 3600 + (subscriptions[i]->start_time.minutes) * 60 + (subscriptions[i]->start_time.seconds)) < 10200)

        {
            print_stuff(subscriptions, i);
        }
    }
}


bool SortCase(int sort_id, marafon* subscriptions[], int size, int id, int id2)
{
    switch (sort_id)
    {
    case 1:
    {
        if ((subscriptions[id]->finish_time.hours) * 3600 + (subscriptions[id]->finish_time.minutes) * 60 + (subscriptions[id]->finish_time.seconds) - (subscriptions[id]->start_time.hours) * 3600 + (subscriptions[id]->start_time.minutes) * 60 + (subscriptions[id]->start_time.seconds))
        {
            return true;
        }
        else
        {
            return false;
        }
        break;
    }
    case 2:
    {
        if (subscriptions[id]->club < subscriptions[id2]->club)
        {
            return false;
        }
        if (subscriptions[id]->club > subscriptions[id2]->club)
        {
            return true;
        }
        if (subscriptions[id]->club == subscriptions[id2]->club)
        {
            if (subscriptions[id]->name < subscriptions[id2]->name)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        break;
    }
    }
}

void heapify(marafon* subscriptions[], int size, int i, int sort_id)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (sort_id == 1) {
        if (l < size && SortCase(sort_id, subscriptions, size, l, largest)) {
            largest = l;
        }
        if (r < size && SortCase(sort_id, subscriptions, size, r, largest)) {
            largest = r;
        }
    }
    else if (sort_id == 2) {
        if (l < size && SortCase(sort_id, subscriptions, size, l, largest)) {
            largest = l;
        }
        if (r < size&& SortCase(sort_id, subscriptions, size, r, largest)) {
            largest = r;
        }
    }

    if (largest != i) {
        marafon* temp = subscriptions[i];
        subscriptions[i] = subscriptions[largest];
        subscriptions[largest] = temp;
        heapify(subscriptions, size, largest, sort_id);
    }
}

/*void heapSort(marafon* subscriptions[], int size, int sort_id)
{
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(subscriptions, size, i, sort_id);
    }
    for (int i = size - 1; i > 0; i--) {
        marafon* temp = subscriptions[0];
        subscriptions[0] = subscriptions[i];
        subscriptions[i] = temp;
        heapify(subscriptions, i, 0, sort_id);
    }
}
*/
int partition(marafon* arr[], int low, int high, int sort_id, int size) {
    marafon* pivot = arr[high];
    int i = low;
    for (int j = low; j < high; j++) {
        if (!SortCase(sort_id, arr, size, j, high)) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[high]);
    return i;
}

void quickSort(marafon* arr[], int low, int high, int sort_id, int permament_size) {
    if (low < high) {
        int p = partition(arr, low, high, sort_id, permament_size);
        quickSort(arr, low, p - 1, sort_id, permament_size);
        quickSort(arr, p + 1, high, sort_id, permament_size);
    }

}
void BubbleSort(marafon* subscriptions[], int size, int sort_id) {
    //сортируем пузырьком
    int i, j;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (SortCase(sort_id, subscriptions, size, j + 1, j))// Вызов функции для сравнения
                swap(subscriptions[j + 1], subscriptions[j]);// Обмен элементов
        }
    }
    for (int d = 0; d < size; d++)
    {
        print_stuff(subscriptions, d); // Вывод данных после сортировки
    }
}
int main() {
    int sort_id;
    setlocale(LC_ALL, "Russian");
    cout << "Laboratory work #8. GIT\n";
    cout << "Variant #9.telephone conversations\n";
    cout << "Author: Anastasia Nabieva\n";
    cout << "Group: 23Ping1d\n";
    marafon* call[MAX_FILE_ROWS_COUNT];

    int size;
    try { //чтение файла 
        read("data.txt", call, size);
        for (int i = 0; i < size; i++) {
            print_stuff(call, i);
        }
    }
    catch (const char* error) {
        cout << error << '\n';
    }
    string filename = "data.txt";

    bool rpts = true;
    int rpts_value = 0;
   while (rpts == true) {
        cout << "What do you want to do next? " << endl
            << "1. Вывод всех разговоров на мобильных телефонах " << endl
            << "2. Разговоры за Ноябрь 21 " << endl
            << "3. Пирамидой" << endl
            << "4. Быстрая сортировка" << endl
            << "5. Exit " << endl
            << "6.Средняя стоимость одной секунды разговора" << endl;
        cin >> rpts_value;
        switch (rpts_value)
        {
        case 1:
        {
            only_spartak(call, size);

            break;
        }
        case 2:
        {
            only_min_time(call, size);

            break;
        }

        case 3:
        {

            cout << "Критерии сортировки" << endl
                << "1.По убыванию продолжительности разговора" << endl
                << "2. По возрастанию номера телефона, а в рамках одного номера по убыванию стоимости разговора" << endl;
            cin >> sort_id;
            BubbleSort(call, size, sort_id);
            for (int i = 0; i < size; i++)
            {
                print_stuff(call, i);
            }
            break;
        }
        case 4:
        {

            cout << "Критерии сортировки" << endl
                << "1.По убыванию продолжительности разговора" << endl
                << "2. По возрастанию номера телефона, а в рамках одного номера по убыванию стоимости разговора" << endl;
            cin >> sort_id;
            quickSort(call, 0, size - 1, sort_id, size);
            for (int i = 0; i < size; i++)
            {
                print_stuff(call, i);
            }
            break;
        }
        case 5:
        {
            rpts = false;
            break;
        }
        case 6:
        {
           
        }
        }
    }
    for (int i = 0; i < size; i++) {
        delete call[i];
    }
    return 0;
}