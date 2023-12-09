#pragma once
#include <iostream>
#include <fstream>
#include <string>

template <typename T>
class Node {
public:
    T data;
    Node* prev;
    Node* next;

    Node(T val) : data(val), prev(nullptr), next(nullptr) {}
};

template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    Node<T>** speedup;
    int speedupSize;

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void insertFront(T val);
    void insertBack(T val);
    void insertAfter(int index, T val);
    Node<T>* getNodeByIndex(int index);
    void sortList();
    void remove(int index);
    void display();
    void displaySpeedup();
    void speedupNodes();
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
    void clear();
    void choice();
};
