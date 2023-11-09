# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/09 17:14:47 by kle-rest          #+#    #+#              #
#    Updated: 2023/11/09 15:14:26 by kle-rest         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra

LIBFT = libft.a
LIBFT_DIR = libft
LIB = $(addprefix $(LIBFT_DIR)/, $(LIBFT))

SOURCES_MAN = main.c \
				error.c \
				command.c \
				free.c \

SOURCES_MAN_DIR = mandatory
SOURCES = $(addprefix $(SOURCES_MAN_DIR)/, $(SOURCES_MAN_DIR))

OBJECTS_MAN = $(SOURCES_MAN:.c=.o)

SOURCES_BONUS = main_bonus.c \
				error_bonus.c \
				here_doc.c \
				free_bonus.c \

BONUS_DIR = bonus
BONUS = $(addprefix $(BONUS_DIR)/, $(SOURCES_BONUS))

OBJECTS_BONUS = $(SOURCES_BONUS:.c=.o)

$(NAME): $(OBJECTS_MAN)
				make -C $(LIBFT_DIR)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS_MAN) $(LIB)

all: $(NAME)

bonus: $(OBJECTS_BONUS)
				make -C $(LIBFT_DIR)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS_BONUS) $(LIB)

clean:
	rm -f $(OBJECTS)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: clean all

.PHONY: all clean fclean re