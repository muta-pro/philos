CC = cc

NAME = philo

CFLAGS = -Wall -Wextra -Werror -g3 -pthread

SRC = main.c err.c parser.c philo_life.c utils.c philo_utils.c checks.c

HEAD = head.h

OBJ = $(SRC:.c=.o)

all : $(NAME)
#link rule
$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
#comp rule
%.o: %.c $(HEAD)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re
