GENERATES = prog liboutput_static.a liboutput.so prog-a prog-so 
TRASH = *.o *~ o.*
CFLAGS = -Wall -fPIC

all: prog prog-a prog-so test

.SECONDARY:	liboutput_static.a(fun.o const.o)

liboutput_static.a:	liboutput_static.a(fun.o const.o)

liboutput.so: fun.o const.o
	cc -shared -o $@ $^

prog: prog.o fun.o const.o

prog-a: prog.o liboutput_static.a
	cc -o $@ $< -L. -loutput_static

prog-so: prog.o liboutput.so
	cc -o $@ $< -L. -loutput

fun.o prog.o:  outlib.h

test: test0 test1 test2

test0: prog prog-a prog-so
	@echo "TEST ZERO PARAMETRS"
	./prog > t0_output_prog.txt 2> t0_error_prog.txt
	./prog-a > t0_output_prog_a.txt 2> t0_error_prog_a.txt
	LD_LIBRARY_PATH=`pwd` ./prog-so > t0_output_prog_so.txt 2> t0_error_prog_so.txt
	cmp t0_output_prog.txt t0_output_prog_a.txt
	cmp t0_output_prog.txt t0_output_prog_so.txt
	sed 's/prog-a/prog/g' t0_error_prog_a.txt | cmp t0_error_prog.txt
	sed 's/prog-so/prog/g' t0_error_prog_so.txt | cmp t0_error_prog.txt

test1: prog prog-a prog-so
	@echo "TEST ONE PARAMETRS"
	./prog ololo > t1_output_prog.txt 2> t1_error_prog.txt
	./prog-a ololo > t1_output_prog_a.txt 2> t1_error_prog_a.txt
	LD_LIBRARY_PATH=`pwd` ./prog-so ololo > t1_output_prog_so.txt 2> t1_error_prog_so.txt
	cmp t1_output_prog.txt t1_output_prog_a.txt
	cmp t1_output_prog.txt t1_output_prog_so.txt

test2: prog prog-a prog-so
	@echo "TEST THREE PARAMETRS"
	./prog ol o lo > t2_output_prog.txt 2> t2_error_prog.txt
	./prog-a ol o lo > t2_output_prog_a.txt 2> t2_error_prog_a.txt
	LD_LIBRARY_PATH=`pwd` ./prog-so ol o lo > t2_output_prog_so.txt 2> t2_error_prog_so.txt
	cmp t2_output_prog.txt t2_output_prog_a.txt
	cmp t2_output_prog.txt t2_output_prog_so.txt

clean:
	rm -f $(TRASH)

distclean:      clean
	rm -rf $(GENERATES)