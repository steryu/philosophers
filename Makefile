# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svan-ass <svan-ass@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/03 09:47:44 by svan-ass          #+#    #+#              #
#    Updated: 2022/03/16 13:06:26 by svan-ass         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

# -g -fsanitize=thread

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
INCLUDE		= -lpthread

all:		$(NAME)

SRCS 		= main.c \
			thread_utils.c \
			utils.c \
			table.c \
			monitoring.c

OBJS		= $(SRCS:.c=.o)

$(NAME): 	$(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $(NAME)
	@echo "\033[0;32mDone!\n\033[0m"

clean:
	rm -f $(OBJS)

fclean:		clean 
	rm -f $(NAME)
	@echo "\033[0;32mClean!\n\033[0m"

re:			fclean all

.PHONY: 	all clean fclean re