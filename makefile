
main : Textura.o main.c
	gcc Textura.o main.c -o casaKaioh -lglut -lGL -lGLU -lm

Textura.o : Textura.h Textura.c draw.c
	gcc -c Textura.c draw.c

