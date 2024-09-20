CC = cc 
CFLAG = -Wall -Wextra -Werror #-fsanitize=address -g3
PTHREAD = -pthread
NAME = philo
SRC =  ./philo.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(SRC)
	$(CC) $(CFLAG) $(PTHREAD)  $(SRC) -o $(NAME)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all