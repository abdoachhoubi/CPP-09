SRC = main.cpp RPN.cpp

CC = c++ -std=c++98

FLAGS = -Wall -Wextra -Werror

NAME = RPN

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re