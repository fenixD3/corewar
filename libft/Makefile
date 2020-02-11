# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylila <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/11 03:31:44 by ylila             #+#    #+#              #
#    Updated: 2020/01/31 21:02:08 by yas              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Wextra -Werror

SRCS = ft_strlen.c ft_strcmp.c ft_strncmp.c ft_strcpy.c ft_strncpy.c \
	ft_strcat.c ft_strncat.c ft_strlcat.c ft_strstr.c ft_strnstr.c \
	ft_strchr.c ft_strrchr.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
	ft_isascii.c ft_isprint.c ft_toupper.c ft_isupper.c ft_islower.c \
	ft_tolower.c ft_strdup.c ft_atoi.c ft_memset.c ft_bzero.c ft_memcpy.c \
	ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_memalloc.c \
	ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c \
	ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c \
	ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c \
	ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c \
	ft_lstadd.c ft_lstiter.c ft_lstpush.c ft_pow.c ft_fib.c ft_sqrt.c \
	ft_isdigit.c ft_isspace.c get_next_line.c ft_is_complex_string.c \
	ft_lstcirc_add.c ft_lstcirc_delelem.c ft_lstcirc_findcontent_size.c \
	ft_strjoinre.c ft_strndup.c ft_lstcirc_strnew.c ft_strlcpy.c ft_sstrchr.c \
	go_exit.c

SRC_ML_DIR = memlist/
SRC_ML = ml_create.c ml_del.c ml_general.c

SRCS_ML = $(addprefix $(SRC_ML_DIR),$(SRC_ML))

OBJECTS = $(SRCS:.c=.o)
OBJECTS_ML = $(SRC_ML:.c=.o)

INCLUDE = ./

all: $(NAME)

$(NAME):
	@gcc -c $(SRCS) $(SRCS_ML) $(FLAGS) -I$(INCLUDE)
	@ar rc $(NAME) $(OBJECTS) $(OBJECTS_ML)
	@ranlib $(NAME)

clean:
	@rm -f $(OBJECTS)
	@rm -f $(OBJECTS_ML)

fclean: clean
	@rm -f $(NAME)

re: fclean all
