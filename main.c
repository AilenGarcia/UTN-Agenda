#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
} Cita;

int main()
{
    char nombreArchivo[50]={"franco.bin"};
    ///fijarse para que se usan y cuales son los validos en la funcion del case 3
    int validos = 0;
    char control = 's';
    int eleccion, eleccionUsuario, eleccionEventos, eleccionTareas;

    do{
        printf("Que desea hacer? \n"
               "1) Usuarios \n "
               "2) Eventos \n "
               "3) Tareas \n");
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
              printf("1) Anotar tarea \n"
               "2) Tachar tarea \n"
               "3) Modificar tarea \n"
               "4) tareas proximas \n"
               "5) Listado de tareas");
        fflush(stdin);
        scanf("%i",&eleccionTareas);

        ///nico (su ayudante favorito) dice que switch dento de switch no plssss :)
            switch(eleccionTareas){
            case 1:
                anotarTarea(nombreArchivo, validos);
                break;
            default:
                printf("Error. Elija una opcion valida \n");
            }

        break;
    default:
        printf("Error. Elija una opcion valida. \n");
        }

        printf("Si desea continuar presione s \n");
        fflush(stdin);
        scanf("%c", &control);
    }while(control == 's');

    return 0;
}

int anotarTarea(char nombreArchivo[], int validos) //anota la tarea dentro del archivo, comprobando tambien si el nombre de la tarea no está repetida
{
    FILE *archi= fopen(archi, "ab");
    ///en
    Cita nuevaTarea;
    if (archi==NULL)
    {
        printf ("no se pudo abrir el archivo.");
        fclose (archi);
        return -1;
    }



   printf("ingrese el numero identificatorio de su nueva tarea: ");
fflush(stdin);
   scanf ("%i", &nuevaTarea.id);
///la funcion esta en el .h, repasar librerias para implementarlas bie, porque las funciones van en un .c aparte
///por eso no anda la funcion de validar
///igualemente coordinen los nombres de las structuras
///cambien el nombre de las variables que pusieron aca
///
   if(validarTarea(nuevaTarea.id, archi)==1){ //comprueba si el nombre que ingresó está repetido o no
    printf("la tarea ya existe.");
    fclose(archi);
   }

   printf("ingrese el nombre de su tarea: ");
fgets(nuevaTarea.nombre,50, stdin);

printf ("ingrese la fecha a recordar de esta tarea(formato dd/mm): ");
fflush (stdin);
scanf ("%i", nuevaTarea.fecha);



   fwrite(&nuevaTarea,sizeof(Cita),1, archi);
    printf("tarea anotada con exito!");

    return 0;
}

