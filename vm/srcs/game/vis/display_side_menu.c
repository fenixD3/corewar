#include "vis.h"

t_vis_tools *g_vs;

void			draw_frame(SDL_Color color, int i, int extndd)
{
	SDL_Rect	rectangle;
	int			rec_h;

	rec_h = extndd ? 162 : 63;
	SDL_SetRenderDrawColor(g_vs->render, color.r, color.g, color.b,
						   SDL_ALPHA_OPAQUE);
	rectangle = create_rect(20 + 64 * 24, i,
							g_vs->wight - 30 - 64 * 24, rec_h);
	SDL_RenderFillRect(g_vs->render, &rectangle);
}

int				display_text(char *text, int x, int y)
{
	int			text_width;
	int			text_height;
	SDL_Rect	dstrect;

	g_vs->txt_srfc = TTF_RenderText_Solid(g_vs->text_font, text,
										  g_vs->text_color[4]);
	g_vs->text = SDL_CreateTextureFromSurface(g_vs->render, g_vs->txt_srfc);
	text_width = g_vs->txt_srfc->w;
	text_height = g_vs->txt_srfc->h;
	dstrect = create_rect(x ? x : 30 + 64 * 24, y, text_width, text_height);
	SDL_RenderCopy(g_vs->render, g_vs->text, NULL, &dstrect);
	free_mem_font();
	free(text);
	return (text_height);
}

void			display_registers(int i, int text_height, t_carriages *carriages, int extndd)
{
	int			j;
	char		*text;

	j = 0;
	if (extndd)
	{
		while (j < 8)
		{
			text = ft_strjoin("1: ", ft_itoa(carriages->reg[j]));
			display_text(text, 0,
					20 + 3 * (j + 1) + text_height * (j + 3) + i);
			j++;
		}
		j = 0;
		while (j < 8)
		{
			text = ft_strjoin("1: ", ft_itoa(carriages->reg[8 + j]));
			display_text(text, 130 + 64 * 24,
						 20 + 3 * (j + 1) + text_height * (j + 3) + i);
			j++;
		}
	}
}

void			fill_frame(int *i, t_carriages *carriages, int extndd)
{
	SDL_Rect	rectangle;
	char		*text;
	int			text_height;

	SDL_SetRenderDrawColor(g_vs->render, 0, 0, 0, SDL_ALPHA_OPAQUE);
	rectangle = create_rect(26 + 64 * 24, *i + 6,
							g_vs->wight - 42 - 64 * 24, (extndd ? 150 : 51));
	SDL_RenderFillRect(g_vs->render, &rectangle);
	text = ft_strjoin("cycles before execution : ",
					  ft_itoa(carriages->cycle_op));
	text_height = display_text(text, 0, *i + 9);
	text = ft_strjoin("operation code : ",
					  g_op[carriages->op_code - 1].name);
	display_text(text, 0, *i + 9 + text_height + 3);
	text = ft_strjoin("previous live execution : ",
					  ft_itoa(carriages->cycle_when_live));
	display_text(text, 0, *i + 15 + text_height * 2);
	display_registers(*i, text_height, carriages, extndd);
	*i += extndd ? 158 : 63;
}

void			display_side_menu(t_corewar *crrw, int ind)
{
	SDL_Color	color;
	int			i;
	SDL_Rect	stat_window;
	t_vc		*vc;

	i = 15;
	SDL_SetRenderDrawColor(g_vs->render, 0, 0, 0, SDL_ALPHA_OPAQUE);
	stat_window = create_rect(15 + 64 * 24, 10,
				g_vs->wight - 20 - 64 * 24, 5 + 64 * 15);
	SDL_RenderFillRect(g_vs->render, &stat_window);
	vc = g_vs->vc_list;
	while (vc != NULL && i < 1030)
	{
		color = (vc->carriage->reg[0] < 0 && vc->carriage->reg[0] > -5) ?
			g_vs->text_color[-(vc->carriage->reg[0]) - 1] : g_vs->text_color[4];
		if (ind < 0 || (ind >= 4100 && g_mode < 0) || (ind >= 4100
		&& g_mode >= 0 && vc->carriage->op_pos == &(crrw->arena[g_mode]))
		|| (ind >= 0 && vc->carriage->op_pos == &(crrw->arena[ind])))
		{
			if ((ind - 4100 > i && ind - 4100 < i + 54))
				vc->is_open = (vc->is_open == true) ? false : true;
			draw_frame(color, i, vc->is_open ? 1 : 0);
			fill_frame(&i, vc->carriage, vc->is_open ? 1 : 0);
		}
		vc = vc->next;
	}
}
