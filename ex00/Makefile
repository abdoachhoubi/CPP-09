SRC = main.cpp BitcoinExchange.cpp

CC = c++ -std=c++98

FLAGS = -Wall -Wextra -Werror

NAME = btc

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re