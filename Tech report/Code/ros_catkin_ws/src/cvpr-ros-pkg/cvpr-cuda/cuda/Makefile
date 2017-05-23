all: install


TOOLKIT_VERSION=4.1
UBUNTU_VERSION=12.04

TOOLKIT_VERSION_US=`echo ${TOOLKIT_VERSION} | tr . _`
BITS=`if test "x86_64" = "\`arch\`"; then echo 64; else echo 32; fi`


TOOLKIT_URL=http://developer.download.nvidia.com/compute/cuda/4_1/rel/toolkit/cudatoolkit_4.1.28_linux_64_ubuntu11.04.run
SDK_URL=http://developer.download.nvidia.com/compute/cuda/4_1/rel/sdk/gpucomputingsdk_4.1.28_linux.run

.PHONY : clean download catch

download:
	mkdir -p tmp
	cd tmp && wget -c $(TOOLKIT_URL)
	cd tmp && wget -c $(SDK_URL)

install: download
	mkdir -p cuda
	if [ ! -f cuda/include/cuda.h ]; then \
	  sudo apt-get install expect-dev; \
	  chmod +x tmp/cudatoolkit_4.1.28_linux_64_ubuntu11.04.run; \
	  ./unpack_cudatoolkit.sh "`pwd -P`/cuda"; \
	fi
	if [ ! -f sdk/shared/common.mk ]; then \
	  sh tmp/gpucomputingsdk_4.1.28_linux.run -- --prefix=`pwd -P`/sdk --cudaprefix=`pwd -P`/cuda; \
	  mv sdk/C/common/common.mk sdk/C/common/common.mk.bak; \
	  sed 's/-lcuda /-L\/usr\/lib\/nvidia-current -lcuda /g' sdk/C/common/common.mk.bak > sdk/C/common/common.mk; \
#          make -C sdk/C; \
	  make -C sdk/C/common; \
          cd sdk/C/lib; \
          ln -s libcutil_x86_64.a libcutil.a; \
          cd ../../..; \
	  make -C sdk/shared; \
          make -C sdk/OpenCL/common; \
	fi

