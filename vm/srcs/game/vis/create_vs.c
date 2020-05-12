/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_vs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanhand <mcanhand@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 21:05:52 by mcanhand          #+#    #+#             */
/*   Updated: 2020/05/12 21:17:44 by romancher        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"
#include "vis_errors.h"

t_vis_tools *g_vs;

SDL_Color			init_color(int r, int g, int b, int a)
{
	SDL_Color		color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = 0;
	return (color);
}

void				create_vs(void)
{
	if (!(g_vs = (t_vis_tools*)ml_malloc(sizeof(t_vis_tools), ML_VS)))
		go_exit(ERR_CREATE_VS);
	g_vs->wight = 1780;
	g_vs->height = 1035;
	g_vs->window = NULL;
	g_vs->render = NULL;
	g_vs->font = NULL;
	g_vs->text_color[0] = init_color(225, 0, 0, 0);
	g_vs->text_color[1] = init_color(0, 127, 225, 0);
	g_vs->text_color[2] = init_color(0, 128, 0, 0);
	g_vs->text_color[3] = init_color(225, 225, 0, 0);
	g_vs->text_color[4] = init_color(128, 128, 128, 0);
	g_vs->text_color[5] = init_color(0, 0, 0, 0);
	g_vs->vc_list = NULL;
	g_vs->speed = 1;
}
