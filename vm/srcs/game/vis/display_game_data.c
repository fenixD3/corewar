
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
	*text_x += g_vs->txt_srfc->w + 40;
	free_mem_font();
}

void			show_abreviations(char string[100])
{
	int			text_x;

	text_x = 670;
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

void			display_game_data(t_corewar *corewar)
{
	char 		string[100];
	int			text_x;

	text_x = 20;
	create_string(string, corewar->game_param.cycles_to_die,
				  "cycles to die : %d\n", NULL);
	display_item(&text_x, string, 0);
	create_string(string, corewar->game_param.cycles_aft_start,
				  "cycles after start : %d\n", NULL);
	display_item(&text_x, string, 0);
	create_string(string, corewar->game_param.who_lst_live,
				  "last live : %d\n", NULL);
	display_item(&text_x, string, 0);
	create_string(string, corewar->game_param.check_cnt,
				  "check count : %d\n", NULL);
	display_item(&text_x, string, 0);
	show_abreviations(string);
}
