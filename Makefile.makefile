all: build
build:
	gcc -Wall -pedantic -ansi -g main.c queue.c extendArray.c -o myexe
run:
	valgrind --leak-check=full ./myexe INNN.txt
clean:
	rm main.obj queue.obj extendArray.obj myexe
