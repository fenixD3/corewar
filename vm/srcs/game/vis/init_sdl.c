
#include "vis.h"
t_vis_tools *g_vs;

//bool	init_sdl_images(void)
//{
//	bool success;
//
//	success = true;
//	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
//		success = false;
//	return (success);
//}

bool		init_font(void)
{
	bool	success;

	success = false;
	if (TTF_Init() == -1)
		go_exit(TTF_GetError());
	else
	{
		g_vs->font = TTF_OpenFont("../media/Anonymous.ttf", 29);
		if (!g_vs->font)
			go_exit(TTF_GetError());
		else
			success = true;
		g_vs->text_font = TTF_OpenFont("../media/Anonymous.ttf", 9);
		if (!g_vs->text_font)
			go_exit(TTF_GetError());
		else
			success = true;
	}
	return (success);
}

bool		init(void)
{
	bool	success;

	success = true;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		success = false;
	else
	{
		g_vs->window = SDL_CreateWindow("Corewar fight",
					SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
					g_vs->wight, g_vs->height, SDL_WINDOW_SHOWN);
		if (g_vs->window == NULL)
			success = false;
		SDL_SetWindowPosition(g_vs->window, 10, 10);
		g_vs->render = SDL_CreateRenderer(g_vs->window, -1, 0);
	}
//	if (!init_sdl_images()) IF SOME PICTURES NEEDED
//		success = false;
	if (!init_font())
		success = false;
//	if (!init_surface(g_vs)) IF SOME PICTURES NEEDED
	return (success);
}

