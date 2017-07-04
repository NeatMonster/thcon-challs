FROM debian:jessie

RUN apt-get update && \
    apt-get -y upgrade && \
    apt-get install -y socat build-essential libc6-dev-i386 && \
    useradd -ms /bin/sh chall

ADD src/* /home/chall/

WORKDIR /home/chall

RUN gcc -m32 -fno-pie -fstack-protector -Wl,-z,relro,-z,now -O2 heapboard.c -o heapboard && \
    strip --strip-all heapboard && \
    chmod 755 heapboard && \
    chmod 644 flag.txt && \
    rm heapboard.c heapboard.h

EXPOSE 5555
CMD socat TCP-LISTEN:5555,fork EXEC:"/home/chall/heapboard",stderr,su=chall
