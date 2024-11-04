CFLAGS=-Wall -O2
bin_PROGRAMS=rhasher
rhasher_SOURCES=rhasher.c
TESTS=test

test:
	@echo "MD5 \"Hello,World!" | ./rhasher > ans.txt
	@echo -n "Hello,World!" | md5sum | awk '{print $$1 }' > gold.txt
	@diff ans.txt gold.txt
	@echo "TEST 1 PASSED"

	@echo "SHA1 \"OLOLOLO" | ./rhasher > ans.txt
	@echo -n "OLOLOLO" | sha1sum | awk '{print $$1 }' > gold.txt
	@diff ans.txt gold.txt
	@echo "TEST 2 PASSED"

gitclean:
	rm -rf *.o rhasher
	git clean -df

