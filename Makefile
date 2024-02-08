SRCS = main.cpp 
NAME = ft_irc
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 
CXX = c++
OBJS = ${SRCS:.cpp=.o}

all:	${NAME}

${NAME}: ${OBJS}
	${CXX} ${CXXFLAGS} ${SRCS} -g -o ${NAME}

clean:
	rm -f ${OBJS}

fclean:	clean
	rm -f ${NAME}

re:	fclean all