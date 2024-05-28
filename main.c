#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIMNOMBRE 50
#define DIMDNI 11

typedef struct{
    char dni[DIMDNI];
    char nombre[DIMNOMBRE];
    int  edad;
    char genero;
} Usuario;
/*
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
*/

int validarNombre(char nombre[]);
void cargarNombre(char nombre[]);
int validarDni(char dni[]);
void cargarDni(char dni[]);
int validarGenero(char genero[]);
char cargarGenero();
int validarEdad(int edad);
int cargarEdad();
Usuario crearUsuario();
void cargarUsuario(char usuarios[]);
void mostrarUsuarios(char usuarios[]);
void mostrarUsuario(Usuario usuario);
Usuario buscarPorDni(char usuarios[], char dni[]);
Usuario modificarUsuario(Usuario usuario);
void modificarUsuarioPorDNI(char usuarios[], char dni[]);

int main()
{
    char control = 's';
    int eleccion, eleccionUsuario, eleccionEventos, eleccionTareas;
    char archivoUsuarios[20];
    char dni[DIMDNI];
    Usuario usuario;
    strcpy(archivoUsuarios, "usuarios.bin");

    do{
        printf("\n --------------------\n"
               "Que desea hacer? \n "
               "1) Usuarios \n "
               "2) Eventos \n "
               "3) Tareas \n"
               "--------------------\n");
        fflush(stdin);
        scanf("%i", &eleccion);

        switch(eleccion){
    case 1:

        printf("\n --------------------\n"
               "1) Crear usuario \n"
               "2) Eliminar usuario \n"
               "3) Modificar usuario \n"
               "4) Consultar por un usuario \n"
               "5) Listado de usuarios \n"
               "--------------------\n");
        fflush(stdin);
        scanf("%i", &eleccionUsuario);

        switch(eleccionUsuario){

    case 1:
        cargarUsuario(archivoUsuarios);
        break;
    case 2:
        break;
    case 3:
        printf("\nIngrese el dni: ");
        fflush(stdin);
        scanf("%s", &dni);
        modificarUsuarioPorDNI(archivoUsuarios, dni);
        break;
    case 4:
        printf("\nIngrese el dni: ");
        fflush(stdin);
        scanf("%s", &dni);
        usuario = buscarPorDni(archivoUsuarios, dni);
        break;
    case 5:
        mostrarUsuarios(archivoUsuarios);
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

            switch(eleccionTareas){
            case 1:
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

// FUNCION QUE RECIBE POR PARAMETRO UN ARREGLO DE STRING Y COMPARA LA CANTIDAD DE CARACTERES QUE CONTIENE, SI ES MAYOR A 1
// RETORNA 0, SINO -1
int validarNombre(char nombre[]){
    if(strlen(nombre) > 1){
        return 0;
    }else{
        printf("\n No ingreso ningun nombre, por favor intentelo otra vez: ");
        return -1;
    }
}

//FUNCION PARA CARGAR NOMBRE, RECIBE POR PARAMETRO UN ARREGLO. EN UN CICLO SE INGRESA EL NOMBRE Y SE GUARDA EN UNA VARIABLE Y SE REPITE
//HASTA QUE SE CUMPLA LA VALIDACION. AL FINAL IGUALA LA VARIABLE A NOMBRE
void cargarNombre(char nombre[]){
    char aux[DIMNOMBRE];
    do{
        printf("\nIngrese nombre: ");
        fflush(stdin);
        gets(aux);
    }while(validarNombre(aux)!=0);
    strcpy(nombre, aux);
}

// FUNCION QUE RECIBE POR PARAMETRO UN ARREGLO DE STRING Y COMPARA LA CANTIDAD DE CARACTERES QUE CONTIENE, SI ES IGUAL A 10
// RETORNA 0, SINO -1
int validarDni(char dni[]){
    if(strlen(dni) == 10){
        return 0;
    }else{
        printf("\n DNI mal ingresado, por favor intentelo otra vez: ");
        return -1;
    }
}

//FUNCION PARA CARGAR DNI, RECIBE POR PARAMETRO UN ARREGLO. EN UN CICLO SE INGRESA EL DNI Y SE GUARDA EN UNA VARIABLE Y SE REPITE
//HASTA QUE SE CUMPLA LA VALIDACION. AL FINAL IGUALA LA VARIABLE A DNI
void cargarDni(char dni[]){
    char aux[DIMDNI];
    do{
        printf("\nIngrese DNI (formato: 00.000.000): ");
        fflush(stdin);
        gets(aux);
    }while(validarDni(aux)!=0);
    strcpy(dni, aux);

}

// FUNCION QUE RECIBE POR PARAMETRO UN INT Y COMPRUEBA SI ES MAYOR O IGUAL A 0, SI ES MAYOR O IGUAL A 0 RETORNA 0, SINO -1
int validarEdad(int edad){
    if(edad>=0){
        return 0;
    }else{
        printf("\n Edad mal ingresada, por favor intentelo otra vez: ");
        return -1;
    }
}

//FUNCION PARA CARGAR EDAD, TRABAJA CON UNA VARIABLE INT. EN UN CICLO SE INGRESA LA EDAD Y SE REPITE HASTA QUE SE CUMPLA LA
//VALIDACION. AL FINAL RETORNA LA EDAD
int cargarEdad(){
    int edad;

    do{
        printf("\nIngrese edad: ");
        fflush(stdin);
        scanf("%i", &edad);
    }while(validarEdad(edad)!=0);

    return edad;
}

// FUNCION QUE RECIBE POR PARAMETRO UN CHAR Y COMPRUEBA SI ES M O F, SI LO ES RETORNA 0, SINO -1
int validarGenero(char genero[]){
    if(genero == 'm' || genero=='f'){
        return 0;
    }else{
        printf("\n Genero mal ingresado, por favor intentelo otra vez: ");
        return -1;
    }
}

//FUNCION PARA CARGAR EDAD, TRABAJA CON UNA VARIABLE CHAR. EN UN CICLO SE INGRESA EL GENERO Y SE REPITE HASTA QUE SE CUMPLA LA
//VALIDACION. AL FINAL RETORNA EL GENERO
char cargarGenero(){
    char genero;
    do{
        printf("\nIngrese genero f/m: ");
        fflush(stdin);
        scanf(" %c",&genero);
    }while(validarGenero(genero)!=0);

    return genero;
}

//FUNCION PARA CREAR USUARIOS, VA LLAMANDO A LAS FUNCIONES DE CARGAR LOS ATRIBUTOS(NOMBRE, DNI, EDAD, GENERO) Y RETORNA EL USUARIO
Usuario crearUsuario(){
    Usuario usuario;

    printf("\n --------------------------- \n");
    cargarNombre(usuario.nombre);
    cargarDni(usuario.dni);
    usuario.edad = cargarEdad();
    usuario.genero = cargarGenero();
    printf("\n --------------------------- \n");

    return usuario;
}

//FUNCION PARA CARGAR USUARIO EN EL ARCHIVO, RECIBE POR PARAMETRO EL NOMBRE DEL ARCHIVO
void cargarUsuario(char usuarios[]){
    FILE *archi;
    Usuario usuario;

    archi=fopen(usuarios, "ab");

    if(archi!=NULL){
            usuario = crearUsuario();
            fwrite(&usuario, sizeof(Usuario), 1, archi);
        fclose(archi);
    }
}

//FUNCION QUE RECIBE UN USUARIO POR PARAMETRO, Y CON LOS DATOS RECIBIDOS LO MUESTRA POR PANTALLA
void mostrarUsuario(Usuario usuario){
    printf("\n ------------------------ ");
    printf("\n Nombre: %s", usuario.nombre);
    printf("\n DNI: %s", usuario.dni);
    printf("\n Edad: %i", usuario.edad);
    printf("\n Genero: %c", usuario.genero);
    printf("\n ------------------------ \n");
}

//FUNCION QUE RECIBE EL NOMBRE DEL ARCHIVO POR PARAMETRO Y MUESTRA SU CONTENIDO
void mostrarUsuarios(char usuarios[]){
    FILE *archi;
    Usuario usuario;
    archi=fopen(usuarios, "rb");

    if(archi!=NULL){
        while(fread(&usuario, sizeof(Usuario),1, archi)>0){
            mostrarUsuario(usuario);
        }
        fclose(archi);
    }
}

//FUNCION QUE RECIBE POR PARAMETROS EL NOMBRE DEL ARCHIVO Y EN DNI, REVISA EN EL ARCHIVO Y EN EL CASO QUE EXISTA TE LO MUESTRA
Usuario buscarPorDni(char usuarios[], char dni[]){
    FILE *archi;
    Usuario usuario;
    int resultado;
    int encontrado = -1;
    archi = fopen(usuarios, "rb");

    if(archi!=NULL){
        while(fread(&usuario, sizeof(Usuario), 1, archi)>0){

        resultado = strcmp(usuario.dni, dni);

        if(resultado==0){
            encontrado=0;
            break;
            }
        }
    }

    if(encontrado == 0){
        mostrarUsuario(usuario);
    }else{
        printf("\nEl usuario no fue encontrado\n");
    }

    fclose(archi);

    return usuario;
}

//FUNCION PARA MODIFICAR UN USUARIO, RECIBE POR PARAMETRO UN USUARIO, CON UN SWITCH SE ELIGE QUE DESEA CAMBIAR Y SE RETORNA EL USUARIO
// MODIFICADO
Usuario modificarUsuario(Usuario usuario){
    printf("\nModificacion del usuario con dni %s \n", usuario.dni);
    char eleccion='s';
    int control;

    do{
        printf("Que desea modificar? \n"
               "1) Nombre \n"
               "2) DNI \n"
               "3) Edad \n"
               "4) Genero \n");
        fflush(stdin);
        scanf("%i", &control);

        switch(control){
    case 1:
        printf("Ingrese el nombre: ");
        fflush(stdin);
        gets(usuario.nombre);
        break;
    case 2:
        printf("Ingrese el dni: ");
        fflush(stdin);
        gets(usuario.dni);
        break;
    case 3:
        printf("Ingrese la edad: ");
        fflush(stdin);
        scanf("%i", &usuario.edad);
        break;
    case 4:
        printf("Ingrese el genero: ");
        fflush(stdin);
        scanf("%c", &usuario.genero);
        break;
    default:
        printf("Elija una opcion valida \n");
        break;
    }
    printf("Si desea continuar modificando presione s \n");
    fflush(stdin);
    scanf("%c", &eleccion);
    }while(eleccion=='s');
    return usuario;
}

//FUNCION PARA MODIFICAR UN USUARIO DE UN ARCHIVO, RECIBE POR PARAMETRO EL USUARIO Y EL DNI, LO BUSCA EN EL ARCHIVO Y DESPUES SE
//MODIFICA Y REESCRIBE EN EL ARCHIVO
void modificarUsuarioPorDNI(char usuarios[], char dni[]){
    FILE *archi;
    archi = fopen(usuarios, "r+b");
    Usuario usuario;
    int encontrado = -1;
    int acc =0;

    if(archi!=NULL){
        while(fread(&usuario, sizeof(Usuario), 1, archi)>0){
            acc++;
            encontrado = strcmp(usuario.dni, dni);

            if(encontrado==0){
                encontrado=0;
                break;
            }
        }

        if(encontrado==-1){
            printf("El usuario no fue encontrado \n");
        }

        if(encontrado==0){
            printf("DNI: %s",usuario.dni);
            usuario = modificarUsuario(usuario);
        }
        fseek(archi, sizeof(Usuario)*(acc-1), SEEK_SET);
        fwrite(&usuario, sizeof(Usuario), 1, archi);
        fclose(archi);
    }
}


