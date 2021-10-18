# Para revisar las opciones de compilacion y ejecucion,
# ingrese en el terminal el comando: make
#
#

SHELL=bash -o pipefail

INCLUDE=
CFLAGS=-Wall -Werror -pedantic -std=c18 $(INCLUDE)

# Para Risc-V
RISCV = /opt/riscv
TARGET = riscv64-unknown-elf
CCRV= ${RISCV}/bin/${TARGET}-gcc -march=rv64gc
CCRV32= ${RISCV}/bin/${TARGET}-gcc -march=rv32imafc -mabi=ilp32f
QEMU=qemu-riscv64
QEMU32=qemu-riscv32

MAK=make --no-print-directory

readme:
	@less README.txt

gengrafos.bin-O gengrafos.bin-g gengrafos.bin-san gengrafos.bin32: \
           gengrafos.c pss.c grafo.h pss.h
	$(CC) $(CFLAGS) gengrafos.c pss.c $(LDLIBS) -o $@

testgrafos.bin-O testgrafos.bin-g testgrafos.bin-san testgrafos.bin32: \
           testgrafos.c leergrafo.c pss.c grafo.h pss.h
	$(CC) $(CFLAGS) testgrafos.c leergrafo.c pss.c $(LDLIBS) -o $@

%.gcc-O:
	@$(MAK) "CFLAGS=-O $(CFLAGS)" $(*F).bin-O

%.gcc-g:
	@$(MAK) "CFLAGS=-g $(CFLAGS)" $(*F).bin-g

%.gcc-san:
	@$(MAK) "CFLAGS=-g -fsanitize=address -DSANITIZE $(CFLAGS)" $(*F).bin-san

%.gcc32:
	@$(MAK) "CFLAGS=-O -m32 $(CFLAGS)" $(*F).bin32

run: run-O

run%: gengrafos.gcc% testgrafos.gcc%
	@echo "Generando archivos con grafos"
	./gengrafos.bin$(*F)
	@echo ./testgrafos.bin `cat grafos.txt`
	@./testgrafos.bin$(*F) `cat grafos.txt` > run.log
	@echo diff run.log run.ref
	@diff run.log run.ref && echo "Felicitaciones: Test aprobado"

%.ddd:
	$(MAK) "CFLAGS=-g $(CFLAGS)" $(*F).bin-g
	ddd --command $(*F).gdb $(*F).bin-g &

%.ddd-san:
	$(MAK) "CFLAGS=-g -fsanitize=address -DSANITIZE $(CFLAGS)" $(*F).bin-san
	ddd --command $(*F).gdb $(*F).bin-san &

ddd-x2: gengrafos.ddd
	./gengrafos.bin-g
	cp coquimbo.gf coquimbo-cp.gf
	cp algarrobo.gf algarrobo-cp.gf
	cp antofagasta.gf antofagasta-cp.gf
	cp las-cruces.gf las-cruces-cp.gf
	$(MAK) "CFLAGS=-g $(CFLAGS)" testgrafos.bin-g
	ddd --command testgrafos-cp.gdb testgrafos.bin-g &
	
zip:
	@$(MAK) clean
	@echo ==== make run ==== | tee resultados.txt
	@$(MAK) run |& tee -a resultados.txt
	@echo ==== make run-g ==== | tee -a resultados.txt
	@$(MAK) run-g |& tee -a resultados.txt
	@echo ==== make run-san ==== |& tee -a resultados.txt
	@$(MAK) run-san |& tee -a resultados.txt
	@echo ==== make run32 ==== | tee -a resultados.txt
	@$(MAK) run32 |& tee -a resultados.txt
	@echo ==== zip ====
	zip -r leergrafo.zip resultados.txt leergrafo.c
	@echo "Entregue por u-cursos el archivo leergrafo.zip"

clean:
	rm -f *.o *.log *.bin* *.gf grafos.txt resultados.txt leergrafo.zip
