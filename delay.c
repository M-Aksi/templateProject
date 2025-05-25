#include "delay.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// функция для задержки консоли в Linux или Windows
void delay_ms(int milliseconds) {
    #ifdef _WIN32
    Sleep(milliseconds);
    #else
    usleep(milliseconds * 1000);
    #endif
}