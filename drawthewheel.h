#ifndef DRAWTHEWHEEL_H
#define DRAWTHEWHEEL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cairo.h>


#define MAX_FIELDS 12
#define NAME_LENGTH 50
#define PI 3.14159265358979323846

typedef struct {
    char name[NAME_LENGTH];
    int level;  // 1-10
    double color[4];  // RGBA values (0-1)
} LifeField;

//extern const char* DEFAULT_FIELDS[];

const double DEFAULT_COLORS[][4] = {
    {0.8, 0.2, 0.2, 0.8}, // Rojo para Amor
    {0.2, 0.6, 0.8, 0.8}, // Azul claro para Familia
    {0.8, 0.6, 0.2, 0.8}, // Naranja para Amigos
    {0.2, 0.8, 0.2, 0.8}, // Verde para Crecimiento
    {0.6, 0.2, 0.8, 0.8}, // Púrpura para Propósito
    {0.1, 0.5, 0.1, 0.8}, // Verde oscuro para Dinero
    {0.4, 0.4, 0.8, 0.8}, // Azul lavanda para Espiritualidad
    {0.8, 0.4, 0.0, 0.8}, // Naranja oscuro para Físico
    {0.5, 0.5, 0.5, 0.8}  // Gris para Mente
};

//void imagenBase();

void draw_wheel(LifeField fields[], int field_count, const char* filename);


#endif // DRAWTHEWHEEL_H
