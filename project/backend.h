#ifndef backend_h
#define backend_h
#include "map/map.h"

typedef struct tarea tarea;

int agregarTarea(HashMap * mapTareas, char id[10], int prioridad);
tarea * crearTarea(char nombre[10], int prioridad);
int agregarPrecedencia(HashMap* mapTareas, char id[10], char tareaPrecedente[10]);
void mostrarTarea(HashMap* mapTareas, char id[10]);









#endif /* backend_h */