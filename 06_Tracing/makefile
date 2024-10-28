CC = gcc
CFLAGS = -O0
CC_DEFINES = -D_GNU_SOURCE

IN_FILE = infile.txt
OUT_FILE = outfile.txt

GENERATES = move *${IN_FILE} ${OUT_FILE} *.o *.so

all: move libremove.so test

move: move.c
	$(CC) ${CFLAGS} -o $@ $<

libremove.so: remove.c
	$(CC) ${CFLAGS} $(CC_DEFINES) -shared -o $@ $<

test: move libremove.so
	@cp move.c ${IN_FILE}
	@strace -e fault=openat:when=1 -P ${IN_FILE} ./move ${IN_FILE} ${OUT_FILE} 2> /dev/null || test $$? -eq 1
	@test -f ${IN_FILE}
	@echo "TEST 1 PASSED"
	@strace -e fault=openat:when=1 -P ${OUT_FILE} ./move ${IN_FILE} ${OUT_FILE} 2> /dev/null || test $$? -eq 2
	@test -f ${IN_FILE}
	@echo "TEST 2 PASSED"
	@strace -e fault=unlink:when=1 -y -P ${IN_FILE} ./move ${IN_FILE} ${OUT_FILE} 2> /dev/null || test $$? -eq 5
	@test -f ${IN_FILE}
	@echo "TEST 3 PASSED"
	@cp move.c PROTECT${IN_FILE}
	@LD_PRELOAD=./libremove.so ./move PROTECT${IN_FILE} ${OUT_FILE} 2> /dev/null || test $$? -eq 5
	@test -f PROTECT${IN_FILE}
	@echo "TEST 4 PASSED"

clean:
	rm -rf ${GENERATES}
