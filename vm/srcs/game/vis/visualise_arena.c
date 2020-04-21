
#include "vis.h"
#include "vis_errors.h"

t_vis_tools *g_vs;

void			draw_backgroung(void)
{
	SDL_Rect	rectangle;
	SDL_Rect	sm_rectangle;

	SDL_SetRenderDrawColor(g_vs->render, 244, 242, 238,
						   SDL_ALPHA_OPAQUE);
	rectangle = create_rect(0, 0, g_vs->wight, g_vs->height);
	SDL_RenderFillRect(g_vs->render, &rectangle);
	SDL_SetRenderDrawColor(g_vs->render, 0, 0, 0, SDL_ALPHA_OPAQUE);
	sm_rectangle = create_rect(5, 10, 64 * 24 + 5,
												64 * 15 + 5);
	SDL_RenderFillRect(g_vs->render, &sm_rectangle);

	SDL_SetRenderDrawColor(g_vs->render, 0, 0, 0, SDL_ALPHA_OPAQUE);
	sm_rectangle = create_rect(5, 64 * 15 + 20,
			64 * 24 + 5, g_vs->height - (64 * 15 + 20) - 10);
	SDL_RenderFillRect(g_vs->render, &sm_rectangle);
}

void	ft_free_strsplit(char **str_array)
{
	int i;

	if (str_array)
	{
		i = 0;
		while (str_array[i] != NULL)
		{
			free(str_array[i]);
			i++;
		}
		free(str_array);
	}
}


char	**convert_arena(t_corewar *corewar)
{
	int		i;
	int		j;
	int		c;
	char	**res;

	i = 0;
	c = 0;
	if (!(res = (char**)malloc(sizeof(char*) * 65)))
		go_exit(ERR_ML_ARENA);
	while (c < MEM_SIZE)
	{
		res[i % 64] = (char*)malloc(sizeof(char) * (64 * 3 + 63));
		j = 0;
		while (j < (64 * 3 + 63))
		{
			res[i % 64][j++] = "0123456789abcdef"[corewar->arena[c] >> 4];
			res[i % 64][j++] = "0123456789abcdef"[corewar->arena[c] & 0x0F];
			res[i % 64][j++] = ' ';
			res[i % 64][j++] = ' ';
			c++;
		}
		if (j >= (64 * 3 + 63))
			res[i % 64][64 * 4 - 2] = '\0';
		i++;
	}
	res[64] = NULL;
	return (res);
}

void			display_game_data(t_corewar *corewar)
{
	char		*text;
	int			text_x;
	int			text_height;
	SDL_Rect	dstrect[4];

	text = ft_strjoin("cycles to die : ", ft_itoa(corewar->game_param.cycles_to_die));
	g_vs->txt_srfc = TTF_RenderText_Solid(g_vs->text_font, text, g_vs->text_color[4]);
	g_vs->text = SDL_CreateTextureFromSurface(g_vs->render, g_vs->txt_srfc);
	text_height = g_vs->txt_srfc->h;
	dstrect[0] = create_rect(20, 64 * 15 + 25, g_vs->txt_srfc->w, text_height);
	SDL_RenderCopy(g_vs->render, g_vs->text, NULL, &dstrect[0]);
	text_x = g_vs->txt_srfc->w + 40;
	free_mem_font();
	free(text);
	text = ft_strjoin("cycles after start : ", ft_itoa(corewar->game_param.cycles_aft_start));
	g_vs->txt_srfc = TTF_RenderText_Solid(g_vs->text_font, text, g_vs->text_color[4]);
	g_vs->text = SDL_CreateTextureFromSurface(g_vs->render, g_vs->txt_srfc);
	dstrect[1] = create_rect(text_x, 64 * 15 + 25,
							 g_vs->txt_srfc->w, g_vs->txt_srfc->h);
	SDL_RenderCopy(g_vs->render, g_vs->text, NULL, &dstrect[1]);
	text_x += g_vs->txt_srfc->w + 20;
	free_mem_font();
	text = ft_strjoin("last live : ", ft_itoa(corewar->game_param.who_lst_live));
	g_vs->txt_srfc = TTF_RenderText_Solid(g_vs->text_font, text, g_vs->text_color[4]);
	g_vs->text = SDL_CreateTextureFromSurface(g_vs->render, g_vs->txt_srfc);
	text_height = g_vs->txt_srfc->h;
	dstrect[2] = create_rect(text_x, 64 * 15 + 25,
							 g_vs->txt_srfc->w, text_height);
	SDL_RenderCopy(g_vs->render, g_vs->text, NULL, &dstrect[2]);
	text_x += g_vs->txt_srfc->w + 20;
	free_mem_font();
	text = ft_strjoin("check count : ",
							ft_itoa(corewar->game_param.check_cnt));
	g_vs->txt_srfc = TTF_RenderText_Solid(g_vs->text_font, text, g_vs->text_color[4]);
	g_vs->text = SDL_CreateTextureFromSurface(g_vs->render, g_vs->txt_srfc);
	text_height = g_vs->txt_srfc->h;
	dstrect[3] = create_rect(text_x, 64 * 15 + 25,
							 g_vs->txt_srfc->w, text_height);
	SDL_RenderCopy(g_vs->render, g_vs->text, NULL, &dstrect[3]);
	free_mem_font();
}

void			display_objs(t_corewar *corewar, int update)
{
	char		**hex_arena;

	draw_backgroung();
	hex_arena = convert_arena(corewar);
	print_arena(hex_arena);
	display_carriages(corewar);
	display_side_menu(corewar, update);
	display_game_data(corewar);
	ft_free_strsplit(hex_arena);
}

void			visualise_arena(t_corewar *corewar, bool *quit)
{
	SDL_Event	e;
	int			stop;
	int			update;

	sort_vc(&g_vs->vc_list);
	update = -1;
	stop = 1;
	g_change = 0;
	display_objs(corewar, update);
	SDL_RenderPresent(g_vs->render);
	SDL_Delay(g_vs->speed);
	while (stop)
	{
		track_events(&update, &e, quit, &stop);
		if (update >= 0)
		{
			display_objs(corewar, update);
			SDL_RenderPresent(g_vs->render);
		}
		update = -1;
	}
}
