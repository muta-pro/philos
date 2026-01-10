CC = cc

NAME = philo

CFLAGS = -Wall -Wextra -Werror -g3

SRC = main.c err.c parser.c philo_life.c utils.c

HEAD = head.h

OBJ = $(SRC:%.c=%.o)

all : $(NAME)

$(OBJ):
	@mkdir -p $(OBJ)

$(NAME) : $ (OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(HEAD) -c $< -o $@


clean:
	rm -r ${OBJ}
fclean: clean
	rm -f ${NAME}
re: fclean all

.PHONY: all clean fclean re
