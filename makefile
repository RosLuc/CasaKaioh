main : Textura.o main.c
	gcc Textura.o main.c -o teste -lglut -lGL -lGLU -lm

Textura.o : Textura.h Textura.c draw.c
	gcc -c Textura.c draw.c

