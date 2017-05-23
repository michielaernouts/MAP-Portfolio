

all: checkout configure_make_install

checkout: 
	CVS_RSH=ssh 
	mkdir build
	cd build && cvs -z3 -d:pserver:anonymous@cvs.savannah.nongnu.org:/sources/toon co -D "Mon May 11 16:29:26 BST 2009" TooN
	touch checkout

configure_make_install:
	cd build/TooN && ./configure --prefix=${PWD}
	cd build/TooN && make
	cd build/TooN && make install
	touch configure_make_install

.PHONY: clean

clean:
	rm -rf checkout configure_make_install build include

