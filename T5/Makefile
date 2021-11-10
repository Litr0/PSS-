# Si desea agregar un programa con archivos test-ejemplo.c, ejemplo.c y
# ejemplo.h, agregue un par de reglas que digan:
# test-ejemplo.o ejemplo.o: ejemplo.h
# test-ejemplo: test-ejemplo.o ejemplo.o

RISCV = /opt/riscv
TARGET = riscv64-unknown-elf
CC = ${RISCV}/bin/${TARGET}-gcc
CXX = ${RISCV}/bin/${TARGET}-g++
AS = ${RISCV}/bin/${TARGET}-as
LD = ${RISCV}/bin/${TARGET}-ld
STRIP = ${RISCV}/bin/${TARGET}-strip
GDB = ${RISCV}/bin/${TARGET}-gdb
PK = ${RISCV}/${TARGET}/bin/pk
DUMP= ${RISCV}/${TARGET}/bin/objdump
QEMU32=qemu-riscv32

SHELL=bash
COMFLAGS= -Wall -pedantic -std=c2x -march=rv32im -mabi=ilp32

CFLAGS= -g ${COMFLAGS}
LDFLAGS= -g
LDLIBS=

readme:
	@less README.txt

sort-rv: test-sort.o sort-rv.o

sort-c: test-sort.o sort-c.o

sort-rv-nbits: test-sort.o sort-rv-nbits.o

sort-c-nbits: test-sort.o sort-c-nbits.o

clean:
	rm -f *.o sort-rv sort-rv-nbits sort-c sort-c-nbits

%.o: %.c
	${CC} -g -c ${COMFLAGS} $< -o $@

%.s: %.c
	${CC} -O -S ${COMFLAGS} $<

%.ddd: %
	qemu-riscv32 -g 1234 $(*F) &
	ddd --debugger ${GDB} --command target.gdb $(*F)

%.o: %.s
	${CC} -c ${COMFLAGS} $< -o $@

%: %.o
	${CC} ${COMFLAGS} ${LDFLAGS} $^ ${LDLIBS} -o $@

%.run: %
	qemu-riscv32 $(*F)

%.dump: %
	${DUMP} -S $(*F) | less
