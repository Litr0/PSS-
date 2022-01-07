=============================================================
Esta es la documentación para compilar y ejecutar su solución
=============================================================

Se está ejecutando el comando: less README.txt

***************************
*** Para salir: tecla q ***
***************************

Para avanzar a una nueva página: tecla <page down>
Para retroceder a la página anterior: tecla <page up>
Para avanzar una sola línea: tecla <enter>
Para buscar un texto: tecla / seguido del texto (/...texto...)
         por ejemplo: /ddd

-----------------------------------------------

Ud. debe crear el archivo volumen.c y programar ahí la función volumen.
Ya hay una plantilla de este archivo en volumen.c.plantilla.

Pruebe su solución bajo Debian 11 de 64 bits.  Su solución funciona
correctamente cuando las ejecuciones make run y make run-g lo felicitan.

Cuando pruebe su solución con make run en su computador asegúrese de que
posea al menos 2 cores, que está configurado en modo alto rendimiento
y que no estén corriendo otros procesos intensivos en uso de CPU al
mismo tiempo.  De otro modo podría no lograr el speed up recomendado.

Para depurar use: make ddd
Esto le permitirá depurar el proceso padre, pero depurar los procesos hijos
requiere usar comandos que no fueron enseñados.  Para depurar los procesos
hijos use printf.

Entrega de esta pregunta: debe entregar el archivo volumen.c.

-----------------------------------------------

Limpieza de archivos

make clean

Hace limpieza borrando todos los archivos que se pueden volver
a reconstruir a partir de los fuentes: *.o binarios etc.

-----------------------------------------------

Acerca del comando make

El comando make sirve para automatizar el proceso de compilación asegurando
recompilar el archivo binario ejecutable cuando cambió uno de los archivos
fuentes de los cuales depende.

A veces es útil usar make con la opción -n para que solo muestre
exactamente qué comandos va a ejecutar, sin ejecutarlos de verdad.
Por ejemplo:

   make -n sort-rv-nbits.ddd

También es útil usar make con la opción -B para forzar la recompilación
de los fuentes a pesar de que no han cambiado desde la última compilación.
Por ejemplo:

   make -B sort-rv-nbits

Recompilará para generar el archivo sort-rv-nbits desde cero
