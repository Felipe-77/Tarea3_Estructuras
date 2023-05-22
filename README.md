# Tarea3_Estructuras

## Sistema organizador de tareas

### Orden del codigo

Tenemos 5 archivos de extension C:
- La libreria de nuestro mapa.
- La libreria de una lista, junto a un stack.
- La librereia de un monticulo.
- Libreria con funciones para poder realizar la tarea asignada.
- Nuestro main, el cual se encarga de la interaccion con el usuario.

Luego podemos observar una carpeta csv:
Esta contiene 1 archivo csv para poder testear nuestro programa.

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
- Marcar tareas como completadas.
- Deshacer la última acción.
### Diseño de la aplicación

La aplicacion usa un mapa que guarda todas las tareas, asi podemos recorrerlas y modificarlas almacenando su clave.

Cada tarea guarda su nombre, su prioridad, y una lista de precedencias.


Ademas para poder ordenar las tareas utilizamos un monticulo binario que determina el orden por prioridad. Este se invoca en un grafo que aprovecha este orden por prioridad y le añade el filtro, de ordenar por precedencia.  
Esta funcionalidad es necesaria para el mostrar.

Para poder guardar acciones pasadas usamos un stack que guarda un dato, y un int. El int nos indica el tipo de accion pasada que ocurrio:
- Agregar Tarea: 1
- Agregar precedencia: 2
- Marcar / Eliminar Tarea: 3
  
  De esta manera al usar deshacer, miraremos el ultimo dato del stack y realizaremos las acciones inversas para poder recrear el estado pasado de el sistema. En el caso de las eliminaciones, se guarda una copia de la tarea para copiar de vuelta.


### Bugs y errores

- Deshacer accion no funciona correctamente con eliminar tarea. Ya que no copia correctamente la lista de precedencia de la tarea anterior.



 ## coevaluacion
 ---



Rubrica Trabajo en equipo:

-    Participacion activa y equitativa: 10

-    Resolucion de conflictos:20

-    Colaboración:13

-    Responsabilidad:11

-    Comunicación:15

Comentario sobre las calificaciones:
Durante este trabajo, nos demoramos mas en empezar a escribir codigo, ya que no nos decidiamos que tipos de TDA usar. Sumado a eso no hubo mucho trabajo en conjunto, sino mas bien, hacer cada uno su parte, mandar el archivo modificado, o subir el commit.


Aun asi hacemos un buen equipo juntos y entendemos bien la forma en que ambos escribimos codigo. Esperamos que en el proyecto podamos ser mas decisivos y directos a la hora de empezar a codificarlo.

Criterio individual:

-    Participación:
-        Manuel: 11
-        Felipe: 17
-    Responsabilidad
-        Manuel: 11
-        Felipe: 17
-    Comunicación
-        Manuel: 18
-        Felipe: 18
-    Calidad del Trabajo
-        Manuel: 17
-        Felipe: 19
-    Trabajo en equipo
-        Manuel: 18
-        Felipe: 18
