#include "agenda.h"

int validarTarea(char *idTarea, char tareas[]){ //FUNCION QUE COMPRUEBA SI EL NOMBRE DE LA TAREA QUE SE QUIERE ANOTAR ESTÁ REPETIDA O NO
    FILE *archi;
    archi = fopen(tareas, "ab");
    Tarea tareaLeida;
//rewind (archi);

    while (fread(&tareaLeida, sizeof(Tarea),1,archi)){

        if (tareaLeida.id==idTarea){

            return 1; //ya hay una tarea con el mismo nombre
           }
    }

 return 0; //ese nombre no existe
}

int anotarTarea(char nombreArchivo[], int validos) //anota la tarea dentro del archivo, comprobando tambien si el nombre de la tarea no está repetida
{
    FILE *archi= fopen(nombreArchivo, "ab");
    ///en
    Tarea nuevaTarea;
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
    if(validarTarea(nuevaTarea.id, archi)==1)  //comprueba si el nombre que ingresó está repetido o no
    {
        printf("la tarea ya existe.");
        fclose(archi);
    }

    printf("ingrese el nombre de su tarea: ");
    fgets(nuevaTarea.nombre,50, stdin);

    printf ("ingrese la fecha a recordar de esta tarea(formato dd/mm): ");
    fflush (stdin);
    scanf ("%i", nuevaTarea.fecha);



    fwrite(&nuevaTarea,sizeof(Tarea),1, archi);
    printf("tarea anotada con exito!");

    return 0;
}

