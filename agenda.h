#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef AGENDA_H_INCLUDED
#define AGENDA_H_INCLUDED
#define DIMNOMBRE 50
#define DIMDNI 11
#define DIMPASS 10
#include "pila.h"

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
    Usuario persona;
    Fecha fecha;
} Evento;

typedef struct{
    int id;
    char nombre[30];
    char estado;
    Fecha fecha;
} Cita;

//CITAS
int rellenarNombreCita(char nombre[]);
int validarNombreCita(char nombre[], FILE *archi, char nombreArchivo[]); //FUNCION QUE COMPRUEBA SI EL NOMBRE DE LA TAREA QUE SE QUIERE ANOTAR EST� REPETIDA O NO

Cita anotar1Cita(FILE *archi, char nombreArchivo[]);
int anotarCita(char nombreArchivo[]);

int retornarIDSegunNombreCita(char nombreArchivo[], char nombre[]);
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


//EVENTOS
void mostrarMatriz(char matriz[12][12], int arrayMes[], char eventos[]);
int pasarFechasArray(int arrayMes[], char eventos[]);
int recorrerArray(int arrayMes[], int validos, int mes);
void mostrarUsuariosParaEvento(char usuarios[]);
int buscarPorUsuarioPorNombre(char usuarios[], char nombre[]);
Usuario elegirUsuarioPorNombre(char usuarios[], char nombre[]);
Fecha cargarFecha ();
Evento cargarEvento(char usuarios[]);
void mostrarFecha (Fecha miFecha);
void mostrarEvento(Evento miEvento);
void mostrarEventos (char archivoEventos[]);
void mostrarPersonaEvento (Evento miEvento);
void mostrarFechaEvento (Evento miEvento);
void guardarEventoEnArchivo(char nombreArchivo[], char usuarios[]);
int cuentaElementosArchivo(char nombreArchivo[]);
int pasajeDeArchivoAArrayEventos(Evento array[],int id, char nombreArchivo[]);
void pasajeDeArregloAArchivoEvento (Evento array[], int validos, char nombreArchivo[]);
void eliminarEvento (char nombreEvento[], Evento array[], int id);
void modificarEventoPorNombre(char archivoEvento[], char archivoUsuarios[], char nombre[]);
Evento buscarEventoSegunNombre(char archivoEventos[]);
int retornarIDSegunNombre(char archivoEventos[], char nombre[]);
void eventosProximos (char archivoEventos[],Evento tuEvento);
int validarDia(int day);
int validarMes(int month);
int posicion_menor (Evento arregloEventos[], int pos, int registros);
void ordenacion_seleccion (Evento arregloEventos[], int registros);
void mostrarArrayMes(Evento arrayMes[], int registros);
int pasarArray(Evento arrayE[], char eventos[]);


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
int pasajeDeArchivoAArray(Usuario **array,char dni[], char usuarios[]);
void pasajeDeArregloAArchivo(Usuario **array, int validos, char usuarios[]);
int cantRegistros(char usuarios[]);
void eliminarUsuario(char usuarios[], Usuario *array, char dni[]);


#endif // AGENDA_H_INCLUDED
