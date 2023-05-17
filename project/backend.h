#ifndef backend_h
#define backend_h
#include "map/map.h"

typedef struct tarea tarea;

int agregarTarea(HashMap * mapTareas, char id[20], int prioridad);
tarea * crearTarea(char nombre[20], int prioridad);
int agregarPrecedencia(HashMap* mapTareas, char id[20], char tareaPrecedente[20]);
void mostrarTareasPorHacer(HashMap * map);
void mostrarTarea(HashMap* mapTareas, char id[20]);
void importarDesdeCSV(HashMap* map, char archivo[20]);










#endif /* backend_h */