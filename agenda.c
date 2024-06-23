#include "agenda.h"
//corregir la funcion validar cita
int rellenarNombreCita(char nombre[])  //FUNCION QUE COMPRUEBA SI EL NOMBRE DE LA CITA QUE SE QUIERE ANOTAR ESTÁ REPETIDA O NO
{
    if(strlen(nombre) > 1)
    {
        return 0;
    }
    else
    {
        printf("\n No ingreso ningun nombre, por favor intentelo otra vez: ");
        return -1;
    }
}

int validarNombreCita(char nombre[], FILE *archi)
{
    int validar=0;
    Cita aux;
 while (fread(&aux, sizeof(Cita), 1, archi )>0)
 {
    validar=strcmp(nombre,aux.nombre);
}

if (validar==0)
{
    printf ("ya hay una cita con el mismo nombre. Ingrese otro nombre.");
    return 0;
}
else if (validar<=0)
    {
        return -1;
    }

    else return 1;
}




int validarDia(int day)
{
    if(day>0 && day<32)
    {
        return 0;
    }
    else
    {
        printf ("ingrese un numero valido.\n");
        return -1;
    }
}

int validarMes(int month)
{
    if(month>0 && month<13)
    {
        return 0;
    }
    else
    {
        printf ("ingrese un numero valido.\n");
        return -1;
    }
}
Cita anotar1Cita()
{
    Cita aux;
FILE *archi;
    aux.id=rand()*9999;
    aux.estado=0;
    do{
        do{
            printf("\ningrese el nombre de su cita: ");
            fflush(stdin);
            gets(aux.nombre);

        }while(rellenarNombreCita(aux.nombre)>0);

    }while (validarNombreCita(aux.nombre, archi)!=0);

    printf ("\nsu cita está terminada? 's' para si, 'n' para no: ");
    fflush (stdin);
    scanf ("%c", &aux.estado);

    aux.fecha=cargarFecha();
    return aux;
}


int anotarCita(char nombreArchivo[]) //anota la tarea dentro del archivo, comprobando tambien si el nombre de la tarea no está repetida
{
    FILE *archi= fopen(nombreArchivo, "ab");

    Cita nuevaCita;
    if (archi!=NULL)
    {
        Cita nuevaCita=anotar1Cita();

        fwrite(&nuevaCita,sizeof(Cita),1, archi);
        printf("\nCita anotada con exito!\n");
    }

    fclose(archi);

    return 0;
}

Fecha cargarFecha ()
{
    Fecha aux;


    printf("\n----------------------------------");

    do
    {
        printf("\nIngrese el dia: \n");
        fflush(stdin);
        scanf("%i", &aux.day);
    }
    while(validarDia(aux.day)!=0);

    do
    {
        printf("\nIngrese el numero de mes: \n");
        fflush(stdin);
        scanf("%i", &aux.month);
    }
    while(validarMes(aux.month)!=0);

    printf("\nIngrese el año: \n");
    fflush(stdin);
    scanf("%i", &aux.year);
    printf("----------------------------------");

    return aux;
}

int retornarIDCitaSegunNombre(char nombreArchivo[]) ///FUNCION QUE RETORNA EL ID DE LA CITA SEGUN EL NOMBRE
{
    FILE*archi;
    archi=fopen(nombreArchivo,"rb");
    char nombre[50];
    Cita cita1;
    int nombreEncontrado=0;
    char control='s';

    if(archi != NULL)
    {
        printf("Ingrese el Nombre a buscar: \n");
        fflush(stdin);
        scanf("%s",&nombre);

        while(fread(&cita1,sizeof(Cita),1,archi) > 0 )
        {
            nombreEncontrado=strcmpi(cita1.nombre, nombre);

            do
            {
                if(nombreEncontrado==0)
                {
                    return cita1.id;
                }
                else
                {
                    printf("El nombre ingresado no se encontro. \n"
                           "Quiere intentar con otro nombre? \n"
                           "Ingrese s para Seguir o cualquier letra para Salir \n");
                }
            }
            while(control == 's');
        }

        fclose(archi);
    }
}

int pasajeDeArchivoAArrayCita (Cita array[],int id, char nombreArchivo[])  ///PASA LOS REGISTROS DE CITAS CARGADAS A UN ARREGLO
{
    FILE *archi;                                                          ///PARA PODER TACHAR LA CITA BUSCADA
    archi=fopen(nombreArchivo, "rb");
    Cita citas;
    int i=0;
    int resultado;

    if(archi!=NULL)
    {
        while(fread(&citas, sizeof(Cita), 1, archi)>0)
        {

            if(citas.id == id)
            {
                resultado = 0;
            }
            if(resultado !=0)
            {
                array[i] = citas;
                i++;
            }
        }
    }
    fclose(archi);
    return i;
}

void pasajeDeArregloAArchivoCita (Cita array[], int validos, char nombreArchivo[])
{
    FILE *archi;
    archi=fopen(nombreArchivo, "wb");
    int i=0;

    if(archi!=NULL)
    {
        while(i< validos)
        {
            fwrite(&array[i], sizeof(Cita),1,archi);
            i++;
        }
    }
    fclose(archi);
}

void tacharCita (char nombreArchivo[], Cita array[], int id)
{
    int validos;

    id=retornarIDCitaSegunNombre(nombreArchivo);

    validos = pasajeDeArchivoAArrayCita (array, id, nombreArchivo);

    pasajeDeArregloAArchivoCita(array,validos, nombreArchivo);

    printf("\n Evento eliminado! \n");
}

Cita modificarCita (Cita cita1, char archivoUsuarios[])
{
    printf("\nModificar el Evento por nombre %s \n", cita1.nombre);
    char eleccion='s';
    int control;
    Fecha fecha1;
    Usuario usuario1;

    do
    {
        printf("Que desea modificar? \n"
               "1) Nombre \n"
               "2) Estado \n"
               "3) Fecha \n"
               "4) Persona \n");
        fflush(stdin);
        scanf("%i", &control);

        switch(control)
        {
        case 1:
            printf("Ingrese el nombre: ");
            fflush(stdin);
            gets(cita1.nombre);
            break;
        case 2:
            printf("Ingrese el Estado: ");
            fflush(stdin);
            gets(cita1.estado);
            break;
        case 3:
            printf("Ingrese la fecha: ");
            fecha1=cargarFecha();
            break;
        case 4:
            printf("Ingrese el Usuario: ");
//        usuario1=crearUsuario(nombreArchivo);
            break;
        default:
            printf("Elija una opcion valida \n");
            break;
        }
        printf("Si desea continuar modificando presione s \n");
        fflush(stdin);
        scanf("%c", &eleccion);
    }
    while(eleccion=='s');
    return cita1;
}

void modificarCitaPorNombre(char nombreArchivo[], char archivoUsuarios[], char nombre[])
{
    FILE *archi;
    archi = fopen(nombreArchivo, "r+b");
    Cita aux;
    int encontrado = -1;
    int acc =0;

    if(archi!=NULL)
    {
        while(fread(&aux, sizeof(Cita), 1, archi)>0)
        {
            acc++;
            encontrado = strcmp(aux.nombre, nombre);

            if(encontrado==0)
            {
                encontrado=0;
                break;
            }
        }

        if(encontrado==-1)
        {
            printf("La cita no fue encontrada. \n");
        }

        if(encontrado!=0)
        {
            printf("cita: %s",aux.nombre);
            aux = modificarCita(aux, archivoUsuarios);
        }

        fseek(archi, sizeof(Cita)*(acc-1), SEEK_SET);
        fwrite(&aux, sizeof(Cita), 1, archi);


    }
    fclose(archi);
}
void mostrarFechaCita (Cita aux)
{
    printf(" Dia: %i \n", aux.fecha.day);
    printf(" Mes: %i \n", aux.fecha.month);
}

void mostrarCita(Cita aux, Usuario persona)
{
    puts("\n----------------------------------\n");
    printf("Nombre: %s \n", aux.nombre);
    printf("Estado: %c \n", aux.estado);
    printf("Usuario: %s\n", persona.nombre);
    mostrarFechaCita(aux);

}

void mostrarCitas (char nombreArchivo[])
{
    FILE *archi;
    Cita cita2;
    archi=fopen(nombreArchivo, "rb");
    Usuario persona;

    if(archi!=NULL)
    {
        while(fread(&cita2, sizeof(Cita),1, archi)>0)
        {
            mostrarCita(cita2, persona);
        }
    }
    fclose(archi);
}

Cita buscarCitaSegunNombre(char nombreArchivo[])
{
    FILE*archi;
    char nombre[50];
    Cita aux;
    int nombreEncontrado=0;

    if(archi != NULL)
    {
        printf("Ingrese el Nombre a buscar:");
        fflush(stdin);
        scanf("%s",&nombre);

        while(fread(&aux,sizeof(Cita),1,archi) > 0 )
        {
            nombreEncontrado=strcmpi(aux.nombre, nombre);

            if(nombreEncontrado==0)
            {
                printf("La cita %s fue encontrado \n", aux.nombre);
                fflush(stdin);
                return aux;
            }
            else
            {
                printf("El nombre ingresado no es valido. \n");
                fflush(stdin);
            }
        }


    }
}
void mostrarCitasProximas(char nombreArchivo[])
{
    FILE *archi;
    Cita cita2;
    archi=fopen(nombreArchivo, "rb");
    Cita array[50];
    int id;
    Usuario persona;

    if (archi!=NULL)
    {
        while (fread(&cita2, sizeof(Cita),1,archi)>0)
        {
            do
            {
                mostrarCita(cita2,persona);

            }
            while (cita2.estado=='n');

        }
        fclose(archi);
    }
}
