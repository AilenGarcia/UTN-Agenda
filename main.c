#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colors.h"
#include "agenda.h"

int main()
{
    char control = 's';
    char controlMenu = 's';
    int menu, eleccion, eleccionUsuario, eleccionEventos, eleccionTareas;
    int accesoPorRol = 5;
    char archivoUsuarios[20];
    char dni[DIMDNI];
    Usuario usuario;
    strcpy(archivoUsuarios, "usuarios.bin");
    Usuario arregloUsuarios[100];

    Evento miEvento;
    char archivoEventos[20];
    strcpy(archivoEventos,"eventos.bin");
    int registros = 0;
    int idAEliminar=0;

    cargarDatos(archivoUsuarios);

    printf( RED );
    printf("          BIENVENIDOS! \n");
    printf( WHITE );

    do{
        printf("1) Iniciar sesion \n"
               "2) Registrase \n");
        fflush(stdin);
        scanf("%i", &menu);

        system("cls");

        switch(menu){
    case 1:
        system("cls");
        accesoPorRol=iniciarSesion(archivoUsuarios);
        if(accesoPorRol != 0 && accesoPorRol != 1){
            printf("\n Datos invalidos, por favor ingreselos correctamente \n");
        }
        break;
    case 2:
        system("cls");
        cargarUsuario(archivoUsuarios);
        accesoPorRol=0;
        break;
    default:
        printf("Error. Elija una opcion valida. \n");
        }

    system("cls");
    }while(accesoPorRol == -1);

    do{
    if(accesoPorRol == 1){
        system("cls");
        printf("\n --------------------\n"
               "1) Crear usuario \n"
               "2) Eliminar usuario \n"
               "3) Modificar usuario \n"
               "4) Consultar por un usuario \n"
               "5) Listado de usuarios \n"
               "--------------------\n");
        fflush(stdin);
        scanf("%i", &eleccionUsuario);

        system("cls");

        switch(eleccionUsuario){
    case 1:
        system("cls");
        cargarUsuario(archivoUsuarios);
        break;
    case 2:
        printf("\nIngrese el dni: ");
        fflush(stdin);
        scanf("%s", &dni);
        system("cls");
        eliminarUsuario(archivoUsuarios, arregloUsuarios, dni);
        break;
    case 3:
        printf("\nIngrese el dni: ");
        fflush(stdin);
        scanf("%s", &dni);
        system("cls");
        modificarUsuarioPorDNI(archivoUsuarios, dni);
        break;
    case 4:
        printf("\nIngrese el dni: ");
        fflush(stdin);
        scanf("%s", &dni);
        system("cls");
        usuario = buscarPorDni(archivoUsuarios, dni);
        break;
    case 5:
        system("cls");
        mostrarUsuarios(archivoUsuarios);
        break;
    default:
        printf("Error. Elija una opcion valida \n");
        }
    }
        if(accesoPorRol == 0){
        system("cls");
        printf("\n --------------------\n"
               "Que desea hacer? \n "
               "1) Eventos \n "
               "2) Tareas \n"
               "--------------------\n");
        fflush(stdin);
        scanf("%i", &eleccion);

    if(eleccion ==1){
        printf("1) Anotar evento \n"
               "2) Tachar evento \n"
               "3) Modificar evento \n"
               "4) Eventos proximos \n"
               "5) Listado de eventos");
        fflush(stdin);
        scanf("%i",&eleccionEventos);
            switch(eleccionEventos){
            case 1:
                cargarEvento(miEvento);
                printf("Evento anotado: \n");
                printf("ID: %i \n", miEvento.id);
                printf("Nombre: %s \n", miEvento.nombre);
                printf("Estado: %c \n", miEvento.estado);
                printf("Fecha: %i / %i / %i \n", miEvento.fecha.day, miEvento.fecha.month, miEvento.fecha.year);

                break;

            case 2:

                registros= cuentaElementosArchivo(archivoEventos);
                printf("Ingrese la ID a eliminar: \n");
                fflush(stdin);
                scanf("%i", &miEvento.id);

                idAEliminar=miEvento.id;

                //eliminarEventoPorID(archivoEventos,idAEliminar,registros);

                break;
            case 3:

                break;

            case 4:

                break;

            case 5:

                break;

            default:
                printf("Error. Elija una opcion valida \n");
            }
        }

    if(eleccion ==2){
              printf("1) Anotar tarea \n"
               "2) Tachar tarea \n"
               "3) Modificar tarea \n"
               "4) tareas proximas \n"
               "5) Listado de tareas");
        fflush(stdin);
        scanf("%i",&eleccionTareas);

            switch(eleccionTareas){
            case 1:
                break;
            default:
                printf("Error. Elija una opcion valida \n");
            }
        }

    if(eleccion !=1 && eleccion !=2){
        printf("Error. Elija una opcion valida. \n");
        }

        }

        printf("Si desea continuar presione s \n");
        fflush(stdin);
        scanf("%c", &control);
    }while(control == 's');

    return 0;
}
