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

genitemes.bin-O genitemes.bin-g genitemes.bin-san genitemes.bin32: \
           genitemes.c item.h
	$(CC) $(CFLAGS) genitemes.c $(LDLIBS) -o $@

testitemes.bin-O testitemes.bin-g testitemes.bin-san testitemes.bin32: \
           testitemes.c leeritemes.c item.h
	$(CC) $(CFLAGS) testitemes.c leeritemes.c $(LDLIBS) -o $@

%.gcc-O:
	@$(MAK) "CFLAGS=-O $(CFLAGS)" $(*F).bin-O

%.gcc-g:
	@$(MAK) "CFLAGS=-g $(CFLAGS)" $(*F).bin-g

%.gcc-san:
	@$(MAK) "CFLAGS=-g -fsanitize=address -fsanitize=undefined -DSANITIZE $(CFLAGS)" $(*F).bin-san

%.gcc32:
	@$(MAK) "CFLAGS=-O -m32 $(CFLAGS)" $(*F).bin32

run: run-O

run%: genitemes.gcc% testitemes.gcc%
	@echo "Generando archivos con itemes"
	./genitemes.bin$(*F)
	@echo ./testitemes.bin `cat itemes.txt`
	@./testitemes.bin$(*F) `cat itemes.txt` > run.log
	@echo diff run.log run.ref
	@diff run.log run.ref && echo "Felicitaciones: Test aprobado"

%.ddd:
	$(MAK) "CFLAGS=-g $(CFLAGS)" $(*F).bin-g
	ddd --command $(*F).gdb $(*F).bin-g &

%.ddd-san:
	$(MAK) "CFLAGS=-g -fsanitize=address -DSANITIZE $(CFLAGS)" $(*F).bin-san
	ddd --command $(*F).gdb $(*F).bin-san &

ddd: testitemes.ddd

ddd-san: testitemes.ddd-san

ddd-x2: genitemes.ddd
	./genitemes.bin-g
	cp coquimbo.arr coquimbo-cp.arr
	cp algarrobo.arr algarrobo-cp.arr
	cp santiago.arr santiago-cp.arr
	$(MAK) "CFLAGS=-g $(CFLAGS)" testitemes.bin-g
	ddd --command testitemes-cp.gdb testitemes.bin-g &
	
resultados.txt: clean
	@echo ==== make run ==== | tee resultados.txt
	@$(MAK) run |& tee -a resultados.txt
	@echo ==== make run-g ==== | tee -a resultados.txt
	@$(MAK) run-g |& tee -a resultados.txt
	@echo ==== make run-san ==== |& tee -a resultados.txt
	@$(MAK) run-san |& tee -a resultados.txt
	@echo "Felicitaciones: funciono con todas las compilaciones"

clean:
	rm -f *.o *.log *.bin* *.arr itemes.txt resultados.txt core
