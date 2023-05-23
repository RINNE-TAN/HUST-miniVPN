FROM ubuntu:latest

WORKDIR /opt/tlsServer

RUN apt-get clean && apt-get update --allow-insecure-repositories
RUN apt-get install -y telnet net-tools --allow-unauthenticated
RUN useradd test && echo 'test:123456' | chpasswd

COPY ./cert/ca.crt /opt/tlsServer/cert/
COPY ./cert/server.key /opt/tlsServer/cert/
COPY ./cert/server.crt /opt/tlsServer/cert/
COPY ./release/tlsserver /opt/tlsServer/
COPY ./lib/ /opt/tlsServer/lib/