#ifndef MYLIST_H 
#define MYLIST_H 

/*  Концепция двухсвязного спиcка

NULL <- [prev0 data0 next0] <-> [prev1 data1 next1] <-> [prev2 data2 next2] -> NULL

            Node0(head)           Node1                  Node2(tail)


next0 = &Node1
next1 = &Node2
next2 = NULL

prev0 = NULL
prev1 = &Node0
prev2 = &Node1

*/

// Cтруктура узла двухсвязного списка (один элемент списка)
typedef struct Node {
    int data;
    struct Node* prev;  // указатель на прерыдущий элемент
    struct Node* next;  // указатель на следующий элемент
} Node;

// Структура самого списка
typedef struct {
    Node* head;         // указатель на первый элемент
    Node* tail;         // указатель на последний элемент
    int size;           // счетчик элементов списка
} DoublyLinkedList;


void initList(DoublyLinkedList* list);
Node* createNode(int value); 
void append(DoublyLinkedList* list, int value);
void freeList(DoublyLinkedList* list);

void printForward(const DoublyLinkedList* list);
void printBackward(const DoublyLinkedList* list);

void generateRandomList(DoublyLinkedList* list, int count);

void printBinaryValue(const DoublyLinkedList* list);


#endif // MYLIST_H