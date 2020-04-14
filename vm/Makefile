NAME_FILE = corewar

LIB_PRINTF = ../ft_printf/libftprintf.a
LIB_PRINTF_NAME = -lftprintf
LIB_PRINTF_PATH = ../ft_printf/
LIB_PRINTF_INCL = ../ft_printf/includes/

LIBFT_NAME = -lft
LIB_PATH = ../libft/

LIB_SDL_NAME = -F ../ -framework SDL2
LIB_SDL_TTF_NAME = -F ../ -framework SDL2_ttf
LIB_SDL_PATH = ../SDL2.framework/
LIB_SDL_TTF_PATH = ../SDL2_ttf.framework
LIB_SDL_INCL = ../SDL2.framework/Headers/
LIB_SDL_TTF_INCL = ../SDL2_ttf.framework/Headers/

SRCS = main.c args_intf.c game.c game_intf.c helper_func.c instuctions.c create_vs.c display_carriages.c \
	display_side_menu.c init_sdl.c print_arena.c support_func.c visualise_arena.c carriage_intf.c corewar_intf.c \
	parse_input_intf.c parse_inputs.c reports.c

OBJS = $(SRCS:.c=.o)

HEADER_PATH = ./includes/
HEADER_FILES = error_defs.h vis.h vis_errors.h vm.h
HEADER_PATH_OP = ../
HEADER_FILES_OP = op.h options.h
HEADERS = $(addprefix $(HEADER_PATH),$(HEADER_FILES)) $(addprefix $(HEADER_PATH_OP),$(HEADER_FILES_OP))

vpath %.c ./srcs/game ./srcs/game/vis ./srcs/struct_intf ./srcs/validation ./srcs

all: $(NAME_FILE)

$(NAME_FILE): $(LIB_PRINTF) $(OBJS)
	@gcc -o $(NAME_FILE) $(OBJS) -L$(LIB_PATH) $(LIBFT_NAME) -L$(LIB_PRINTF_PATH) $(LIB_PRINTF_NAME) \
	-L$(LIB_SDL_PATH) $(LIB_SDL_NAME) -L$(LIB_SDL_TTF_PATH) $(LIB_SDL_TTF_NAME)

$(LIB_PRINTF):
	@make -C $(LIB_PRINTF_PATH)

$(OBJS): %.o: %.c $(HEADERS)
	@gcc -c $< -I$(HEADER_PATH) -I$(HEADER_PATH_OP) -I$(LIB_PATH) -I$(LIB_PRINTF_INCL) -I$(LIB_SDL_INCL) -I$(LIB_SDL_TTF_INCL) -O3 -o $@

.PHONY: clean fclean re
clean:
	@rm -f $(OBJS)
	@make -C $(LIB_PRINTF_PATH) clean

fclean: clean
	@rm -f $(NAME_FILE)
	@make -C $(LIB_PRINTF_PATH) fclean

re: fclean all
