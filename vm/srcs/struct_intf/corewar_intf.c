/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_intf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <ylila@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 14:28:05 by ylila             #+#    #+#             */
/*   Updated: 2020/05/17 14:28:11 by ylila            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		init_struct(t_corewar *corewar)
{
	ft_memcpy(&corewar->flgs, &(t_flgs){0, 0, -1}, sizeof(corewar->flgs));
	corewar->champs = NULL;
	ft_bzero(corewar->arena, sizeof(corewar->arena));
	ft_memcpy(&corewar->game_param,
			&(t_game_param){0, 0, 0, 0, CYCLE_TO_DIE, 0},
			sizeof(corewar->game_param));
	corewar->carriages = NULL;
}

t_champion	*create_new_champ(const char *fname)
{
	t_champion	*new;

	if (!(new = (t_champion *)ml_malloc(sizeof(t_champion), CHAMP_NODE)))
		return (NULL);
	new->filename = (char *)fname;
	new->num = 0;
	ft_memcpy(&new->file, &(t_file){
		*(t_header *)ft_memcpy(&new->file.header,
				&(t_header){0, 0, 0, 0}, sizeof(new->file.header)), 0,
		*(unsigned char *)ft_memset(new->file.exec_code, 0,
				sizeof(new->file.exec_code))},
		sizeof(new->file));
	new->lst = new;
	new->next = NULL;
	return (new);
}

void		push_back_champ(t_champion **champs, const char *fname)
{
	if (!*champs)
		*champs = create_new_champ(fname);
	else
	{
		(*champs)->lst->next = create_new_champ(fname);
		(*champs)->lst = (*champs)->lst->next;
	}
	if (!(*champs)->lst)
		get_error("Champion weren't been alloc");
}

int			champions_cnt(t_champion *champs)
{
	int		cnt;

	cnt = 0;
	while (champs)
	{
		++cnt;
		champs = champs->next;
	}
	return (cnt);
}
