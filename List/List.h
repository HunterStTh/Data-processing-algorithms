//Автор: Гаврилов Д.А.
#pragma once
#include"Container.h"
// Шаблон класса для узла списка //Оценки
template<typename T>
class Node {
public:
	T data; // Данные узла
	Node* next; // Указатель на следующий узел
	Node* prev; // Указатель на предыдущий узел

	// Конструктор узла
	Node(T data) : data(data), next(nullptr), prev(nullptr) {}

	// Деструктор узла
	~Node() = default;

	// Конструктор копирования узла
	Node(const Node& other) : data(other.data), next(other.next ? new Node(*other.next) : nullptr), prev(other.prev ? new Node(*other.prev) : nullptr) {}

	// Оператор присваивания копированием
	Node& operator=(const Node& other) {
		if (this != &other) { // Проверка на присваивание самого себе
			data = other.data; // Копирование данных
			next = other.next ? new Node(*other.next) : nullptr; // Копирование указателя на следующий узел
			prev = other.prev ? new Node(*other.prev) : nullptr; // Копирование указателя на предыдущий узел
		}
		return *this; // Возвращение ссылки на текущий объект
	}

	// Конструктор перемещения
	Node(Node&& other) noexcept : data(std::move(other.data)), next(other.next), prev(other.prev) {
		other.next = nullptr; // Обнуление указателя на следующий узел в исходном объекте
		other.prev = nullptr; // Обнуление указателя на предыдущий узел в исходном объекте
	}

	// Оператор присваивания перемещением
	Node& operator=(Node&& other) noexcept {
		if (this != &other) { // Проверка на самоприсваивание
			data = std::move(other.data); // Перемещение данных
			next = other.next; // Копирование указателя на следующий узел
			prev = other.prev; // Копирование указателя на предыдущий узел
			other.next = nullptr; // Обнуление указателя на следующий узел в исходном объекте
			other.prev = nullptr; // Обнуление указателя на предыдущий узел в исходном объекте
		}
		return *this; // Возвращение ссылки на текущий объект
	}
};

// Шаблон класса для двусвязного списка, наследуемого от Container
template<typename T>
class DoublyLinkedList : public Container<T> {
private:
	Node<T>* head; // Указатель на голову списка
	Node<T>* tail; // Указатель на хвост списка
	size_t size; // Размер списка

public:
	// Конструктор списка O(1)
	DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

	// Конструктор копирования(глубокое)
	DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr), size(0) {
		for (Node<T>* node = other.head; node; node = node->next) {
			insert_end(node->data);
		}
	}
	// Конструктор перемещения
	DoublyLinkedList(DoublyLinkedList&& other) noexcept : head(other.head), tail(other.tail), size(other.size) {
		other.head = nullptr;
		other.tail = nullptr;
		other.size = 0;
	}

	// Деструктор списка O(n)
	~DoublyLinkedList() { clear(); }
	
}
	// Оператор присваивания копированием (глубокое копирование)
	DoublyLinkedList& operator=(const DoublyLinkedList& other) {
		if (this != &other) { // Проверяем, не является ли other тем же объектом, что и текущий
			while (head) { // Пока есть голова списка
				Node<T>* temp = head; // Сохраняем ссылку на голову списка
				head = head->next; // Обновляем голову списка
				delete temp; // Удаляем сохраненный узел
			}
			head = nullptr; // Обнуляем голову списка
			tail = nullptr; // Обнуляем хвост списка
			size = 0; // Обнуляем размер списка
			for (Node<T>* node = other.head; node; node = node->next) { // Проходим по всем узлам списка other
				insert_end(node->data); // Вставляем данные каждого узла в конец текущего списка
			}
		}
		return *this; // Возвращаем ссылку на текущий объект
	}

	//начало, конец, после и в[]
	// Вставка элемента в начало списка O(1)
	void insert_begin(T data) override {
		Node<T>* node = new Node<T>(data);// Создаем новый узел
		node->next = head;
		if (head) {// Если голова существует
			head->prev = node;// Устанавливаем голову как предыдущий для нового узла
		}
		head = node; // Устанавливаем новый узел как голову
		if (tail == nullptr) {// Если хвост пуст
			tail = head;// Тогда хвост станет головой
		}
		size++;
	}
	// Вставка элемента в конец списка O(1)
	void insert_end(T data) override {
		Node<T>* node = new Node<T>(data); // Создаем новый узел
		if (tail) { // Если хвост существует
			tail->next = node; // Устанавливаем новый узел как следующий для хвоста
			node->prev = tail; // Устанавливаем хвост как предыдущий для нового узла
			tail = node; // Обновляем хвост списка
		}
		else {
			head = tail = node; // Если список пуст, устанавливаем новый узел как голову и хвост
		}
		size++; // Увеличиваем размер списка
	}

	// Вставка элемента после определенного элемента O(n)
	void insert_after(T key, T data) {
		Node<T>* key_node = find(key); // Ищем узел с ключом
		if (key_node) { // Если узел найден
			Node<T>* node = new Node<T>(data); // Создаем новый узел
			node->next = key_node->next; // Устанавливаем следующий узел для нового узла
			node->prev = key_node; // Устанавливаем найденный узел как предыдущий для нового узла
			if (key_node->next) { // Если у найденного узла есть следующий
				key_node->next->prev = node; // Устанавливаем новый узел как предыдущий для следующего узла
			}
			key_node->next = node; // Устанавливаем новый узел как следующий для найденного узла
			if (key_node == tail) { // Если найденный узел является хвостом
				tail = node; // Обновляем хвост списка
			}
			size++; // Увеличиваем размер списка
		}
	}

	// Вставка элемента по индексу O(n)
	void insert_at(size_t index, T data) {
		if (index > size) { // Если индекс больше размера списка
			throw std::out_of_range("Index out of range"); // Бросаем исключение
		}
		if (index == 0) { // Если индекс равен 0
			insert_begin(data); // Вставляем элемент в начало списка
		}
		else if (index == size) { // Если индекс равен размеру списка
			insert_end(data); // Вставляем элемент в конец списка
		}
		else {
			Node<T>* temp = head; // Начинаем с головы списка
			for (size_t i = 0; i < index - 1; i++) { // Проходим по списку до нужного индекса
				temp = temp->next;
			}
			Node<T>* node = new Node<T>(data); // Создаем новый узел
			node->next = temp->next; // Устанавливаем следующий узел для нового узла
			node->prev = temp; // Устанавливаем текущий узел как предыдущий для нового узла
			temp->next->prev = node; // Устанавливаем новый узел как предыдущий для следующего узла
			temp->next = node; // Устанавливаем новый узел как следующий для текущего узла
			size++; // Увеличиваем размер списка
		}
	}

	// Оператор присваивания перемещением
	DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept {
		if (this != &other) { // Если текущий объект не является объектом other
			while (head) { // Пока есть голова списка
				Node<T>* temp = head; // Сохраняем ссылку на голову списка
				head = head->next; // Обновляем голову списка
				delete temp; // Удаляем сохраненный узел
			}
			head = other.head; // Копируем голову из other
			tail = other.tail; // Копируем хвост из other
			size = other.size; // Копируем размер из other
			other.head = nullptr; // Обнуляем голову в other
			other.tail = nullptr; // Обнуляем хвост в other
			other.size = 0; // Обнуляем размер в other
		}
		return *this; // Возвращаем ссылку на текущий объект
	}

	// Удаление элемента из списка по значению
	bool remove(T data) override {
		Node<T>* temp = head; // Начинаем с головы списка
		while (temp) { // Проходим по всем элементам списка
			if (temp->data == data) { // Если нашли элемент с нужными данными
				if (temp->prev) { // Если у элемента есть предыдущий
					temp->prev->next = temp->next; // Обновляем ссылку на следующий элемент у предыдущего
				}
				if (temp->next) { // Если у элемента есть следующий
					temp->next->prev = temp->prev; // Обновляем ссылку на предыдущий элемент у следующего
				}
				if (temp == head) { // Если элемент является головой списка
					head = temp->next; // Обновляем голову списка
				}
				if (temp == tail) { // Если элемент является хвостом списка
					tail = temp->prev; // Обновляем хвост списка
				}
				delete temp; // Удаляем элемент
				size--; // Уменьшаем размер списка
				return true; // Возвращаем true, так как элемент был удален
			}
			temp = temp->next; // Переходим к следующему элементу
		}
		return false; // Если элемент не найден, возвращаем false
	}

	// Поиск элемента в списке
	Node<T>* find(T data) {
		Node<T>* temp = head; // Начинаем с головы списка
		while (temp) { // Проходим по всем элементам списка
			if (temp->data == data) { // Если нашли элемент с нужными данными
				return temp; // Возвращаем найденный элемент
			}
			temp = temp->next; // Переходим к следующему элементу
		}
		return nullptr; // Если элемент не найден, возвращаем пустой объект типа T
	}

	// Объединение двух списков с обрезанием
	void concatenate(DoublyLinkedList<T>& list) {
		if (tail) { // Если у текущего списка есть хвост
			tail->next = list.head; // Обновляем ссылку на следующий элемент у хвоста текущего списка
		}
		if (list.head) { // Если у второго списка есть голова
			list.head->prev = tail; // Обновляем ссылку на предыдущий элемент у головы второго списка
		}
		if (list.tail) { // Если у второго списка есть хвост
			tail = list.tail; // Обновляем хвост текущего списка
		}
		size += list.size; // Увеличиваем размер текущего списка
		list.head = list.tail = nullptr; // Обнуляем голову и хвост второго списка
		list.size = 0; // Обнуляем размер второго списка
	}
	// Доступ к элементу по индексу O(n) //Бросаем исключение
	T get_at(size_t index) {
		if (index >= size) { // Если индекс больше или равен размеру списка
			throw std::out_of_range("Index out of range"); // Бросаем исключение
		}
		Node<T>* temp = head; // Начинаем с головы списка
		for (size_t i = 0; i < index; i++) { // Проходим по списку до нужного индекса
			temp = temp->next;
		}
		return temp->data; // Возвращаем данные узла
	}

	// Получение размера списка
	size_t get_size() override {
		return size; // Возвращаем размер списка
	}

	// Очистка списка
	void clear() {
		while (head) { // Пока есть голова списка
			Node<T>* temp = head; // Сохраняем ссылку на голову списка
			head = head->next; // Обновляем голову списка
			delete temp; // Удаляем сохраненный элемент
			size--;
		}
	}
};