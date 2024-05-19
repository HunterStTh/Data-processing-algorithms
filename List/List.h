//�����: �������� �.�.
#pragma once
#include"Container.h"
// ������ ������ ��� ���� ������ //������
template<typename T>
class Node {
public:
	T data; // ������ ����
	Node* next; // ��������� �� ��������� ����
	Node* prev; // ��������� �� ���������� ����

	// ����������� ����
	Node(T data) : data(data), next(nullptr), prev(nullptr) {}

	// ���������� ����
	~Node() = default;

	// ����������� ����������� ����
	Node(const Node& other) : data(other.data), next(other.next ? new Node(*other.next) : nullptr), prev(other.prev ? new Node(*other.prev) : nullptr) {}

	// �������� ������������ ������������
	Node& operator=(const Node& other) {
		if (this != &other) { // �������� �� ������������ ������ ����
			data = other.data; // ����������� ������
			next = other.next ? new Node(*other.next) : nullptr; // ����������� ��������� �� ��������� ����
			prev = other.prev ? new Node(*other.prev) : nullptr; // ����������� ��������� �� ���������� ����
		}
		return *this; // ����������� ������ �� ������� ������
	}

	// ����������� �����������
	Node(Node&& other) noexcept : data(std::move(other.data)), next(other.next), prev(other.prev) {
		other.next = nullptr; // ��������� ��������� �� ��������� ���� � �������� �������
		other.prev = nullptr; // ��������� ��������� �� ���������� ���� � �������� �������
	}

	// �������� ������������ ������������
	Node& operator=(Node&& other) noexcept {
		if (this != &other) { // �������� �� ����������������
			data = std::move(other.data); // ����������� ������
			next = other.next; // ����������� ��������� �� ��������� ����
			prev = other.prev; // ����������� ��������� �� ���������� ����
			other.next = nullptr; // ��������� ��������� �� ��������� ���� � �������� �������
			other.prev = nullptr; // ��������� ��������� �� ���������� ���� � �������� �������
		}
		return *this; // ����������� ������ �� ������� ������
	}
};

// ������ ������ ��� ����������� ������, ������������ �� Container
template<typename T>
class DoublyLinkedList : public Container<T> {
private:
	Node<T>* head; // ��������� �� ������ ������
	Node<T>* tail; // ��������� �� ����� ������
	size_t size; // ������ ������

public:
	// ����������� ������ O(1)
	DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

	// ����������� �����������(��������)
	DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr), size(0) {
		for (Node<T>* node = other.head; node; node = node->next) {
			insert_end(node->data);
		}
	}
	// ����������� �����������
	DoublyLinkedList(DoublyLinkedList&& other) noexcept : head(other.head), tail(other.tail), size(other.size) {
		other.head = nullptr;
		other.tail = nullptr;
		other.size = 0;
	}

	// ���������� ������ O(n)
	~DoublyLinkedList() { clear(); }
	
}
	// �������� ������������ ������������ (�������� �����������)
	DoublyLinkedList& operator=(const DoublyLinkedList& other) {
		if (this != &other) { // ���������, �� �������� �� other ��� �� ��������, ��� � �������
			while (head) { // ���� ���� ������ ������
				Node<T>* temp = head; // ��������� ������ �� ������ ������
				head = head->next; // ��������� ������ ������
				delete temp; // ������� ����������� ����
			}
			head = nullptr; // �������� ������ ������
			tail = nullptr; // �������� ����� ������
			size = 0; // �������� ������ ������
			for (Node<T>* node = other.head; node; node = node->next) { // �������� �� ���� ����� ������ other
				insert_end(node->data); // ��������� ������ ������� ���� � ����� �������� ������
			}
		}
		return *this; // ���������� ������ �� ������� ������
	}

	//������, �����, ����� � �[]
	// ������� �������� � ������ ������ O(1)
	void insert_begin(T data) override {
		Node<T>* node = new Node<T>(data);// ������� ����� ����
		node->next = head;
		if (head) {// ���� ������ ����������
			head->prev = node;// ������������� ������ ��� ���������� ��� ������ ����
		}
		head = node; // ������������� ����� ���� ��� ������
		if (tail == nullptr) {// ���� ����� ����
			tail = head;// ����� ����� ������ �������
		}
		size++;
	}
	// ������� �������� � ����� ������ O(1)
	void insert_end(T data) override {
		Node<T>* node = new Node<T>(data); // ������� ����� ����
		if (tail) { // ���� ����� ����������
			tail->next = node; // ������������� ����� ���� ��� ��������� ��� ������
			node->prev = tail; // ������������� ����� ��� ���������� ��� ������ ����
			tail = node; // ��������� ����� ������
		}
		else {
			head = tail = node; // ���� ������ ����, ������������� ����� ���� ��� ������ � �����
		}
		size++; // ����������� ������ ������
	}

	// ������� �������� ����� ������������� �������� O(n)
	void insert_after(T key, T data) {
		Node<T>* key_node = find(key); // ���� ���� � ������
		if (key_node) { // ���� ���� ������
			Node<T>* node = new Node<T>(data); // ������� ����� ����
			node->next = key_node->next; // ������������� ��������� ���� ��� ������ ����
			node->prev = key_node; // ������������� ��������� ���� ��� ���������� ��� ������ ����
			if (key_node->next) { // ���� � ���������� ���� ���� ���������
				key_node->next->prev = node; // ������������� ����� ���� ��� ���������� ��� ���������� ����
			}
			key_node->next = node; // ������������� ����� ���� ��� ��������� ��� ���������� ����
			if (key_node == tail) { // ���� ��������� ���� �������� �������
				tail = node; // ��������� ����� ������
			}
			size++; // ����������� ������ ������
		}
	}

	// ������� �������� �� ������� O(n)
	void insert_at(size_t index, T data) {
		if (index > size) { // ���� ������ ������ ������� ������
			throw std::out_of_range("Index out of range"); // ������� ����������
		}
		if (index == 0) { // ���� ������ ����� 0
			insert_begin(data); // ��������� ������� � ������ ������
		}
		else if (index == size) { // ���� ������ ����� ������� ������
			insert_end(data); // ��������� ������� � ����� ������
		}
		else {
			Node<T>* temp = head; // �������� � ������ ������
			for (size_t i = 0; i < index - 1; i++) { // �������� �� ������ �� ������� �������
				temp = temp->next;
			}
			Node<T>* node = new Node<T>(data); // ������� ����� ����
			node->next = temp->next; // ������������� ��������� ���� ��� ������ ����
			node->prev = temp; // ������������� ������� ���� ��� ���������� ��� ������ ����
			temp->next->prev = node; // ������������� ����� ���� ��� ���������� ��� ���������� ����
			temp->next = node; // ������������� ����� ���� ��� ��������� ��� �������� ����
			size++; // ����������� ������ ������
		}
	}

	// �������� ������������ ������������
	DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept {
		if (this != &other) { // ���� ������� ������ �� �������� �������� other
			while (head) { // ���� ���� ������ ������
				Node<T>* temp = head; // ��������� ������ �� ������ ������
				head = head->next; // ��������� ������ ������
				delete temp; // ������� ����������� ����
			}
			head = other.head; // �������� ������ �� other
			tail = other.tail; // �������� ����� �� other
			size = other.size; // �������� ������ �� other
			other.head = nullptr; // �������� ������ � other
			other.tail = nullptr; // �������� ����� � other
			other.size = 0; // �������� ������ � other
		}
		return *this; // ���������� ������ �� ������� ������
	}

	// �������� �������� �� ������ �� ��������
	bool remove(T data) override {
		Node<T>* temp = head; // �������� � ������ ������
		while (temp) { // �������� �� ���� ��������� ������
			if (temp->data == data) { // ���� ����� ������� � ������� �������
				if (temp->prev) { // ���� � �������� ���� ����������
					temp->prev->next = temp->next; // ��������� ������ �� ��������� ������� � �����������
				}
				if (temp->next) { // ���� � �������� ���� ���������
					temp->next->prev = temp->prev; // ��������� ������ �� ���������� ������� � ����������
				}
				if (temp == head) { // ���� ������� �������� ������� ������
					head = temp->next; // ��������� ������ ������
				}
				if (temp == tail) { // ���� ������� �������� ������� ������
					tail = temp->prev; // ��������� ����� ������
				}
				delete temp; // ������� �������
				size--; // ��������� ������ ������
				return true; // ���������� true, ��� ��� ������� ��� ������
			}
			temp = temp->next; // ��������� � ���������� ��������
		}
		return false; // ���� ������� �� ������, ���������� false
	}

	// ����� �������� � ������
	Node<T>* find(T data) {
		Node<T>* temp = head; // �������� � ������ ������
		while (temp) { // �������� �� ���� ��������� ������
			if (temp->data == data) { // ���� ����� ������� � ������� �������
				return temp; // ���������� ��������� �������
			}
			temp = temp->next; // ��������� � ���������� ��������
		}
		return nullptr; // ���� ������� �� ������, ���������� ������ ������ ���� T
	}

	// ����������� ���� ������� � ����������
	void concatenate(DoublyLinkedList<T>& list) {
		if (tail) { // ���� � �������� ������ ���� �����
			tail->next = list.head; // ��������� ������ �� ��������� ������� � ������ �������� ������
		}
		if (list.head) { // ���� � ������� ������ ���� ������
			list.head->prev = tail; // ��������� ������ �� ���������� ������� � ������ ������� ������
		}
		if (list.tail) { // ���� � ������� ������ ���� �����
			tail = list.tail; // ��������� ����� �������� ������
		}
		size += list.size; // ����������� ������ �������� ������
		list.head = list.tail = nullptr; // �������� ������ � ����� ������� ������
		list.size = 0; // �������� ������ ������� ������
	}
	// ������ � �������� �� ������� O(n) //������� ����������
	T get_at(size_t index) {
		if (index >= size) { // ���� ������ ������ ��� ����� ������� ������
			throw std::out_of_range("Index out of range"); // ������� ����������
		}
		Node<T>* temp = head; // �������� � ������ ������
		for (size_t i = 0; i < index; i++) { // �������� �� ������ �� ������� �������
			temp = temp->next;
		}
		return temp->data; // ���������� ������ ����
	}

	// ��������� ������� ������
	size_t get_size() override {
		return size; // ���������� ������ ������
	}

	// ������� ������
	void clear() {
		while (head) { // ���� ���� ������ ������
			Node<T>* temp = head; // ��������� ������ �� ������ ������
			head = head->next; // ��������� ������ ������
			delete temp; // ������� ����������� �������
			size--;
		}
	}
};