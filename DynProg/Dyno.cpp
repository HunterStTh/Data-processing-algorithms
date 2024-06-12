//Автор:Гаврилов Д.А

#include<vector>//для коллекций векторов
#include <cassert>//для тестов
#include <fstream>//для работы с файлами
#include <string>


/// Функция принимает в аргументах число N ящиков, возвращает количество безопасных стопок
int SafetyCase(int N)
{
    // Если N меньше или равно 0, возвращаем 0
    if (N <= 0) return 0;

    // Создаем вектор dp размером N+1 для хранения количества безопасных стопок для каждого числа контейнеров
    std::vector<size_t> dp(N + 1);

    // Инициализируем первые три элемента вектора dp
    dp[0] = 1; // Существует только одна безопасная стопка из 1 контейнеров (пустая стопка)
    if (N >= 1) dp[1] = 2; // Существуют две безопасные стопки из одного контейнера: A и B
    if (N >= 2) dp[2] = 4; // Существуют четыре безопасные стопки из двух контейнеров: AA, AB, BA и BB

    // Для каждого i от 3 до N вычисляем dp[i] как сумму dp[i-1], dp[i-2] и dp[i-3]
    for (int i = 3; i <= N; i++) {
        dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
    }

    // Возвращаем количество безопасных стопок для N контейнеров
    return dp[N];
}

//тесты SafetyCase
void test_safety_case() {
    assert(SafetyCase(0) == 0);//0
    assert(SafetyCase(1) == 2);//a,b
    assert(SafetyCase(2) == 4);//aa,ab,ba,bb
    assert(SafetyCase(3) == 7);//всего 8, но 1 небезопасный
    assert(SafetyCase(4) == 13);//7+4+2
    assert(SafetyCase(-2) == 0);//incorrect
}

// Функция для чтения данных из файла
int fromFile(const std::string &filename) {
    std::ifstream file(filename); // Открываем файл

    if (!file) { // Если файл не открыт
        return -1;
    }

    int N;
    file >> N; // Считываем число контейнеров

    file.close(); // Закрываем файл

    return N;
}