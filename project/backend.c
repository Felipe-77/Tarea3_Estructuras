#include "backend.h"
#include "map/map.h"
#include "lista/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAXC 10

typedef struct tarea
{
    char * nombre;
    int prioridad;
    List * precedentes;
}tarea;

tarea * crearTarea(char nombre[MAXC], int prioridad)
{
    tarea * nueva = (tarea *)malloc(sizeof(tarea));
    nueva->nombre = (char *)malloc(sizeof(char)*MAXC);
    strcpy(nueva->nombre, nombre);
    nueva->prioridad = prioridad;
    nueva->precedentes = createList();
    return nueva;
}

int agregarTarea(HashMap * mapTareas, char id[MAXC], int prioridad)
{
    if (searchMap(mapTareas, id) != NULL)   return 1;
   
    tarea * nueva = crearTarea(id, prioridad);
    insertMap(mapTareas, id, nueva);
    return 0;
}


