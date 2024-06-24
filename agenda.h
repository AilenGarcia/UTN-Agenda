#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef AGENDA_H_INCLUDED
#define AGENDA_H_INCLUDED
#include "pila.h"

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

//CITAS//
int rellenarNombreCita(char nombre[]);
int validarNombreCita(char nombre[], FILE *archi, char nombreArchivo[]); //FUNCION QUE COMPRUEBA SI EL NOMBRE DE LA TAREA QUE SE QUIERE ANOTAR ESTÁ REPETIDA O NO
int validarDia(int day);
int validarDia(int day);

Cita anotar1Cita(FILE *archi, char nombreArchivo[]);
int anotarCita(char nombreArchivo[]);
Fecha cargarFecha();

int retornarIDSegunNombre(char nombreArchivo[], char nombre[]);
int pasajeDeArchivoAArrayCitas(Cita array[],int id, char nombreArchivo[]);
void pasajeDeArregloAArchivoCita (Cita array[], int validos, char nombreArchivo[]);
void eliminarCita(char nombreArchivo[], Cita array[], int id);

Cita modificarCita(Cita cita1, char archivoUsuarios[]);
void modificarCitaPorNombre(char nombreArchivo[], char archivoUsuarios[], char nombre[]);
Cita buscarCitaSegunNombre(char nombreArchivo[]);

void citasProximas (char nombreArchivo[], Cita cita1);

void mostrarFechaCita (Cita aux);
void mostrar1Cita(Cita cita1);
void mostrarCitas (char nombreArchivo[]);

void cargarPila(Pila *pila, char nombreArchivo[], int mes);
int cantidadCitasEnMes(char citas[], Pila pila, int mes, char nombreArchivo[]);


#endif // AGENDA_H_INCLUDED
