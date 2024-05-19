#include <iostream> // Подключение библиотеки для работы с вводом-выводом
#include <fstream> // Подключение библиотеки для работы с файлами
#include <vector> // Подключение библиотеки для работы с векторами
#include <limits> // Подключение библиотеки для работы с числовыми лимитами
#include <cassert> // Подключение библиотеки для работы с assert
#include <string>
using namespace std; // Использование пространства имен std

// Тесты
void testFunctions();

// Функция для ввода чисел
vector<int> inputNumbers(int N);

// Функция для поиска второго по величине числа
int findSecondMax(const vector<int>& numbers);

// Функция для вывода результата в файл
void outputToFile(int second_max);

int main() {
    setlocale(LC_ALL, "Rus");
    int N; // Количество чисел для ввода
    //testFunctions();
    cout << "Введите количество чисел: "; // Вывод сообщения о вводе количества чисел
    while (!(cin >> N)) { // Проверка корректности ввода
        cin.clear(); // Очистка флагов ошибок потока
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорирование оставшихся символов в потоке
        cout << "Ошибка ввода. Пожалуйста, введите целое число.\n"; // Вывод сообщения об ошибке
    }

    vector<int> numbers = inputNumbers(N); // Ввод чисел
    int second_max = findSecondMax(numbers); // Поиск второго по величине числа
    outputToFile(second_max); // Вывод результата в файл

    return 0; // Завершение программы
}
void testFunctions() {
    // Тестирование функции inputNumbers
    {
        // Тест на корректность ввода
        vector<int> expected = { 1, 2, 3, 4, 5, 6 };
        vector<int> actual = inputNumbers(6);
        assert(expected == actual);

        // Тест на некорректный размер
        actual = inputNumbers(-1);
        assert(actual.size() >= 2); // Если размер меньше двух, это ошибка
    }

    // Тестирование функции findSecondMax
    {
        // Тест на корректность ввода
        int expected = 5;
        vector<int> numbers = { 1, 2, 3, 4, 5, 6 };
        int actual = findSecondMax(numbers);
        assert(expected == actual);

        // Тест на некорректный размер
        numbers = { 1 };
        actual = findSecondMax(numbers);
        assert(numbers.size() >= 2); // Если размер меньше двух, это ошибка

        // Тест на случай с повторяющимися максимальными числами
        {
            int expected = 5;
            vector<int> numbers = { 5, 7, 7 };
            int actual = findSecondMax(numbers);
            assert(expected == actual);
        }

        // Тест на случай с повторяющимися вторыми по величине числами
        {
            int expected = 3;
            vector<int> numbers = { 1, 3, 9, 9 };
            int actual = findSecondMax(numbers);
            assert(expected == actual);
        }
    }

    // Тестирование функции outputToFile
    {
        // Тест на корректность вывода
        int second_max = 5;
        outputToFile(second_max);

        // Чтение из файла и проверка результата
        ifstream file("output.txt");
        string line;
        getline(file, line);
        assert(line == "Второе по величине число: 5");
        file.close();
    }
}
vector<int> inputNumbers(int N) {
    vector<int> numbers(N); // Создание вектора для хранения чисел
    cout << "Введите " << N << " чисел: "; // Вывод сообщения о вводе чисел
    for (int i = 0; i < N; ++i) { // Цикл для ввода чисел
        while (!(cin >> numbers[i])) { // Проверка корректности ввода
            cin.clear(); // Очистка флагов ошибок потока
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорирование оставшихся символов в потоке
            cout << "Ошибка ввода. Пожалуйста, введите целое число.\n"; // Вывод сообщения об ошибке
        }
    }
    return numbers; // Возвращение вектора чисел
}

//Функция поиск второго после max
//Лучший случай: O(N)
//Средний случай: O(N)
//Худший случай:O(N)
int findSecondMax(const vector<int>& numbers) {
    /// <summary>
    /// 
    /// </summary>
    /// <param name="numbers">Массив чисел</param>
    /// <returns></returns>
    assert(numbers.size() >= 2 && "Для вызова функции массив должен содержать как минимум два элемента."); // Проверка размера вектора
    
    int max_num = numeric_limits<int>::min(); // Инициализация максимального числа
    int second_max = numeric_limits<int>::min(); // Инициализация второго по величине числа

    // Проходим по списку чисел
    for (int num : numbers) {
        // Если текущее число больше максимального, обновляем максимальное и второе максимальное числа
        if (num > max_num) {
            second_max = max_num;
            max_num = num;
        }
        // Если текущее число меньше максимального и больше второго максимального, обновляем второе максимальное число
        else if (num > second_max && num < max_num) {
            second_max = num;
        }
    }

    // Если второе максимальное число не было обновлено, все числа в списке одинаковы
    assert(second_max != numeric_limits<int>::min() && "Все элементы в списке одинаковы.");

    return second_max; // Возвращение второго по величине числа
}
// Функция для вывода результата в файл
void outputToFile(int second_max) {
    /// <summary>
    /// 
    /// </summary>
    /// <param name="second_max">Второе по величине </param>
    ofstream file("output.txt"); // Создание объекта файла для записи
    file << "Второе по величине число: " << second_max << "\n"; // Запись результата в файл
    file.close(); // Закрытие файла
}
