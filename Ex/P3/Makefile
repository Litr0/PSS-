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
QEMU32=qemu-riscv32

SHELL=bash
COMFLAGS= -Wall -pedantic -std=c18 -march=rv32im -mabi=ilp32

CFLAGS= -g ${COMFLAGS}
LDFLAGS= -g
LDLIBS=

readme:
	@less README.txt

clean:
	rm -f *.o

%.o: %.c
	${CC} -g -c ${COMFLAGS} $< -o $@

%.s: %.c
	${CC} -O -S ${COMFLAGS} $<

%.o: %.s
	${CC} -c ${COMFLAGS} $< -o $@

%.o: %.S
	${CC} -c ${COMFLAGS} $< -o $@

%: %.o
	${CC} ${COMFLAGS} ${LDFLAGS} $^ ${LDLIBS} -o $@

%.qemu: %
	${QEMU32} $(*F)
