# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/23 09:47:29 by hpatsi            #+#    #+#              #
#    Updated: 2024/03/05 12:57:09 by hpatsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SOURCES = $(addprefix srcs/, main.c prepare.c mutex_helpers.c \
			philo_start.c monitor.c \
			philo_actions.c fork_actions.c get_philo.c set_philo.c \
			better_sleep.c extract_arg.c)

OBJECTS = $(SOURCES:.c=.o)

INCLUDES = -I ./includes/

DEBUG = -g -fsanitize=thread

CFLAGS += -Wall -Wextra -Werror -Wunreachable-code -Wpedantic -Wtype-limits $(INCLUDES)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	cc $(CFLAGS) $(OBJECTS) -o $(NAME)

$(OBJECTS): $(SOURCES)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all