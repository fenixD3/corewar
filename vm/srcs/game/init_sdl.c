#include "vis.h"

//bool	init_sdl_images(void)
//{
//	bool success;
//
//	success = true;
//	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
//		success = false;
//	return (success);
//}

bool	init_font(t_vis_tools *vs)
{
	bool	success;

	success = false;
	if (TTF_Init() == -1)
		go_exit(TTF_GetError());
	else
	{
		vs->font = TTF_OpenFont("../media/eqw.TTF", 13);
		if (!vs->font)
			go_exit(TTF_GetError());
		else
			success = true;
	}
	return (success);
}

bool	init(t_vis_tools *vs)
{
	bool	success;

	success = true;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		success = false;
	else
	{
		vs->window = SDL_CreateWindow("Corewar fight", SDL_WINDOWPOS_UNDEFINED,
		                              SDL_WINDOWPOS_UNDEFINED, vs->wight, vs->height,
		                              SDL_WINDOW_SHOWN);
		if (vs->window == NULL)
			success = false;
		vs->render = SDL_CreateRenderer(vs->window, -1, 0);
	}
//	if (!init_sdl_images()) IF SOME PICTURES NEEDED
//		success = false;
	if (!init_font(vs))
		success = false;
//	if (!init_surface(vs)) IF SOME PICTURES NEEDED
		return (success);
}
