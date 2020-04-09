
#include "vis.h"
#include "vis_errors.h"

void			draw_backgroung(t_vis_tools *vs)
{
	SDL_Rect rectangle;
	SDL_Rect sm_rectangle;
	SDL_Rect stat_window;

	SDL_SetRenderDrawColor(vs->render, 244, 242, 238,
												SDL_ALPHA_OPAQUE);
	rectangle = create_rect(0, 0, vs->wight, vs->height);
	SDL_RenderFillRect(vs->render, &rectangle);
//	SDL_SetRenderDrawColor(vs->render, 40, 39, 36, SDL_ALPHA_OPAQUE);
	SDL_SetRenderDrawColor(vs->render, 0, 0, 0, SDL_ALPHA_OPAQUE);
	sm_rectangle = create_rect(5, 10, 64 * 24 + 5,
												64 * 15 + 5);
	SDL_RenderFillRect(vs->render, &sm_rectangle);
	SDL_SetRenderDrawColor(vs->render, 0, 0, 0, SDL_ALPHA_OPAQUE);

//	SDL_SetRenderDrawColor(vs->render, 40, 39, 36, SDL_ALPHA_OPAQUE);
	stat_window = create_rect(15 + 64 * 24, 10, vs->wight - 20 - 64 * 24, 5 + 64 * 15);
	SDL_RenderFillRect(vs->render, &stat_window);
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

void			display_objs(t_vis_tools *vs, t_corewar *corewar)
{
	char		**hex_arena;

	draw_backgroung(vs);
	hex_arena = convert_arena(corewar);
	print_arena(vs, hex_arena);
	display_carriages(vs, corewar);
	display_side_menu(vs, corewar);
	ft_free_strsplit(hex_arena);
}

void			visualise_arena(t_corewar *corewar, t_vis_tools *vs, bool *quit)
{
	SDL_Event	e;
	int			stop;

	stop = 1;
	g_change = 0;
	display_objs(vs, corewar);
	SDL_RenderPresent(vs->render);
//	SDL_Delay(vs->speed);
	while (stop)
		track_events(vs, &e, quit, &stop);
//	corewar->champs->
}


//	champs = corewar->champs;
//	if (!(arena = (t_arena*)ml_malloc(sizeof(t_arena), ML_ARENA)))
//		go_exit(ERR_ML_CELL);
//	arena->chmp_num = 0;
//	while (champs != NULL)
//	{
//		arena->prog_size[arena->chmp_num] = champs->file.header.prog_size;
//		champs = champs->next;
//		arena->chmp_num++;
//	}
//	while (arena->chmp_num + i < 4)
//		arena->prog_size[arena->chmp_num + i++] = 0;
//	arena->step = MEM_SIZE / arena->chmp_num;


//void			cell_fill(t_cells *cell, t_vis_tools *vs, t_arena *arena, int i)
//{
//	cell->color = (i - (i / arena->step) * arena->step
//	               < arena->prog_size[i / arena->step])
//	              ? vs->text_color[i / arena->step] : vs->text_color[4];
//}