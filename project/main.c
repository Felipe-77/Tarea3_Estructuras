#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backend.h"

#define MAXC 100
#define SEP printf("\n**************************************************\n")


int main(void)
{
    int opcion;
    SEP;
    printf("¡Bienvenid@ al sistema para organizar tareas!\n");

    while (1)
    {
        SEP;
        printf("¿Qué desea hacer?\n\n");
        printf("1) Agregar una tarea nueva\n");
        printf("2) Establecer precedencia\n");
        printf("3) Mostrar tareas por hacer\n");
        printf("4) Marcar tarea como completada\n\n");
        printf("5) Deshacer última acción\n");
        printf("6) Cargar datos de tareas desde un archivo de texto\n\n");
        printf("0) Salir\n\n");
        SEP;
        printf(">");
        scanf("%d", &opcion);
        getchar();

        switch (opcion)
        {
        case 1:
            printf("todo\n");
            break;
        case 2:
            printf("todo\n");
            break;
        case 3:
            printf("todo\n");
            break;
        case 4:
            printf("todo\n");
            break;
        case 5:
            printf("todo\n");
            break;
        case 6:
            printf("todo\n");
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
