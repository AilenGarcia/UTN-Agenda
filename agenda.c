#include "agenda.h"

//EVENTOS
///Funcion para cargar fecha, retorna un dato de tipo fecha
Fecha cargarFecha ()
{
    Fecha miFecha;

    printf("\n ---------------------------- \n");
    do
    {
        printf("Ingrese el dia: \n");
        fflush(stdin);
        scanf("%i",&miFecha.day);
    }while(validarDia(miFecha.day)!=0);

    do
    {
        printf("Ingrese el mes: \n");
        fflush(stdin);
        scanf("%i", &miFecha.month);
    }while(validarMes(miFecha.month) !=0);

    printf("Ingrese el año: \n");
    fflush(stdin);
    scanf("%i", &miFecha.year);
    printf("---------------------------------- \n");

    return miFecha;
}

/// Funcion que recibe un dato de tipo entero como parametro y comprueba el rango de valor de este, retorna 0 en caso de funcionar o -1 en caso que no
int validarDia(int day)
{
    if(day>0 && day<32){
        return 0;
    }else{
        printf("\n -------------- Dia mal ingresado -------------- \n");
        return -1;
    }
}

/// Funcion que recibe un dato de tipo entero como parametro y comprueba el rango de valor de este, retorna 0 en caso de funcionar o -1 en caso que no
int validarMes(int month)
{
    if(month>0 && month<13){
        return 0;
    }else{
        printf("\n -------------- Mes mal ingresado -------------- \n");
        return -1;
    }
}

///Funcion que recibe un dato de tipo Fecha por parametro y muestra este mismo
void mostrarFecha (Fecha miFecha)
{
    printf("\n ---------------------------- \n");
    printf("Dia: %i \n", miFecha.day);
    printf("Mes: %i \n", miFecha.month);
    printf("Anio: %i \n", miFecha.year);
    printf("\n ---------------------------- \n");
}

///Funcion para la carga de eventos, recibe como parametro el archivo de usuarios y retorna un dato de tipo Evento
Evento cargarEvento(char usuarios[])
{
    Evento miEvento;
    Usuario miUsuario;
    char nombre[50];
    char validacionEstado = 'm';

    miEvento.id=rand()*9999;
    do
    {
        printf("\n Ingrese el nombre del Evento: \n");
        fflush(stdin);
        gets(miEvento.nombre);

    }while(validarNombre(miEvento.nombre) != 0);

    printf("Ingrese la fecha del evento: \n");
    miEvento.fecha = cargarFecha();
    do{
    printf("\n Usuarios disponibles: \n");
    mostrarUsuariosParaEvento(usuarios);

    printf("\n Ingrese el usuario \n");
    fflush(stdin);
    gets(nombre);

    }while(buscarPorUsuarioPorNombre(usuarios, nombre)==-1);

    miEvento.persona = elegirUsuarioPorNombre(usuarios, nombre);
    miEvento.estado= 'n';

    return miEvento;
}

///Funcion para mostrar usuarios de eventos, recibe por parametro el archivo usuarios, entra en el archivo y muestra su contenido.
void mostrarUsuariosParaEvento(char usuarios[]){
    FILE *archi;
    Usuario usuario;
    archi=fopen(usuarios, "rb");

    if(archi!=NULL){
        while(fread(&usuario, sizeof(Usuario),1, archi)>0){
            printf("|  %s  ", usuario.nombre);
        }
        fclose(archi);
    }
}

///Funcion para eleccion de usuario, se le pasa por parametro el archivo de usuarios y un string, lee el archivo y retorna el usuario encontrado
Usuario elegirUsuarioPorNombre(char usuarios[], char nombre[]){
    FILE *archi;
    Usuario usuario;
    int resultado;
    int encontrado = -1;
    archi = fopen(usuarios, "rb");

    if(archi!=NULL){
        while(fread(&usuario, sizeof(Usuario), 1, archi)>0){

        resultado = strcmp(usuario.nombre, nombre);

        if(resultado==0){
            fclose(archi);
            return usuario;
            }
        }
    fclose(archi);
    }
}

///Funcion para buscar usuario segun nombre, se le pasa por parametro el archivo usuarios y un string, lee el archivo y retorna el usuario encontrado.
int buscarPorUsuarioPorNombre(char usuarios[], char nombre[]){
    FILE *archi;
    Usuario usuario;
    int resultado;
    int encontrado = -1;
    archi = fopen(usuarios, "rb");

    if(archi!=NULL){
        while(fread(&usuario, sizeof(Usuario), 1, archi)>0){

        resultado = strcmp(usuario.nombre, nombre);

        if(resultado==0){
            fclose(archi);
            return 0;
            }
        }
    fclose(archi);
    }
    printf("\n Usuario no encontrado, elija uno de la lista \n");
    return -1;
}

///Carga de evento pasando por parametro el archivo
void guardarEventoEnArchivo(char nombreArchivo[], char usuarios[])
{
    FILE *archivo = fopen(nombreArchivo, "ab");
    Evento miEvento;

    if (archivo == NULL) {
        printf("Error al abrir el archivo");
        return;
    }

        if(archivo!=NULL){
    FILE *archivo = fopen(nombreArchivo, "ab");
    Evento miEvento;

    if (archivo == NULL) {
        printf("Error al abrir el archivo");
        return;
    }

        if(archivo!=NULL){
            miEvento = cargarEvento(usuarios);
            fwrite(&miEvento, sizeof(Evento), 1, archivo);
        fclose(archivo);
    }

    fclose(archivo);
    }

    fclose(archivo);
}

///Funcion para saber la cantidad de registros que se encuentran en el archivo, se pasa por parametro el archivo
int cuentaElementosArchivo(char nombreArchivo[])
{

    FILE* archi= fopen(nombreArchivo, "rb");
    int registros= 0;
    Evento miEvento;

    if(archi!=NULL)
    {
        while(fread(&miEvento, sizeof(Evento), 1, archi)>0)
        {
            registros++;
        }
        fclose(archi);
    }
    return registros;
}

///Funcion que retorna ID de un evento segun el nombre que se busca, se pasa por parametro solo el archivo retorna el numero de ID
int retornarIDSegunNombre(char archivoEventos[], char nombre[])
{
    FILE *archiE;
    archiE=fopen(archivoEventos,"rb");
    Evento miEvento;
    int nombreEncontrado=0;

    if(archiE != NULL)
    {
        while(fread(&miEvento,sizeof(Evento),1,archiE) > 0 )
        {
            nombreEncontrado=strcmp(miEvento.nombre, nombre);

                if(nombreEncontrado==0)
                {
                    fclose(archiE);
                    return miEvento.id;
                }
            }
        printf("El nombre ingresado no se encontro. \n");
        fclose(archiE);
    }
}

///Funcion para el pasaje de archivo a arreglo, se le pasa por parametro un arreglo de tipo Evento, el ID del evento y el archivo
int pasajeDeArchivoAArrayEventos(Evento array[],int id, char nombreArchivo[]){
    FILE *archi;
    archi=fopen(nombreArchivo, "rb");
    Evento eventos;
    int i=0;

    if(archi!=NULL){
        while(fread(&eventos, sizeof(Evento), 1, archi)>0){
            if(eventos.id !=id){
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

///Funcion para eliminar un evento del archivo segun el ID, pasandolo a un arreglo y devuelta al archivo los restantes
void eliminarEvento (char nombreEvento[], Evento array[], int id){
    int validos;
    validos = pasajeDeArchivoAArrayEventos(array, id, nombreEvento);
    pasajeDeArregloAArchivoEvento(array,validos, nombreEvento);

    printf("\n Evento eliminado \n");
}

///Funcion para modificar evento, por parametro se le pasa un evento y el archivo de usuarios, se le pide al usuario que seleccione que parametro modificar.
Evento modificarEvento (Evento miEvento, char archivoUsuarios[]){
    printf("\nModificar el Evento por nombre %s \n", miEvento.nombre);
    char eleccion='s';
    char nombre[50];
    int control;

    do{
        printf("Que desea modificar? \n"
               "1) Nombre \n"
               "2) Estado \n"
               "3) Fecha \n");
        fflush(stdin);
        scanf("%i", &control);

        switch(control){
    case 1:
        printf("Ingrese el nombre: ");
        fflush(stdin);
        gets(miEvento.nombre);
        break;
    case 2:
        printf("Ingrese el Estado: ");
        fflush(stdin);
        scanf("%c" ,&miEvento.estado);
        break;
    case 3:
        printf("Ingrese la fecha: ");
        miEvento.fecha=cargarFecha();
        break;
    default:
        printf("Elija una opcion valida \n");
        break;
    }
    printf("Si desea continuar modificando presione s \n");
    fflush(stdin);
    scanf("%c", &eleccion);
    }while(eleccion=='s');
    return miEvento;
}
///Funcion para modificar un evento, recibiendo como parametro el nombre de esta, el archivo eventos y usuarios, entra en una secuencia y compara los nombres
///de los eventos, retorna 0 en caso de encontrarlo
void modificarEventoPorNombre(char archivoEvento[], char archivoUsuarios[], char nombre[]){
    FILE *archi;
    archi = fopen(archivoEvento, "r+b");
    Evento miEvento;
    int encontrado = -1;
    int acc =0;

    if(archi!=NULL){
        while(fread(&miEvento, sizeof(Evento), 1, archi)>0){
            acc++;
            encontrado = strcmp(miEvento.nombre, nombre);

            if(encontrado==0){
                encontrado=0;
                break;
            }
        }

        if(encontrado==-1){
            printf("El Evento no fue encontrado \n");
        }

        if(encontrado==0){
            printf("Evento: %s",miEvento.nombre);
            miEvento = modificarEvento(miEvento, archivoUsuarios);
        }
        fseek(archi, sizeof(Evento)*(acc-1), SEEK_SET);
        fwrite(&miEvento, sizeof(Evento), 1, archi);
        fclose(archi);
    }
}

///Funcion para la busqueda de un evento segun nombre, recibe por parametro el archivo eventos, en caso de encontrar el evento retorna 0.
Evento buscarEventoSegunNombre(char archivoEventos[])
{
    FILE*archiE;
    archiE=fopen(archivoEventos,"rb");
    char nombre[50];
    Evento miEvento;
    int nombreEncontrado=0;

    if(archiE != NULL)
    {
        printf("Ingrese el Nombre a buscar:");
        fflush(stdin);
        scanf("%s",&nombre);

        while(fread(&miEvento,sizeof(Evento),1,archiE) > 0 )
        {
            nombreEncontrado=strcmpi(miEvento.nombre, nombre);

            if(nombreEncontrado==0)
            {
                printf("El evento %s fue encontrado \n", miEvento.nombre);
                fflush(stdin);
                return miEvento;
            }
            else
            {
                printf("El nombre ingresado no es valido. \n");
                fflush(stdin);
            }
        }

        fclose(archiE);
    }
}

///Funcion para ver los siguientes eventos,se le pasa por parametro el archivo eventos y un evento. Recorrer el archivo y hace uso de la funcnion mostrar evento.
void eventosProximos (char archivoEventos[], Evento tuEvento)
{
    FILE * archiE;
    archiE=fopen(archivoEventos, "rb");
    int i = 0;

    if(archiE != NULL)
    {
        while (fread(&tuEvento, sizeof(Evento),1,archiE) > 0)
        {
            if(tuEvento.estado== 'n')
            {
                mostrarEvento(tuEvento);
            }
        }
        fclose(archiE);
    }
}

///Funcion para poder mostrar un usuario dentro de eventos, recibe por parametro un evento
void mostrarPersonaEvento (Evento miEvento)
{
  printf("\n Nombre: %s \n", miEvento.persona.nombre);
    printf(" DNI: %s \n", miEvento.persona.dni);
    printf(" Edad: %i \n", miEvento.persona.edad);
    printf(" Genero: %c \n", miEvento.persona.genero);
}

///Funcion para poder mostrar una fecha dentro de eventos, recibe por parametro un evento
void mostrarFechaEvento (Evento miEvento)
{
    printf(" %i / %i / %i \n", miEvento.fecha.day, miEvento.fecha.month, miEvento.fecha.year);
}

///Funcion para poder mostrar un evento entero, recibe por parametro un evento.
void mostrarEvento(Evento miEvento)
{
    puts("\n----------------------------------\n");
    printf("Nombre: %s \n", miEvento.nombre);
    printf("Estado: %c \n", miEvento.estado);
    printf("Usuario: %s\n", miEvento.persona.nombre);
    printf("Fecha: ");
    mostrarFechaEvento(miEvento);
    puts("\n----------------------------------\n");
}

///Funcion para mostrar lo eventos guardados dentro de un archivo, recibe por parametro el archivo eventos y hace uso de la funcion mostrarEvento
void mostrarEventos (char archivoEventos[]){
    FILE *archi;
    Evento miEvento;
    archi=fopen(archivoEventos, "rb");

    if(archi!=NULL){
        while(fread(&miEvento, sizeof(Evento),1, archi)>0){
            mostrarEvento(miEvento);
        }
        fclose(archi);
    }
}

///Funcion para poder mostrar el contenido de una matriz, recibe por parametro una matriz, un arreglo y un evento.
void mostrarMatriz(char matriz[12][12], int arrayMes[], char eventos[]){
    int validos = pasarFechasArray(arrayMes, eventos);
    int encontrado = -1;
    printf("\n En rojo apareceran los meses con eventos \n");
    printf("-----------------------------------------\n");
    for(int i=0; i<12; i++){
        encontrado = recorrerArray(arrayMes, validos, i+1);
        if(encontrado ==0){
            printf("\x1b[31m");
            printf("   %s   ", matriz[i]);
            printf("\n");
            printf("\x1B[37m");
        }else{
            printf("   %s   ", matriz[i]);
            printf("\n");
            }
    }
}

///Funcion para cargar fechas dentro de un arreglo, se le pasa por parametro un arreglo y un evento.
int pasarFechasArray(int arrayMes[], char eventos[]){
    FILE *archi;
    archi = fopen(eventos, "rb");
    Evento evento;
    int i=0;

    if(archi!=NULL){
        while(fread(&evento, sizeof(Evento), 1, archi)>0){
            if(evento.estado == 'n'){
                arrayMes[i]= evento.fecha.month;
                i++;
            }
        }
        fclose(archi);
    }
    return i;
}

///Funcion para pasar un evento a un arreglo, se le pasa por parametro un arreglo de eventos y el archivo eventos
int pasarArray(Evento arrayE[], char eventos[])
{
    FILE *archi;
    archi = fopen(eventos, "rb");
    Evento evento;
    int i=0;

    if(archi!=NULL){
        while(fread(&evento, sizeof(Evento), 1, archi)>0){
                arrayE[i]= evento;
                i++;
        }
        fclose(archi);
    }
    return i;
}

///Funcion para recorrer un arreglo, recibe por parametro un arreglo,
int recorrerArray(int arrayMes[], int validos, int mes){
    for(int i=0; i<validos; i++){
        if(arrayMes[i] == mes){
            return 0;
        }
    }
    return -1;
}

///Funcion para encontrar el menor mes dentro de un arreglo de eventos, se le pasa por parametro un arreglo de eventos, la posicion a buscar y la cantidad de eventos dentro del arreglo
int posicion_menor (Evento arregloEventos[], int pos, int registros)
{
    Evento menor = arregloEventos[pos];
    int posmenor = pos;
    int index = pos +1;


    while (index < registros)
    {
        if(menor.fecha.month > arregloEventos[index].fecha.month)
        {
            menor = arregloEventos[index];
            posmenor = index;
        }
        index++;
    }
    return posmenor;
}

///Funcion que ordena los meses de un arreglo de evento de menor a mayor, se le pasa por parametro un arreglo de tipo eventos y la cantidad de eventos dentro del arreglo
void ordenacion_seleccion (Evento arregloEventos[], int registros)
{
    int posmenor;
    int i = 0;
    Evento aux;
    while(i < registros-1)
    {
        posmenor = posicion_menor(arregloEventos,i,registros);
        aux = arregloEventos[posmenor];
        arregloEventos[posmenor]= arregloEventos[i];
        arregloEventos[i] = aux;
        i++;
    }
}

///Funcion para mostrar un arreglo de eventos, se le pasa por parametro un arreglo de tipo evento y la cantidad de eventos dentro del arreglo
void mostrarArrayMes(Evento arrayMes[], int registros)
{
    for (int i=0 ; i<registros ; i++)
    {
        mostrarEvento(arrayMes[i]);
    }
}
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
int pasajeDeArchivoAArray(Usuario **array, char dni[], char usuarios[]){
    int validos = cantRegistros(usuarios);
    FILE *archi;
    archi=fopen(usuarios, "rb");
    Usuario usuario;
    int i=0;
    int resultado;
    *array = (Usuario*) malloc(validos* sizeof(Usuario));

    if(archi!=NULL){
        while(fread(&usuario, sizeof(Usuario), 1, archi)>0){

            resultado = strcmp(usuario.dni, dni);

            if(resultado !=0){
                (*array)[i] = usuario;
                i++;
            }
        }
    }
    fclose(archi);
    return i;
}

//FUNCION PARA PASAR DATOS DE UN ARRAY A UN ARCHIVO PASA POR PARAMETRO UN ARRAY, LA CANTIDAD DE VALIDOS Y EL ARCHIVO
void pasajeDeArregloAArchivo(Usuario **array, int validos, char usuarios[]){
    FILE *archi;
    archi=fopen(usuarios, "wb");
    int i=0;

    if(archi!=NULL){
        while(i< validos){
            fwrite(&(*array)[i], sizeof(Usuario),1,archi);
            i++;
        }
    }
    fclose(archi);
}

int cantRegistros(char usuarios[]){
    FILE *archi;
    archi = fopen(usuarios, "rb");
    int cant;

    if(archi!=NULL){
        fseek(archi,0, SEEK_END);
        cant = ftell(archi)/sizeof(Usuario);
        fclose(archi);
    }

    return cant;
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


