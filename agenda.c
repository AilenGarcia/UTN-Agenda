#include "agenda.h"

int validarCita(char *id, char Citas[]){ //FUNCION QUE COMPRUEBA SI EL NOMBRE DE LA TAREA QUE SE QUIERE ANOTAR ESTÁ REPETIDA O NO
    Cita citaLeida;


    while (fread(&citaLeida, sizeof(Cita),1,archi)){

        if (citaLeida.id==id){

            return 1; //ya hay una cita con el mismo nombre
           }
    }

 return 0; //ese nombre no existe
}

int anotarCita(char nombreArchivo[]) //anota la tarea dentro del archivo, comprobando tambien si el nombre de la tarea no está repetida
{
    FILE *archi= fopen(nombreArchivo, "ab");

    Cita nuevaCita;
    if (archi==NULL)
    {
        printf ("\nno se pudo abrir el archivo.");
        fclose (archi);
        return -1;
    }



    printf("\ningrese el numero identificatorio de su nueva cita: ");
    fflush(stdin);
    scanf ("%i", &nuevaCita.id);
///la funcion esta en el .h, repasar librerias para implementarlas bie, porque las funciones van en un .c aparte
///por eso no anda la funcion de validar
///igualemente coordinen los nombres de las structuras
///cambien el nombre de las variables que pusieron aca
///
    if(validarCita(nuevaCita.id, archi)==1)  //comprueba si el nombre que ingresó está repetido o no
    {
        printf("\nla cita ya existe.");
        fclose(archi);
    }

    printf("\ningrese el nombre de su cita: ");
    fflush(stdin);
    scanf("%s", &nuevaCita.nombre);

    printf ("\ningrese la fecha a recordar de esta cita(formato dd/mm): ");
    fflush (stdin);
    scanf ("%i", &nuevaCita.fecha);



    fwrite(&nuevaCita,sizeof(Cita),1, archi);
    printf("\nCita anotada con exito!\n");
fclose(archi);
    return 0;
}

int tacharCita(char nombreArchivo)
{
 FILE *archi= fopen(nombreArchivo, "ab");

 Cita tachar1Cita;

if (archi==NULL)
    {
        printf ("\nno se pudo abrir el archivo.");
        fclose (archi);
        return -1;
    }

    printf("ingrese el identificador de la cita a tachar: ");
    fflush(stdin);
    scanf("%i", &tachar1Cita.id);

}
