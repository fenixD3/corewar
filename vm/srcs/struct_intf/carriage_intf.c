/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage_intf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <ylila@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 14:27:16 by ylila             #+#    #+#             */
/*   Updated: 2020/05/17 14:27:54 by mcanhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

t_vis_tools	*g_vs;

t_carriages	*create_new_carriage(void)
{
	static int	nxt_id;
	t_carriages	*new;

	if (!(new = (t_carriages *)ml_malloc(sizeof(t_carriages), CARRIAGE_NODE)))
		return (NULL);
	new->id = ++nxt_id;
	new->carry = 0;
	new->op_code = 0;
	new->cycle_when_live = 0;
	new->cycle_op = 0;
	new->op_pos = NULL;
	new->cnt_bytes_to_op = 0;
	ft_bzero(new->reg, sizeof(new->reg));
	new->next = NULL;
	return (new);
}

void		push_front_carriage(t_carriages **carriages, const t_flgs *flg)
{
	t_carriages	*new_carriage;

	if (!*carriages)
		*carriages = create_new_carriage();
	else
	{
		if (!(new_carriage = create_new_carriage()))
			get_error("Carriage weren't been alloc");
		new_carriage->next = *carriages;
		*carriages = new_carriage;
	}
	if (flg->set_flg & VIS_FLG)
		add_new_vc(&(g_vs->vc_list), *carriages);
}

t_carriages	*delete_carriage(t_corewar *corewar, int search_id)
{
	t_carriages	*carriage;
	t_carriages	*prev;

	carriage = corewar->carriages;
	prev = NULL;
	while (carriage)
	{
		if (carriage->id == search_id)
			break ;
		prev = carriage;
		carriage = carriage->next;
	}
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 8)
		call_printf_v_8(corewar, carriage, search_id);
	if (!prev)
		corewar->carriages = carriage->next;
	else
		prev->next = carriage->next;
	if (corewar->flgs.set_flg & VIS_FLG)
		delete_vc_by_deletion_carriage(carriage);
	ml_free(carriage, CARRIAGE_NODE);
	return (prev);
}
