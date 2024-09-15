CC = cc 
CFLAG = -Wall -Wextra -Werror -fsanitize=address -g3
PTHREAD = -pthread
NAME = philo
SRC =  ./philo.c
OBJ = $(SRC: .c=.o)

all: $(NAME)

$(NAME) : $(SRC)
	$(CC) $(CFLAG) $(PTHREAD) -o $(NAME)
clean :
	rm -rf $(OBJ)
flcean : clean
	rm -rf $(NAME)
re : fclean all