# Para revisar las opciones de compilacion y ejecucion,
# ingrese en el terminal el comando: make
#
#
PROB=dividir
TEST=test-dividir
HEADER=$(PROB)
BIN=bin-g
OPT=-g

SHELL=bash -o pipefail

INCLUDE=
CFLAGS=-Wall -Werror -pedantic -std=c18 $(INCLUDE)
LDLIBS=-lm

MAK=make --no-print-directory

readme:
	@less README.txt

run: bin
	@echo "Midiendo cuanto demora la solucion del profesor"
	rm -f tiempo-ref.txt
	chmod +x prof.ref
	./prof.ref ref > /dev/null
	@echo "Tiempo de referencia = " `cat tiempo-ref.txt`
	@echo "Verificando y comparando con su solucion"
	./$(TEST).bin `cat tiempo-ref.txt`

run-g: bin-g
	./$(TEST).bin-g

run-san: bin-san
	./$(TEST).bin-san

ddd: bin-g
	ddd --command prolog.gdb $(TEST).bin-g &

ddd-san: bin-san
	ddd --command prolog.gdb $(TEST).bin-san &

bin:
	@$(MAK) "OPT=-O -DBENCH=1" BIN=bin $(TEST).$@

bin-g:
	@$(MAK) OPT=-g BIN=bin-g $(TEST).$@

bin-san:
	@$(MAK) "OPT=-g -fsanitize=address -DSANITIZE" BIN=bin-san $(TEST).$@

$(TEST).$(BIN): $(PROB).c $(TEST).c $(HEADER).h
	$(CC) $(OPT) $(CFLAGS) $(PROB).c $(TEST).c $(LDLIBS) -o $@

clean:
	rm -f *.o *.bin* resultados.txt tiempo-ref.txt
