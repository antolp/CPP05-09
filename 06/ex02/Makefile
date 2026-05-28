CXX      ?= c++
CXXFLAGS  = -Wall -Wextra -Werror -std=c++98 -I.

NAME = ex02
SRC  = main.cpp main.cpp Base.cpp
OBJ  = $(SRC:.cpp=.o)

all: $(NAME)	

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
.PHONY: all clean fclean re
 