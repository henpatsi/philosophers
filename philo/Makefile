# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/23 09:47:29 by hpatsi            #+#    #+#              #
#    Updated: 2024/02/23 10:11:22 by hpatsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SOURCES = $(addprefix srcs/, main.c)

OBJECTS = $(SOURCES:.c=.o)

INCLUDES = -I ./includes/

CFLAGS += -Wall -Wextra -Werror -Wunreachable-code -Wpedantic -Wtype-limits -g $(INCLUDES)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	cc $(CFLAGS) $(OBJECTS) -o $(NAME)

$(OBJECTS): $(SOURCES)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all