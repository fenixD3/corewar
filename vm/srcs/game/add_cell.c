
#include "vis.h"
#include "vis_errors.h"

void			save_cell(t_cells **celllst, t_cells *new_cell)
{
	t_cells		**head;
	t_cells		*pr;

	pr = *celllst;
	head = celllst;
	if (*head)
	{
		while (pr->next != NULL)
			pr = pr->next;
		pr->next = new_cell;
		pr->next->next = NULL;
	}
	if (!*head)
	{
		*head = new_cell;
		(*head)->next = NULL;
	}
}

t_cells			*add_cell(int i, t_corewar *corewar)
{
	t_cells		*new;
	t_carriages	*carriage;

	if (!(new = (t_cells*)ml_malloc(sizeof(t_cells), ML_CELL)))
		go_exit(ERR_ML_CELL);
	if (!(new->code = (char*)malloc(sizeof(char) * 3)))
		go_exit(ERR_ML_CELL);
	new->code[0] = "0123456789abcdef"[corewar->arena[i] >> 4];
	new->code[1] = "0123456789abcdef"[corewar->arena[i] & 0x0F];
	new->code[2] = '\0';
	new->carriages = NULL;
	carriage = corewar->carriages;
	while (carriage != NULL)
	{
		if (&(corewar->arena[i]) == carriage->op_pos)
			new->carriages = carriage;
		carriage = carriage->next;
	}
	new->next = NULL;
	return (new);
}
