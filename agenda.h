#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef AGENDA_H_INCLUDED
#define AGENDA_H_INCLUDED
#define DIMNOMBRE 50
#define DIMDNI 11
#define DIMPASS 10

typedef struct{
    char dni[DIMDNI];
    char nombre[DIMNOMBRE];
    int  edad;
    char genero;
    char pass[DIMPASS];
    int rol;
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

//TAREAS
int validarTarea(char *idTarea, char tareas[]); //FUNCION QUE COMPRUEBA SI EL NOMBRE DE LA TAREA QUE SE QUIERE ANOTAR ESTÁ REPETIDA O NO
int anotarTarea(char nombreArchivo[], int validos);

//USUARIOS

int validarPorDni(char usuarios[], char dni[]);
int iniciarSesion(char usuarios[]);
void cargarDatos(char nombreArchivo[]);
int validarPass(char pass[]);
void cargarPass(char pass[]);
int validarNombre(char nombre[]);
void cargarNombre(char nombre[]);
int validarDni(char dni[]);
void cargarDni(char dni[], char usuarios[]);
int validarGenero(char genero[]);
char cargarGenero();
int validarEdad(int edad);
int cargarEdad();
Usuario crearUsuario();
void cargarUsuario(char usuarios[]);
void mostrarUsuarios(char usuarios[]);
void mostrarUsuario(Usuario usuario);
Usuario buscarPorDni(char usuarios[], char dni[]);
Usuario buscador(char usuarios[], char dni[]);
Usuario modificarUsuario(Usuario usuario);
void modificarUsuarioPorDNI(char usuarios[], char dni[]);
int pasajeDeArchivoAArray(Usuario array[],char dni[], char usuarios[]);
void pasajeDeArregloAArchivo(Usuario array[], int validos, char usuarios[]);
void eliminarUsuario(char usuarios[], Usuario *array, char dni[]);


#endif // AGENDA_H_INCLUDED
