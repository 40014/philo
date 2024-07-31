NAME = philo

SOURCE = main.c actions.c parsing.c thread.c ft_atoi.c utils.c utils2.c

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3

all: $(NAME)

$(NAME): $(SOURCE)
	cc $(CFLAGS) $(SOURCE) -o $(NAME)

clean:

fclean: clean
	rm -rf $(NAME)

re: fclean all