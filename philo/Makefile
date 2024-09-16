CC = cc 
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
NAME = philo
SRC = ./src/main.c
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re: