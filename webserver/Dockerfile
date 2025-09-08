# FROM alpine/git as builder

# WORKDIR /app


FROM alpine:latest

# WORKDIR /app


RUN apk add --no-cache --update build-base
# RUN apk add curl

COPY . /home/webserver
# RUN chmod 777 -R /home/webserver
WORKDIR /home/webserver

RUN make re

# COPY . .

# RUN apk add --no-cache make gcc musl-dev

# RUN make
# COPY --from=builder /app/webserv /usr/local/bin/webserv

EXPOSE 8081

# CMD ["webserv" ]

# ENTRYPOINT ["/bin/sh","-c","sleep infinity"]

ENTRYPOINT [ "./webserv" , "config.cfg" ]
