# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/23 09:47:29 by hpatsi            #+#    #+#              #
#    Updated: 2024/02/23 09:56:17 by hpatsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SOURCES = $(addprefix srcs, main.c)

OBJECTS = $(SOURCES:.c=.o)

LIBFT = libft/libft.a

INCLUDES = -I ./includes/

CFLAGS += -Wall -Wextra -Werror -Wunreachable-code -Wpedantic -Wtype-limits -g

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	cc $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME)

$(OBJECTS): $(SOURCES)

$(LIBFT):
	make -C ./libft/

clean:
	rm -f $(OBJECTS)
	make clean -C ./libft/

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re: fclean all