/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanhand <mcanhand@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 21:32:08 by mcanhand          #+#    #+#             */
/*   Updated: 2020/05/12 21:32:19 by mcanhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

t_vis_tools *g_vs;

void			create_string(char str[100], int input, char *str_inp, char *f)
{
	int			i;

	i = 0;
	if (f)
		ft_sprintf(str, str_inp, f);
	else
		ft_sprintf(str, str_inp, input);
	while (str[i] != '\n')
		i++;
	str[i] = '\0';
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

void			free_mem_font(void)
{
	SDL_FreeSurface(g_vs->txt_srfc);
	g_vs->txt_srfc = NULL;
	DESTROY_TXTR(g_vs->text);
}

void			ft_free_strsplit(char **str_array)
{
	int			i;

	if (str_array)
	{
		i = 0;
		while (str_array[i] != NULL)
		{
			free(str_array[i]);
			i++;
		}
		free(str_array);
	}
}
