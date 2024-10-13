GENERATES = range
TRASH = *.o *~ o.* tmp_file 

range: range.c
	cc -O0 -g -o $@ $<

test: range
	gdb --batch --quiet -x gdb_1 ./range | grep -P "^@@@" > gdb1_out.txt
	gdb --batch --quiet -x gdb_2 ./range | grep -P "^@@@" > gdb2_out.txt

	
clean:
	rm -f $(TRASH) $(GENERATES) 