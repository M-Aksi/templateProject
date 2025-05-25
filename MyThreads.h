#ifndef MYTHREADS_H 
#define MYTHREADS_H
#include "MyList.h"

// Структура аргументов для работы с потоком
typedef struct {
    Node* head;                           // Указатель на голову списка
    Node* tail;                           // Указатель на хвост списка
    int countZero;                   // Счетчик нулевых битов (для потока 1)
    int countOne;                    // Счетчик единичных битов (для потока 2)
    int countNodes;                   // Счетчик обработанных элементов
    int flag;                        // Флаг направления обхода (1 - от головы, 0 - от хвоста)
    pthread_mutex_t* listMutex;           // Мьютекс для синхронизации доступа к списку
} ThreadArgs;

int countZeroBits(int numberDec);
int countOneBits(int numberDec);
void threadStart(ThreadArgs* args1, ThreadArgs* args2);
void* threadExecution(void* args);
void threadPrint(ThreadArgs* args1, ThreadArgs* args2);

#endif //MYTHREADS_H