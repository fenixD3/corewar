/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanhand <mcanhand@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 22:37:28 by mcanhand          #+#    #+#             */
/*   Updated: 2020/05/12 22:37:43 by mcanhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

t_vis_tools *g_vs;

int				sidemenu_pressed(int32_t y, t_corewar *crwr)
{
	int			k;
	t_vc		*vc;
	int			done;

	done = 0;
	k = 15;
	vc = g_vs->vc_list;
	while (vc != NULL && k < 900 && g_mode >= 0)
	{
		if (vc->carriage->op_pos == &(crwr->arena[g_mode]))
		{
			if (!done && (y > k && ((vc->is_open == true) ?
									y < k + 162 : y < k + 54)))
			{
				done = 1;
				k += (vc->is_open == true) ? 63 : 162;
			}
			else
				k += vc->is_open ? 162 : 63;
		}
		vc = vc->next;
	}
	g_mode = (!done) ? -1 : g_mode;
	return (y + 4100);
}

int				catch(SDL_Event *e, t_corewar *crwr)
{
	int			i;
	int			j;
	int32_t		x;
	int32_t		y;

	x = (*e).button.x;
	y = (*e).button.y;
	i = 0;
	if (x > 26 + 64 * 24 && x < g_vs->wight - 16 && y > 21 && y < 1000)
		return (sidemenu_pressed(y, crwr));
	while (i < MEM_SIZE)
	{
		j = 0;
		while (j < 64)
		{
			if (10 + j * 24 < x && x < 24 + j * 24 && 15 +
				(i / 64) * 15 < y && y < 25 + (i / 64) * 15)
				return (g_mode = i);
			j++;
			i++;
		}
	}
	return (g_mode = -1);
}

int				track_events(int *ind, SDL_Event *e, bool *quit,
								t_corewar *corewar)
{
	int			stop;

	stop = 1;
	while (SDL_PollEvent(&(*e)) != 0)
	{
		if ((*e).type == SDL_QUIT ||
			((*e).type == SDL_KEYDOWN && (*e).key.keysym.sym == SDLK_ESCAPE))
		{
			stop = 0;
			*quit = true;
		}
		else if ((*e).type == SDL_KEYDOWN || (*e).type == SDL_MOUSEBUTTONDOWN)
		{
			if ((*e).key.keysym.sym == SDLK_RIGHT)
			{
				g_mode = -1;
				stop = 0;
				g_contnue = false;
			}
			if ((*e).key.keysym.sym == SDLK_RETURN)
				g_contnue = true;
			*ind = (*e).type == SDL_MOUSEBUTTONDOWN ? catch(e, corewar) : *ind;
		}
	}
	return (stop);
}
