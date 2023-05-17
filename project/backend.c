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
    Pair * par = firstMap(map);
    while (par != NULL)
    {
        tarea * current = (tarea *)par->value;
        node * nuevo = crearNodo(current);
        tarea * precedente = firstList(current->precedentes);
        while (precedente != NULL)
        {
            Pair * par = searchMap(nodeMap, precedente->nombre);
            node * nodoPrecedente = (node *) par->value;
            if (nodoPrecedente == NULL)
            {
                nodoPrecedente = crearNodo(precedente);
                insertMap(nodeMap, precedente->nombre, nodoPrecedente);
            }
            pushBack(nuevo->precedentes, nodoPrecedente);
            precedente = nextList(current->precedentes);
        }
        insertMap(nodeMap, current->nombre, nuevo); 
        par = nextMap(map);
    }

    return nodeMap;
}

List * encontrarOrden(HashMap * map)
{
    HashMap * nodeMap = crearGrafo(map);
    //Heap * colaP = createHeap();

    bool todosVisitados = false;
    while (!todosVisitados)
    {
        Pair * par = firstMap(nodeMap);
        while (par != NULL)
        {
            node * actual = (node *)par->value;
            if (actual->precedentes == NULL)
            {
                //heap_push(colaP, actual, actual->estado);
            }
            par = nextMap(nodeMap);
        }
    }
    return NULL;
}

int compararTareas(void* ptr_a, void* ptr_b)
{
    tarea* a = (tarea* ) ptr_a;
    tarea* b = (tarea* ) ptr_b;

    if (a->prioridad >= b->prioridad) return 1;
    
    return 0;
}


tarea * crearTarea(char nombre[MAXC], int prioridad)
{
    tarea * nueva = (tarea *)malloc(sizeof(tarea));
    nueva->nombre = (char *)malloc(sizeof(char)*MAXC);
    strcpy(nueva->nombre, nombre);
    nueva->prioridad = prioridad;
    nueva->precedentes = createList();

    return nueva;
}

int agregarPrecedencia(HashMap* mapTareas, char id[MAXC], char tareaPrecedente[MAXC])
{
    if (searchMap(mapTareas, id) == NULL)   return 1;
    Pair* par = (Pair*)searchMap(mapTareas,id)->value;
    tarea* current = (tarea*)par->value;

    if (searchMap(mapTareas, tareaPrecedente) == NULL)   return 1;
    Pair * par2 = (Pair*)searchMap(mapTareas,tareaPrecedente)->value;
    tarea* precedente = (tarea*)par2->value;
    pushBack(current->precedentes,precedente);
    return 0;
}

void mostrarTarea(HashMap* mapTareas, char id[MAXC])
{
    Pair* par = (Pair*)searchMap(mapTareas,id)->value;
    tarea* current = (tarea*)par->value;
    printf("Tarea: %s\n",current->nombre);
    printf("Prioridad: %d\n",current->prioridad);
    printf("Precedentes: ");
    //List is a Linked List with methods from list.h
    
    tarea * precedente = firstList(current->precedentes);
    while(precedente != NULL)
    {
        printf("- %s\n", precedente->nombre);
        precedente = nextList(current->precedentes);
    }
    
    printf("\n");
}

