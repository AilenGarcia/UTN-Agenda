#include "agenda.h"
//corregir la funcion validar cita
int validarCita(char nombre[])  //FUNCION QUE COMPRUEBA SI EL NOMBRE DE LA CITA QUE SE QUIERE ANOTAR ESTÁ REPETIDA O NO
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


Cita anotar1Cita()
{
    Cita aux;

    aux.id=rand()*9999;

    printf("\ningrese el nombre de su cita: ");
    fflush(stdin);
    gets(aux.nombre);

    if(validarCita(aux.nombre)==0)  //comprueba si el nombre que ingresó está repetido o no
    {
printf("no hay citas repetidas!\n");
    }

    return aux;
}

int anotarCita(char nombreArchivo[]) //anota la tarea dentro del archivo, comprobando tambien si el nombre de la tarea no está repetida
{
    FILE *archi= fopen(nombreArchivo, "ab");

    Cita nuevaCita;
    if (archi!=NULL)
    {
        Cita unaCita=anotar1Cita();

        fwrite(&nuevaCita,sizeof(Cita),1, archi);
        printf("\nCita anotada con exito!\n");
    }

    fclose(archi);
    mostrarCita(nombreArchivo);
    return 0;
}

void mostrar1Cita(Cita a)
{
    printf ("id de la cita: %i",a.id);
    printf ("\nnombre de la cita: %s", a.nombre);
    printf ("\nfecha de la cita: ");
    printf ("estado de la cita: %i", a.estado);
}

void mostrarCita(char nombreArchivo[])
{
    Cita aux;
    FILE *archi;
    fopen(archi,"rb");
    printf("funcion");
    if (archi!=NULL)
    {
        printf("Dentro del archivo: \n");
//        while( (fread(&a,sizeof(Cita),1,archi)) >0 )
  //      {
  //          mostrar1Cita(a);
  //      }

        fclose(archi);
    }
}

Fecha cargarFecha ()
{
    Fecha miFecha;

    printf("----------------------------------");
    printf("Ingrese el dia: \n");
    fflush(stdin);
    scanf("%i", &miFecha.day);

    printf("Ingrese el mes: \n");
    fflush(stdin);
    scanf("%i", &miFecha.month);

    printf("Ingrese el año: \n");
    fflush(stdin);
    scanf("%i", &miFecha.year);
    printf("----------------------------------");

    return miFecha;
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
            }while(control == 's');
        }

        fclose(archi);
    }
}

int pasajeDeArchivoAArrayCita (Cita array[],int id, char nombreArchivo[]){ ///PASA LOS REGISTROS DE CITAS CARGADAS A UN ARREGLO
    FILE *archi;                                                          ///PARA PODER TACHAR LA CITA BUSCADA
    archi=fopen(nombreArchivo, "rb");
    Cita citas;
    int i=0;
    int resultado;

    if(archi!=NULL){
        while(fread(&citas, sizeof(Cita), 1, archi)>0){

            if(citas.id == id){
            resultado = 0;
            }
            if(resultado !=0){
                array[i] = citas;
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

void tacharCita (char nombreArchivo[], Cita array[], int id){
    int validos;

    id=retornarIDCitaSegunNombre(nombreArchivo);

    validos = pasajeDeArchivoAArrayCita (array, id, nombreArchivo);

    pasajeDeArregloAArchivoCita(array,validos, nombreArchivo);

    printf("\n Evento eliminado! \n");
}

Cita modificarCita (Cita cita1, char archivoUsuarios[]){
    printf("\nModificar el Evento por nombre %s \n", miEvento.nombre);
    char eleccion='s';
    int control;
    Fecha fecha1;
    Usuario usuario1;

    do{
        printf("Que desea modificar? \n"
               "1) Nombre \n"
               "2) Estado \n"
               "3) Fecha \n"
               "4) Persona \n");
        fflush(stdin);
        scanf("%i", &control);

        switch(control){
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
        usuario1=crearUsuario(archivoUsuarios);
        break;
    default:
        printf("Elija una opcion valida \n");
        break;
    }
    printf("Si desea continuar modificando presione s \n");
    fflush(stdin);
    scanf("%c", &eleccion);
    }while(eleccion=='s');
    return cita1;
}


void modificarCitaPorNombre(char nombreArchivo[], char archivoUsuarios[], char nombre[]){
    FILE *archi;
    archi = fopen(archivoEvento, "r+b");
    Cita aux;
    int encontrado = -1;
    int acc =0;

    if(archi!=NULL){
        while(fread(&aux, sizeof(Cita), 1, archi)>0){
            acc++;
            encontrado = strcmp(aux.nombre, nombre);

            if(encontrado==0){
                encontrado=0;
                break;
            }
        }

        if(encontrado==-1){
            printf("La cita no fue encontrada. \n");
        }

        if(encontrado!=0){
            printf("cita: %s",aux.nombre);
            aux = modificarCita(aux, archivoUsuarios);
        }
        fseek(archi, sizeof(Cita)*(acc-1), SEEK_SET);
        fwrite(&aux, sizeof(Cita), 1, archi);
        fclose(archi);
    }
}

void modificarCitaPorNombre(char nombreArchivo[], char archivoUsuarios[], char nombre[]){
    FILE *archi;
    archi = fopen(archivoEvento, "r+b");
    Cita aux;
    int encontrado = -1;
    int acc =0;

    if(archi!=NULL){
        while(fread(&aux, sizeof(Cita), 1, archi)>0){
            acc++;
            encontrado = strcmp(aux.nombre, nombre);

            if(encontrado==0){
                encontrado=0;
                break;
            }
        }

        if(encontrado==-1){
            printf("La cita no fue encontrada. \n");
        }

        if(encontrado!=0){
            printf("cita: %s",aux.nombre);
            aux = modificarCita(aux, archivoUsuarios);
        }
        fseek(archi, sizeof(Cita)*(acc-1), SEEK_SET);
        fwrite(&aux, sizeof(Cita), 1, archi);
        fclose(archi);
    }
}
void mostrarFechaCita (Cita aux)
{
    printf(" Dia: %i \n", aux.fecha.day);
    printf(" Mes: %i \n", aux.fecha.month);
}

void mostrarCita(Cita aux)
{
    puts("\n----------------------------------\n");
    printf("Nombre: %s \n", aux.nombre);
    printf("Estado: %s \n", aux.estado);
    printf("Usuario: \n");
    printf("Fecha: \n");
    mostrarFechaCita(aux);

}

void mostrarCitas (char nombreArchivo[]){
    FILE *archi;
    Cita aux;
    archi=fopen(nombreArchivo, "rb");

    if(archi!=NULL){
        while(fread(&aux, sizeof(Cita),1, archi)>0){
            mostrarCita(aux);
        }
        fclose(archi);
    }
}


