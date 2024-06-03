#ifndef TAREAS_H_INCLUDED
#define TAREAS_H_INCLUDED

int validarTarea(const char *idTarea, FILE *archi){ //FUNCION QUE COMPRUEBA SI EL NOMBRE DE LA TAREA QUE SE QUIERE ANOTAR ESTÁ REPETIDA O NO

    tarea tareaLeida;
rewind (archi);

    while (fread(&tareaLeida, sizeof(tarea),1,archi)){

        if (tareaLeida.idTarea==idTarea){

            return 1; //ya hay una tarea con el mismo nombre
           }
    }

 return 0; //ese nombre no existe
}


#endif // TAREAS_H_INCLUDED
