GENERATES = create_lab0 create_lab1 create_lab2 create_lab3 create_lab1.c create_lab2.c create_lab3.c

run: create_lab0 create_lab1 create_lab2 create_lab3
	./create_lab0
	./create_lab1 15
	./create_lab2 " #" 15
	./create_lab3 1 " +" 15
	./create_lab3 100 " *" 15

create_lab1.c: create_lab0.c patch1.patch
	patch -b $< patch1.patch
	mv $< $@
	mv $<.orig $<

create_lab2.c: create_lab1.c patch2.patch
	patch -b $< patch2.patch
	mv $< $@
	mv $<.orig $<

create_lab3.c: create_lab2.c patch3.patch
	patch -b $< patch3.patch
	mv $< $@
	mv $<.orig $<

create_lab0: create_lab0.c

create_lab1: create_lab1.c

create_lab2: create_lab2.c

create_lab3: create_lab3.c

clean:
	rm -rf $(GENERATES)