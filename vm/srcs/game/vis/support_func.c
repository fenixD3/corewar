

#include "vis.h"

t_vis_tools *g_vs;

int		sidemenu_pressed(int32_t y, t_corewar *crwr)
{
	int 		k;
	t_vc		*vc;
	int 		done;

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


int				prosess_press(int32_t x, int32_t y, t_corewar *crwr)
{
	int			i;
	int			j;
	int			res;

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

int			track_events(int *indx, SDL_Event *e, bool *quit, t_corewar *corewar)
{
	int		stop;

	stop = 1;
	while (SDL_PollEvent(&(*e)) != 0)
	{
		if ((*e).type == SDL_QUIT ||
			((*e).type == SDL_KEYDOWN && (*e).key.keysym.sym == SDLK_ESCAPE))
		{
			stop = 0;
			*quit = true;
		}
		if ((*e).type == SDL_MOUSEBUTTONDOWN)
			*indx = prosess_press((*e).button.x, (*e).button.y, corewar);
		else if ((*e).type == SDL_KEYDOWN)
		{
			if ((*e).key.keysym.sym == SDLK_RIGHT)
			{
				g_mode = -1;
				stop = 0;
				g_contnue = false;
			}
			if ((*e).key.keysym.sym == SDLK_RETURN)
				g_contnue = true;
		}
	}
	return (stop);
}

void			create_string(char str[100], int input, char *str_inp, char *f)
{
	int			i;

	i = 0;
	ft_sprintf(str, str_inp, f != NULL ? f : input);
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
