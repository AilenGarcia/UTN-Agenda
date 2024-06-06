#include "agenda.h"

//TAREAS
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

//EVENTOS
Fecha cargarFecha ()
{
    Fecha fecha;
    printf("Ingrese el dia: \n");
    fflush(stdin);
    scanf("%i", &fecha.day);

    printf("Ingrese el mes: \n");
    fflush(stdin);
    scanf("%i", &fecha.month);

    printf("Ingrese el a�o: ");
    fflush(stdin);
    scanf("%i", &fecha.year);

    return fecha;
}

Evento cargarEvento()
{
    Evento miEvento;
    char validacionEstado = 'm';

    printf("Ingrese el ID del evento \n");
    fflush(stdin);
    scanf("%i", &miEvento.id);

    printf("Ingrese el nombre del Evento: \n");
    fflush(stdin);
    scanf("%s", &miEvento.nombre);

    printf("Ingrese la fecha del evento: \n");
    miEvento.fecha = cargarFecha();

   // printf("Ingrese el usuario anfitrion");
    ///poner la funcion carga de usuario
    do{
    printf("El evento ya a ocurrido? \n"
           "\n Ingrese 's', para si o 'n' para no \n");
    fflush(stdin);
    scanf("%c",&validacionEstado);

    }while(validacionEstado != 'n' && validacionEstado != 'N' && validacionEstado != 's' && validacionEstado != 'S');
    return miEvento;
}


void guardarEventoEnArchivo(char nombreArchivo[])
{
    FILE *archivo = fopen(nombreArchivo, "ab");
    Evento miEvento;

    if (archivo == NULL) {
        printf("Error al abrir el archivo");
        return;
    }

        if(archivo!=NULL){
            miEvento = cargarEvento();
            fwrite(&miEvento, sizeof(Evento), 1, archivo);
        fclose(archivo);
    }
    /*fprintf(archivo, "ID: %i\n",miEvento.id);
    fprintf(archivo, "Nombre: %s\n", miEvento.nombre);
    fprintf(archivo, "Estado: %c\n", miEvento.estado);
    fprintf(archivo, "Fecha: %02d/%02d/%04d\n", miEvento.fecha.day, miEvento.fecha.month, miEvento.fecha.year);

    for (int i = 0; i < 20; i++) {
        if (miEvento.persona[i].dni != 0) { // Verificar si el usuario tiene un DNI asignado
            fprintf(archivo, "Usuario %i:\n", i + 1);
            fprintf(archivo, "  DNI: %i\n", miEvento.persona[i].dni);
            fprintf(archivo, "  Nombre: %s\n", miEvento.persona[i].nombre);
            fprintf(archivo, "  Edad: %i\n", miEvento.persona[i].edad);
            fprintf(archivo, "  G�nero: %c\n", miEvento.persona[i].genero);
        }
    }*/

    fclose(archivo);
}

int cuentaElementosArchivo(char nombreArchivo)
{

    FILE* archi= fopen(nombreArchivo, "rb");
    int registros= 0;

    if(archi!=NULL)
    {
        int aux;

        while(fread(&aux, sizeof(int), 1, archi)>0)
        {
            registros++;
        }
        fclose(archi);
    }
    return registros;
}

int pasajeDeArchivoAArrayEventos(Evento array[],int id, char nombreArchivo[]){
    FILE *archi;
    archi=fopen(nombreArchivo, "rb");
    Evento eventos;
    int i=0;
    int resultado;

    if(archi!=NULL){
        while(fread(&eventos, sizeof(Evento), 1, archi)>0){

            if(eventos.id == id){
            resultado = 0;
            }
            if(resultado !=0){
                array[i] = eventos;
                i++;
            }
        }
    }
    fclose(archi);
    return i;
}
void pasajeDeArregloAArchivoEvento (Evento array[], int validos, char nombreArchivo[]){
    FILE *archi;
    archi=fopen(nombreArchivo, "wb");
    int i=0;

    if(archi!=NULL){
        while(i< validos){
            fwrite(&array[i], sizeof(Evento),1,archi);
            i++;
        }
    }
    fclose(archi);
}

void eliminarEvento (char nombreEvento[], Evento array[], int id){
    int validos;
    validos = pasajeDeArchivoAArrayEventos(array, id, nombreEvento);
    pasajeDeArregloAArchivo(array,validos, nombreEvento);

    printf("\n Evento eliminado \n");
}

/*
void eliminarEventoPorID(char *nombreArchivo, int id, int registros) {
    Evento miEvento[20];

    int indicador = -1;
    for (int i = 0; i < registros; i++) {
        if (miEvento[i].id == id) {
            indicador = i;
        }
    }

    if (indicador == -1) {
        printf("Evento con ID %d no encontrado\n", id);
        return;
    }

    for (int i = indicador; i < registros - 1; i++) {
        miEvento[i] = miEvento[i + 1];
    }
    registros--;

    cargarEvento(miEvento);
    guardarEventoEnArchivo(miEvento, nombreArchivo);

    printf("Evento con ID %d eliminado\n", id);
}
*/


//USUARIOS


int iniciarSesion(char usuarios[]){
    Usuario usuario;
    char dni[DIMDNI];
    char pass[DIMPASS];

    printf("Ingresar dni: ");
    fflush(stdin);
    gets(dni);

    printf("Ingresar pass: ");
    fflush(stdin);
    gets(pass);

    usuario = buscador(usuarios,dni);

    if(strcmp(usuario.pass,pass)==0){
        return usuario.rol;
    }else{
        return -1;
    }
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

//FUNCION QUE RECIBE POR PARAMETROS EL NOMBRE DEL ARCHIVO Y EN DNI, REVISA EN EL ARCHIVO Y EN EL CASO QUE EXISTA RETORNA 0, SINO -1
int validarPorDni(char usuarios[], char dni[]){
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

    fclose(archi);

    if(encontrado == 0){
        printf("\n Error. DNI existente \n");
        return -1;
    }else{
        return 0;
    }
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
void cargarDni(char dni[], char usuarios[]){
    char aux[DIMDNI];
    do{
        printf("\nIngrese DNI (formato: 00.000.000): ");
        fflush(stdin);
        gets(aux);
    }while(validarDni(aux)!=0 || validarPorDni(usuarios, aux)!=0);
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
    if((genero == 'm') || (genero=='f')){
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

// FUNCION QUE RECIBE POR PARAMETRO UN ARREGLO DE STRING Y COMPARA LA CANTIDAD DE CARACTERES QUE CONTIENE, SI ES IGUAL A 8
// RETORNA 0, SINO -1
int validarPass(char pass[]){
    if(strlen(pass) == 8){
        return 0;
    }else{
        printf("\n Pass mal ingresado, por favor intentelo otra vez: ");
        return -1;
    }
}

//FUNCION PARA CARGAR PASS, RECIBE POR PARAMETRO UN ARREGLO. EN UN CICLO SE INGRESA EL PASS Y SE GUARDA EN UNA VARIABLE Y SE REPITE
//HASTA QUE SE CUMPLA LA VALIDACION. AL FINAL IGUALA LA VARIABLE A PASS
void cargarPass(char pass[]){
    char aux[DIMPASS];
    do{
        printf("\nIngresar password (Tiene que tener 8 caracteres): ");
        fflush(stdin);
        gets(aux);
    }while(validarPass(aux)!=0);
    strcpy(pass, aux);
}

//FUNCION PARA CREAR USUARIOS, VA LLAMANDO A LAS FUNCIONES DE CARGAR LOS ATRIBUTOS(NOMBRE, DNI, EDAD, GENERO) Y RETORNA EL USUARIO
Usuario crearUsuario(char usuarios[]){
    Usuario usuario;

    printf("\n --------------------------- \n");
    cargarNombre(usuario.nombre);
    cargarPass(usuario.pass);
    cargarDni(usuario.dni, usuarios);
    usuario.edad = cargarEdad();
    usuario.genero = cargarGenero();
    usuario.rol = 0;
    printf("\n --------------------------- \n");

    return usuario;
}

//FUNCION PARA CARGAR USUARIO EN EL ARCHIVO, RECIBE POR PARAMETRO EL NOMBRE DEL ARCHIVO
void cargarUsuario(char usuarios[]){
    FILE *archi;
    Usuario usuario;

    archi=fopen(usuarios, "ab");

    if(archi!=NULL){
            usuario = crearUsuario(usuarios);
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

//FUNCION QUE RECIBE POR PARAMETROS EL NOMBRE DEL ARCHIVO Y EN DNI, REVISA EN EL ARCHIVO Y EN EL CASO QUE EXISTA TE LO MUESTRA Y RETORNA
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

//FUNCION QUE RECIBE POR PARAMETROS EL NOMBRE DEL ARCHIVO Y EN DNI, REVISA EN EL ARCHIVO Y EN EL CASO QUE EXISTA TE LO RETORNA
Usuario buscador(char usuarios[], char dni[]){
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

    if(encontrado != 0){
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

//FUNCION PARA PASAR DATOS DE UN ARCHIVO A UN ARRAY EXCEPTO EL USUARIO CON EL DNI PASADO POR PARAMETRO
//PASA POR PARAMETRO UN ARRAY, UN DNI Y EL ARCHIVO. RETORNA LOS VALIDOS
int pasajeDeArchivoAArray(Usuario array[],char dni[], char usuarios[]){
    FILE *archi;
    archi=fopen(usuarios, "rb");
    Usuario usuario;
    int i=0;
    int resultado;

    if(archi!=NULL){
        while(fread(&usuario, sizeof(Usuario), 1, archi)>0){

            resultado = strcmp(usuario.dni, dni);

            if(resultado !=0){
                array[i] = usuario;
                i++;
            }
        }
    }
    fclose(archi);
    return i;
}

//FUNCION PARA PASAR DATOS DE UN ARRAY A UN ARCHIVO PASA POR PARAMETRO UN ARRAY, LA CANTIDAD DE VALIDOS Y EL ARCHIVO
void pasajeDeArregloAArchivo(Usuario array[], int validos, char usuarios[]){
    FILE *archi;
    archi=fopen(usuarios, "wb");
    int i=0;

    if(archi!=NULL){
        while(i< validos){
            fwrite(&array[i], sizeof(Usuario),1,archi);
            i++;
        }
    }
    fclose(archi);
}

//FUNCION PARA ELIMINAR UN USUARIO, PASA POR PARAMETROS EL ARCHIVO, UN ARRAY DE USUARIOS Y UN DNI
void eliminarUsuario(char usuarios[], Usuario array[], char dni[]){
    int validos;
    validos = pasajeDeArchivoAArray(array, dni, usuarios);
    pasajeDeArregloAArchivo(array,validos, usuarios);

    printf("\n Usuario eliminado \n");
}

//FUNCION PARA CARGAR 10 DATOS DE PRUEBA
void cargarDatos(char nombreArchivo[]){
    FILE *archi;

    archi = fopen(nombreArchivo, "rb");
    if (archi != NULL) {
        fclose(archi);
        return;
    }

    Usuario usuarios[10] = {
        {"12.345.678", "Ailen Garcia", 25, 'F', "hola", 0},
        {"23.456.789", "Pedro Do Brito", 40, 'M', "hola", 0},
        {"34.567.891", "Franco Ferreira", 20, 'M', "hola", 0},
        {"45.678.912", "Marta Lopez", 35, 'F', "hola", 0},
        {"56.789.123", "Camila Perez", 22, 'F', "hola", 0},
        {"98.765.432", "Franco Sanchez", 40, 'M', "hola", 0},
        {"87.654.321", "Patricia Rodriguez", 26, 'F', "hola", 0},
        {"76.543.219", "Diego Fernandez", 33, 'M', "hola", 0},
        {"65.432.198", "Mabel Gullo", 27, 'F', "hola", 0},
        {"00.000.000", "Administrador", 30, 'M', "mundo", 1}
    };

    archi = fopen(nombreArchivo, "wb");
    if (archi != NULL) {
        fwrite(usuarios, sizeof(Usuario), 10, archi);
        fclose(archi);
    }
}


