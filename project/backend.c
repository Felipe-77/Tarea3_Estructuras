#include "backend.h"
#include "map/map.h"
#include "arraylist/arraylist.h"
#include "heap/heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#define MAXC 20
#define EXPLORADO 2
#define VISITADO 1

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};


typedef struct tarea
{
    char * nombre;
    int prioridad;
    ArrayList * precedentes;
}tarea;

typedef struct node
{
    char * nombre;
    int prioridad;
    int estado;
    ArrayList * precedentes;
}node;


node * crearNodo(tarea * tarea)
{
    node * nuevo = (node *)malloc(sizeof(node));
    nuevo->nombre = tarea->nombre;
    nuevo->estado = 0;
    nuevo->prioridad = tarea->prioridad;
    nuevo->precedentes = createList();
    return nuevo;
}

int agregarTarea(HashMap * mapTareas, char id[MAXC], int prioridad)
{
    if (searchMap(mapTareas, id) != NULL)   return 1;
   
    tarea * nueva = crearTarea(id, prioridad);
    insertMap(mapTareas, nueva->nombre, nueva);
    return 0;
}

HashMap * crearGrafo(HashMap * map)
{
    HashMap * nodeMap = createMap(20);
    Pair * par = firstMap(map);
    tarea * current = par->value;
    while (current != NULL)
    {
        node * nuevo = crearNodo(current);
        for (int i = 0; i < get_size(current->precedentes); i++)  
        {
            tarea * tareaPrecedente = (tarea*)get(current->precedentes, i);
            if (tareaPrecedente == NULL) continue;

            Pair * par = searchMap(nodeMap, tareaPrecedente->nombre);

            if (par == NULL)
            {
                
                node * nodoPrecedente = crearNodo(tareaPrecedente);
                insertMap(nodeMap, nodoPrecedente->nombre, nodoPrecedente);
                append(nuevo->precedentes, nodoPrecedente);
            }
            else
            {
                node * nodoPrecedente = par->value;
                append(nuevo->precedentes, nodoPrecedente);
            }
            
        }
        
        insertMap(nodeMap, nuevo->nombre, nuevo);
        Pair * par = nextMap(map);
        if (par == NULL)    break;
        current = par->value;
        
    }
    return nodeMap;
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
    Pair * par = searchMap(mapTareas, id);
    if (par == NULL)   return 1;
    tarea* current = (tarea*)par->value;

    par = searchMap(mapTareas, tareaPrecedente);
    if (par == NULL)   return 1;
    tarea* precedente = (tarea*)par->value;
    append(current->precedentes,precedente);
    return 0;
}

ArrayList * encontrarOrden(HashMap * map)
{
    
    HashMap * nodeMap = crearGrafo(map);
    
    Heap * colaP = createHeap();
    ArrayList * orden = createList();
    while (nodeMap->size != 0)
    {
        Pair * par = firstMap(nodeMap);
        if (par == NULL)    break;
        node * current = par->value;
        while (current != NULL)
        {
            if (current->estado != 0)
            {
                par = nextMap(nodeMap);
                if (par == NULL)    break;
                current = par->value;
                continue;
            }
            bool flag = true;
            for (int i = 0; i < get_size(current->precedentes); i++)
            {
                node * nodo = (node *)get(current->precedentes, i);
                if (nodo->estado == 0)
                {
                    flag = false;
                    break;
                }
            }
            if (flag){
                heap_push(colaP, current, current->prioridad);
                current->estado = VISITADO;
            }
            par = nextMap(nodeMap);
            if (par == NULL)    break;
            current = par->value;
        }
        node * nodo = (node *)heap_top(colaP);
        if (nodo == NULL)   break;
        nodo->estado = EXPLORADO;
        heap_pop(colaP);
        append(orden, nodo);
        eraseMap(nodeMap, nodo->nombre);
    }
    
    return orden;
}

void mostrarTareasPorHacer(HashMap * map)
{
    ArrayList * orden = encontrarOrden(map);
    for (int i = 0; i < get_size(orden); i++)
    {
        node * current = (node*)get(orden, i);
        mostrarTarea(map, current->nombre);
    }
}

void mostrarTarea(HashMap* mapTareas, char id[MAXC])
{
    Pair * par = searchMap(mapTareas, id);
    if (par == NULL)    return;
    tarea* current = (tarea*)par->value;
    printf("\n ---------------------------- \n");
    printf("\nTarea: %s\n",current->nombre);
    printf("Prioridad: %d\n",current->prioridad);
    printf("Precedentes: \n");
    
    for (int i = 0; i < get_size(current->precedentes); i++)
    {
        tarea * precedente = get(current->precedentes, i);
        printf("- %s\n",precedente->nombre);
    }
    
    printf("\n");
}


void importarDesdeCSV(HashMap* map, char archivo[MAXC]) 
{
	free(map);	//se libera la memoria del mapa de jugadores
	map = createMap(20);	//se crea un nuevo mapa de jugadores
	FILE *csv = fopen(archivo, "r");	//se abre el archivo csv
	if (!csv) {
    	printf("\nEl archivo no existe\n");
    	return;
  	}

  	char buffer[1000];
  	long linea = 0;
  	while (fgets(buffer, sizeof(buffer), csv)) {	//se lee el archivo linea por linea
    	linea++;
    	if (linea == 1) continue;	//se salta la primera linea
    	buffer[strcspn(buffer, "\n") - 1] = 0; // quitar el salto de linea de la linea leida
    
    	int columna = 1;
    	char *valor = strtok(buffer, ",");	//se separa en palabras la linea por comas
        char * nombre = (char *)malloc(sizeof(char)*MAXC);
        int prioridad;
        ArrayList * precedentes = createList();
        Pair * par;
        tarea * precedente;

    	while (valor != NULL) {
    		if (columna == 1){	//se guarda el nombre del jugador
        		strcpy(nombre, valor);
			}
    		if (columna == 2)	//se guarda la habilidad del jugador
                prioridad = (int)strtol(valor, NULL, 10); 	
      		if (columna > 2){
                par = searchMap(map, valor);
                if (par == NULL)    continue;
                precedente = (tarea*)par->value;
                append(precedentes, precedente);
	  		}
			valor = strtok(NULL, " ,");
    		columna++;
    	}
        tarea * tarea = crearTarea(nombre, prioridad);
        tarea->precedentes = precedentes;
    	insertMap(map, tarea->nombre, tarea);	//se agrega el jugador al mapa de jugadores
		printf("\nInserción de linea %ld\n", linea);
  	}

  	printf("\nArchivo importado correctamente\n");
  	fclose(csv);
  	return;
}

