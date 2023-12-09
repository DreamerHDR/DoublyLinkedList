#include "DoublyLinkedList.h"

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), speedup(nullptr), speedupSize(0) {}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() 
{
    while (head) 
    {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
    delete[] speedup;
}

template <typename T>
void DoublyLinkedList<T>::insertFront(T val) 
{
    Node<T>* newNode = new Node<T>(val);
    if (!head) 
    {
        head = tail = newNode;
    }
    else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    speedupNodes();
}

template <typename T>
void DoublyLinkedList<T>::insertBack(T val) 
{
    Node<T>* newNode = new Node<T>(val);
    if (!tail) 
    {
        head = tail = newNode;
    }
    else 
    {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    speedupNodes();
}

template <typename T>
void DoublyLinkedList<T>::insertAfter(int index, T val) 
{
    if (index < 0) 
    {
        std::cout << "Неверный индекс." << std::endl;
        return;
    }

    Node<T>* newNode = new Node<T>(val);

    Node<T>* current = getNodeByIndex(index);
    if (!current) 
    {
        std::cout << "Неверный индекс." << std::endl;
        return;
    }

    newNode->next = current->next;
    if (current->next) 
    {
        current->next->prev = newNode;
    }
    current->next = newNode;
    newNode->prev = current;
    if (current == tail) 
    {
        tail = newNode;
    }

    speedupNodes();

    // Выводим список без сортировки
    std::cout << "После вставки " << val << " по логическому индексу " << index << " (без сортировки): ";
    display();

    // Сортируем и выводим
    sortList();
    std::cout << "После сортировки: ";
    display();
}

template <typename T>
Node<T>* DoublyLinkedList<T>::getNodeByIndex(int index) {
    if (index < 0) 
    {
        return nullptr;
    }

    Node<T>* current = head;
    int currentIndex = 0;

    while (current && currentIndex < index) 
    {
        current = current->next;
        currentIndex++;
    }

    return current;
}

template <typename T>
void DoublyLinkedList<T>::sortList() {
    // Сортировка списка
    Node<T>* i, * j;
    T temp;

    for (i = head; i != nullptr; i = i->next) 
    {
        for (j = i->next; j != nullptr; j = j->next) 
        {
            if (i->data > j->data) 
            {
                temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

template <typename T>
void DoublyLinkedList<T>::remove(int index) 
{
    if (index < 0) 
    {
        std::cout << "Неверный индекс." << std::endl;
        return;
    }

    Node<T>* current = getNodeByIndex(index);
    if (!current) 
    {
        std::cout << "Неверный индекс." << std::endl;
        return;
    }

    if (index == 0) 
    {
        if (!head) 
        {
            std::cout << "Список пуст." << std::endl;
            return;
        }

        Node<T>* temp = head;
        head = head->next;
        if (head) 
        {
            head->prev = nullptr;
        }
        delete temp;

        if (!head) 
        {
            tail = nullptr;
        }

        speedupNodes();
        return;
    }

    current->prev->next = current->next;
    if (current->next) {
        current->next->prev = current->prev;
    }
    if (current == tail) {
        tail = current->prev;
    }
    delete current;

    speedupNodes();
}

template <typename T>
void DoublyLinkedList<T>::display() 
{
    Node<T>* current = head;
    while (current) 
    {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

template <typename T>
void DoublyLinkedList<T>::displaySpeedup() 
{
    for (int i = 0; i < speedupSize; i++) 
    {
        std::cout << speedup[i]->data << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void DoublyLinkedList<T>::speedupNodes() {
    delete[] speedup;
    speedupSize = 0;
    Node<T>* current = head;
    int index = 0;
    while (current) {
        if (index % 10 == 0) 
        {
            speedupSize++;
        }
        current = current->next;
        index++;
    }
    speedup = new Node<T>*[speedupSize];
    current = head;
    index = 0;
    int speedupIndex = 0;
    while (current) 
    {
        if (index % 10 == 0) 
        {
            speedup[speedupIndex] = current;
            speedupIndex++;
        }
        current = current->next;
        index++;
    }
}

template <typename T>
void DoublyLinkedList<T>::saveToFile(const std::string& filename) 
{
    std::ofstream file(filename);
    if (!file.is_open()) 
    {
        std::cout << "Не удалось открыть файл для записи." << std::endl;
        return;
    }

    Node<T>* current = head;
    while (current) 
    {
        file << current->data << " ";
        current = current->next;
    }

    file.close();
    std::cout << "Список сохранен в файл: " << filename << std::endl;
}

template <typename T>
void DoublyLinkedList<T>::loadFromFile(const std::string& filename) 
{
    std::ifstream file(filename);
    if (!file.is_open()) 
    {
        std::cout << "Не удалось открыть файл для чтения." << std::endl;
        return;
    }

    // Очистим текущий список перед загрузкой
    clear();

    T value;
    while (file >> value)
    {
        insertBack(value);
    }

    file.close();
    std::cout << "Список загружен из файла: " << filename << std::endl;
}

template <typename T>
void DoublyLinkedList<T>::clear() 
{
    while (head) 
    {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    delete[] speedup;
    speedup = nullptr;
    speedupSize = 0;
}

template <typename T>
void DoublyLinkedList<T>::choice() 
{
    while (true) 
    {
        int option;
        std::cout << "Выберите действие:" << std::endl;
        std::cout << "1. Отображение с использованием массива ускорения" << std::endl;
        std::cout << "2. Вывод после вставки по логическому индексу" << std::endl;
        std::cout << "3. После удаления элемента по логическому индексу" << std::endl;
        std::cout << "4. Сохранить список в файл" << std::endl;
        std::cout << "5. Загрузить список из файла" << std::endl;
        std::cout << "6. Вставить и сортировать" << std::endl;
        std::cout << "0. Выход из программы" << std::endl;
        std::cout << "Ваш выбор: ";
        std::cin >> option;

        switch (option) 
        {
        case 1:
            std::cout << "Отображение с использованием массива ускорения: ";
            displaySpeedup();
            break;
        case 2: 
        {
            int insertIndex;
            T insertValue;
            std::cout << "Введите логический индекс для вставки: ";
            std::cin >> insertIndex;
            std::cout << "Введите значение для вставки: ";
            std::cin >> insertValue;
            insertAfter(insertIndex, insertValue);
            break;
        }
        case 3: 
        {
            int removeIndex;
            std::cout << "Введите логический индекс для удаления: ";
            std::cin >> removeIndex;
            remove(removeIndex);
            std::cout << "После удаления элемента по логическому индексу " << removeIndex << ": ";
            display();
            break;
        }
        case 4: 
        {
            std::string saveFilename;
            std::cout << "Введите имя файла для сохранения: ";
            std::cin >> saveFilename;
            saveToFile(saveFilename);
            break;
        }
        case 5: 
        {
            std::string loadFilename;
            std::cout << "Введите имя файла для загрузки: ";
            std::cin >> loadFilename;
            loadFromFile(loadFilename);
            std::cout << "Список после загрузки: ";
            display();
            break;
        }
        case 6: 
        {
            int insertSortIndex;
            T insertSortValue;
            std::cout << "Введите логический индекс для вставки и сортировки: ";
            std::cin >> insertSortIndex;
            std::cout << "Введите значение для вставки и сортировки: ";
            std::cin >> insertSortValue;
            insertAfter(insertSortIndex, insertSortValue);
            sortList();
            break;
        }
        case 0:
            std::cout << "Выход из программы." << std::endl;
            return;
        default:
            std::cout << "Неверный выбор." << std::endl;
        }
    }
}

template class DoublyLinkedList<int>;
template class DoublyLinkedList<double>;