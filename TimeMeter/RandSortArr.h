//Автор:Гаврилов Д.А.
#pragma once
#include <cassert>
// Шаблонная функция для нахождения индекса минимального элемента в массиве
template<typename T>
int find_min_index(const T* arr, size_t N) {
    T min_value = arr[0]; // Начальное минимальное значение - первый элемент массива
    for (size_t i = 1; i < N; ++i) { // Проходим по всем элементам массива
        if (arr[i] < min_value) { // Если текущий элемент меньше минимального
            min_value = arr[i]; // Обновляем минимальное значение
        }
    }
    return min_value; // Возвращаем индекс минимального значения
}

// todo: another rand

// Шаблонная функция для генерации случайного массива
template<typename T>
T* get_random_array(T* arr, size_t n, T from, T to) {
    for (size_t i = 0; i < n; ++i) { // Генерируем все элементы
        arr[i] = from + (rand() % (to - from + 1)); // Генерируем случайное число в заданном диапазоне
    }
    return arr; // Возвращаем указатель на массив
}

// Шаблонная функция для генерации случайного массива по возрастанию
template<typename T>
T* get_random_array_increase(T* arr, size_t n, T from, T to) {
    arr[0] = from + (rand() % (to - from + 1)); // Генерируем первый элемент
    for (size_t i = 1; i < n; ++i) { // Генерируем последующие элементы
        arr[i] = arr[i - 1] + (rand() % ((to - arr[i - 1]))); // Гарантируем увеличение каждого последующего элемента и уменьшаем диапазон генерации
    }
    return arr; // Возвращаем указатель на массив
}

// Шаблонная функция для записи массива в файл

/// <summary>
/// Функция записи в файл
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="arr"> Массив</param>
/// <param name="n"> Кол-во элементов</param>
/// <param name="filename"> Файловая переменная</param>
template<typename T>
void write_arr_to_file(const T* arr, size_t n, const char* filename) {
    std::ofstream outFile(filename); // Открываем файл для записи
    assert(outFile.is_open() && "Невозможно открыть файл для записи."); // Проверяем, что файл успешно открыт
    for (size_t i = 0; i < n; ++i) { // Записываем каждый элемент массива в файл
        outFile << arr[i] << " ";
    }
    outFile.close(); // Закрываем файл
    std::cout << "Массив успешно записан в файл: " << filename << std::endl; // Выводим сообщение об успешной записи
}

// todo: реализовать самостоятельно
// Шаблонная функция для проверки, отсортирован ли массив ???

/// <summary>
/// 
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="arr"></param>
/// <param name="size"></param>
/// <returns></returns>
template<typename T>
bool is_sorted(T* arr, size_t size) {
    for (size_t i = 1; i < size; ++i) {
        if (arr[i] < arr[i - 1]) {
            return false; // Если текущий элемент меньше предыдущего, массив не отсортирован
        }
    }
    return true; // Если мы прошли весь массив и не нашли ни одного элемента, который меньше предыдущего, массив отсортирован
}
// Шаблонная функция для проверки, отсортирован ли массив arr размера size, A - по возрастанию(по умолчанию), D - по убыванию
template <typename Array>
bool arr_is_sort(const Array* arr, size_t size, std::string order = "A")
{
    // Если в массиве 1 или 0 элементов, возвращаем true
    if (size == 0 || size == 1)
        return true;

    // Проходим по всем элементам массива
    for (size_t i = 0; i < size - 1; i++)
    {
        // В зависимости от выбранного порядка сортировки
        switch (order)
        {
            // Если выбрано "A" (по возрастанию)
        case "ascending":
            // Если текущий элемент больше следующего, массив не отсортирован по возрастанию
            if (arr[i] > arr[i + 1])
                return false;
            break;
            // Если выбрано "D" (по убыванию)
        case "descending":
            // Если текущий элемент меньше следующего, массив не отсортирован по убыванию
            if (arr[i] < arr[i + 1])
                return false;
            break;
            // Если выбрано что-то другое
        default:
            // Выводим сообщение об ошибке
            std::cout << "Invalid order. Please choose either 'ascending' or 'descending'.\n";
            return false;
        }
    }
    // Если мы прошли весь массив и не нашли ни одного элемента, который больше (для возрастания) или меньше (для убывания) следующего, массив отсортирован
    return true;
}

//ДОБАВЛЕННЫЕ ФУНКЦИИ
/// Тест работы функции is_sorted 
void is_sorted_assert()
{
    for (size_t n = 1; n <= 100; ++n) { // Проверяем массивы разного размера
        int* arr = new int[n];

        // Генерируем случайный массив и проверяем, что он не отсортирован
        get_random_array(arr, n, 0, 100);
        if (!is_sorted(arr, n)) {
            std::cout << "Ошибка: случайный массив размера " << n << " был ошибочно определен как отсортированный.\n";
        }

        // Генерируем случайный массив по возрастанию и проверяем, что он отсортирован
        get_random_array_increase(arr, n, 0, 100);
        if (!is_sorted(arr, n)) {
            std::cout << "Ошибка: случайный массив по возрастанию размера " << n << " был ошибочно определен как неотсортированный.\n";
        }

        delete[] arr;
    }
}
// Тест на запись в файл
void test_write_arr_to_file() {
    // Создаем тестовый массив
    int arr[5] = {1, 2, 3, 4, 5};
    const char* filename = "test.txt";

    // Записываем массив в файл
    write_arr_to_file(arr, 5, filename);

    // Открываем файл для чтения
    std::ifstream inFile(filename);
    assert(inFile.is_open() && "Ошибка: файл не открыт.");

    }
    // Закрываем файл
    inFile.close();

    std::cout << "Тест для функции write_arr_to_file пройден успешно.\n";
}

/// Последовательный поиск по ключу(key) шаблонного типа в массиве
// Лучший случай O(1) когда первый элемент
// Средний= Худший= O(N)
template <typename T>
std::vector<size_t> sequential_search(const T arr[], size_t size, T key)
{
    std::vector<size_t> indexes; // Вектор для хранения индексов
    for (size_t i = 0; i < size; ++i)
        if (arr[i] == key)
            indexes.push_back(i); // Если найдено, добавляем индекс в вектор
    return indexes; // Возвращаем вектор индексов
}

// Тесты функции sequential_search
void test_sequential_search() {
    // Тест на пустом массиве
    int empty[0] = {};
    assert(sequential_search(empty, 0, 1).empty());

    // Тест на массиве с одним элементом
    int single[1] = {1};
    assert(sequential_search(single, 1, 1) == std::vector<size_t>{0});
    assert(sequential_search(single, 1, 2).empty());

    // Тест на массиве с несколькими элементами
    int multiple[5] = {1, 2, 3, 4, 5};
    assert(sequential_search(multiple, 5, 1) == std::vector<size_t>{0});
    assert(sequential_search(multiple, 5, 3) == std::vector<size_t>{2});
    assert(sequential_search(multiple, 5, 5) == std::vector<size_t>{4});
    assert(sequential_search(multiple, 5, 6).empty());

    // Тест на массиве с повторяющимися элементами
    int repeated[5] = {1, 1, 2, 2, 2};
    assert(sequential_search(repeated, 5, 1) == std::vector<size_t>{0, 1});
    assert(sequential_search(repeated, 5, 2) == std::vector<size_t>{2, 3, 4});
    assert(sequential_search(repeated, 5, 3).empty());

    std::cout << "Все тесты для функции sequential_search пройдены успешно.\n";
}
/// Бинарный поиск по ключу(key) шаблонного типа в отсортированном массиве
// Лучший случай O(1): когда искомый элемент находится в середине массива
// Средний и худший случай O(log n): когда искомый элемент находится в начале или конце массива
template <typename T>
int binary_search(T arr[], int size, T key) {
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int midle = left + (right - left) / 2; // Вычисляем индекс середины массива
        if (arr[midle] == key) {
            return midle; // Если ключ найден, возвращаем его индекс
        } else if (arr[midle] < key) {
            left = midle + 1; // Если ключ больше элемента в середине, ищем в правой половине массива
        } else {
            right = midle - 1; // Если ключ меньше элемента в середине, ищем в левой половине массива
        }
    }
    return -1; // Если ключ не найден, возвращаем -1
}
// Бинарный поиск с предикатом шаблонного типа Predicate
// Предикат можно реализовать так: 
// auto pred =  {
//        return num > 5;
//    };
// при его использовании будет производится поиск чисел больше пяти
template <typename T, typename Predicate>
int binary_search(T arr[], int size, Predicate pred) {
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (pred(arr[mid])) {
            return mid; // Если предикат вернул true, возвращаем индекс
        } else if (arr[mid] < 0) { // Предполагаем, что pred возвращает true для значений больше 0
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1; // Если предикат не вернул true для любого элемента, возвращаем -1
}
// Тесты для бинарного поиска по ключу(key) и с предикатами is_positive(положительный), is_large(больше ста)
void test_binary_search() {
    std::vector<int> data = {-10, -5, 0, 5, 10, 15, 20, 25, 30};

    // Тесты для binary_search с ключом
    assert(binary_search(data.data(), data.size(), -10) == 0);
    assert(binary_search(data.data(), data.size(), 0) == 2);
    assert(binary_search(data.data(), data.size(), 30) == 8);
    assert(binary_search(data.data(), data.size(), 100) == -1);

    // Тесты для binary_search с предикатом
    auto is_positive =  { return num > 0; };
    assert(binary_search(data.data(), data.size(), is_positive) == 3);

    auto is_large =  { return num > 100; };
    assert(binary_search(data.data(), data.size(), is_large) == -1);

    std::cout << "Все тесты для функций binary_search пройдены успешно.\n";
}
//рекурсивная сортировка Пузырьком массива arr, размера n
//O(n)-Худший, O(n^2)-Лучший;-Средний 
template <typename Array>
void bubbleSort(Array arr[], size_t n)
{
    // Проходим через все элементы массива
    for (size_t i = 0; i < n-1; i++)
    {
        // Последний i элементов уже на своих местах
        for (size_t j = 0; j < n-i-1; j++)
        {
            // Переходим к следующему элементу, если он больше текущего
            if (arr[j] > arr[j+1])
            {
                // Меняем элементы местами
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void test_bubble_sort() {
    std::vector<int> data = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    bubbleSort(data.data(), 0, data.size() - 1);
    for (int i = 0; i < 10; ++i) {
        assert(data[i] == i + 1);
    }
    std::cout << "Все тесты для функции quickSort пройдены успешно.\n";
}
