#ifndef VM_H
# define VM_H

# include "ft_ptintf.h"
# include "op.h"
# include <fcntl.h>
# define N_FLG 1u
# define DUMP_FLG 2u
# define A_FLG 3u

# define CHAMP_NODE 1u
# define CARRIAGE_NODE 2u

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
	uint8_t	flgs;
	int		nxt_player_num;
	int		nbr_cycles_dump;
}				t_flgs;

typedef struct	s_game_param
{
	int		who_lst_live;
	int		cycles_aft_start;
	int		live_period_cnt;
	int		cycles_to_die;
	int 	live_check_cnt;
}				t_game_param;

typedef struct	s_carriages
{
	int					id;
	_Bool				carry;
	unsigned char		op_code;
	int					cycle_when_live;
	int					cycle_to_op;
	unsigned char		*curr_pos;
	unsigned char		cnt_bytes_to_op;
	int 				reg[REG_NUMBER];
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

void		init_struct(t_corewar *corewar);
t_champion	*create_new_champ(const char *fname);
void		push_back_champ(t_champion **champs, const char *fname);
int			champions_cnt(t_champion *champs);
int			max_champs_num(t_champion *champs);
_Bool		is_there_same_champ_num(t_champion *champs,
						int nxt_player_num);

t_carriages	*create_new_carriage(void);
void		push_front_carriage(t_carriages **carriages);

void	get_usage(void);
void	get_error(char *error);

void	parse_arguments(int ac, char **av, t_corewar *corewar);
void	validation_champions(t_champion *champs);
void	byte_code_validation(const int fd, t_champion *champ);
void	reverse_bytes(unsigned int *num_to_rev);

_Bool	is_flg(const char *arg, t_flgs *flgs);
_Bool	is_champion(const char *arg, t_corewar *corewar);

void	start_game(t_corewar *corewar);
void	init_arena(unsigned char arena[], t_champion *champs,
					t_carriages **carriages);
void	introducing_fighter(t_champion *champs);

#endif
