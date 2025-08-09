NAME=philo
CC=gcc
CFLAGS=-Wall -Wextra -Werror
SRC=philo.c srcs/atoi.c srcs/check_arguments.c srcs/is_number.c srcs/parse_arguments.c srcs/routine.c srcs/monitor.c
OBJ= $(SRC:.c=.o)

all: $(NAME)
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
valgrind:
	make
	valgrind -s --leak-check=full --track-origins=yes ./$(NAME) $(PARAMS)
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re:fclean all

.PHONY:all clean fclean re