/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanhand <mcanhand@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 21:29:11 by mcanhand          #+#    #+#             */
/*   Updated: 2020/05/12 21:29:42 by mcanhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

t_vis_tools *g_vs;

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
	if (!init_font())
		success = false;
	return (success);
}
