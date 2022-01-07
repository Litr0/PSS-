# Para revisar las opciones de compilacion y ejecucion,
# ingrese en el terminal el comando: make
#
#

SHELL=bash -o pipefail

INCLUDE=
CFLAGS=-Wall -Werror -pedantic -std=c18 $(INCLUDE)
LDLIBS= -lm

MAK=make --no-print-directory

readme:
	@less README.txt

volumen.bin volumen.bin-g volumen.bin-san: volumen.c test-volumen.c volumen.h

run-san: volumen.bin-san
	./volumen.bin-san

run-g: volumen.bin-g
	./volumen.bin-g

run: volumen.bin
	./volumen.bin

ddd: volumen.ddd

ddd-san: volumen.ddd-san

%.bin: %.c
	gcc -O -DOPT=1 $(CFLAGS) $^ $(LDLIBS) -o $@

%.bin-g: %.c
	gcc -g $(CFLAGS) $^ $(LDLIBS) -o $@

%.bin-san: %.c
	gcc -g -DSAN=1 -fsanitize=address -DSANITIZE $(CFLAGS) $^ $(LDLIBS) -o $@

%.ddd: %.bin-g
	ddd $(*F).bin-g &

%.ddd-san: %.bin-san
	ddd $(*F).bin-san &

clean:
	rm -f *.o *.log *.bin*
