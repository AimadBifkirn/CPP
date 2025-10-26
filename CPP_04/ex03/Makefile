NAME = ex03
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = main.cpp AMateria.cpp Character.cpp Cure.cpp Ice.cpp ICharacter.cpp IMateriaSource.cpp MateriaSource.cpp

OBJ = ${SRC:.cpp=.o}

all: ${NAME}

%.o:%.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

${NAME}: ${OBJ}
	${CXX} ${CXXFLAGS} ${OBJ} -o ${NAME}

clean: 
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all