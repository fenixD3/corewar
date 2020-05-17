/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <ylila@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 14:28:05 by ylila             #+#    #+#             */
/*   Updated: 2020/05/17 14:28:11 by ylila            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_STRUCTS_H
# define VM_STRUCTS_H

# include <stdint.h>
# include <stdio.h>
# include "op.h"

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
	t_file				file;
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
	ssize_t	cycles_bfr_check;
	int		live_period_cnt;
	ssize_t	cycles_to_die;
	int		check_cnt;
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
	int					reg[REG_NUMBER];
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
	int				val[3];
}				t_parse_args;

#endif
