#include "Textura.h"

#include <stdio.h>
#include <GL/glut.h>
#include <GL/glu.h>

int idTextura = -1;

int carregaBmp (const char* nomearquivo)
{
	
    int i;
    char temp;

    MBITMAPINFOHEADER cabecalho;

    idTextura++;

    FILE* file = fopen(nomearquivo, "rb");

    if (file == NULL)
        exit(0);


    fseek(file, 18, SEEK_CUR);

    fread(&cabecalho.biWidth, sizeof(int), 1, file);
    fread(&cabecalho.biHeight, sizeof(int), 1, file);
    fread(&cabecalho.biPlanes, sizeof(short int), 1, file);

    if (cabecalho.biPlanes != 1)
	    exit(0);

    fread(&cabecalho.biBitCount, sizeof(unsigned short int), 1, file);

    if (cabecalho.biBitCount != 24)
        exit(0);

    fseek(file, 24, SEEK_CUR);

    cabecalho.data = (char*) malloc(cabecalho.biWidth * cabecalho.biHeight * 3);

    if (cabecalho.data == NULL)
	    exit(0);

    if (fread(cabecalho.data, cabecalho.biWidth * cabecalho.biHeight * 3, 1, file) != 1)
		exit(0);

    for (i=0; i < (cabecalho.biWidth * cabecalho.biHeight * 3); i += 3)
    {
	    temp = cabecalho.data[i];
	    cabecalho.data[i] = cabecalho.data[i+2];
	    cabecalho.data[i+2] = temp;
    }


    fclose(file);

	glBindTexture(GL_TEXTURE_2D, idTextura);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glTexImage2D(GL_TEXTURE_2D, 0, 3, cabecalho.biWidth, cabecalho.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, cabecalho.data);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, cabecalho.biWidth, cabecalho.biHeight, GL_RGB, GL_UNSIGNED_BYTE, cabecalho.data);

    free(cabecalho.data);

    return idTextura;
    
}
