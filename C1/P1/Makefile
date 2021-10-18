# Para revisar las opciones de compilacion y ejecucion,
# ingrese en el terminal el comando: make
#
#
PROB=suma-dec
TEST=test
HEADER=$(PROB)
BIN=bin-g
OPT=-g

SHELL=bash -o pipefail

INCLUDE=
CFLAGS=-Wall -Werror -pedantic -std=c18 $(INCLUDE)
LDLIBS=-lm

# Para Risc-V
RISCV = /opt/riscv
TARGET = riscv64-unknown-elf
RVCC= ${RISCV}/bin/${TARGET}-gcc -march=rv64gc
RV32CC= ${RISCV}/bin/${TARGET}-gcc -march=rv32imafc -mabi=ilp32f
QEMU=qemu-riscv64
QEMU32=qemu-riscv32

MAK=make --no-print-directory

readme:
	@less README.txt

run: bin
	./$(TEST).bin

run-g: bin-g
	./$(TEST).bin-g

run-san: bin-san
	./$(TEST).bin-san

run32: bin32
	./$(TEST).bin32

run32-g: bin32-g
	./$(TEST).bin32-g

runrv32: binrv32
	$(QEMU32) $(TEST).binrv32

runrv: binrv
	$(QEMU) $(TEST).binrv

ddd: bin-g
	ddd --command prolog.gdb $(TEST).bin-g &

ddd32: bin32-g
	ddd --command prolog.gdb $(TEST).bin32-g &

ddd-san: bin-san
	ddd --command prolog.gdb $(TEST).bin-san &

resultados.txt: clean
	@echo ==== make run ==== | tee resultados.txt
	@$(MAK) run |& tee -a resultados.txt
	@echo ==== make run-g ==== | tee -a resultados.txt
	@$(MAK) run-g |& tee -a resultados.txt
	@echo ==== make run-san ==== |& tee -a resultados.txt
	@$(MAK) run-san |& tee -a resultados.txt
	@echo "Felicitaciones: su solucion es correcta con las 3 compilaciones"
	@echo "Los resultados estan en el archivo resultados.txt"

bin:
	@$(MAK) "OPT=-O -DBENCH=1" BIN=bin $(TEST).$@

bin-g:
	@$(MAK) OPT=-g BIN=bin-g $(TEST).$@

bin-san:
	@$(MAK) "OPT=-g -fsanitize=undefined -DSANITIZE" BIN=bin-san $(TEST).$@


$(TEST).$(BIN): $(PROB).c $(TEST).c $(HEADER).h
	$(CC) $(OPT) $(CFLAGS) $(PROB).c $(TEST).c $(LDLIBS) -o $@

clean:
	rm -f *.o *.bin* resultados.txt tiempo-ref.txt
