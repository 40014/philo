NAME = philo

SOURCE = main.c actions.c parsing.c thread.c ft_atoi.c utils.c utils2.c
OBJECTS = main.o actions.o parsing.o thread.o ft_atoi.o utils.o utils2.o

CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g3

all: $(NAME)

$(NAME): $(OBJECTS)
	cc $(CFLAGS) $(OBJECTS) -o $(NAME)

clean:
	rm -rf $(OBJECTS)
fclean: clean
	rm -rf $(NAME)

re: fclean all
