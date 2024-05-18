//Автор:Гаврилов Д.А.
#include <ctime>
#include <iostream>
#include <fstream>
#include "RandSortArr.h" // Подключаем заголовочный файл с объявлениями функций
#include <cassert> // Подключаем библиотеку для использования макроса assert

using namespace std;

int main()
{

    setlocale(LC_ALL, "Rus"); // Устанавливаем локаль для корректного отображения кириллических символов
    size_t N = 10e4; // Задаем размер массива
    srand(time(nullptr)); // Инициализируем генератор случайных чисел

    int* arr = new int[N]; // Выделяем память под массив
    arr = get_random_array_increase<int>(arr, N, 1, 10e4); // Генерируем случайный массив
    assert(is_sorted<int>(arr, N));
    // todo: дру варианты

    // Выводим сообщение о том, отсортирован ли массив

    cout << "Массив " << (is_sorted<int>(arr, N) ? "отсортирован" : "не отсортирован") << endl;

    // Запоминаем начало отсчета времени
    time_t t0 = time(nullptr);

    // Записываем массив в файл
    write_arr_to_file<int>(arr, N, "array.txt");

    // Запоминаем конец отсчета времени
    time_t t1 = time(nullptr);

    // Выводим минимальный элемент массива
    cout << "Минимальный элемент: " << find_min_index<int>(arr, N) << endl;

    // Открываем файл в блокноте
    system("notepad array.txt");

    // Выводим время выполнения программы
    cout << "time delta (seconds) " << t1 - t0;

    // Удаляем файл
    remove("array.txt");
}
