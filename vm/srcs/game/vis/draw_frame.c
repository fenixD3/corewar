/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanhand <mcanhand@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 22:37:52 by mcanhand          #+#    #+#             */
/*   Updated: 2020/05/12 22:38:05 by mcanhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

t_vis_tools *g_vs;

int						display_text(char *text, int x, int y)
{
	int					text_width;
	int					text_height;
	SDL_Rect			dstrect;

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

void					display_registers(int i, t_carriages *carriages,
		int extndd, t_corewar *crwr)
{
	int					j;
	int					c;
	char				todisplay[100];
	unsigned char		str[100];

	j = 1;
	c = 0;
	if (extndd)
	{
		disasm(carriages, str, crwr->arena);
		ft_sprintf(todisplay, "OP : %s\n", str);
		while (todisplay[c] != '\n')
			c++;
		todisplay[c] = '\0';
		display_text(todisplay, 0, i + 15 + 9 * 2);
		while (j < 17)
		{
			c = 0;
			ft_sprintf(todisplay, j < 10 ? "%d : %#10x\n" : "%d: %#10x\n",
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

void					fill_frame(int *i, t_carriages *carriages,
											int extndd, t_corewar *crwr)
{
	char				todisplay[100];
	int					text_height;
	int					arena_coord;

	create_string(todisplay, carriages->cycle_op < 0 ? 0 :
				carriages->cycle_op, "CBE : %d\n", NULL);
	text_height = display_text(todisplay, 0, *i + 9);
	create_string(todisplay, carriages->cycle_when_live,
							"PR LIVE EX : %d\n", NULL);
	display_text(todisplay, 0, *i + 12 + text_height);
	if (!extndd)
	{
		create_string(todisplay, carriages->op_code, "OP : %#x\n", NULL);
		display_text(todisplay, 0, *i + 15 + text_height * 2);
	}
	arena_coord = carriages->op_pos - crwr->arena;
	create_string(todisplay, arena_coord, "POS : %d\n", NULL);
	display_text(todisplay, 0, *i + 18 + text_height * 3);
	create_string(todisplay, arena_coord % 64, "X : %d\n", NULL);
	display_text(todisplay, 95, *i + 18 + text_height * 3);
	create_string(todisplay, arena_coord / 64, "Y : %d\n", NULL);
	display_text(todisplay, 150, *i + 18 + text_height * 3);
	display_registers(*i, carriages, extndd, crwr);
	*i += extndd ? 162 : 63;
}

void					draw_frame(t_vc *vc, int *i, int extnd, t_corewar *crwr)
{
	SDL_Color			color;
	SDL_Rect			rectangle;
	int					rec_h;
	int					player;

	player = vc->carriage->reg[0];
	color = (player < 0 && player > -5) ?
			g_vs->text_color[-(player) - 1] : g_vs->text_color[4];
	rec_h = extnd ? 162 : 63;
	SDL_SetRenderDrawColor(g_vs->render, color.r, color.g, color.b,
						SDL_ALPHA_OPAQUE);
	rectangle = create_rect(20 + 64 * 24, *i,
					g_vs->wight - 30 - 64 * 24, rec_h);
	SDL_RenderFillRect(g_vs->render, &rectangle);
	SDL_SetRenderDrawColor(g_vs->render, 0, 0, 0, SDL_ALPHA_OPAQUE);
	rectangle = create_rect(26 + 64 * 24, *i + 6,
			g_vs->wight - 42 - 64 * 24, (extnd ? 150 : 51));
	SDL_RenderFillRect(g_vs->render, &rectangle);
	fill_frame(i, vc->carriage, vc->is_open, crwr);
}
