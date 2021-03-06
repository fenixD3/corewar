/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arena.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanhand <mcanhand@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 21:31:48 by mcanhand          #+#    #+#             */
/*   Updated: 2020/05/12 21:32:01 by mcanhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"
#include "op.h"

t_vis_tools *g_vs;

void			print_arena(char **arena)
{
	int			text_width;
	int			text_height;
	SDL_Rect	dstrect;
	int			i;

	i = 0;
	while (i < 64)
	{
		g_vs->txt_srfc = TTF_RenderText_Solid(g_vs->text_font,
								arena[i], g_vs->text_color[4]);
		g_vs->text = SDL_CreateTextureFromSurface(g_vs->render,
													g_vs->txt_srfc);
		text_width = g_vs->txt_srfc->w;
		text_height = g_vs->txt_srfc->h;
		dstrect = create_rect(10,
			15 + i * (text_height + 6), text_width, text_height);
		SDL_RenderCopy(g_vs->render, g_vs->text, NULL, &dstrect);
		free_mem_font();
		i++;
	}
}
