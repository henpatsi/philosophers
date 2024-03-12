# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/23 09:47:29 by hpatsi            #+#    #+#              #
#    Updated: 2024/03/12 14:02:04 by hpatsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SOURCES = $(addsuffix _bonus.c, $(addprefix srcs/, main prepare extract_arg \
													start_processes \
													child_start set_philo \
													philo_actions fork_actions \
													better_sleep))

OBJECTS = $(SOURCES:.c=.o)

INCLUDES = -I ./includes/

DEBUG = -g

CFLAGS += -Wall -Wextra -Werror -Wpedantic -Wtype-limits $(INCLUDES) $(DEBUG)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	cc $(CFLAGS) $(OBJECTS) -o $(NAME)

$(OBJECTS): $(SOURCES)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all