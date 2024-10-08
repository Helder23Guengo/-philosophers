NAME = philo

CC = cc

CFLAGS = -g -Wall -Wextra -Werror

RM = rm -f

FILE = philo.c philo_life.c status.c utils.c

OBJS = philo.o philo_life.o status.o utils.o

all: $(NAME)

$(NAME):
	$(CC) $(FILE) -c
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(REF)

clean: 
	$(RM) $(OBJS)

fclean:clean
	$(RM) $(NAME)

re: fclean all

rec: fclean all
	$(RM) $(OBJS)
