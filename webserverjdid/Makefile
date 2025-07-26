SRC = webserv.cpp main.cpp config.cpp tools.cpp config_parse.cpp singleServer.cpp mime.cpp
NAME = webserv
CPP = c++

CPPFLAGS= # -std=c++98 -Wall -Wextra -Werror #-g -fsanitize=address
MSA7 = rm -rf
OBJ = ${SRC:.cpp=.o}


# .SILENT:
all : ${NAME}

${NAME} : ${OBJ}
	${CPP} ${CPPFLAGS}  ${OBJ} -o $(NAME)
	
%.o: %.cpp
	${CPP} ${CPPFLAGS} -c $< -o $@

test :
	${CPP} test.cpp -o hh && ./hh
tests :
	${CPP} test2.cpp -o hh_specific && ./hh_specific

clean : 
	${MSA7} ${OBJ}

fclean : clean
	${MSA7} ${NAME}

re : fclean all