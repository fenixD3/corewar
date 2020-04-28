
#include "vis.h"

t_vis_tools *g_vs;

SDL_Color			init_color(int r, int g, int b, int a)
{
	SDL_Color color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = 0;
	return (color);
}

int		prosess_press(int32_t x, int32_t y)
{
	int			i;
	int			j;

	i = 0;
	while (i < MEM_SIZE)
	{
		j = 0;
		while (j < 64)
		{
			if (10 + j * 24 < x && x < 24 + j * 24 && 15 +
				(i / 64) * 15 < y && y < 25 + (i / 64) * 15)
				return (g_mode = i);
			if (x > 26 + 64 * 24 && x < 26 + 64 * 24 +
				g_vs->wight - 42 - 64 * 24 && y > 21 +
						63 * i && y < 21 + 51 + 63 * i)
			{
				printf("carrage %d\n", i);
				return (y + 4100);
			}
			j++;
			i++;
		}
	}
	return (-1);
}

void	track_events(int *indx, SDL_Event *e, bool *quit, int *stop)
{
	t_vc		*vc;

	while (SDL_PollEvent(&(*e)) != 0)
	{
		if ((*e).type == SDL_QUIT)
		{
			*stop = 0;
			*quit = true;
		}
		else if ((*e).type == SDL_MOUSEBUTTONDOWN)
			*indx = prosess_press((*e).button.x, (*e).button.y);
		else if ((*e).type == SDL_KEYDOWN)
		{
			if ((*e).key.keysym.sym == SDLK_ESCAPE)
			{
				*stop = 0;
				*quit = true;
			}
			if ((*e).key.keysym.sym == SDLK_RIGHT)
			{
				*stop = 0;
				g_mode = -1;
				vc = g_vs->vc_list;
				while (vc != NULL)
				{
					vc->is_open = false;
					vc = vc->next;
				}
			}
		}
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

void free_mem_font(void)
{
	SDL_FreeSurface(g_vs->txt_srfc);
	g_vs->txt_srfc = NULL;
	DESTROY_TXTR(g_vs->text);
}
