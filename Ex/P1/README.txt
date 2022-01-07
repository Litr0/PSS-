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

Ud. debe crear el archivo corregir.c y programar ahí la función corregir.
Ya hay una plantilla de este archivo en corregir.c.plantilla.

Pruebe su solución bajo Debian 11 de 64 bits.  Su solución funciona
correctamente cuando las ejecuciones make run-san, make run y make run-g
lo felicitan.  Make run-san no debe reportar errores de manejo de memoria.

Cuando pruebe su solución con make run en su computador asegúrese
de que está configurado en modo alto rendimiento y que no estén
corriendo otros procesos intensivos en uso de CPU al mismo tiempo.
De otro modo las medidas de desempeño podrían verse alteradas.

Para depurar use: make ddd

Entrega de esta pregunta: debe entregar el archivo corregir.c.

-----------------------------------------------

Limpieza de archivos

make clean: hace limpieza borrando todos los archivos que se pueden volver
            a reconstruir a partir de los fuentes: *.o *.bin etc.

-----------------------------------------------

Acerca del comando make

El comando make sirve para automatizar el proceso de compilación asegurando
recompilar el archivo binario ejecutable cuando cambió uno de los archivos
fuentes de los cuales depende.

La especificación de los archivos de los cuales depende está en el archivo
Makefile, que es muy complicado de entender.  Es el profesor el que los
elabora.

Durante la invocación, make muestra los comandos que está ejecutando,
junto a otros mensajes.  Ud. puede invocar manualmente estos comandos
en el terminal y obtendrá el mismo resultado, si los invoca en el
mismo orden.

A veces es útil usar make con la opción -n para que solo muestre
exactamente qué comandos va a ejecutar, sin ejecutarlos de verdad.
Por ejemplo en la tarea 1, para determinar qué comandos ejecutará make run,
esto es lo que mostrará la invocación de: make clean; make -n run

  cc -O  recortar.c test-recortar.c -lm -o test-recortar.bin
  echo "Midiendo cuanto demora la solución del profesor"
  rm -f tiempo-ref.txt
  ./prof.binref ref | tee tiempo-ref.txt
  echo "Verificando y comparando con su solución"
  ./test-recortar.bin `cat tiempo-ref.txt`

También es útil usar make con la opción -B para forzar la recompilación
de los fuentes a pesar de que no han cambiado desde la última compilación.
Por ejemplo:

make -B run

Recompilará para generar el archivo test-recortar.bin
Si a continuación invoca:

make run

No recompilará nada porque los fuentes no han cambiado desde la última
compilación.  Solo ejecutará el binario.  Este ahorro no es relevante en
esta tarea que consiste en solo 2 archivos fuentes.  Pero un programa
grande puede consistir en cientos o miles de archivos y recompilar
todo puede tomar mucho tiempo.  Si se se cambia un solo archivo, make
solo recompilará lo que dependa de ese archivo economizando un tiempo
considerable.

Si ahora invoca:

make -B run

Se recompilará nuevamente todo, producto de la opción -B, a pesar de que
los fuentes no han cambiado.
