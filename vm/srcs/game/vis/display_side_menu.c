#include "vis.h"

void			draw_frame(t_vis_tools *vs, SDL_Color color, int i)
{
	SDL_Rect	rectangle;

	SDL_SetRenderDrawColor(vs->render, color.r, color.g, color.b,
	                       SDL_ALPHA_OPAQUE);
	rectangle = create_rect(20 + 64 * 24, 15 + 63 * i,
	                        vs->wight - 30 - 64 * 24, 63);
	SDL_RenderFillRect(vs->render, &rectangle);
}

void			fill_frame(t_vis_tools *vs, int i)
{
	SDL_Rect	rectangle;

	SDL_SetRenderDrawColor(vs->render, 0, 0, 0,
	                       SDL_ALPHA_OPAQUE);
	rectangle = create_rect(26 + 64 * 24, 21 + 63 * i,
	                        vs->wight - 42 - 64 * 24, 51);
	SDL_RenderFillRect(vs->render, &rectangle);
}

void			display_side_menu(t_vis_tools *vs, t_corewar *corewar)
{
	SDL_Color	color;
	int			i;
	t_carriages	*carriage;

	i = 0;
	carriage = corewar->carriages;
	while (carriage != NULL)
	{
		color = (carriage->reg[0] < 0 && carriage->reg[0] > -5) ?
		        vs->text_color[-(carriage->reg[0]) - 1] : vs->text_color[4];
		draw_frame(vs, color, i);
		fill_frame(vs, i);
		carriage = carriage->next;
		i++;
	}
}
