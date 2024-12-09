.PHONY: build	

build:
	autoreconf -fisv
	./configure
	make

test: build
	./src/tests

install: build
	sudo ./sh/install.sh

uninstall:
	sudo ./sh/uninstall.sh