# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svan-ass <svan-ass@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/03 09:47:44 by svan-ass          #+#    #+#              #
#    Updated: 2022/03/14 10:58:58 by svan-ass         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

# -fsanitize=thread

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -fsanitize=thread
INCLUDE		= -lpthread

all:		$(NAME)

SRCS 		= main.c \
			utils.c \
			errror.c \
			table.c \

OBJS		= $(SRCS:.c=.o)

$(NAME): 	$(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $(NAME)
	@echo "\033[0;32mDone!"

clean:
	rm -f $(OBJS)

fclean:		clean 
	rm -f $(NAME)
	@echo "\033[0;32mClean!"

re:			fclean all

.PHONY: 	all clean fclean re