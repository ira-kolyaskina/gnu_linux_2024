GENERATES = esub esub*.txt sed*.txt

all: test

esub: esub.c

test1: esub
	@./$< 'user' 'OLOLO' 'Hello, user' > esub1.txt
	@echo 'Hello, user' | sed -E 's/user/OLOLO/' > sed1.txt
	@cmp esub1.txt sed1.txt
	@echo "TEST 1 PASSED"

test2: esub
	@./$< '([0-9][0-9]*)' '<\1>' 'Sat Oct 19 23:49:05 MSK 2024' > esub2.txt
	@echo 'Sat Oct 19 23:49:05 MSK 2024' | sed -E 's/([0-9][0-9]*)/<\1>/' > sed2.txt
	@cmp esub2.txt sed2.txt
	@echo "TEST 2 PASSED"

test3: esub
	@./$< '(a.*b)' '#\\1\\#' '12aaabbb3' > esub3.txt
	@echo '12aaabbb3' | sed -E 's/(a.*b)/#\\1\\#/' > sed3.txt
	@cmp esub3.txt sed3.txt
	@echo "TEST 3 PASSED"

test4: esub
	@./$< '([0-9]+)th' '(\1-3)' 'This is 4th test' > esub4.txt
	@echo 'This is 4th test' | sed -E 's/([0-9]+)th/(\1-3)/' > sed4.txt
	@cmp esub4.txt sed4.txt
	@echo "TEST 4 PASSED"

test: test1 test2 test3 test4

clean:
	rm -rf ${GENERATES}