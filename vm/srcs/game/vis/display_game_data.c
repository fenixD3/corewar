/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_game_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanhand <mcanhand@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 21:30:47 by mcanhand          #+#    #+#             */
/*   Updated: 2020/05/12 21:31:03 by mcanhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

t_vis_tools *g_vs;

void			display_item(int *text_x, char string[100], int y)
{
	SDL_Rect	dstrect;
	int			text_height;

	g_vs->txt_srfc = TTF_RenderText_Solid(g_vs->text_font, string,
								g_vs->text_color[4]);
	g_vs->text = SDL_CreateTextureFromSurface(g_vs->render, g_vs->txt_srfc);
	text_height = g_vs->txt_srfc->h;
	dstrect = create_rect(*text_x, 64 * 15 + 25 + y,
								g_vs->txt_srfc->w, text_height);
	SDL_RenderCopy(g_vs->render, g_vs->text, NULL, &dstrect);
	*text_x += g_vs->txt_srfc->w + 30;
	free_mem_font();
}

void			show_abreviations(char string[100])
{
	int			text_x;

	text_x = 705;
	create_string(string, 0,
				"= = = %s - cycles before execution\n", "CBE");
	display_item(&text_x, string, 25);
	create_string(string, 0,
				"%s - previous LIVE execution\n", "PR LIVE EX");
	display_item(&text_x, string, 25);
	create_string(string, 0,
				"%s - operation code\n", "OP CODE");
	display_item(&text_x, string, 25);
	create_string(string, 0,
				"%s - carriage id = = =\n", "CAR ID");
	display_item(&text_x, string, 25);
}

void			show_usage(char string[100])
{
	int			text_x;

	text_x = 1575;
	create_string(string, 0,
				"= = = %s = = =\n", "USAGE. Press ...");
	display_item(&text_x, string, 0);
	text_x = 1560;
	create_string(string, 0,
				"%s\n", "Enter - to speed up the game");
	display_item(&text_x, string, 12);
	text_x = 1560;
	create_string(string, 0,
				"%s\n", "-> - to manage game manually");
	display_item(&text_x, string, 24);
}

void			display_game_data(t_corewar *corewar)
{
	char		string[100];
	int			text_x;

	text_x = 15;
	create_string(string, corewar->game_param.cycles_to_die,
					"cycles to die : %d\n", NULL);
	display_item(&text_x, string, 25);
	create_string(string, corewar->game_param.cycles_aft_start,
				"cycles after start : %d\n", NULL);
	display_item(&text_x, string, 25);
	create_string(string, corewar->game_param.who_lst_live,
					"last live : %d\n", NULL);
	display_item(&text_x, string, 25);
	create_string(string, corewar->game_param.check_cnt,
			"check count : %d\n", NULL);
	display_item(&text_x, string, 25);
	create_string(string, corewar->game_param.live_period_cnt,
				  "live period cnt : %d\n", NULL);
	display_item(&text_x, string, 25);
	text_x = 290;
	create_string(string, 0, "GAME  %s\n", "STATISTICS");
	display_item(&text_x, string, 3);
	text_x = 1050;
	create_string(string, 0, "%s\n", "ABBREVIATIONS");
	display_item(&text_x, string, 3);
	show_abreviations(string);
	show_usage(string);
}
