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
//ДОБАВЛЕННЫЕ ФУНКЦИИ
// Шаблонная функция для проверки, отсортирован ли массив
template <typename Array>
bool arr_is_sort(const Array* arr, size_t size, std::string order = "ascending")
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
            // Если выбрано "ascending" (по возрастанию)
        case "ascending":
            // Если текущий элемент больше следующего, массив не отсортирован по возрастанию
            if (arr[i] > arr[i + 1])
                return false;
            break;
            // Если выбрано "descending" (по убыванию)
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
