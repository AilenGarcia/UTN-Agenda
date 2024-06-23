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
   int day,month,year;
} Fecha;

typedef struct{
    int id;
    char nombre[30];
    char estado;
    Usuario persona[20];
    Fecha fecha;
} Evento;

typedef struct{
    int id;
    char nombre[30];
    char estado;
    Fecha fecha;
} Cita;

int validarCita(char nombre[]); //FUNCION QUE COMPRUEBA SI EL NOMBRE DE LA TAREA QUE SE QUIERE ANOTAR ESTÁ REPETIDA O NO
int anotarCita(char nombreArchivo[]);
Fecha cargarFecha();

void tacharCita (char nombreArchivo[], Cita array[], int id);
int retornarIDCitaSegunNombre(char nombreArchivo[]);
void pasajeDeArregloAArchivoCita (Cita array[], int validos, char nombreArchivo[]);
int pasajeDeArchivoAArrayCita (Cita array[],int id, char nombreArchivo[]);

Cita modificarCita (Cita cita1, char archivoUsuarios[]);
void modificarCitaPorNombre(char nombreArchivo[], char archivoUsuarios[], char nombre[]);

void mostrarCitas (char nombreArchivo[]);
void mostrarCita(Cita aux, Usuario persona);
void mostrarFechaCita (Cita aux);


#endif // AGENDA_H_INCLUDED
