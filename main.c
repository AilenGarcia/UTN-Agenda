#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agenda.h"

int main()
{
    char control = 's';
    char controlMenu = 's';
    int menu, eleccion, eleccionUsuario, eleccionEventos, eleccionCitas, mes, cantidad;
    int accesoPorRol = 5;
    char archivoUsuarios[20];
    char dni[DIMDNI];
    Usuario usuario;
    strcpy(archivoUsuarios, "usuarios.bin");
    Usuario arregloUsuarios[100];

    char nombreArchivo[50]={"cita.bin"};
    char controlCitas='s';
    int id;
    Cita cita1;
    Cita arrayCita[50];
    Pila pila1;
    inicpila(&pila1);

    Evento miEvento;
    char archivoEventos[20];
    strcpy(archivoEventos,"eventos.bin");
    int registros = 0;
    int idAEliminar=0;
    Evento arrayEvento[100];
    char nombre[50];
    char controlEvento = 's';
    Evento eventoM[50][50];
    char matriz[12][12]={"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};
    int arrayMes[100];
    int mesPosicion=0;



    cargarDatos(archivoUsuarios);

    printf("\x1b[31m");
    printf("     BIENVENIDOS! \n");
    printf("\x1B[37m");

    do{
        printf("1) Iniciar sesion \n"
               "2) Registrase \n"
               "3) Salir \n");
        fflush(stdin);
        scanf("%i", &menu);

        system("cls");

        switch(menu){
    case 1:
        system("cls");
        accesoPorRol=iniciarSesion(archivoUsuarios);
        if(accesoPorRol != 0 && accesoPorRol != 1){
            printf("\nPor favor ingrese los datos correctamente correctamente \n\n");
        }
        break;
    case 2:
        system("cls");
        cargarUsuario(archivoUsuarios);
        accesoPorRol=0;
        break;
    case 3:
        printf("\n Saliendo del sistema.....\n");
        exit(0);
        break;
    default:
        printf("Error. Elija una opcion valida. \n");
        }
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
               "2) Citas \n"
               "3) Salir \n"
               "--------------------\n");
        fflush(stdin);
        scanf("%i", &eleccion);

        system("cls");

        if(eleccion ==1){
                printf("\n --------------------\n"
                        "1) Anotar evento \n"
                        "2) Tachar evento \n"
                        "3) Modificar evento \n"
                        "4) Eventos proximos \n"
                        "5) Listado de eventos \n"
                        "6) Mostrar Calendario \n"
                        "7) Buscar evento por nombre \n"
                        "8) Ordenar por mes \n"
                        " --------------------\n");
        fflush(stdin);
        scanf("%i",&eleccionEventos);
            switch(eleccionEventos){
            case 1:
                    while (controlEvento=='s')
                    {
                        guardarEventoEnArchivo(archivoEventos, archivoUsuarios);
                        printf("Quiere cargar otro Evento? \n"
                               "Ingrese s para SI o n para NO \n");
                        fflush(stdin);
                        scanf("%c", &controlEvento);
                    }
                    controlEvento='s';
                break;
            case 2:
                    printf("Ingrese el Nombre a buscar: \n");
                    fflush(stdin);
                    gets(nombre);

                    idAEliminar=retornarIDSegunNombre(archivoEventos, nombre);

                    if(idAEliminar!=0){
                        eliminarEvento(archivoEventos, arrayEvento,idAEliminar);
                    }
                break;
            case 3:
                    printf("\nIngrese el Nombre: ");
                    fflush(stdin);
                    scanf("%s", &nombre);

                    modificarEventoPorNombre(archivoEventos, archivoUsuarios, nombre);
                break;
            case 4:
                    eventosProximos(archivoEventos,miEvento);
                break;
            case 5:
                    mostrarEventos(archivoEventos);
                break;
            case 6:
                    mostrarMatriz(matriz, arrayMes, archivoEventos);
                break;
            case 7:
                    miEvento = buscarEventoSegunNombre(archivoEventos);
                    if(strcmp(miEvento.nombre, "ERROR.ERROR.")!=0){
                        mostrarEvento(miEvento);
                    }
                break;

            case 8:
                    registros = pasarArray(arrayEvento,archivoEventos);
                    ordenacion_seleccion(arrayEvento, registros);
                    mostrarArrayMes(arrayEvento,registros);

                break;

            default:
                printf("Error. Elija una opcion valida \n");
            }
        }

        if(eleccion ==2){
              printf("\n --------------------\n"
                    "1) Anotar cita \n"
                    "2) Tachar cita \n"
                    "3) Modificar cita \n"
                    "4) Citas proximas \n"
                    "5) Listado de citas\n"
                    "6) Total de citas en el mes\n"
                    "7) Buscar cita por nombre \n"
                    "8) Ordenar citas alfabeticamente\n"
                    "--------------------\n");
        fflush(stdin);
        scanf("%i",&eleccionCitas);

            switch(eleccionCitas){
            case 1:
                while(controlCitas== 's')
                {
                anotarCita(nombreArchivo);

                printf("Quiere agregar otra cita? \n"
                "Ingrese s para SI o n para NO \n");
                fflush(stdin);
                scanf("%c", &controlCitas);
                }
                controlCitas='s';
                break;
            case 2:
                    printf("Ingrese el Nombre a buscar: \n");
                    fflush(stdin);
                    gets(nombre);

                    idAEliminar=retornarIDSegunNombreCita(nombreArchivo, nombre);

                    if(idAEliminar!=0){
                        eliminarCita(nombreArchivo, arrayCita,idAEliminar);
                    }
                break;
            case 3:
                printf("\nIngrese el Nombre: ");
                fflush(stdin);
                scanf("%s", &nombre);
                system("cls");
                modificarCitaPorNombre(nombreArchivo, archivoUsuarios, nombre);
                break;
            case 4:
                citasProximas(nombreArchivo,cita1);
                break;
            case 5:
                mostrarCitas(nombreArchivo);
                break;
            case 6:
                printf ("ingrese el numero del mes a averiguar: ");
                fflush(stdin);
                scanf("%i", &mes);

                cantidad = cantidadCitasEnMes(arrayCita,pila1,mes, nombreArchivo);
                printf ("Total de citas en el mes %i: %i \n", mes, cantidad);
                break;
            case 7:
                cita1 = buscarCitaSegunNombre(nombreArchivo);
                if(strcmp(cita1.nombre, "ERROR.ERROR.")!=0){
                    mostrar1Cita(cita1);
                }
                break;
            case 8:
                mostrarCitasOrdenadas(nombreArchivo, arrayCita);
                break;
            default:
                printf("Error. Elija una opcion valida \n");
            }
        }

        if(eleccion ==3){
            printf("\n Saliendo del sistema.....\n");
            exit(0);
        }

        if(eleccion !=1 && eleccion !=2 && eleccion !=3){
        printf("Error. Elija una opcion valida. \n");
        }

        }

        printf("Si desea continuar presione s \n");
        fflush(stdin);
        scanf("%c", &control);
    }while(control == 's');

    return 0;
}
