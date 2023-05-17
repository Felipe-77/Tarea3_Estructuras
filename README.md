# Tarea3_Estructuras

## Sistema organizador de tareas

### Orden del codigo

Tenemos 5 archivos de extension C:
- La libreria de nuestro mapa.
- La libreria de una lista.
- La librereia de un monticulo.
- Libreria con funciones para poder realizar la tarea asignada.
- Nuestro main, el cual se encarga de la interaccion con el usuario.

Luego podemos observar una carpeta csv:
Esta contiene 2 archivos csv para poder testear nuestro programa.

Además escribímos un script en bash para ejecutar el código más facilmente con el comando:
>sh run.sh

Lo puedes encontrar en la carpeta proyecto.


### Objetivo de la aplicación

Este proyecto creara un sistema para poder almacenar tareas y sus precendcias, además de organizarlas por su prioridad y precedencia correspondiente.
Las tareas serán almacenadas en un mapa de tareas, donde la clave será su nombre y el valor un struct tarea que contiene varios datos de esta, incluyendo una lista de tareas precendentes. 

Deseamos poder realizar una serie de operaciones con la aplicación.

Tal como:

- Agregar tareas y su prioridad (un entero positivo).
- Mostrar tareas ordenadas de la manera en que deben realizarse segun su prioridad y respetando el orden de precedencia,
- Establecer relaciones de precedencia,
- Exportar e importar tareas.
- MArcar tareas como completadas.
- Deshacer la última acción.
### Diseño de la aplicación


 ---


Rubrica Trabajo en equipo:

-    Participacion activa y equitativa: 15

-    Resolucion de conflictos:18

-    Colaboración:18

-    Responsabilidad:18

-    Comunicación:18

Criterio individual:

-    Participación:
-        Manuel: 20
-        Eliseo: 17
-        Felipe: 20
-    Responsabilidad
-        Manuel: 18
-        Eliseo: 17
-        Felipe: 18
-    Comunicación
-        Manuel: 20
-        Eliseo: 18
-        Felipe: 18
-    Calidad del Trabajo
-        Manuel: 20
-        Eliseo: 18
-        Felipe: 19
-    Trabajo en equipo
-        Manuel: 17
-        Eliseo: 17
-        Felipe: 17
