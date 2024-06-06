#include "agenda.h"
//corregir la funcion validar cita
int validarCita(int id, FILE* archi)  //FUNCION QUE COMPRUEBA SI EL NOMBRE DE LA TAREA QUE SE QUIERE ANOTAR ESTÁ REPETIDA O NO
{

    Cita citaLeida;

    while (fread(&citaLeida, sizeof(Cita),1,archi))
    {

        if (citaLeida.id==id)
        {

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

        return -1;
    }
    else
    {

        printf("\ningrese el numero identificatorio de su nueva cita: ");
        fflush(stdin);
        scanf ("%i", &nuevaCita.id);

        if(validarCita(nuevaCita.id, archi)==1)  //comprueba si el nombre que ingresó está repetido o no
        {
            printf("\nla cita ya existe.");
            fclose(archi);
        }

        printf("\ningrese el nombre de su cita: ");
        fflush(stdin);
        scanf("%s", &nuevaCita.nombre);

        //funcion que te cargue una fecah
        //Fecha nuevaF= cargarNuevaFecha();
       // strcpy(nuevaCita.fecha, nuevaFecha); //lo que me devuelve la funcion

//crear funcion de id random
//

        fwrite(&nuevaCita,sizeof(Cita),1, archi);
        printf("\nCita anotada con exito!\n");
    }



    fclose(archi);
    mostrarCita(nombreArchivo);
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


//if (fread(tachar1Cita,sizeof(Cita), 1, *archi)==tachar1Cita.id)
    {

    }

}

//funcion retorne el arreglo citas
// wb

void mostrar1Cita(Cita a)
{
    printf ("id de la cita: %i",a.id);
    printf ("\nnombre de la cita: %s", a.nombre);
    printf ("\nfecha de la cita: %i", a.fecha);
    printf ("estado de la cita: %i", a.estado);
}

void mostrarCita(char nombreArchivo[])
{
    Cita a;
    FILE *archi;
    fopen(archi,"rb");
    printf("funcion");
    if (archi==NULL)
    {
        printf ("el archivo no existe");
    }
    else
    {
        printf("Dentro del archivo");
        while( (fread(&a,sizeof(Cita),1,archi)) >0 )
        {
            mostrar1Cita(a);
        }

        fclose(archi);
    }
}

Fecha cargarNuevaFecha(){
    //Fecha fecha;
//dia, entre 1-30
//mes 1-12
//fecha=24
//return fecha

}
