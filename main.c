#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agenda.h"
#define DIMNOMBRE 50
#include "pila.h"

int main()
{
    char archivoUsuarios[50];
    char nombreArchivo[50]={"cita.bin"};
    char control = 's';
    char controlCitas='s';
    char nombre[25];
    int id;
    int eleccion, eleccionUsuario, eleccionEventos, eleccionCitas,idAEliminar, mes;
Cita cita1;
Cita arrayCita[50];
Pila *pila1;

inicpila(pila1);

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
               "6) Total de citas en el mes"
                    "\nEleccion: ");
        fflush(stdin);
        scanf("%i",&eleccionCitas);

            switch(eleccionCitas){

            case 1:
                anotarCita(nombreArchivo);
                break;

            case 2:
              while(controlCitas== 's')
                {
                    printf("Ingrese el Nombre a buscar: \n");
                    fflush(stdin);
                    gets(nombre);

                    idAEliminar=retornarIDSegunNombre(nombreArchivo, nombre);

                    if(idAEliminar!=0){
                        eliminarCita(nombreArchivo, arrayCita,idAEliminar);
                    }
                    printf("Quiere eliminar otra cita? \n"
                               "Ingrese s para SI o n para NO \n");
                        fflush(stdin);
                        scanf("%c", &controlCitas);
                }
                break;

            case 3:
                while(controlCitas=='s')
                    {
                 printf("\nIngrese el Nombre: ");
                    fflush(stdin);
                    scanf("%s", &nombre);
                    system("cls");

                    modificarCitaPorNombre(nombreArchivo, archivoUsuarios, nombre);

                    printf("Quiere modificar otra cita? \n"
                               "Ingrese s para SI o n para NO \n");
                        fflush(stdin);
                        scanf("%c", &controlCitas);
                }
            break;

            case 4:
           citasProximas(nombreArchivo,cita1);
                break;

            case 5:
             mostrarCitas(nombreArchivo);
                break;

            case 6:
            while(controlCitas=='s')
            {
                printf ("ingrese el numero del mes a averiguar: ");
                fflush(stdin);
                scanf("%i", &mes);

                cantidadCitasEnMes(arrayCita,pila1,mes, nombreArchivo);

            }
                break;

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
}
