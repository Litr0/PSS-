==========================================================
Esta es la documentación para compilar y ejecutar su tarea
==========================================================

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

Requisitos que debe cumplir para poder entregar su tarea

Ejecute bajo Debian 11 en un terminal estos comandos:

    make run
    make run-g
    make run-san
    make run32

Estos comandos compilan y ejecutan para x86 de 64 bits, x86 de 64 bits
con opciones de depuración, x86 de 64 bits con opciones para verificar el
uso correcto de los punteros y x86 de 32 bits respectivamente.

Se exige que estos 4 comandos terminen con el mensaje 'Felicitaciones: ...'.

Si una de las compilaciones falla, lea atentamente el mensaje de error y
edite el archivo con el código fuente para corregir el problema.

Si la compilación es exitosa pero uno de los comandos de más arriba no
termina con felicitaciones, deberá depurar su tarea con uno de estos
comandos que lanza ddd para averiguar qué falló:

    make testgrafos.ddd
    make testgrafos.ddd-san

También le será útil depurar paso a paso gengrafos.c para entender el formato
del archivo que contiene el grafo.  Depure con este comando:

    make gengrafos.ddd

Por último, para verificar que está leyendo los datos en orden correcto,
use este comando:

    make ddd-x2

Se lanzará un ddd para gengrafos.c y otro para testgrafos.c.  Avance paso a
paso en ambos ddd, verificando que cada dato escrito con fwrite, coincide
con el dato leído con fread.

Video con ejemplos de uso de ddd: https://youtu.be/FtHZy7UkTT4
Archivos con los ejemplos: https://www.u-cursos.cl/ingenieria/2020/2/CC3301/1/novedades/r/demo-ddd.zip

Es normal que ddd abra una ventana de diálogo para reclamar porque no
encuentra los fuentes de algunas funciones de biblioteca, como exit.
Ignore el problema presionando el botón OK y continúe.

Otro problema es que es "normal" que al usar ddd junto con sanitize, se produce
un error al terminar la ejecución.  Si es el caso, al abrir el backtrace,
no aparecerá la función main.

-----------------------------------------------

Resumen de opciones de compilación/ejecución:

*** Pruebas para la arquitectura x86 de 64 bits ***
make run : Compila y ejecuta con opciones de optimización
make run-g : Compila y ejecuta con opciones de depuración
make run-san : Compila y ejecuta con opciones para verificar el buen
               uso de punteros
make testgrafos.ddd : Para depurar testgrafos.c con ddd
make testgrafos.ddd-san : Para depurar testgrafos.c con ddd y sanitize
make gengrafos.ddd : Para depurar gengrafos.c con ddd

make ddd-x2 : Para depurar simultáneamente gengrafos.c y testgrafos.c

*** Pruebas para la arquitectura x86 de 32 bits ***
make run32 : Compila y ejecuta con opciones de optimización para x86 de 32 bits

-----------------------------------------------

Entrega de la tarea y los resultados

Ejecute en un terminal: make zip

Se ejecutarán automáticamente: make run, make run-g, make run-san y make run32.
Si todos terminan con felicitaciones, se creará un archivo
leergrafo.zip que contiene el archivo leergrafo.c y otro archivo
resultados.txt con la salida de los 3 comandos de más arriba.
Vaya a U-cursos -> CC3301 -> Tareas -> Tarea 4 y entregue el archivo
leergrafo.zip.

A continuación es muy importante que descargue de U-cursos el mismo
archivo que subió y lo descomprima.  Luego examine los archivos leergrafo.c
y resultados.txt revisando que son los correctos.  Es frecuente que no lo sean
producto de un defecto de U-cursos.

Observación: los ayudantes ejecutarán este mismo comando para probar su tarea
bajo Debian 11.  Si no cumple los requisitos su tarea será rechazada.

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
