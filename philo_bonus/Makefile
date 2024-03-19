# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/23 09:47:29 by hpatsi            #+#    #+#              #
#    Updated: 2024/03/19 08:42:43 by hpatsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SOURCES = $(addsuffix _bonus.c, $(addprefix srcs/, main prepare extract_arg \
													start_processes \
													child_start state \
													philo_actions fork_actions \
													better_sleep))

OBJECTS = $(SOURCES:.c=.o)

INCLUDES = -I ./includes/

DEBUG = -g -fsanitize=address

CFLAGS += -Wall -Wextra -Werror -Wpedantic -Wtype-limits $(INCLUDES)

all: $(NAME)

$(NAME): $(OBJECTS)
	cc $(CFLAGS) $(OBJECTS) -o $(NAME)

$(OBJECTS): $(SOURCES)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all