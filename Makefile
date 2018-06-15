main:	manager.o	file.o
	gcc	manager.o	file.o	-o	manager.exe
	rm *.o
manager.o:
	gcc -c manager.c
file.o:	file.h	file.c
	gcc -c file.c