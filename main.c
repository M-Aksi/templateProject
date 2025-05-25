#include <stdio.h>
#include <pthread.h>
#include "MyList.h"
#include "delay.h"
#include "MyThreads.h"
 

int main() {
    // Подготовка данных
    int sizeList = 0;
    printf("Enter a number of type int: ");
    scanf("%d", &sizeList);
    printf("\n");
    DoublyLinkedList MyList;
    initList(&MyList);                       
    generateRandomList(&MyList, sizeList);
    
    // Смотрим на подготовленные данные
    printForward(&MyList);                 // десятичный вид
    printBinaryValue(&MyList);             // двоичный вид

    // Многопоточность

    // Инициализация мьютекса
    pthread_mutex_t listMutex = PTHREAD_MUTEX_INITIALIZER;
    /*
        Мьютексы нужны для защиты от одновременного 
        доступа сразу нескольких потоков к одному
        обЪекту. Их необходимо использовать, если 
        предполагается, что список будет не просто 
        считываться, а изменяться в разных потоках.

    */

    // Подготовка аргументов для потоков (инициализация структур)
    ThreadArgs args1 = {MyList.head, MyList.tail, 0, 0, 0, 1, &listMutex};    // Поток 1 (от головы)
    ThreadArgs args2 = {MyList.head, MyList.tail, 0, 0, 0, 0, &listMutex};    // Поток 2 (от хвоста)
    
    // Запуск многопоточной обработки
    threadStart(&args1, &args2);

    // Вывод результатов
    threadPrint(&args1, &args2);

    delay_ms(5000);                        // задержка отображения в консоли (Linux|Windows)
    pthread_mutex_destroy(&listMutex);    // Уничтожение мьютекса
    freeList(&MyList);                     // освобождение памяти
    return 0;
}