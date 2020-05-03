#include "vis.h"

t_vis_tools *g_vs;


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
	new->is_live = 1;
	new->next = NULL;
	return (new);
}

void push_front_carriage(t_carriages **carriages)
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
// при условии если программа запущена с -vis
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
	if (corewar->flgs.set_flg & V_FLG && corewar->flgs.verb_num & 8) {
		printf("Process %d hasn't lived for %ld cycles (CTD %ld)\n",
			search_id,
			corewar->game_param.cycles_aft_start - carriage->cycle_when_live,
			corewar->game_param.cycles_to_die);
		fprintf(file, "Process %d hasn't lived for %ld cycles (CTD %ld)\n",
			search_id,
			corewar->game_param.cycles_aft_start - carriage->cycle_when_live,
			corewar->game_param.cycles_to_die);
	}
	if (!prev)
		corewar->carriages = carriage->next;
	else
		prev->next = carriage->next;
	///// egors
	delete_vc_by_deletion_carriage(carriage);
	/////
	ml_free(carriage, CARRIAGE_NODE);
	return (prev);
}
