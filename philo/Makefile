CC = cc 
CFLAG = -Wall -Wextra -Werror -fsanitize=thread -g3
PTHREAD = -pthread
NAME = philo
SRC =	./philo.c \
		./init.c \
		./ft_free.c \
		./creat_forks.c \
		./utils.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(SRC)
	$(CC) $(CFLAG) $(PTHREAD)  $(SRC) -o $(NAME)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all