#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backend.h"
#include "map/map.h"
#include "heap/heap.h"

#define MAXC 20
#define SEP printf("\n**************************************************\n")





int main(void)
{
    int opcion;
    char id[MAXC];
    char precedente[MAXC];
    char archivo[30];
    int prioridad;
    HashMap * mapTareas = createMap(20);
    SEP;
    printf("¡Bienvenid@ al sistema para organizar tareas!\n");

    while (1)
    {
        SEP;
        printf("¿Qué desea hacer?\n\n");
        printf("1) Agregar una tarea nueva\n");
        printf("2) Establecer precedencia\n");
        printf("3) Mostrar tareas por hacer\n");
        printf("4) Marcar tarea como completada y eliminar\n\n");
        printf("5) Deshacer última acción\n");
        printf("6) Cargar datos de tareas desde un archivo de texto\n\n");
        printf("7) Mostrar una tarea\n");
        printf("0) Salir\n\n");
        SEP;
        printf(">");
        scanf("%d", &opcion);
        getchar();

        switch (opcion)
        {
        case 1:
            SEP;
            printf("Ingrese el nombre de la tarea:\n");
            scanf("%10[^\n]s", id);
            getchar();
            printf("Ingrese la prioridad de la tarea:\n");
            scanf("%d", &prioridad);
            getchar();

            if (agregarTarea(mapTareas, id, prioridad) == 0)
                printf("\nTarea agregada con éxito!\n");
            else
                printf("\nHa ocurrido un error al agregar la tarea\n");
            break;
            
        case 2:
            SEP;
            printf("Ingrese el nombre de la tarea a modificar:\n");
            scanf("%10[^\n]s", id);
            getchar();
            printf("Ingrese la prioridad de la tarea precedente:\n");
            scanf("%10[^\n]s", precedente);
            getchar();

            if (agregarPrecedencia(mapTareas, id, precedente) == 0)
                printf("\nPrecedencia añadida con éxito!\n");
            else
                printf("\nHa ocurrido un error al agregar la precedencia\n");
            break;
        case 3:
            SEP;
            mostrarTareasPorHacer(mapTareas);
            break;
        case 4:
            SEP;
            printf("Ingrese el nombre de la tarea a eliminar:\n");
            scanf("%10[^\n]s", id);
            getchar();

            if (eliminarTarea(mapTareas, id) == 0)
                printf("\nTarea eliminada con éxito!\n");
            else
                printf("\nHa ocurrido un error al eliminar la tarea\n");
            break;
        case 5:
            printf("todo\n");

            break;
        case 6:
            SEP;
            printf("Ingrese el nombre del archivo:\n");
            scanf("%30[^\n]s", archivo);
            getchar();

            importarDesdeCSV(mapTareas, archivo) ;
            break;
        case 7:
            SEP;
            printf("Ingrese el nombre de la tarea a mostrar:\n");
            scanf("%10[^\n]s", id);
            getchar();

            if (mostrarTarea(mapTareas, id) != 0)
                printf("\nLa tarea no se encuentra en el sistema...\n");
            
            break;
        case 0:
            printf("\n¡Hasta luego!\n");
            return 0;
            break;
        default:
            printf("Opción inválida\n");
            break;
        }
    }

    return 0;
}



