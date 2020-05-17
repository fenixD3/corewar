/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_side_menu.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanhand <mcanhand@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 21:31:17 by mcanhand          #+#    #+#             */
/*   Updated: 2020/05/12 21:31:33 by mcanhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

t_vis_tools *g_vs;

void		more(void)
{
	SDL_Rect			dstrect;

	g_vs->txt_srfc = TTF_RenderText_Solid(g_vs->text_font, "And more...",
			g_vs->text_color[4]);
	g_vs->text = SDL_CreateTextureFromSurface(g_vs->render, g_vs->txt_srfc);
	dstrect = create_rect(89 + 64 * 24, 64 * 15 + 3,
			g_vs->txt_srfc->w, g_vs->txt_srfc->h);
	SDL_RenderCopy(g_vs->render, g_vs->text, NULL, &dstrect);
	free_mem_font();
}

void		if_open(int i, int *done, int ind, t_vc *vc)
{
	if (!*done && ind - 4100 > i && ind - 4100 < i + (vc->is_open ? 162 : 54))
	{
		vc->is_open = !vc->is_open;
		*done = 1;
	}
}

void		display_side_menu(t_corewar *crwr, int ind, t_vc *vc,
													int *num_on_menu)
{
	int		i;
	int		done;

	*num_on_menu = 0;
	i = 15;
	done = 0;
	while (vc != NULL && i < 900)
	{
		if ((i > 800 && vc->is_open) || (i > 800 && !vc->is_open &&
						!done && ind - 4100 > i && ind - 4100 < i + 54))
		{
			i += 100;
			continue ;
		}
		else if (ind < 0 || (ind >= 4100 && g_mode < 0) || (ind >= 4100
		&& g_mode >= 0 && vc->carriage->op_pos == &(crwr->arena[g_mode]))
		|| (ind >= 0 && vc->carriage->op_pos == &(crwr->arena[ind])))
		{
			if_open(i, &done, ind, vc);
			draw_frame(vc, &i, vc->is_open, crwr);
			(*num_on_menu)++;
		}
		vc = vc->next;
	}
	vc != NULL ? more() : 0;
}
