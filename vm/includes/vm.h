#ifndef VM_H
# define VM_H

# include "ft_ptintf.h"
# include "op.h"
# include "vm_structs.h"
# include "vis.h"


# include <fcntl.h>
# include "options.h"

# include <stdio.h>
# include <stdbool.h>

# define N_FLG 1u
# define DUMP_FLG 2u
# define A_FLG 4u
# define V_FLG 8u
# define VIS_FLG 16u

# define CHAMP_NODE 1u
# define CARRIAGE_NODE 2u

int g_change;

void			init_struct(t_corewar *corewar);
t_champion		*create_new_champ(const char *fname);
void			push_back_champ(t_champion **champs, const char *fname);
int				champions_cnt(t_champion *champs);
int				max_champs_num(t_champion *champs);
_Bool			is_there_same_champ_num(t_champion *champs, int nxt_player_num);

t_carriages		*create_new_carriage(void);
void			push_front_carriage(t_carriages **carriages, const t_flgs *flg);
t_carriages		*delete_carriage(t_corewar *corewar, int search_id);

void			get_usage(void);
void			get_error(char *error);
void			prepare_battle(t_corewar *corewar, bool *quit);

void			parse_arguments(int ac, char **av, t_corewar *corewar);
void parse_flags(t_corewar *corewar, const int ac, char **av, int *i);
void			validation_champions(t_champion *champs,
												t_game_param *game_params);
void			byte_code_validation(const int fd, t_champion *champ);
void			validation_before_comment(const int fd, t_champion *champ);
void			reverse_int_bytes(unsigned int *num_to_rev);
int				reverse_vm_bytes(unsigned char *num_to_rev, int bytes,
														unsigned char *arena);

_Bool			is_flg(const char *arg, t_flgs *flgs);
_Bool			is_champion(const char *arg, t_corewar *corewar);

void			start_game(t_corewar *corewar);
void			init_arena(unsigned char arena[], t_champion *champs,
									t_carriages **carriages, const t_flgs *flg);
void			introducing_fighter(t_champion *champs);
void			print_map(t_corewar *corewar);
void			introducing_winner(t_corewar *corewar);

void			carriages_actions(t_corewar *corewar, bool *quit);
unsigned char	*do_steps(unsigned char *start, int step, unsigned char *arena);
void			lets_check(t_corewar *corewar);
void			decrease_cycles_to_die(t_corewar *corewar);
_Bool			valid_op_set_cycle(unsigned char *start_oper, int *cycle_to_op);
void			make_operation_and_go_next(t_corewar *corewar,
												t_carriages **carriage_head);
unsigned char	*get_arguments_frm_code(unsigned char *arg_type_code,
							t_arg_type *args, t_op oper, unsigned char *arena);
_Bool			is_args_valid(t_parse_args *args_val, unsigned char *arg_start,
							const t_op *oper, unsigned char *arena);
void			get_arguments_values(t_parse_args *args_val,
			unsigned char *arg_start, const t_op *oper, unsigned char *arena);
unsigned char	*skip_op(unsigned char *start_op, t_arg_type *args, t_op oper,
							unsigned char *arena);

int				get_value_frm_arg(t_parse_args *arg_val, int arg_idx,
							t_corewar *corewar, _Bool is_idx_mod);
void			live(t_corewar *corewar, t_parse_args *arg_val,
							t_carriages **head);
void			ld(t_corewar *corewar, t_parse_args *arg_val,
							t_carriages **head);
void			ldi(t_corewar *corewar, t_parse_args *arg_val,
							t_carriages **head);
void			lld(t_corewar *corewar, t_parse_args *arg_val,
							t_carriages **head);
void			lldi(t_corewar *corewar, t_parse_args *arg_val,
							t_carriages **head);
void			st(t_corewar *corewar, t_parse_args *arg_val,
							t_carriages **head);
void			sti(t_corewar *corewar, t_parse_args *arg_val,
							t_carriages **head);
void			add(t_corewar *corewar, t_parse_args *arg_val,
							t_carriages **head);
void			sub(t_corewar *corewar, t_parse_args *arg_val,
							t_carriages **head);
void			and(t_corewar *corewar, t_parse_args *arg_val,
							t_carriages **head);
void			or(t_corewar *corewar, t_parse_args *arg_val,
							t_carriages **head);
void			xor(t_corewar *corewar, t_parse_args *arg_val,
							t_carriages **head);
void			nfork(t_corewar *corewar, t_parse_args *arg_val,
							t_carriages **head);
void			lfork(t_corewar *corewar, t_parse_args *arg_val,
							t_carriages **head);
void			zjump(t_corewar *corewar, t_parse_args *arg_val,
							t_carriages **head);
void			aff(t_corewar *corewar, t_parse_args *arg_val,
							t_carriages **head);

static void		(*g_instrs_ptr[16])(t_corewar *corewar, t_parse_args *arg_val,
									t_carriages **head) = {
				live, ld, st, add, sub, and, or, xor, zjump, ldi, sti, nfork,
				lld, lldi, lfork, aff };

int				cnt_bytes_for_op(const t_op *op, const t_arg_type *code_args);
void			print_command_bytes(unsigned char *start_op,
							int bytes_to_nxt, unsigned char *arena);

FILE *file;

void	call_printf_v_2(t_corewar *corewar, _Bool printf_cycle_die);
void	call_printf_v_16(t_corewar *corewar);
void	call_printf_v_1(const t_corewar *corewar, const t_champion *champ);
void	call_printf_v_8(const t_corewar *corewar,
					 const t_carriages *carriage,
					 int search_id);
void	call_printf_v_4(t_corewar *corewar, t_parse_args *arg_val,
						const char *cmd);

void			print_v_4_live(t_corewar *corewar, t_parse_args *arg_val,
						const char *cmd);
void			print_v_4_nfork(t_corewar *corewar, t_parse_args *arg_val,
						const char *cmd);
void			print_v_4_lfork(t_corewar *corewar, t_parse_args *arg_val,
						const char *cmd);
void			print_v_4_zjmp(t_corewar *corewar, t_parse_args *arg_val,
						const char *cmd);
void			print_v_4_ld(t_corewar *corewar, t_parse_args *arg_val,
						const char *cmd);
void			print_v_4_ldi(t_corewar *corewar, t_parse_args *arg_val,
						const char *cmd);
void			print_v_4_lld(t_corewar *corewar, t_parse_args *arg_val,
						const char *cmd);
void			print_v_4_lldi(t_corewar *corewar, t_parse_args *arg_val,
						const char *cmd);
void			print_v_4_st(t_corewar *corewar, t_parse_args *arg_val,
						const char *cmd);
void			print_v_4_sti(t_corewar *corewar, t_parse_args *arg_val,
						const char *cmd);
void			print_v_4_add(t_corewar *corewar, t_parse_args *arg_val,
						const char *cmd);
void			print_v_4_sub(t_corewar *corewar, t_parse_args *arg_val,
						const char *cmd);
void			print_v_4_and(t_corewar *corewar, t_parse_args *arg_val,
						const char *cmd);
void			print_v_4_or(t_corewar *corewar, t_parse_args *arg_val,
						const char *cmd);
void			print_v_4_xor(t_corewar *corewar, t_parse_args *arg_val,
						const char *cmd);

#endif
