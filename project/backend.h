#ifndef backend_h
#define backend_h
#include "map/map.h"

typedef struct tarea tarea;

int agregarTarea(HashMap * mapTareas, char id[10], int prioridad);
tarea * crearTarea(char nombre[10], int prioridad);







#endif /* backend_h */