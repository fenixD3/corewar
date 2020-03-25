
#include "vis.h"
#include "vis_errors.h"

void	track_events(t_vis_tools *vs, SDL_Event *e, bool *quit)
{
	while (SDL_PollEvent(&(*e)) != 0)
	{
		if ((*e).type == SDL_QUIT)
			*quit = true;
	}
}

SDL_Rect		create_rect(int x, int y, int text_w, int text_h)
{
	SDL_Rect	dstrect;

	dstrect.x = x;
	dstrect.y = y;
	dstrect.w = text_w;
	dstrect.h = text_h;
	return (dstrect);
}

void			free_mem_font(t_vis_tools *vs)
{
	SDL_FreeSurface(vs->text_surface);
	vs->text_surface = NULL;
	DESTROY_TXTR(vs->text);
}

void			print_arena(char **arena, t_vis_tools *vs)
{
	int			text_width;
	int			text_height;
	SDL_Rect	dstrect;
	int			i;

	i = 0;
	while (i < 64)
	{
		vs->text_surface = TTF_RenderText_Solid(vs->font,
							arena[i], vs->text_color);
		vs->text = SDL_CreateTextureFromSurface(vs->render, vs->text_surface);
		text_width = vs->text_surface->w;
		text_height = vs->text_surface->h;
		dstrect = create_rect(25,
						15 + i * text_height, text_width, text_height);
		SDL_RenderCopy(vs->render, vs->text, NULL, &dstrect);
		i++;
		free_mem_font(vs);
	}
}

void			draw_backgroung(t_corewar *corewar, t_vis_tools *vs)
{
	SDL_Rect rectangle;
	SDL_Rect sm_rectangle;

	SDL_RenderClear(vs->render);
	SDL_SetRenderDrawColor(vs->render, 142, 178, 172, SDL_ALPHA_OPAQUE);
	rectangle.x = 0;
	rectangle.y = 0;
	rectangle.w = 1140;
	rectangle.h = 880;
	SDL_RenderFillRect(vs->render, &rectangle);
	SDL_SetRenderDrawColor(vs->render, 254, 253, 233, SDL_ALPHA_OPAQUE);
	sm_rectangle.x = 20;
	sm_rectangle.y = 10;
	sm_rectangle.w = 1100;
	sm_rectangle.h = 860;
	SDL_RenderFillRect(vs->render, &sm_rectangle);
}


char	**convert_arena(unsigned char *arena)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	if (!(res = (char**)malloc(sizeof(char*) * 64)))
		go_exit(ERR_ML_ARENA);
	while (i < MEM_SIZE)
	{
		res[i % 64] = (char*)malloc(sizeof(char) * 64 * 3);
		j = 0;
		while (j < 64 * 3)
		{
			res[i % 64][j++] = "0123456789ABCDEF"[arena[i] >> 4];
			res[i % 64][j++] = "0123456789ABCDEF"[arena[i] & 0x0F];
			res[i % 64][j++] = ' ';
		}
		i++;
	}
	return (res);
}


void	ft_free_strsplit(char **str_array)
{
	int i;

	if (str_array)
	{
		i = 0;
		while (str_array[i])
		{
			ft_strdel(str_array + i);
			i++;
		}
		free(str_array);
	}
}

void    display_objs(t_corewar *corewar, t_vis_tools *vs)
{
	char **hex_arena;

	draw_backgroung(corewar, vs);
	hex_arena = convert_arena(corewar->arena);
	print_arena(hex_arena, vs);
//	ft_free_strsplit(hex_arena);
}

void	visualise_arena(t_corewar *corewar, t_vis_tools *vs, bool *quit)
{
	SDL_Event e;

	display_objs(corewar, vs);
	SDL_RenderPresent(vs->render);
	SDL_Delay(vs->speed);
	track_events(vs, &e, quit);
}
