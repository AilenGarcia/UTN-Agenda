#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agenda.h"
#define DIMNOMBRE 50

int main()
{
    char nombreArchivo[50]={"cita.bin"};
    char control = 's';
    int eleccion, eleccionUsuario, eleccionEventos, eleccionCitas;
Cita cita1;
Cita array[50];
int id;
char nombre[25];
    do{
        printf("Que desea hacer? \n"
               "1) Usuarios \n "
               "2) Eventos \n "
               "3) Citas \n");
        fflush(stdin);
        scanf("%i", &eleccion);

        switch(eleccion){
    case 1:

        printf("1) Crear usuario \n"
               "2) Eliminar usuario \n"
               "3) Modificar usuario \n"
               "4) Consultar por un usuario \n"
               "5) Listado de usuarios \n");
        fflush(stdin);
        scanf("%i", &eleccionUsuario);

        switch(eleccionUsuario){

    case 1:
        break;
    default:
        printf("Error. Elija una opcion valida \n");
        }
        break;
    case 2:
        printf("1) Anotar evento \n"
               "2) Tachar evento \n"
               "3) Modificar evento \n"
               "4) Eventos proximos \n"
               "5) Listado de eventos");
        fflush(stdin);
        scanf("%i",&eleccionEventos);
            switch(eleccionEventos){
            case 1:
                break;
            default:
                printf("Error. Elija una opcion valida \n");
            }
        break;

    case 3:
              printf("1) Anotar cita \n"
               "2) Tachar cita \n"
               "3) Modificar cita \n"
               "4) citas proximas \n"
               "5) Listado de citas\n"
                    "\nEleccion: ");
        fflush(stdin);
        scanf("%i",&eleccionCitas);

            switch(eleccionCitas){

            case 1:
                anotarCita(nombreArchivo);
                break;

            case 2:
                tacharCita(nombreArchivo,array,id);
                break;
            case 3:
                modificarCitaPorNombre(nombreArchivo,archivoUsuarios,nombre[])

            case 5:
                mostrarCitas(nombreArchivo);

            default:
                printf("Error. Elija una opcion valida \n");
            }

        break;
    default:
        printf("Error. Elija una opcion valida. \n");
        }

        printf("Si desea continuar presione s: \n");
        fflush(stdin);
        scanf("%c", &control);
    }while(control == 's');

    return 0;
