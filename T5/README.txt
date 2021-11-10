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

Modifique la función sort incluida en el archivo assembler sort-rv-nbits.s,
de acuerdo a lo que se pide en el enunciado.

Para compilar y ejecutar bajo Debian 11 ingrese este comando en un terminal: 

   make sort-rv-nbits.run   (o make sort-c-nbits.run para la versión en C)

Se exige que la ejecución termine con el mensaje 'Felicitaciones: ...'.
De otra forma su tarea será rechazada.

Si una de las compilaciones falla, lea atentamente el mensaje de error y
edite el archivo con el código fuente para corregir el problema.

Si la compilación es exitosa pero la ejecución de más arriba no
termina con felicitaciones, deberá depurar su tarea con este comando:

   make sort-rv-nbits.ddd   (o make sort-c-nbits.ddd para la versión en C)

Video con ejemplos de uso de ddd: https://youtu.be/FtHZy7UkTT4
Archivos con los ejemplos: https://www.u-cursos.cl/ingenieria/2020/2/CC3301/1/novedades/r/demo-ddd.zip

La ejecución ya comenzó y se detuvo en la función main de test-sort.c.
Continúe la ejecución con el botón cont.  La salida del programa se muestra
en la ventana del terminal, no en la ventana de ddd.

Si falla uno de los tests, la ejecución se detendrá justo después del
test que falló.  Vaya al menú Status de ddd y seleccione Backtrace para abrir
una ventana con las funciones en ejecución.  Seleccione la función main,
para determinar cuál test falló.

Es normal que ddd abra una ventana de diálogo para reclamar porque no
encuentra los fuentes de algunas funciones de biblioteca, como exit.
Ignore el problema presionando el botón OK y continúe.

-----------------------------------------------

Otras compilaciones disponibles:

make sort-c-nbits.s

Luego edite sort-c-nbits.s para examinar el assembler generado para su
versión en C.

-----------------------------------------------

Entrega de la tarea

Entregue por U-cursos el archivo sort-rv-nbits.s

A continuación es muy importante que descargue de U-cursos el mismo
archivo que subió.  Luego examine el archivo sort-rv.im.s revisando
que es el correcto.  Es frecuente que no lo sea producto de un defecto
de U-cursos.

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
