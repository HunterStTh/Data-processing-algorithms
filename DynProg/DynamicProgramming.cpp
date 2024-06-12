//Автор:Гаврилов Д.А
/*
.Задача Взрывоопасность
При переработке радиоактивных материалов образуются отходы двух видов — особо опасные (тип A) и неопасные (тип B).
Для их хранения используются одинаковые контейнеры. После помещения отходов в контейнеры, последние укладываются вертикальной стопкой.
Стопка считается взрывоопасной, если в ней подряд идет более двух контейнеров типа A. Для заданного количества контейнеров N
определить число безопасных стопок. Формат входных данных Одно число 0 < N < 31. Формат выходных данных Одно число — количество
безопасных вариантов формирования стопки.
*/
#include <iostream>// потоки вв/ выв
#include "Dyno.h"//для test_safety_case и SafetyCase

int main() {

    size_t N;// число ящиков
    char choice;//выбор из файла или с консоли
    test_safety_case();//тестируем
    do {
        std::cout << "Enter 'k' from keyboard, 'f' from file: ";
        std::cin >> choice;
        switch (choice) {
        case 'k':
        {do {
                std::cout << "Add number(between 0 to 32): ";

                while (!(std::cin >> N)) {
                    std::cout << "That's not a number! Please enter a number: ";

                    // Очищаем флаг ошибки
                    std::cin.clear();

                    // Пропускаем оставшиеся символы в буфере
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

            } while (N > 32);
            break;}
            
        case 'f':
        {
            const std::string  filename = "number.txt";//название файла
            N = fromFile(filename);//записываем число из файла в переменную N 
            break;
        }
        default:{
            std::cout << "Invalid choice! Please enter 'k' for keyboard input or 'f' for file input: ";
            choice = ' ';
            break;
        }
        
        }
    } while (choice == ' ');
    // Выводим значение c, которое представляет собой количество безопасных стопок для N
    std::cout << "Variants: " << SafetyCase(N) << std::endl;

    return 0;
}