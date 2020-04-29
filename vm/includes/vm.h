#ifndef VM_H
# define VM_H

# include "ft_ptintf.h"
# include "op.h"
# include <fcntl.h>
# include "options.h"

#include <stdio.h>

# define N_FLG 1u
# define DUMP_FLG 2u
# define A_FLG 3u
# define V_FLG 4u

# define CHAMP_NODE 1u
# define CARRIAGE_NODE 2u

int g_change;

typedef struct	s_file
{
	t_header		header;
	unsigned int	zero;
	unsigned char	exec_code[CHAMP_MAX_SIZE];
}				t_file;

typedef struct	s_champion
{
	char				*filename;
	int					num;
	t_file 				file;
	struct s_champion	*lst;
	struct s_champion	*next;
}				t_champion;

typedef struct	s_flgs
{
	uint8_t	set_flg;
	int		nxt_player_num;
	int		nbr_cycles_dump;
	int		verb_num;
}				t_flgs;

typedef struct	s_game_param
{
	int		who_lst_live;
	ssize_t	cycles_aft_start;
	int		live_period_cnt;
	ssize_t	cycles_to_die;
	int 	check_cnt;
}				t_game_param;

typedef struct	s_carriages
{
	int					id;
	_Bool				carry;
	unsigned char		op_code;
	ssize_t				cycle_when_live;
	int					cycle_op;
	unsigned char		*op_pos;
	unsigned char		cnt_bytes_to_op;
	int 				reg[REG_NUMBER];
	_Bool				is_live;
	struct s_carriages	*next;
}				t_carriages;

typedef struct	s_corewar
{
	t_flgs			flgs;
	t_champion		*champs;
	unsigned char	arena[MEM_SIZE];
	t_game_param	game_param;
	t_carriages		*carriages;
}				t_corewar;

typedef struct	s_parse_args
{
	t_arg_type		code_args[3];
	int 			val[3];
}				t_parse_args;

union			u_get_arg
{
	unsigned char	*chr_ptr;
	unsigned short	*srt_ptr;
	unsigned int	*int_ptr;
};

void		init_struct(t_corewar *corewar);
t_champion	*create_new_champ(const char *fname);
void		push_back_champ(t_champion **champs, const char *fname);
int			champions_cnt(t_champion *champs);
int			max_champs_num(t_champion *champs);
_Bool		is_there_same_champ_num(t_champion *champs,
						int nxt_player_num);

t_carriages	*create_new_carriage(void);
# include "vis.h"

//void push_front_carriage(t_carriages **carriages, t_vis_tools *g_vs);
int			carriage_amount_live(t_carriages *carriage);
t_carriages * delete_carriage(t_corewar *corewar, int search_id);

void	get_usage(void);
void	get_error(char *error);

void	parse_arguments(int ac, char **av, t_corewar *corewar);
void validation_champions(t_champion *champs, t_game_param *game_params);
void	byte_code_validation(const int fd, t_champion *champ);
void	reverse_int_bytes(unsigned int *num_to_rev);
int		reverse_vm_bytes(unsigned char *num_to_rev, int bytes,
				unsigned char *arena);

_Bool	is_flg(const char *arg, t_flgs *flgs);
_Bool	is_champion(const char *arg, t_corewar *corewar);

void	start_game(t_corewar *corewar);
//void
//init_arena(unsigned char arena[], t_champion *champs, t_carriages **carriages,
//           t_vis_tools *g_vs);
void	introducing_fighter(t_champion *champs);
void    print_map(t_corewar *corewar);
void introducing_winner(t_corewar *corewar);

void carriages_actions(t_corewar *corewar);
unsigned char	*do_steps(unsigned char *start, int step, unsigned char *arena);
void
lets_check(t_corewar *corewar);
_Bool	valid_op_set_cycle(unsigned char *start_oper, int *cycle_to_op);
void
make_operation_and_go_next(t_corewar *corewar, t_carriages **carriage_head);
unsigned char *get_arguments_frm_code(unsigned char *arg_type_code, t_arg_type *args,
					   t_op oper, unsigned char *arena);
_Bool is_args_valid(t_parse_args *args_val, unsigned char *arg_start, const t_op *oper,
					unsigned char *arena);
void get_arguments_values(t_parse_args *args_val, unsigned char *arg_start,
						  const t_op *oper, unsigned char *arena);
unsigned char *skip_op(unsigned char *start_op, t_arg_type *args, t_op oper,
					   unsigned char *arena);

int		get_value_frm_arg(t_parse_args *arg_val, int arg_idx,
							 t_corewar *corewar, _Bool is_idx_mod);
void    live(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head);
void    ld(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head);
void    ldi(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head);
void    lld(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head);
void    lldi(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head);
void    st(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head);
void    sti(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head);
void    add(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head);
void    sub(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head);
void    and(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head);
void    or(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head);
void    xor(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head);
void    nfork(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head);
void    lfork(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head);
void    zjump(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head);
void    aff(t_corewar *corewar, t_parse_args *arg_val, t_carriages **head);

static void (*instrs_ptr[16])(t_corewar *corewar, t_parse_args *arg_val,
							  t_carriages **head) =
	{live, ld, st, add, sub, and, or, xor, zjump, ldi, sti, nfork,
  	lld, lldi, lfork, aff};

int		cnt_bytes_for_op(const t_op *op, const t_arg_type *code_args);
void print_command_bytes(unsigned char *start_op,
						 int bytes_to_nxt,
						 unsigned char *arena);

FILE *file;

#endif
