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

SRCS = main.c args_intf.c game.c game_intf.c helper_func.c instr_fork_zjmp_live_aff.c instr_ld.c instr_operations.c \
	instr_st.c print_fork_zjmp_live_aff.c print_v_4_flg.c print_v_flg.c print_v_ld.c print_v_operations.c print_v_st.c carriage_intf.c \
	corewar_intf.c parse_input_intf.c parse_inputs.c reports.c create_vs.c disasm.c disasm_funcs.c display_carriages.c \
	display_game_data.c display_side_menu.c draw_frame.c higlight_cells.c init_sdl.c print_arena.c support_func.c \
	track_events.c vc_list.c vc_sort.c visualise_arena.c

OBJS = $(SRCS:.c=.o)

HEADER_PATH = ./includes/
HEADER_FILES = error_defs.h vis.h vis_errors.h vm.h
HEADER_PATH_OP = ../
HEADER_FILES_OP = op.h options.h
#HEADER_PATH_ASM = ../asm/
#HEADER_FILES_ASM = asm.h
HEADERS = $(addprefix $(HEADER_PATH),$(HEADER_FILES)) $(addprefix $(HEADER_PATH_OP),$(HEADER_FILES_OP))

# For libftprintf
export SRC_FILES_GEN = field_len.c fill_union.c ft_itoa_base_printf.c ft_printf.c get_binary.c is_parser.c is_typeflags.c \
	make_field.c parsing_funcs.c parsing_generaly.c prepare_lennum.c set_buff.c set_flags.c str_tolower.c \
	to_buff.c which_sign.c zeroing.c

export SRC_FILES_FLOAT = check_create_float_res.c e_flag_intf.c float_intf.c float_rounding.c frees_for_float.c ft_log10.c \
	ft_log2.c g_flag_intf.c get_dbl_values.c get_ldbl_values.c high_precision.c high_precision_intf.c \
	high_precision_intf_long.c high_precision_long.c my_float.c my_long_float.c print_reserve_dbl.c

export HEADERS_NAME = ft_ptintf.h high_precision.h my_float.h

PREREQUISITE_FT_PRINTF = $(SRC_FILES_GEN) $(SRC_FILES_FLOAT) $(HEADERS_NAME)

vpath %.c ./srcs/game ./srcs/game/vis ./srcs/struct_intf ./srcs/validation ./srcs ../ft_printf/srcs ../ft_printf/srcsFloat
vpath %.h ../ft_printf/includes

.PHONY: clean fclean re #$(LIB_PRINTF) #1st var
all: $(NAME_FILE)

$(NAME_FILE): $(LIB_PRINTF) $(OBJS)
	gcc -o $(NAME_FILE) $(OBJS) -L$(LIB_PATH) $(LIBFT_NAME) -L$(LIB_PRINTF_PATH) $(LIB_PRINTF_NAME) \
	-L$(LIB_SDL_PATH) $(LIB_SDL_NAME) -L$(LIB_SDL_TTF_PATH) $(LIB_SDL_TTF_NAME)

$(LIB_PRINTF): $(PREREQUISITE_FT_PRINTF)
	make -C $(LIB_PRINTF_PATH)

$(OBJS): %.o:%.c $(HEADERS)
	@gcc -c $< -I$(HEADER_PATH) -I$(HEADER_PATH_OP) -I$(LIB_PATH) -I$(LIB_PRINTF_INCL) -I$(LIB_SDL_INCL) -I$(LIB_SDL_TTF_INCL) -O3 -o $@

clean:
	@rm -f $(OBJS)
	@make -C $(LIB_PRINTF_PATH) clean

fclean: clean
	@rm -f $(NAME_FILE)
	@make -C $(LIB_PRINTF_PATH) fclean

re: fclean all

print-%:
	@echo $*=$($*)
