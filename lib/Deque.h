//Автор:Гаврилов Д. 
//шаблонный//size_t//тесты assert// is_empty//размер возвр//capacity методы// правило пяти*
using namespace std;
// Реализация очереди на основе массива
class ArrayQueue {
    int front, rear, capacity; // front - начало очереди, rear - конец очереди, capacity - вместимость очереди
    int* queue; // указатель на массив, который будет использоваться для хранения элементов очереди
public:
    ArrayQueue(int c) { // конструктор класса
        front = rear = 0; // инициализация начала и конца очереди
        capacity = c; // установка вместимости очереди
        queue = new int [c]; // выделение памяти под массив
    }

    ~ArrayQueue() { delete[] queue; } // деструктор класса, освобождает память

    void enqueue(int data) { // функция добавления элемента в очередь
        if (capacity == rear) { // если очередь полная
            cout << "\nОчередь заполнена\n";
            return;
        }
        else {
            queue[rear] = data; // добавление элемента в конец очереди
            rear++; // сдвиг конца очереди
        }
    }

    void dequeue() { // функция удаления элемента из очереди
        if (front == rear) { // если очередь пуста
            cout << "\nОчередь пуста\n";
            return;
        }
        else {
            for (int i = 0; i < rear - 1; i++) { // сдвиг всех элементов влево
                queue[i] = queue[i + 1];
            }
            rear--; // сдвиг конца очереди
        }
    }

    void display() { // функция вывода элементов очереди
        if (front == rear) { // если очередь пуста
            cout << "\nОчередь пуста";
            return;
        }
        for (int i = front; i < rear; i++) { // вывод всех элементов очереди
            cout << queue[i] << "<-";
        }
    }
};

// Реализация очереди на основе списка//в отдельный класс// list переделать
struct Node { // структура узла списка
    int data; // данные узла
    struct Node* next; // указатель на следующий узел
};

void enqueue(Node** front, Node** rear, int data) { // функция добавления элемента в очередь
    Node* newNode = new Node(); // создание нового узла
    if (newNode == NULL) { // если не удалось выделить память
        cout << "Очередь заполнена";
    }
    else {
        newNode->data = data; // присвоение данных новому узлу
        newNode->next = NULL; // следующий узел пока не определен
        if (*front == NULL) { // если очередь пуста
            *front = *rear = newNode; // новый узел становится началом и концом очереди
        }
        else {
            (*rear)->next = newNode; // новый узел становится концом очереди
            *rear = newNode; // обновление указателя на конец очереди
        }
    }
}

void dequeue(Node** front, Node** rear) { // функция удаления элемента из очереди
    Node* temp;
    if (*front == NULL) { // если очередь пуста
        cout << "Очередь пуста";
    }
    else {
        temp = *front; // сохранение указателя на удаляемый узел
        *front = (*front)->next; // сдвиг начала очереди
        if (*front == NULL) { // если очередь стала пустой
            *rear = NULL; // обнуление указателя на конец очереди
        }
        delete(temp); // удаление узла
    }
}