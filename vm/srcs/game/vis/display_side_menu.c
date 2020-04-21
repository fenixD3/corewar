#include "vis.h"

t_vis_tools *g_vs;

void			draw_frame(SDL_Color color, int i, int extndd)
{
	SDL_Rect	rectangle;
	int			rec_h;

	rec_h = extndd ? 162 : 63;
	SDL_SetRenderDrawColor(g_vs->render, color.r, color.g, color.b,
						   SDL_ALPHA_OPAQUE);
	rectangle = create_rect(20 + 64 * 24, 15 + rec_h * i,
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
						 30 + 3 * (j + 1) + text_height * (j + 3) + 126 * i);
			j++;
		}
		j = 0;
		while (j < 8)
		{
			text = ft_strjoin("1: ", ft_itoa(carriages->reg[8 + j]));
			display_text(text, 130 + 64 * 24,
					30 + 3 * (j + 1) + text_height * (j + 3) + 126 * i);
			j++;
		}
	}
}

void			fill_frame(int i, t_carriages *carriages, int extndd)
{
	SDL_Rect	rectangle;
	char		*text;
	int			text_height;

	SDL_SetRenderDrawColor(g_vs->render, 0, 0, 0, SDL_ALPHA_OPAQUE);
	rectangle = create_rect(26 + 64 * 24, 21 + (extndd ? 162 : 63) * i,
							g_vs->wight - 42 - 64 * 24, (extndd ? 146 : 51));
	SDL_RenderFillRect(g_vs->render, &rectangle);
	text = ft_strjoin("cycles before execution : ",
			ft_itoa(carriages->cycle_op));
	text_height = display_text(text, 0, 24 + (extndd ? 158 : 63) * i);
	text = ft_strjoin("operation code : ",
			g_op[carriages->op_code - 1].name);
	display_text(text, 0, 24 + text_height + 3 + (extndd ? 158 : 63) * i);
	text = ft_strjoin("previous live execution : ",
			ft_itoa(carriages->cycle_when_live));
	display_text(text, 0, 30 + text_height * 2 + (extndd ? 158 : 63) * i);
	display_registers(i, text_height, carriages, extndd);
}

void display_side_menu(t_corewar *crrw, int ind)
{
	SDL_Color	color;
	int			i;
	SDL_Rect	stat_window;
	t_vc		*vc;

	i = 0;
	SDL_SetRenderDrawColor(g_vs->render, 0, 0, 0, SDL_ALPHA_OPAQUE);
	stat_window = create_rect(15 + 64 * 24, 10,
							  g_vs->wight - 20 - 64 * 24, 5 + 64 * 15);
	SDL_RenderFillRect(g_vs->render, &stat_window);
	vc = g_vs->vc_list;
	while (vc != NULL && ((ind < 0) ? i < 15 : i < 6))
	{
		color = (vc->carriage->reg[0] < 0 && vc->carriage->reg[0] > -5) ?
				g_vs->text_color[-(vc->carriage->reg[0]) - 1] : g_vs->text_color[4];
		if (ind < 0 || (ind >= 0 && vc->carriage->op_pos == &(crrw->arena[ind])))
		{
			draw_frame(color, i, (ind < 0) ? 0 : 1);
			fill_frame(i++, vc->carriage, (ind < 0) ? 0 : 1);
		}
		vc = vc->next;
	}
}
