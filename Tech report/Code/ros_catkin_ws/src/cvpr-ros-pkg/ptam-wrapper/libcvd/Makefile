
TOON_DIR=$(shell rospack find toon)

all: checkout configure_make_install

checkout: 
	CVS_RSH=ssh 
	mkdir build
	cd build && cvs -z3 -d:pserver:anonymous@cvs.savannah.nongnu.org:/sources/libcvd co -D "Mon May 11 16:29:26 BST 2009" libcvd
	touch checkout

configure_make_install:
	cd build/libcvd && patch < ../../patch-configure
	cd build/libcvd/cvd_src && patch < ../../../patch-convolution
	cd build/libcvd && ./configure --prefix=${PWD} --includedir=${TOON_DIR}/include --without-ffmpeg
	cd build/libcvd && make
	cd build/libcvd && make install
	mkdir -p include
	cp -r build/libcvd/cvd include
	touch configure_make_install

.PHONY: clean

clean:
	rm -rf checkout configure_make_install build include bin lib

