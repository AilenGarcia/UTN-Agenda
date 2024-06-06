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
   int day;
   int month;
   int year;
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
} Cita;

int validarCita(int id, FILE* archi); //FUNCION QUE COMPRUEBA SI EL NOMBRE DE LA TAREA QUE SE QUIERE ANOTAR ESTÁ REPETIDA O NO
int anotarCita(char nombreArchivo[]);
void mostrar1Cita(Cita a);

#endif // AGENDA_H_INCLUDED
