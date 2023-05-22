#include "backend.h"
#include "map/map.h"
#include "arraylist/arraylist.h"
#include "heap/heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#define MAXC 10
#define EXPLORADO 2
#define VISITADO 1

//Macros para deshacer acciones
#define AGREGAR_TAREA 1
#define AGREGAR_PRECEDENCIA 2
#define MARCAR_TAREA 3

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

typedef struct accion {
    void* data;
    int tipo;
} accion;


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

int eliminarTarea(HashMap * mapTareas, char id[MAXC])
{
    Pair * par = firstMap(mapTareas);
    if (par == NULL)    return 1;
    tarea * current = par->value;
    while (current != NULL)
    {
        for (int i = 0; i < get_size(current->precedentes); i++)
        {
            tarea * precedente = (tarea*)get(current->precedentes, i);
            if (precedente == NULL) continue;
            if (strcmp(precedente->nombre, id) == 0)
            {
                pop(current->precedentes, i);
                break;
            }
        }
        par = nextMap(mapTareas);
        if (par == NULL)    break;
        current = par->value;
    }
    eraseMap(mapTareas, id);
    return 0;
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
    printf("\nTareas que faltan por hacer, ordenadas de la manera mas eficiente de realizar: \n");
    for (int i = 0; i < get_size(orden); i++)
    {
        node * current = (node*)get(orden, i);
        mostrarTarea(map, current->nombre);
    }
}

int mostrarTarea(HashMap* mapTareas, char id[MAXC])
{
    Pair * par = searchMap(mapTareas, id);
    if (par == NULL)    return 1;
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
    return 0;
}

/*typedef struct accion {
    void* data;
    int tipo;
} accion;
*/
void copyArraylist(ArrayList* a, ArrayList* b)
{
    for (int i = 0; i < get_size(a); i++)
    {
        append(b, get(a, i));
    }
}
void stackUndo(Stack* s, void* data, int tipo)
{
    if (tipo == MARCAR_TAREA)
    {
        tarea* original = (tarea*)data;
        tarea* copy = (tarea*)malloc(sizeof(tarea));
        copy->nombre = original->nombre;
        copy->prioridad	= original->prioridad;
        copy->precedentes = createList();
        copyArraylist(copy->precedentes, original->precedentes);
        pushStack((void*)copy,s);
        return;
    }
    accion *accion = malloc(sizeof(accion));
    accion->data = data;
    accion->tipo = tipo;
    pushStack(s, accion);
}

void deshacerAccion(Stack* s, HashMap* mapTareas)
{
    accion *ultima = (accion*)topStack(s);
    if (ultima == NULL) return;

    switch (ultima->tipo)
    {
        case AGREGAR_TAREA: ;
            //Para agregar tarea se guarda:
            //la id de la tarea para poder eliminar.
        
            eliminarTarea(mapTareas, ultima->data);
            break;
        case AGREGAR_PRECEDENCIA: ;
            //Para agregar precedencia se guarda:
            //un puntero a la tarea almacenda en el mapa de tareas
            //la id no es necesaria, ya que se almacena en ultima posicion
            tarea* current;
            current = (tarea*)ultima->data;
            pop(current->precedentes, -1);

            break;
        case MARCAR_TAREA: ;
            //se guarda una copia de la tarea para poder deshacer   
            tarea* past = (tarea*)ultima->data;
            agregarTarea(mapTareas, past->nombre, past->prioridad);
            tarea* new = searchMap(mapTareas, past->nombre)->value;
            copyArraylist(past->precedentes, new->precedentes);
            break;
    }
    popStack(s);
}


void importarDesdeCSV(HashMap* map, char *archivo) 
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

