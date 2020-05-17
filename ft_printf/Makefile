# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylila <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/11 03:21:36 by ylila             #+#    #+#              #
#    Updated: 2019/08/17 21:15:43 by mdeanne          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
LIB_NAME = ./libft/libft.a

FLAGS = -Wall -Wextra -Werror

SRC_GEN = ./srcs/
SRC_FLOAT = ./srcsFloat/
HEAD_PATH = ./includes/
LIB_PATH = ../libft/

OBJS = $(SRC_FILES_GEN:.c=.o) $(SRC_FILES_FLOAT:.c=.o)

HEADERS_PRTF = $(addprefix $(HEAD_PATH),$(HEADERS_NAME))

print-%:
	@echo $*=$($*)

vpath %.c ./srcs ./srcsFloat

all: $(NAME)

$(NAME): $(LIB_NAME) $(OBJS)
	@cp ../libft/libft.a ./$(NAME)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

$(LIB_NAME):
	@make -C $(LIB_PATH)

$(OBJS): %.o: %.c $(HEADERS_PRTF)
	@gcc -c $< -I$(HEAD_PATH) -I$(LIB_PATH) $(FLAGS) -O3 -o $@
#	@gcc -c $< -I$(HEAD_PATH) -I$(LIB_PATH) -O3 -o $@

.PHONY: clean fclean re
clean:
	@rm -f $(OBJS)
	@make -C $(LIB_PATH) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIB_PATH) fclean

re: fclean all
