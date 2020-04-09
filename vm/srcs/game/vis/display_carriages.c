
#include "vis.h"
#include "vis_errors.h"

void			draw_carriage(t_vis_tools *vs, int i, int priority, SDL_Color color)
{
	SDL_Rect	carrg;

	if (priority > 3)
		return ;
	else
	{
		SDL_SetRenderDrawColor(vs->render, color.r, color.g, color.b, 0);
		carrg = create_rect(10 + ((i - (i / 64) * 64) * 24) +
		                    (priority ? (priority + 2) * 3 : 0),
		                    13 + ((i / 64) * 15) + 13,
		                    (16 / (priority + 1)) - 1, 2);
		SDL_RenderFillRect(vs->render, &carrg);
	}
}

void			display_carriages(t_vis_tools *vs, t_corewar *corewar)
{
	t_carriages	*carriage;
	t_carriages	*tmp;
	int			i;
	int			priority;
	SDL_Color	color;

	i = 0;
	priority = 0;
	carriage = corewar->carriages;
	tmp = corewar->carriages;
	i = 0;
	while (i < MEM_SIZE)
	{
		carriage = tmp;
		while (carriage != NULL)
		{
			color = (carriage->reg[0] < 0 && carriage->reg[0] > -5) ?
			        vs->text_color[-(carriage->reg[0]) - 1] : vs->text_color[4];
			if (&(corewar->arena[i]) == carriage->op_pos)
				draw_carriage(vs, i, priority++, color);
			carriage = carriage->next;
		}
		priority = 0;
		i++;
	}
}