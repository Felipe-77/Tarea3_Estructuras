#include "backend.h"
#include "map/map.h"
#include "lista/list.h"
#include "heap/heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#define MAXC 10
#define EXPLORADO 2
#define VISITADO 1

typedef struct tarea
{
    char * nombre;
    int prioridad;
    List * precedentes;
}tarea;

typedef struct node
{
    char * nombre;
    int estado;
    List * precedentes;
}node;

tarea * crearTarea(char nombre[MAXC], int prioridad)
{
    tarea * nueva = (tarea *)malloc(sizeof(tarea));
    nueva->nombre = (char *)malloc(sizeof(char)*MAXC);
    strcpy(nueva->nombre, nombre);
    nueva->prioridad = prioridad;
    nueva->precedentes = createList();
    return nueva;
}

node * crearNodo(tarea * tarea)
{
    node * nuevo = (node *)malloc(sizeof(node));
    nuevo->nombre = tarea->nombre;
    nuevo->estado = 0;
    nuevo->precedentes = NULL;
    return nuevo;
}

int agregarTarea(HashMap * mapTareas, char id[MAXC], int prioridad)
{
    if (searchMap(mapTareas, id) != NULL)   return 1;
   
    tarea * nueva = crearTarea(id, prioridad);
    insertMap(mapTareas, id, nueva);
    return 0;
}

HashMap * crearGrafo(HashMap * map)
{
    HashMap * nodeMap = createMap(10);
    tarea * current = firstMap(map);
    while (current != NULL)
    {
        node * nuevo = crearNodo(current);
        tarea * precedente = firstList(current->precedentes);
        while (precedente != NULL)
        {
            node * nodoPrecedente = searchMap(nodeMap, precedente->nombre);
            if (nodoPrecedente == NULL)
            {
                nodoPrecedente = crearNodo(precedente);
                insertMap(nodeMap, precedente->nombre, nodoPrecedente);
            }
            pushBack(nuevo->precedentes, nodoPrecedente);
            precedente = nextList(current->precedentes);
        }
        insertMap(nodeMap, current->nombre, nuevo); 
        current = nextMap(map);
    }

    return nodeMap;
}

List * encontrarOrden(HashMap * map)
{
    HashMap * nodeMap = crearGrafo(map);
    Heap * colaP = createHeap();

    bool todosVisitados = false;
    while (!todosVisitados)
    {
        node * actual = firstMap(nodeMap);
        while (actual != NULL)
        {
            if (actual->precedentes == NULL)
            {
                heap_push(colaP, actual, actual->estado);
            }
            actual = nextMap(nodeMap);
        }
    }
}

void mostrarTareas(HashMap * mapTareas)
{
    List * tareasEnOrden = encontrarOrden(mapTareas);
    tarea * current = firstList(tareasEnOrden);
    while (current != NULL)
    {
        printf("%s\n", current->nombre);
        current = nextList(tareasEnOrden);
    }
}

