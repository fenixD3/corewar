
#include "vis.h"
#include "op.h"

void			print_arena(t_vis_tools *vs, t_arena *arena)
{
	int			text_width;
	int			text_height;
	t_cells		*cell;
	SDL_Rect	dstrect;
	int			i;
	int			j;

	i = 0;
	cell = arena->cell;
	while (i < MEM_SIZE)
	{
		j = 0;
		while (j < 64)
		{
			vs->txt_srfc = TTF_RenderText_Solid(vs->font,
			                                    cell->code, cell->color);
			vs->text = SDL_CreateTextureFromSurface(vs->render,
					vs->txt_srfc);
			text_width = vs->txt_srfc->w;
			text_height = vs->txt_srfc->h;
			dstrect = create_rect(10 + j++ * 23,
				15 + (i++ / 64) * (text_height + 2), text_width, text_height);
			SDL_RenderCopy(vs->render, vs->text, NULL, &dstrect);
			free_mem_font(vs);
			cell = cell->next;
		}
	}
}
