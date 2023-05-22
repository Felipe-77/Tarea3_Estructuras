#ifndef backend_h
#define backend_h
#include "map/map.h"
#include "arraylist/arraylist.h"
#define AGREGAR_TAREA 1
#define AGREGAR_PRECEDENCIA 2
#define MARCAR_TAREA 3

typedef struct tarea tarea;

int agregarTarea(HashMap * mapTareas, char id[10], int prioridad);
tarea * crearTarea(char nombre[10], int prioridad);
int eliminarTarea(HashMap * mapTareas, char id[10]);
int agregarPrecedencia(HashMap* mapTareas, char id[10], char tareaPrecedente[10]);
void mostrarTareasPorHacer(HashMap * map);
int mostrarTarea(HashMap* mapTareas, char id[10]);
void importarDesdeCSV(HashMap* map, char * archivo);

void deshacerAccion(Stack* s, HashMap* mapTareas);
void stackUndo(Stack* s, void* data, int tipo);







#endif /* backend_h */