/*

#include "vis.h"
#include "vis_errors.h"

void			draw_backgroung(t_vis_tools *vs)
{
	SDL_Rect rectangle;
	SDL_Rect sm_rectangle;

	SDL_SetRenderDrawColor(vs->render, 244, 242, 238,
												SDL_ALPHA_OPAQUE);
	rectangle = create_rect(0, 0, vs->wight, vs->height);
	SDL_RenderFillRect(vs->render, &rectangle);
	SDL_SetRenderDrawColor(vs->render, 0, 0, 0, SDL_ALPHA_OPAQUE);
	sm_rectangle = create_rect(5, 10, 64 * 24 + 5,
												64 * 15 + 5);
	SDL_RenderFillRect(vs->render, &sm_rectangle);

	SDL_SetRenderDrawColor(vs->render, 0, 0, 0, SDL_ALPHA_OPAQUE);
	sm_rectangle = create_rect(5, 64 * 15 + 20,
			64 * 24 + 5, vs->height - (64 * 15 + 20) - 10);
	SDL_RenderFillRect(vs->render, &sm_rectangle);
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

char		**convert_arena(t_corewar *corewar)
{
	int     i;
	int     j;
	char    **res;

	i = 0;
	if (!(res = (char**)malloc(sizeof(char*) * MEM_SIZE + 1)))
		go_exit("AAAAA");
	while (i < MEM_SIZE)
	{
		if (!(res[i] = (char*)malloc(sizeof(char) * 3)))
			go_exit(ERR_ML_CELL);
		res[i][0] = "0123456789ABCDEF"[corewar->arena[i] >> 4];
		res[i][1] = "0123456789ABCDEF"[corewar->arena[i] & 0x0F];
		res[i++][2] = '\0';
	}
	res[MEM_SIZE] = NULL;
	return (res);
}

void			display_game_data(t_vis_tools *vs, t_corewar *corewar)
{
	char		*text;
	int			text_x;
	int			text_height;
	SDL_Rect	dstrect[4];

	text = ft_strjoin("cycles to die : ", ft_itoa(corewar->game_param.cycles_to_die));
	vs->txt_srfc = TTF_RenderText_Solid(vs->text_font, text, vs->text_color[4]);
	vs->text = SDL_CreateTextureFromSurface(vs->render, vs->txt_srfc);
	text_height = vs->txt_srfc->h;
	dstrect[0] = create_rect(20, 64 * 15 + 25, vs->txt_srfc->w, text_height);
	SDL_RenderCopy(vs->render, vs->text, NULL, &dstrect[0]);
	text_x = vs->txt_srfc->w + 40;
	free_mem_font(vs);
	free(text);

	text = ft_strjoin("cycles after start : ", ft_itoa(corewar->game_param.cycles_aft_start));
	vs->txt_srfc = TTF_RenderText_Solid(vs->text_font, text, vs->text_color[4]);
	vs->text = SDL_CreateTextureFromSurface(vs->render, vs->txt_srfc);
	dstrect[1] = create_rect(text_x, 64 * 15 + 25,
	                         vs->txt_srfc->w, vs->txt_srfc->h);
	SDL_RenderCopy(vs->render, vs->text, NULL, &dstrect[1]);
	text_x = text_x + vs->txt_srfc->w + 20;

	free_mem_font(vs);
	text = ft_strjoin("last live : ", ft_itoa(corewar->game_param.who_lst_live));
	vs->txt_srfc = TTF_RenderText_Solid(vs->text_font, text, vs->text_color[4]);
	vs->text = SDL_CreateTextureFromSurface(vs->render, vs->txt_srfc);
	text_height = vs->txt_srfc->h;
	dstrect[2] = create_rect(text_x, 64 * 15 + 25,
	                         vs->txt_srfc->w, text_height);
	SDL_RenderCopy(vs->render, vs->text, NULL, &dstrect[2]);
	free_mem_font(vs);

//	corewar->game_param.who_lst_live
//	corewar->game_param.cycles_aft_start
//	corewar->game_param.check_cnt

}

void			display_objs(t_vis_tools *vs, t_corewar *corewar, int update)
{
	char		**hex_arena;

	draw_backgroung(vs);
	hex_arena = convert_arena(corewar);
	print_arena(vs, hex_arena);
	display_carriages(vs, corewar);
	display_side_menu(corewar, update, vs);
	display_game_data(vs, corewar);
	ft_free_strsplit(hex_arena);
}

void			visualise_arena(t_corewar *corewar, t_vis_tools *vs, bool *quit)
{
	SDL_Event	e;
	int			stop;
	int			update;

	update = -1;
	stop = 1;
	g_change = 0;
	display_objs(vs, corewar, update);
	SDL_RenderPresent(vs->render);
	SDL_Delay(vs->speed);
	while (stop)
	{
		track_events(&update, &e, quit, &stop);
		if (update > 0)
		{
			display_objs(vs, corewar, update);
			SDL_RenderPresent(vs->render);
		}
		update = -1;
	}
}
*/
