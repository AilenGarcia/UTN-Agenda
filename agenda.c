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

int validarNombreCita(char nombre[], FILE *archi, char nombreArchivo[])
{
    archi=fopen(nombreArchivo, "rb");
    if (archi!=NULL){
    int validar=0;
    Cita cita1;

    while (fread(&cita1, sizeof(Cita), 1, archi )>0)
    {

        int validar=strcmp(nombre,cita1.nombre);

        if (validar==0)
        {
            printf ("ya hay una cita con el mismo nombre. Ingrese otro nombre.\n");
            return 0;
        }

    }

    return -1;
}
}

int validarDia(int day)
{
    if(day>0 && day<32)
    {
        return 0;
    }
    else
    {
        printf("\n -------------- Dia mal ingresado -------------- \n");
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
        printf("\n -------------- Mes mal ingresado -------------- \n");
        return -1;
    }
}

Cita anotar1Cita(FILE *archi, char nombreArchivo[])
{
    Cita aux;
    aux.id=rand()*9999;
    aux.estado;
    int validacionNombre;
    int validacionCita;

    do
    {
        printf("\n Ingrese el nombre de su cita: ");
        fflush(stdin);
        gets(aux.nombre);
        validacionNombre=validarNombreCita(aux.nombre, archi, nombreArchivo);
    }
    while(rellenarNombreCita(aux.nombre)==-1 || validacionNombre==0);

    aux.estado = 'n';

    aux.fecha=cargarFecha();
    return aux;
}

int anotarCita(char nombreArchivo[]) //anota la tarea dentro del archivo, comprobando tambien si el nombre de la tarea no está repetida
{
    FILE *archi;

    Cita nuevaCita;
    if (archi!=NULL)
    {
        Cita nuevaCita=anotar1Cita(archi, nombreArchivo);

        archi= fopen(nombreArchivo, "ab");
        fwrite(&nuevaCita,sizeof(Cita),1, archi);
        printf("\nCita anotada con exito!\n");
    }

    fclose(archi);

    return 0;
}

Fecha cargarFecha ()
{
    Fecha miFecha;

    printf("\n ---------------------------- \n");
    do
    {
        printf("Ingrese el dia: \n");
        fflush(stdin);
        scanf("%i",&miFecha.day);
    }
    while(validarDia(miFecha.day)!=0);

    do
    {
        printf("Ingrese el mes: \n");
        fflush(stdin);
        scanf("%i", &miFecha.month);
    }
    while(validarMes(miFecha.month) !=0);

    printf("Ingrese el año: \n");
    fflush(stdin);
    scanf("%i", &miFecha.year);
    printf("---------------------------------- \n");

    return miFecha;
}


int retornarIDSegunNombre(char nombreArchivo[], char nombre[])
{
    FILE *archi;
    archi=fopen(nombreArchivo,"rb");
    Cita cita1;
    int nombreEncontrado=0;

    if(archi != NULL)
    {
        while(fread(&cita1,sizeof(Cita),1,archi) > 0 )
        {
            nombreEncontrado=strcmp(cita1.nombre, nombre);

                if(nombreEncontrado==0)
                {
                    fclose(archi);
                    return cita1.id;
                }
            }
        printf("El nombre ingresado no se encontro. \n");
        fclose(archi);
    }
}

int pasajeDeArchivoAArrayCitas(Cita array[],int id, char nombreArchivo[]){
    FILE *archi;
    archi=fopen(nombreArchivo, "rb");
    Cita cita1;
    int i=0;

    if(archi!=NULL){
        while(fread(&cita1, sizeof(Cita), 1, archi)>0){
            if(cita1.id !=id){
                array[i] = cita1;
                i++;
            }
        }
    }
    fclose(archi);

    return i;
}

void pasajeDeArregloAArchivoCita (Cita array[], int validos, char nombreArchivo[]){
    FILE *archi;
    archi=fopen(nombreArchivo, "wb");
    int i=0;

    if(archi!=NULL){
        while(i< validos){
            fwrite(&array[i], sizeof(Cita),1,archi);
            i++;
        }
    }
    fclose(archi);
}

void eliminarCita(char nombreArchivo[], Cita array[], int id){
    int validos;
    validos = pasajeDeArchivoAArrayCitas(array, id, nombreArchivo);
    pasajeDeArregloAArchivoCita(array,validos, nombreArchivo);

    printf("\n Cita eliminada \n");
}

Cita modificarCita(Cita cita1, char archivoUsuarios[])
{

    printf("\nModificar la cita por nombre %s \n", cita1.nombre);
    char eleccion='s';
    int control;
    Fecha fecha1;

    do
    {
        printf("Que desea modificar? \n"
               "1) Nombre \n"
               "2) Estado \n"
               "3) Fecha \n");
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
            printf ("recuerde: 's' para hechas, 'n' para pendientes\n");
            printf("Ingrese el Estado: ");
            fflush(stdin);
            scanf("%c",&cita1.estado);
            break;
        case 3:
            printf("Ingrese la fecha: ");
            fecha1=cargarFecha();
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

void modificarCitaPorNombre(char nombreArchivo[], char archivoUsuarios[], char nombre[]){
    FILE *archi;
    archi = fopen(nombreArchivo, "r+b");
    Cita cita1;
    int encontrado = -1;
    int acc =0;

    if(archi!=NULL){
        while(fread(&cita1, sizeof(Cita), 1, archi)>0){
            acc++;
            encontrado = strcmp(cita1.nombre, nombre);

            if(encontrado==0){
                encontrado=0;
                break;
            }
        }

        if(encontrado==-1){
            printf("La cita no fue encontrada \n");
        }

        if(encontrado==0){
            printf("Cita: %s",cita1.nombre);
            cita1 = modificarCita(cita1, archivoUsuarios);
        }
        fseek(archi, sizeof(Cita)*(acc-1), SEEK_SET);
        fwrite(&cita1, sizeof(Cita), 1, archi);
        fclose(archi);
    }
}

Cita buscarCitaSegunNombre(char nombreArchivo[])
{
    FILE*archi;
    archi=fopen(nombreArchivo,"rb");
    char nombre[50];
    Cita cita1;
    int nombreEncontrado=0;

    if(archi != NULL)
    {
        printf("Ingrese el Nombre a buscar:");
        fflush(stdin);
        scanf("%s",&nombre);

        while(fread(&cita1,sizeof(Cita),1,archi) > 0 )
        {
            nombreEncontrado=strcmpi(cita1.nombre, nombre);

            if(nombreEncontrado==0)
            {
                printf("La cita %s fue encontrado \n", cita1.nombre);
                fflush(stdin);
                return cita1;
            }
            else
            {
                printf("El nombre ingresado no es valido. \n");
                fflush(stdin);
            }
        }

        fclose(archi);
    }
}
void citasProximas (char nombreArchivo[], Cita cita1)
{
    FILE * archi;
    archi=fopen(nombreArchivo, "rb");
    int i = 0;

    if(archi != NULL)
    {
        while (fread(&cita1, sizeof(Cita),1,archi) > 0)
        {
            if(cita1.estado== 'n')
            {
                mostrarCitas(nombreArchivo);
            }
        }
        fclose(archi);
    }
}

void mostrarFechaCita (Cita aux)
{
    printf(" %i / %i / %i \n", aux.fecha.day, aux.fecha.month, aux.fecha.year);
}

void mostrar1Cita(Cita cita1)
{
    puts("\n----------------------------------\n");
    printf("Nombre: %s \n", cita1.nombre);
    printf("Estado: %c \n", cita1.estado);
    printf("Fecha: ");
    mostrarFechaCita(cita1);
    puts("\n----------------------------------\n");
}

void mostrarCitas (char nombreArchivo[]){
    FILE *archi;
    Cita cita1;
    archi=fopen(nombreArchivo, "rb");

    if(archi!=NULL){
        while(fread(&cita1, sizeof(Cita),1, archi)>0){
            mostrar1Cita(cita1);
        }
        fclose(archi);
    }
}
