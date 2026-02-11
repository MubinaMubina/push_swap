# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/09 20:06:31 by mmubina           #+#    #+#              #
#    Updated: 2026/02/12 01:28:02 by mmubina          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

SRCS_PATH = src/

INC_PATH = includes/

OBJS_PATH = objs/

SRCS = main.c \
       stack.c \
       operations.c \
       rotate.c \
       parser.c \
       utils.c \
       sort.c \
	   operations_utils.c \
	   parser_utils.c \
	   rotate_utils.c \
	   stack_utils.c

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