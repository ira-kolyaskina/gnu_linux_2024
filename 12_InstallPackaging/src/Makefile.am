AM_CFLAGS = -Wall

bin_PROGRAMS = main tests

pkgdata_DATA = ./ru/LC_MESSAGES/guess.mo

main_SOURCES = guess.c main.c

tests_SOURCES = tests.c guess.c

ru/LC_MESSAGES/guess.mo: ru.po
	mkdir -p `dirname $@`
	msgfmt $< -o $@

ru.po: guess.pot
	msgmerge -U $@ $<

guess.pot: guess.pot guess.c
	xgettext guess.c -o translate.new.pot
	cp guess.pot $@
	msgmerge -U $@ translate.new.pot

gitclean:
	git clean -xdf
	rm -f *.o *~ o.*