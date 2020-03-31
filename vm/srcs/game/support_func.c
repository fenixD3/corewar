
#include "vis.h"

SDL_Color			init_color(int r, int g, int b, int a)
{
	SDL_Color color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = 0;
	return (color);
}

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
	SDL_FreeSurface(vs->txt_srfc);
	vs->txt_srfc = NULL;
	DESTROY_TXTR(vs->text);
}
