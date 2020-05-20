#ifndef TEXTURA_H_INCLUDED
#define TEXTURA_H_INCLUDED

#include <GL/glut.h>
#include <GL/glu.h>

typedef struct {
    unsigned int biSize;
    int biWidth;
    int biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int biCompression;
    unsigned int biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    unsigned int biClrUsed;
    unsigned int biClrImportant;
    char* data;
} MBITMAPINFOHEADER;

int carregaBmp (const char*);

#endif // TEXTURA_H_INCLUDED
