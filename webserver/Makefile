SRC = ./sources/webserv.cpp ./sources/main.cpp ./sources/config.cpp ./sources/tools.cpp ./sources/config_parse.cpp ./sources/singleServer.cpp ./sources/mime.cpp ./sources/reqobject.cpp ./sources/clients_tools.cpp ./sources/cgi.cpp
OBJS = ./obj/webserv.o ./obj/main.o ./obj/config.o ./obj/tools.o ./obj/config_parse.o ./obj/singleServer.o ./obj/mime.o ./obj/reqobject.o ./obj/clients_tools.o ./obj/cgi.o
NAME = webserv
CPP = g++
LDFLAGS  = -ljsoncpp
CPPFLAGS= -std=c++11 -I/usr/include/jsoncpp -g  #-fsanitize=address
MSA7 = rm -rf
# OBJ = ${SRC:.cpp=.o}


# .SILENT:
all : folder ${NAME}

${NAME} : ${OBJS}
	${CPP} ${CPPFLAGS}  ${OBJS} -o $(NAME) ${LDFLAGS}
	
./obj/%.o: ./sources/%.cpp
	${CPP} ${CPPFLAGS} -c $< -o $@

folder:
	if [ ! -d "obj/" ]; then \
		mkdir obj; \
	fi \

clean : 
	${MSA7} ${OBJS}
	rm -rf obj

fclean : clean
	${MSA7} ${NAME}

re : fclean all