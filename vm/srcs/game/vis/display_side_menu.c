
#include "vis.h"

t_vis_tools *g_vs;

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
	dstrect = create_rect(x ? 30 + 64 * 24 + x : 30 + 64 * 24, y,
						  text_width, text_height);
	SDL_RenderCopy(g_vs->render, g_vs->text, NULL, &dstrect);
	free_mem_font();
	return (text_height);
}

void			display_registers(int i, t_carriages *carriages,
											int extndd, t_corewar *crwr)
{
	int					j;
	int					c;
	char		todisplay[100];
	unsigned char		str[100];

	j = 1;
	c = 0;
	if (extndd)
	{
		disasm(str, carriages->op_pos, crwr->arena);
		ft_sprintf(todisplay, "OPERATION : %s\n", str);
		display_text(todisplay, 0, i + 15 + 9 * 2);
		while (j < 17)
		{
			c = 0;
			ft_sprintf(todisplay, j < 10 ? "%d : %10x\n" : "%d: %10x\n",
														j, carriages->reg[j]);
			while (todisplay[c] != '\n')
				c++;
			todisplay[c] = '\0';
			display_text(todisplay, j <= 8 ? 0 : 100, 20 + 3 * ((j > 8 ? j -
					8 : j) + 1) + 9 * ((j > 8 ? j - 8 : j) + 3) + i);
			j++;
		}
	}
}

void			fill_frame(int *i, t_carriages *carriages,
									int extndd, t_corewar *crwr)
{
	char		todisplay[100];
	int			text_height;
	int			arena_coord;

	create_string(todisplay, carriages->cycle_op < 0 ? 0 :
	carriages->cycle_op, "CBE : %d\n", NULL);
	text_height = display_text(todisplay, 0, *i + 9);
	create_string(todisplay, carriages->cycle_when_live,
									"PR LIVE EX : %d\n", NULL);
	display_text(todisplay, 0, *i + 12 + text_height);
	if (!extndd)
	{
		create_string(todisplay, carriages->op_code, "OPERATTON : %d\n", NULL);
		display_text(todisplay, 0, *i + 15 + text_height * 2);
	}
	arena_coord = carriages->op_pos - crwr->arena;
	create_string(todisplay, arena_coord, "POS : %d\n", NULL);
	display_text(todisplay, 0, *i + 18 + text_height * 3);
	create_string(todisplay, arena_coord % 64, "X : %d\n", NULL);
	display_text(todisplay, 85, *i + 18 + text_height * 3);
	create_string(todisplay, arena_coord / 64, "Y : %d\n", NULL);
	display_text(todisplay, 140, *i + 18 + text_height * 3);
	display_registers(*i, carriages, extndd, crwr);
	*i += extndd ? 162 : 63;
}

void			draw_frame(t_vc *vc, int *i, int extndd, t_corewar *crwr)
{
	SDL_Color	color;
	SDL_Rect	rectangle;
	int			rec_h;
	int			player;

	player = vc->carriage->reg[0];
	color = (player < 0 && player > -5) ?
			g_vs->text_color[-(player) - 1] : g_vs->text_color[4];
	rec_h = extndd ? 162 : 63;
	SDL_SetRenderDrawColor(g_vs->render, color.r, color.g, color.b,
														SDL_ALPHA_OPAQUE);
	rectangle = create_rect(20 + 64 * 24, *i,
							g_vs->wight - 30 - 64 * 24, rec_h);
	SDL_RenderFillRect(g_vs->render, &rectangle);
	SDL_SetRenderDrawColor(g_vs->render, 0, 0, 0, SDL_ALPHA_OPAQUE);
	rectangle = create_rect(26 + 64 * 24, *i + 6,
				g_vs->wight - 42 - 64 * 24, (extndd ? 150 : 51));
	SDL_RenderFillRect(g_vs->render, &rectangle);
	fill_frame(i, vc->carriage, vc->is_open, crwr);
}

void			more()
{
	SDL_Rect	dstrect;
	SDL_Rect	sm_rectangle;

	SDL_SetRenderDrawColor(g_vs->render, 200, 200, 0, SDL_ALPHA_OPAQUE);
	sm_rectangle = create_rect(64 * 24 + 50, 64 * 15,
							   g_vs->wight - 95 - 64 * 24, 15);
	SDL_RenderFillRect(g_vs->render, &sm_rectangle);
	g_vs->txt_srfc = TTF_RenderText_Solid(g_vs->text_font, "And more...",
										  g_vs->text_color[5]);
	g_vs->text = SDL_CreateTextureFromSurface(g_vs->render, g_vs->txt_srfc);
	dstrect = create_rect(60 + 64 * 24, 64 * 15 + 3,
						  g_vs->txt_srfc->w, g_vs->txt_srfc->h);
	SDL_RenderCopy(g_vs->render, g_vs->text, NULL, &dstrect);
	free_mem_font();
}

void	if_open(int i, int *done, int ind, t_vc *vc)
{
	if (!*done && ind - 4100 > i && ind - 4100 < i + (vc->is_open ? 162 : 54))
	{
		vc->is_open = !vc->is_open;
		*done = 1;
	}
}

void			display_side_menu(t_corewar *crwr, int ind, t_vc *vc)
{
	int			i;
	int			done;

	i = 15;
	done = 0;
	while (vc != NULL && i < 900)
	{
		if ((i > 800 && vc->is_open) || (i > 800 && !vc->is_open &&
						!done && ind - 4100 > i && ind - 4100 < i + 54))
		{
			i += 100;
			continue ;
		}
		else if (ind < 0 || (ind >= 4100 && g_mode < 0) || (ind >= 4100
		&& g_mode >= 0 && vc->carriage->op_pos == &(crwr->arena[g_mode]))
		|| (ind >= 0 && vc->carriage->op_pos == &(crwr->arena[ind])))
		{
			if_open(i, &done, ind, vc);
			draw_frame(vc, &i, vc->is_open, crwr);
		}
		vc = vc->next;
	}
	vc != NULL ? more() : 0;
}
