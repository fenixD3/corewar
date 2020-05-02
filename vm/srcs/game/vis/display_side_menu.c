
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
	return (text_height);
}

void			display_registers(int i, int text_height, t_carriages *carriages, int extndd)
{
	int			j;
	int			c;
	char 		todisplay[100];

	j = 0;
	c = 0;
	if (extndd)
	{
		while (j < 16)
		{
			c = 0;
			ft_sprintf(todisplay, j < 10 ? "%d : %10x\n" : "%d: %10x\n",
					j, carriages->reg[j]);
			while (todisplay[c] != '\n')
				c++;
			todisplay[c] = '\0';
			display_text(todisplay, j < 8 ? 0 : 130 + 64 * 24,
					20 + 3 * ((j >= 8 ? j - 8 : j) + 1) +
					text_height * ((j >= 8 ? j - 8 : j) + 3) + i);
			j++;
		}
	}
}

void			fill_frame(int *i, t_carriages *carriages, int extndd)
{
	SDL_Rect	rectangle;
	int 		c;
	char 		todisplay[100];
	int			text_height;

	c = 0;
	SDL_SetRenderDrawColor(g_vs->render, 0, 0, 0, SDL_ALPHA_OPAQUE);
	rectangle = create_rect(26 + 64 * 24, *i + 6,
			g_vs->wight - 42 - 64 * 24, (extndd ? 150 : 51));
	SDL_RenderFillRect(g_vs->render, &rectangle);
	create_string(todisplay, carriages->cycle_op, "CBE : %d\n");
	text_height = display_text(todisplay, 0, *i + 9);
	ft_sprintf(todisplay, "OP_CODE : %s\n", disasm(carriages->op_pos));
	c = 0;
	while (todisplay[c] != '\n')
		c++;
	todisplay[c] = '\0';
	display_text(todisplay, 0, *i + 9 + text_height + 3);
	create_string(todisplay, carriages->cycle_when_live, "PR_LIVE_EX : %d\n");
	display_text(todisplay, 0, *i + 15 + text_height * 2);
	display_registers(*i, text_height, carriages, extndd);
	*i += extndd ? 162 : 63;
}

void			display_side_menu(t_corewar *crrw, int ind)
{
	SDL_Color	color;
	int			i;
	SDL_Rect	stat_window;
	t_vc		*vc;
	int 		done;

	i = 15;
	done = 0;
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
			if (!done && (ind - 4100 > i && ((vc->is_open == true) ?
					ind - 4100 < i + 162 : ind - 4100 < i + 54)))
			{
				done = 1;
				vc->is_open = (vc->is_open == true) ? false : true;
			}
			draw_frame(color, i, vc->is_open ? 1 : 0);
			fill_frame(&i, vc->carriage, vc->is_open ? 1 : 0);
		}
		vc = vc->next;
	}
}
