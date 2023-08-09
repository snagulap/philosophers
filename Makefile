# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snagulap <snagulap@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/24 21:07:58 by snagulap          #+#    #+#              #
#    Updated: 2023/07/29 19:36:00 by snagulap         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosopher

CC = gcc

FLAGS = -pthread -Wall -Wextra -Werror -g -fsanitize=thread

SRCS = main.c philo.c utils.c check.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS)
	
%.o: %.c
	$(CC) $(FLAGS) -o $@ -c $<


clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re