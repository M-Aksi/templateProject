CC = gcc               # Используем компилятор gcc
CFLAGS = -Wall -Wextra # Флаги компиляции: включить все предупреждения
LDFLAGS = -lpthread    # Флаги линковки: подключить pthread
TARGET = bdz_3         # Имя итогового исполняемого файла

all: $(TARGET)         # Сборка главной цели (TARGET)

$(TARGET): main.o MyList.o delay.o MyThreads.o # Линковка object-файлов $^ — все зависимости, $@ — цель
	$(CC) $^ -o $@ $(LDFLAGS)    

main.o: main.c MyList.h                        #$< — первая зависимость
	$(CC) $(CFLAGS) -c $< -o $@  

MyList.o: MyList.c MyList.h
	$(CC) $(CFLAGS) -c $< -o $@

delay.o: delay.c delay.h
	$(CC) $(CFLAGS) -c $< -o $@

MyThreads.o: MyThreads.c MyThreads.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:                                          # Удаление всех .o-файлов и бинарника
	rm -f *.o $(TARGET)

.PHONY: all clean