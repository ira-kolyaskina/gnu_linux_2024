SUBDIRS = src

all-local: doxygen-clean doxygen-doc

doxygen-doc/man/man1/guess.1: doxygen-doc

man1_MANS = doxygen-doc/man/man1/guess.1

doxygen-clean:
	rm -rf doxygen-doc

doxygen-doc: doxygen-clean
	doxygen Doxyfile

install-data-local:
	mkdir -p $(DESTDIR)/$(docdir)
	cp -a doxygen-doc/html $(DESTDIR)/$(docdir)

http: doxygen-doc
	python3 -m http.server --directory $</html 5000

gitclean:
	git clean -xdf
	rm -f *.o *~ o.*

test:
	./src/tests

install:
	sudo ./sh/install.sh

uninstall:
	sudo ./sh/uninstall.sh