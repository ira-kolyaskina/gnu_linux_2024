GENERATES = range
TRASH = *.o *~ o.* gdb_1_out.txt gdb_2_out.txt

range: range.c
	cc -O0 -g -o $@ $<

test: range
	gdb --batch --quiet -x gdb_1 ./range | grep -P "^@@@" > gdb_1_out.txt
	cmp gdb_1_out.txt gdb_1_gold.txt
	gdb --batch --quiet -x gdb_2 ./range | grep -P "^@@@" > gdb_2_out.txt
	cmp gdb_2_out.txt gdb_2_gold.txt
	@echo ALL TESTS PASSED 
	
clean:
	rm -f $(TRASH) $(GENERATES) 