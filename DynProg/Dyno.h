//Автор:Гаврилов Д.А
#pragma once
#ifndef DYNO_H
#define DYNO_H

//Ф-ция принимает в аргументах число N ящиков, возвращает кол-во безопасных стопок
int SafetyCase(int N);

//тесты SafetyCase
void test_safety_case();

// Функция для чтения данных из файла
int fromFile(const std::string &filename);

#endif