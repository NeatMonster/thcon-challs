FROM debian:jessie

RUN apt-get update && \
    apt-get -y upgrade && \
    apt-get install -y default-jdk maven tomcat7

COPY src/ /home/tomcat7/

WORKDIR /home/tomcat7/

RUN mvn package && \
    cp target/Useless.war /var/lib/tomcat7/webapps/ROOT.war && \
    rm -rf /var/lib/tomcat7/webapps/ROOT/ && \
    rm -rf /home/tomcat7/*

ADD src/flag.txt /home/tomcat7/

EXPOSE 8080
CMD service tomcat7 start && tail -f /var/log/tomcat7/*
