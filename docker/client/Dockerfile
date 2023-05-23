FROM ubuntu:latest

WORKDIR /opt/tlsClient

RUN apt-get clean && apt-get update --allow-insecure-repositories
RUN apt-get install -y telnet net-tools --allow-unauthenticated

COPY ./cert/ca.crt /opt/tlsClient/cert/
COPY ./cert/client.key /opt/tlsClient/cert/
COPY ./cert/client.crt /opt/tlsClient/cert/
COPY ./release/tlsclient /opt/tlsClient/
COPY ./lib/ /opt/tlsClient/lib/