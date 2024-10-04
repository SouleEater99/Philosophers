CC = cc 
CFLAG = -Wall -Wextra -Werror # -fsanitize=thread -g3
PTHREAD = -pthread
NAME = philo
SRC =	./src/philo.c \
		./src/init.c \
		./src/ft_free.c \
		./src/creat_forks.c \
		./src/utils.c \
		./src/monitor.c \
		./src/write_read_protect.c \
		./src/routine.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAG) $(PTHREAD)  $(SRC) -o $(NAME)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all