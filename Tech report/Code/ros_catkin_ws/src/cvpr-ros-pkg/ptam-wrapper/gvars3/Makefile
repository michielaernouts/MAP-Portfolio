
TOON_DIR=$(shell rospack find toon)

all: checkout configure_make_install

checkout: 
	CVS_RSH=ssh 
	mkdir build
	cd build && cvs -z3 -d:pserver:anonymous@cvs.savannah.nongnu.org:/sources/libcvd co gvars3
	touch checkout

configure_make_install:
	cd build/gvars3 && ./configure --prefix=${PWD} --includedir=${TOON_DIR}/include
	cd build/gvars3 && make
	cd build/gvars3 && make install
	mkdir -p include
	cp -r build/gvars3/gvars3 include
	touch configure_make_install

.PHONY: clean

clean:
	rm -rf checkout configure_make_install build include bin lib

