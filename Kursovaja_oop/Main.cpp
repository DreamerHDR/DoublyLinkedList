#include "DoublyLinkedList.h"

int main() 
{
    system("chcp 1251");
    DoublyLinkedList<double> myList;

    for (double i = 0; i <= 30; i += 1) 
    {
        myList.insertBack(i);
    }

    myList.display();

    myList.choice();

    return 0;
}
