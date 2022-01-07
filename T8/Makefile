# Para revisar las opciones de compilacion y ejecucion,
# ingrese en el terminal el comando: make
#
#

SHELL=bash -o pipefail

INCLUDE=
CFLAGS=-Wall -Werror -pedantic -std=c18 $(INCLUDE)

MAK=make --no-print-directory

readme:
	@less README.txt

suma.bin suma.bin-g suma.bin-san: suma.c test-suma.c suma.h

run-san: suma.bin-san
	./suma.bin-san

run-g: suma.bin-g
	./suma.bin-g

run: suma.bin
	./suma.bin

ddd: suma.ddd

ddd-san: suma.ddd-san

zip:
	@rm -f resultados.txt suma.zip
	@echo ==== run ==== | tee resultados.txt
	@$(MAK) -B run | tee -a resultados.txt
	@echo ==== run-g ==== | tee -a resultados.txt
	@$(MAK) -B run-g | tee -a resultados.txt
	@echo ==== zip ====
	zip -r suma.zip resultados.txt suma.c
	@echo "Entregue por u-cursos el archivo suma.zip"

%.bin: %.c
	gcc -O -DOPT=1 $(CFLAGS) $^ -o $@

%.bin-g: %.c
	gcc -g $(CFLAGS) $^ -o $@

%.bin-san: %.c
	gcc -g -DSAN=1 -fsanitize=address -DSANITIZE $(CFLAGS) $^ -o $@

%.ddd: %.bin-g
	ddd $(*F).bin-g &

%.ddd-san: %.bin-san
	ddd $(*F).bin-san &

clean:
	rm -f *.o *.log *.bin*
