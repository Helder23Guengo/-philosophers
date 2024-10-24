# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hguengo <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/23 10:54:49 by hguengo           #+#    #+#              #
#    Updated: 2024/10/23 10:55:00 by hguengo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

FILE = philo.c philo_life.c status.c utils.c utils2.c

OBJS = philo.o philo_life.o status.o utils.o utils2.o

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(FILE) -o $(NAME)

clean: 
	$(RM) $(OBJS)

fclean:clean
	$(RM) $(NAME)

re: fclean all

rec: fclean all
	$(RM) $(OBJS)
