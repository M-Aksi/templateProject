#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "MyList.h"
#define SIZE 10            // максимальный размер двоичного числа


// Функция для инициализации списка
void initList(DoublyLinkedList* list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}


// Функция выделения памяти под новый узел
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation error!\n");
        exit(1);                                 // аварийное завершение 
    }
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Функция добавления элемента в конец списка
void append(DoublyLinkedList* list, int value) {
    Node* newElement = createNode(value); 
    if (list -> head == NULL){                   // если список пустой
        newElement -> prev = NULL;
        list -> head = newElement;
    }
    else {                                       // уже не пустой
        newElement -> prev = list -> tail;       // связь текущего с предыдущим
        list -> tail -> next = newElement;       // связь предыдущего с текущим
    }
    list -> tail = newElement;                   // переопределение конца(указателя) на новый элемент
    ++(list -> size);                            // увеличение списка
}

// Функция освобождения памяти
void freeList(DoublyLinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;                 // освобождаем память, запоминая указатель на следующий элемент
        free(temp);
    }
    list->head = NULL;                           // уничтожаем указатели непосредственно списка
    list->tail = NULL;
    list->size = 0;
}

// Функция вывода списка от начала к концу
void printForward(const DoublyLinkedList* list){
    Node* current = list -> head;
    printf("Dec list: ");
    while(current != NULL){
        printf("%d ", current -> data);
        current = current -> next;
    }
    printf("\n");
}

// Функция вывода списка от конца к началу
void printBackward(const DoublyLinkedList* list){
    Node* current = list -> tail;
    printf("Dec list: ");
    while(current != NULL){
        printf("%d ", current -> data);
        current = current -> prev;
    }
    printf("\n");
}

void generateRandomList(DoublyLinkedList* list, int count){
    // Инициализация генератора случайных чисел
    srand(time(NULL));
    for (int i = 0; i < count; ++i){
        append(list, rand() % 100);
    }
}

// Функция для вывода списка в двоичном виде
void printBinaryValue(const DoublyLinkedList* list) {
    printf("Binary list: ");
    Node* current = list -> head;
    int numberDec;
    int count = -1;
    while(current != NULL){
        numberDec = current -> data;
        int* numberBin = (int*)calloc(SIZE, sizeof(int));
        if (numberBin == NULL){
            printf("Memory allocation error!\n");
            exit(1);
        }
        //printf("%d ", numberDex);
        numberBin[++count] = numberDec % 2;
        while (numberDec != 0){
            numberDec /= 2;
            numberBin[++count] = numberDec % 2;  // добываем 0 и 1 из числа       
        }
        
        
        // разворачиваем двоичное число 
        for (int i = 0; i < count / 2; ++i){
            int bubble = numberBin[i];
            numberBin[i] = numberBin[count - 1 - i]; // обмен крайних элементов, двигаемся к середине
            numberBin[count - 1 - i] = bubble; 
        }
        // вывод в консоль
        for (int i = 0;i < count; ++i){
            printf("%d",numberBin[i]);
        }
        printf(" "); // пробел между двоичными числами
        free(numberBin); // освобождаем память
        numberBin = NULL;
        numberDec = 0;
        count = -1;
        current = current -> next;
    }
    printf("\n");
}