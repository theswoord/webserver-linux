FROM alpine:latest

RUN apk add --no-cache --update build-base
# RUN apk add curl

COPY . /home/webserver
RUN chmod 777 -R /home/webserver
WORKDIR /home/webserver

RUN make re
EXPOSE 8082

# ENTRYPOINT ["tail", "-f", "/dev/null"]

CMD [ "ls" , "-la" ]
# ENTRYPOINT [ "/home/webserver/webserv","/home/webserver/config.cfg" ]
# ENTRYPOINT [ "cat","config.cfg" ]
ENTRYPOINT [ "./entrypoint.sh" ]

