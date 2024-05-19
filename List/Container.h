//Автор: Гаврилов Д.А.
#pragma once
// Шаблон класса для контейнера
template<typename T>
class Container {
public:
    // Виртуальные функции для операций, которые должны быть реализованы в производных классах
    virtual void insert_begin(T data) = 0; // Вставка элемента в начало
    virtual void insert_end(T data) = 0; // Вставка элемента в конец
    virtual bool remove(T data) = 0; // Удаление элемента
    virtual size_t get_size() = 0; // Получение размера контейнера
};