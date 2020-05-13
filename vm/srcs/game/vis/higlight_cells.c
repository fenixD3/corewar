

#include "vis.h"

t_vis_tools *g_vs;

bool				duplicate(unsigned char *to_fill[3], int cariages,
												unsigned char *op_pos)
{
	int				i;

	i = 0;
	while (i < cariages)
	{
		if (to_fill[i] == op_pos)
			return (1);
		i++;
	}
	return (0);
}

void				higlighting(t_vc *vc, t_corewar *crwr)
{
	SDL_Color		color;
	SDL_Rect		carrg;
	int				c;
	SDL_Rect		dstrect;
	char 			res[3];

	c = vc->carriage->op_pos - crwr->arena;
	color = (vc->carriage->reg[0] < 0 && vc->carriage->reg[0] > -5) ?
			g_vs->text_color[-(vc->carriage->reg[0]) - 1] : g_vs->text_color[4];
	SDL_SetRenderDrawColor(g_vs->render, color.r, color.g, color.b, 0);
	carrg = create_rect(10 + ((c - (c / 64) * 64) * 24),
						13 + ((c / 64) * 15), 16, 10);
	SDL_RenderFillRect(g_vs->render, &carrg);
	res[0] = "0123456789abcdef"[crwr->arena[c] >> 4];
	res[1] = "0123456789abcdef"[crwr->arena[c] & 0x0F];
	res[2] = '\0';
	g_vs->txt_srfc = TTF_RenderText_Solid(g_vs->text_font,
										  res, g_vs->text_color[5]);
	g_vs->text = SDL_CreateTextureFromSurface(g_vs->render, g_vs->txt_srfc);
	dstrect = create_rect(12 + ((c - (c / 64) * 64) * 24),
				14 + ((c / 64) * 15), g_vs->txt_srfc->w, g_vs->txt_srfc->h);
	SDL_RenderCopy(g_vs->render, g_vs->text, NULL, &dstrect);
	free_mem_font();
}

void				higlight_cells(int cariages, t_vc *vc, t_corewar *crwr, int ind)
{
	unsigned char	*to_fill[cariages];
	int				i;

	i = 0;
	while (i < cariages)
		to_fill[i++] = 0;
	i = 0;
	while (vc != NULL && i <= cariages)
	{
		if (ind < 0 || (ind >= 4100 && g_mode < 0) || (ind >= 4100
			&& g_mode >= 0 && vc->carriage->op_pos == &(crwr->arena[g_mode]))
			|| (ind >= 0 && vc->carriage->op_pos == &(crwr->arena[ind])))
		{
			if (!duplicate(to_fill, cariages, vc->carriage->op_pos) && vc->is_open)
			{
				higlighting(vc, crwr);
				to_fill[i] = vc->carriage->op_pos;
			}
			i++;
		}
		vc = vc->next;
	}
}
