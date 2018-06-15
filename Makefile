main:	manager.o	file.o	tree.o
	gcc	manager.o	file.o	tree.o	-o	manager.exe
	rm *.o
manager.o:
	gcc -c manager.c
file.o:	file.h	file.c
	gcc -c file.c
tree.o:	tree.h	tree.c
	gcc -c tree.c