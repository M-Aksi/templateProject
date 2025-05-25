#include <pthread.h>
#include <stdio.h>
#include "MyThreads.h"

// Функция для посчета нулевых битов в числе
int countZeroBits(int numberDec){
    int count = 0;
    while(numberDec != 0){
        if (numberDec % 2 == 0){
            ++count;
        }
        numberDec /= 2;
    }
    return count;
}

// Функция для подсчета единичных битов в числе
int countOneBits(int numberDec){
    int count = 0;
    while(numberDec != 0){
        if (numberDec % 2 == 1){
            ++count;
        }
        numberDec /= 2;
    }
    return count;
}
// Функция инициализации и запуска потоков
void threadStart(ThreadArgs* args1, ThreadArgs* args2){
    // Создание потоков
    pthread_t thread1;
    pthread_t thread2;

    if (pthread_create(&thread1, NULL, threadExecution, args1) != 0) {
        printf("Failed to create thread 1");
        exit(1); // аварийное завершение
    }
    if (pthread_create(&thread2, NULL, threadExecution, args2) != 0) {
        printf("Failed to create thread 2");
        exit(1); // аварийное завершение
    }
    /*  разбор функции pthread_create
        &thread1 - Указатель на переменную типа pthread_t, в которую будет записан идентификатор созданного потока
        NULL - Указатель на атрибуты потока (используем атрибуты по умолчанию)
        threadExecution - Функция обработки данных в потоке
        &args1 - Указатель на аргументы, которые будут переданы в функцию threadExecution
    */
    
    // Ожидание завершения потоков
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
}

// функция выполнения обработки данных в потоке
void* threadExecution(void* args) {
    ThreadArgs* targs = (ThreadArgs*)args;       // преобразуем принятые аргументы в структуру
    
    Node* currentNode = NULL;                       // объявляем текущий узел
    Node* nextNode = NULL;                           // и следующий
    
    currentNode = targs -> flag ? targs -> head : targs -> tail; 

    while (1) {

        // блокируем список на время чтения узла
        pthread_mutex_lock(targs -> listMutex);   

        // разблокировка, если конец списка
        if (currentNode == NULL) {
            pthread_mutex_unlock(targs -> listMutex); 
            break; 
        } 

        // Сохраняем данные и следующий узел локально
        int data = currentNode -> data;
        nextNode = targs -> flag ? currentNode -> next : currentNode -> prev;
        
        // теперь разблокируем список (чтение завершено)
        pthread_mutex_unlock(targs -> listMutex);
        
        // Обработка данных
        if (targs -> flag) {
            targs -> countZero += countZeroBits(data);
        } else {
            targs -> countOne += countOneBits(data);
        }
        ++(targs -> countNodes);
        currentNode = nextNode;
    }
    targs = NULL;
    return NULL;
}

// функция для вывода результата в консоль
void threadPrint(ThreadArgs* args1, ThreadArgs* args2){
    printf("\n");
    printf("Thread 1:\n");
    printf("Zero bits: %d\n", args1 -> countZero);
    printf("Count nodes: %d\n", args1 -> countNodes);
    printf("\n");
    printf("Thread 2:\n");
    printf("One bits: %d\n", args2 -> countOne);
    printf("Count nodes: %d\n", args2 -> countNodes);
}


