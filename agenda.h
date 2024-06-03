#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef AGENDA_H_INCLUDED
#define AGENDA_H_INCLUDED


typedef struct{
    int dni;
    char nombre[20];
    int  edad;
    char genero;
} Usuario;

typedef struct{
   int day, month, year;
} Fecha;

typedef struct{
    int id;
    char nombre[30];
    char estado;
    Usuario persona[20];
    Fecha fecha[];
} Evento;

typedef struct{
    int id;
    char nombre[30];
    char estado;
    Fecha fecha[];
} Tarea;

int validarTarea(char *idTarea, char tareas[]); //FUNCION QUE COMPRUEBA SI EL NOMBRE DE LA TAREA QUE SE QUIERE ANOTAR ESTÁ REPETIDA O NO
int anotarTarea(char nombreArchivo[], int validos);

#endif // AGENDA_H_INCLUDED
