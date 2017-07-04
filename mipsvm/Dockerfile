FROM ubuntu:16.10

RUN apt-get update && apt-get -y upgrade
RUN apt-get install -y build-essential wget zip vim-common

RUN useradd -m build
WORKDIR /home/build

RUN wget https://ftp.gnu.org/gnu/binutils/binutils-2.27.tar.gz && \
    tar -xvzf binutils-2.27.tar.gz && \
    cd binutils-2.27 && \
    mkdir build && \
    cd build && \
    ../configure --target=mipsel-elf --disable-nls && \
    make && \
    make install && \
    cd ../.. && \
    wget http://www.netgull.com/gcc/releases/gcc-6.3.0/gcc-6.3.0.tar.gz && \
    tar -xvzf gcc-6.3.0.tar.gz && \
    cd gcc-6.3.0 && \
    wget http://www.mpfr.org/mpfr-current/mpfr-3.1.5.tar.gz && \
    tar -xvzf mpfr-3.1.5.tar.gz && \
    mv mpfr-3.1.5 mpfr && \
    wget https://ftp.gnu.org/gnu/mpc/mpc-1.0.3.tar.gz && \
    tar -xvzf mpc-1.0.3.tar.gz && \
    mv mpc-1.0.3 mpc && \
    wget https://gmplib.org/download/gmp/gmp-6.1.2.tar.bz2 && \
    tar -xjvf gmp-6.1.2.tar.bz2 && \
    mv gmp-6.1.2 gmp && \
    mkdir build && \
    cd build && \
    ../configure --target=mipsel-elf --enable-languages=c --without-headers --disable-nls && \
    make all-gcc && \
    make install-gcc && \
    make all-target-libgcc && \
    make install-target-libgcc && \
    cd .. && \
    rm -rf binutils-2.27 gcc-6.3.0

COPY Makefile ./
COPY src/* src/
COPY lib/* lib/
RUN make build
