FROM ubuntu:16.10

RUN apt-get update && apt-get -y upgrade
RUN apt-get install -y python2.7 socat
RUN useradd -ms /bin/sh chall

ADD src/script.py /home/chall/script.py
ADD src/flag.txt /home/chall/flag.txt

WORKDIR /home/chall

EXPOSE 5555

CMD socat TCP-LISTEN:5555,fork EXEC:"python2.7 /home/chall/script.py",stderr,user=chall
