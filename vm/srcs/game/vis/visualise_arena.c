/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualise_arena.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanhand <mcanhand@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 21:32:59 by mcanhand          #+#    #+#             */
/*   Updated: 2020/05/12 21:33:16 by mcanhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"
#include "vis_errors.h"

t_vis_tools *g_vs;

void			draw_backgroung(void)
{
	SDL_Rect	rectangle;
	SDL_Rect	sm_rectangle;

	SDL_SetRenderDrawColor(g_vs->render, 244, 242, 238, SDL_ALPHA_OPAQUE);
	rectangle = create_rect(0, 0, g_vs->wight, g_vs->height);
	SDL_RenderFillRect(g_vs->render, &rectangle);
	SDL_SetRenderDrawColor(g_vs->render, 0, 0, 0, SDL_ALPHA_OPAQUE);
	sm_rectangle = create_rect(5, 10, 64 * 24 + 5, 64 * 15 + 5);
	SDL_RenderFillRect(g_vs->render, &sm_rectangle);
	SDL_SetRenderDrawColor(g_vs->render, 0, 0, 0, SDL_ALPHA_OPAQUE);
	sm_rectangle = create_rect(5, 980, 680, g_vs->height - 990);
	SDL_RenderFillRect(g_vs->render, &sm_rectangle);
	SDL_SetRenderDrawColor(g_vs->render, 0, 0, 0, SDL_ALPHA_OPAQUE);
	sm_rectangle = create_rect(690, 980, 855, g_vs->height - 990);
	SDL_RenderFillRect(g_vs->render, &sm_rectangle);
	SDL_SetRenderDrawColor(g_vs->render, 0, 0, 0, SDL_ALPHA_OPAQUE);
	sm_rectangle = create_rect(15 + 64 * 24, 20 + 64 * 15,
							g_vs->wight - 20 - 64 * 24, 45);
	SDL_RenderFillRect(g_vs->render, &sm_rectangle);
	SDL_SetRenderDrawColor(g_vs->render, 0, 0, 0, SDL_ALPHA_OPAQUE);
	sm_rectangle = create_rect(15 + 64 * 24, 10,
					g_vs->wight - 20 - 64 * 24, 5 + 64 * 15);
	SDL_RenderFillRect(g_vs->render, &sm_rectangle);
}

char			**convert_arena(t_corewar *corewar)
{
	int			i;
	int			j;
	int			c;
	char		**res;

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
			res[i % 64][j++] = "0123456789abcdef"[corewar->arena[c++] & 0x0F];
			res[i % 64][j++] = ' ';
			res[i % 64][j++] = ' ';
		}
		if (j >= (64 * 3 + 63))
			res[i++ % 64][64 * 4 - 2] = '\0';
	}
	res[64] = NULL;
	return (res);
}

void display_objs(t_corewar *corewar, int update, t_carriages *carriag)
{
	char		**hex_arena;
	t_vc		*vc;
	int 		num_on_menu;

	vc = g_vs->vc_list;
	draw_backgroung();
	hex_arena = convert_arena(corewar);
	print_arena(hex_arena);
	display_carriages(corewar->arena, carriag ? carriag : corewar->carriages);
	num_on_menu = display_side_menu(corewar, update, vc);
	higlight_cells(num_on_menu, vc, corewar, update);
	display_game_data(corewar);
	ft_free_strsplit(hex_arena);
}

void			show_winer(t_champion *champ)
{
	SDL_Rect	rectangle;
	SDL_Rect	sm_rectangle;
	char		string[100];
	SDL_Rect	dstrect;

	create_string(string, champ->num, "Contestant %d, \n", NULL);
	create_string(&string[14], 0, "\"%s\", has won !\n",
											champ->file.header.prog_name);
	SDL_SetRenderDrawColor(g_vs->render, 244, 242, 238, SDL_ALPHA_OPAQUE);
	rectangle = create_rect(0, 0, g_vs->wight, g_vs->height);
	SDL_RenderFillRect(g_vs->render, &rectangle);
	SDL_SetRenderDrawColor(g_vs->render, 0, 0, 0, SDL_ALPHA_OPAQUE);
	sm_rectangle = create_rect(5, 10, g_vs->wight - 10, g_vs->height - 20);
	SDL_RenderFillRect(g_vs->render, &sm_rectangle);
	g_vs->txt_srfc = TTF_RenderText_Solid(g_vs->font, string,
									g_vs->text_color[champ->num - 1]);
	g_vs->text = SDL_CreateTextureFromSurface(g_vs->render, g_vs->txt_srfc);
	dstrect = create_rect(g_vs->wight / 2 - g_vs->txt_srfc->w,
			g_vs->height / 2, g_vs->txt_srfc->w, g_vs->txt_srfc->h);
	SDL_RenderCopy(g_vs->render, g_vs->text, NULL, &dstrect);
	free_mem_font();
	SDL_RenderPresent(g_vs->render);
	SDL_Delay(4000);
	exit(0);
}

void visualise_arena(t_corewar *corewar, bool *quit, t_carriages *carriag)
{
	SDL_Event	e;
	int			stop;
	int			update;

	if (g_mode == -100)
		show_winer(corewar->champs);
	sort_vc(&g_vs->vc_list);
	update = -1;
	g_change = 0;
	display_objs(corewar, update, carriag);
	SDL_RenderPresent(g_vs->render);
	SDL_Delay(g_vs->speed);
	stop = track_events(&update, &e, quit, corewar);
	while (stop && !g_contnue)
	{
		stop = track_events(&update, &e, quit, corewar);
		if (update >= 0)
		{
			display_objs(corewar, update, carriag);
			SDL_RenderPresent(g_vs->render);
		}
		update = -1;
	}
}
