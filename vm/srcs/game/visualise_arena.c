
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
	SDL_SetRenderDrawColor(vs->render, 40, 39, 36, SDL_ALPHA_OPAQUE);
	sm_rectangle = create_rect(5, 10, 64 * 23 + 5,
												64 * 15 + 5);
	SDL_RenderFillRect(vs->render, &sm_rectangle);
	SDL_SetRenderDrawColor(vs->render, 40, 39, 36, SDL_ALPHA_OPAQUE);
	stat_window = create_rect(15 + 64 * 23, 10,
			vs->wight - 30 + 64 * 23, 5 + 64 * 15);
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

void			display_carriages(t_arena *arena, t_vis_tools *vs)
{
	SDL_Rect	carrg[MEM_SIZE * 2];
	int			i;
	int			j;
	int			c;
	t_cells		*cell;

	c = 0;
	cell = arena->cell;
	i = 0;
	while (i < MEM_SIZE && cell != NULL)
	{
		j = 0;
		while (j < 64)
		{
			if (cell->carriages != NULL)
			{
				SDL_SetRenderDrawColor(vs->render, cell->color.r, cell->color.g,
				                       cell->color.b, 0);
				carrg[c] = create_rect(8 + j * 23,
						13 + (i / 64) * 15, 16, 14);
				SDL_RenderFillRect(vs->render, &carrg[c++]);
				vs->txt_srfc = TTF_RenderText_Solid(vs->font, cell->code,
						init_color(40, 39, 36, SDL_ALPHA_OPAQUE));
				vs->text = SDL_CreateTextureFromSurface(vs->render,
																vs->txt_srfc);
				carrg[c] = create_rect(10 + j * 23, 15 + (i / 64) *
				(vs->txt_srfc->h + 2), vs->txt_srfc->w, vs->txt_srfc->h);
				SDL_RenderCopy(vs->render, vs->text, NULL, &carrg[c++]);
				free_mem_font(vs);
			}
			j++;
			i++;
			cell = cell->next;
		}
	}
}

void			display_objs(t_vis_tools *vs, t_arena *arena)
{
	draw_backgroung(vs);
	print_arena(vs, arena);
	display_carriages(arena, vs);
//	ft_free_strsplit();
}

void			cell_fill(t_cells *cell, t_vis_tools *vs, t_arena *arena, int i)
{
	cell->color = (i - (i / arena->step) * arena->step
	               < arena->prog_size[i / arena->step])
	              ? vs->text_color[i / arena->step] : vs->text_color[4];
}

void			arena_features_prep(t_corewar *corewar, t_arena *arena, t_vis_tools *vs)
{
	t_champion  *champs;
	int			i;
	t_cells		*cell;

	i = 0;
	cell = NULL;
	arena->chmp_num = 0;
	champs = corewar->champs;
	while (champs != NULL)
	{
		arena->prog_size[arena->chmp_num] = champs->file.header.prog_size;
		champs = champs->next;
		arena->chmp_num++;
	}
	while (arena->chmp_num + i < 4)
		arena->prog_size[arena->chmp_num + i++] = 0;
	arena->step = MEM_SIZE / arena->chmp_num;
	i = 0;
	while (i < MEM_SIZE)
	{
		cell = add_cell(i, corewar);
		cell_fill(cell, vs, arena, i++);
		save_cell(&(arena->cell), cell);
	}
}

void			visualise_arena(t_corewar *corewar, t_vis_tools *vs, bool *quit, int i)
{
	SDL_Event	e;
	t_arena		*arena;

	if (!(arena = (t_arena*)ml_malloc(sizeof(t_arena), ML_ARENA)))
		go_exit(ERR_ML_CELL);
	arena->cell = NULL;
	arena_features_prep(corewar, arena, vs);
	display_objs(vs, arena);
	SDL_RenderPresent(vs->render);
	SDL_Delay(vs->speed);
	track_events(vs, &e, quit);
}
