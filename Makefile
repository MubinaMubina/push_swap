# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/09 20:06:31 by mmubina           #+#    #+#              #
#    Updated: 2026/02/13 02:02:52 by mmubina          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

SRCS_PATH = src/

INC_PATH = includes/

OBJS_PATH = objs/

SRCS = main.c \
	   sort.c \
	   sort_small.c \
	   operations.c \
	   operations_utils.c \
	   stack.c \
	   special_input.c \
	   utils.c \
	   validate_input.c

PATH_LIBFT = ./include/libft/
LIBFT = $(PATH_LIBFT)libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -I $(INC_PATH) -I $(PATH_LIBFT)

OBJS = $(SRCS:%.c=$(OBJS_PATH)%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS_PATH) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c | $(OBJS_PATH)
	$(CC) $(CFLAGS) -I $(INC_PATH) -c $< -o $@ $(INCLUDE)

$(OBJS_PATH):
	mkdir -p $(OBJS_PATH)

$(LIBFT):
	make -C $(PATH_LIBFT) re

clean:
	rm -rf $(OBJS_PATH)
	make -C $(PATH_LIBFT) clean
fclean: clean
	rm -f $(NAME)
	make -C $(PATH_LIBFT) fclean
re: fclean all
.PHONY: all clean fclean re