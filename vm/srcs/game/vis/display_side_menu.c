#include "vis.h"

t_vis_tools *vs;

void			draw_frame(SDL_Color color, int i, int extndd)
{
	SDL_Rect	rectangle;
	int			rec_h;

	rec_h = extndd ? 162 : 63;
	SDL_SetRenderDrawColor(vs->render, color.r, color.g, color.b,
	                       SDL_ALPHA_OPAQUE);
	rectangle = create_rect(20 + 64 * 24, 15 + rec_h * i,
	                        vs->wight - 30 - 64 * 24, rec_h);
	SDL_RenderFillRect(vs->render, &rectangle);
}

int				display_text(char *text, int x, int y)
{
	int			text_width;
	int			text_height;
	SDL_Rect	dstrect;

	vs->txt_srfc = TTF_RenderText_Solid(vs->text_font, text,
												vs->text_color[4]);
	vs->text = SDL_CreateTextureFromSurface(vs->render, vs->txt_srfc);
	text_width = vs->txt_srfc->w;
	text_height = vs->txt_srfc->h;
	dstrect = create_rect(x ? x : 30 + 64 * 24, y, text_width, text_height);
	SDL_RenderCopy(vs->render, vs->text, NULL, &dstrect);
	free_mem_font();
	free(text);
	return (text_height);
}

void			display_registers(int i, int text_height, t_carriages *carriages, int extndd)
{
	int			j;
	char		*text;

	j = 0;
	if (extndd)
	{
		while (j < 8)
		{
			text = ft_strjoin("1: ", ft_itoa(carriages->reg[j]));
			display_text(text, 0,
						 30 + 3 * (j + 1) + text_height * (j + 3) + 126 * i);
			j++;
		}
		j = 0;
		while (j < 8)
		{
			text = ft_strjoin("1: ", ft_itoa(carriages->reg[8 + j]));
			display_text(text, 130 + 64 * 24,
					30 + 3 * (j + 1) + text_height * (j + 3) + 126 * i);
			j++;
		}
	}
}

void			fill_frame(int i, t_carriages *carriages, int extndd)
{
	SDL_Rect	rectangle;
	char		*text;
	int			text_height;

	SDL_SetRenderDrawColor(vs->render, 0, 0, 0, SDL_ALPHA_OPAQUE);
	rectangle = create_rect(26 + 64 * 24, 21 + (extndd ? 158 : 63) * i,
	       vs->wight - 42 - 64 * 24, (extndd ? 146: 51));
	SDL_RenderFillRect(vs->render, &rectangle);
	text = ft_strjoin("cycles before execution : ",
			ft_itoa(carriages->cycle_op));
	text_height = display_text(text, 0, 24 + (extndd ? 158 : 63) * i);
	text = ft_strjoin("operation code : ",
			g_op[carriages->op_code - 1].name);
	display_text(text, 0, 24 + text_height + 3 + (extndd ? 158 : 63) * i);
	text = ft_strjoin("previous live execution : ",
			ft_itoa(carriages->cycle_when_live));
	display_text(text, 0, 30 + text_height * 2 + (extndd ? 158 : 63) * i);
	display_registers(i, text_height, carriages, extndd);
}

void display_side_menu(t_corewar *crrw, int ind)
{
	SDL_Color	color;
	int			i;
	SDL_Rect	stat_window;
	t_carriages	*carriages;

	i = 0;
	SDL_SetRenderDrawColor(vs->render, 0, 0, 0, SDL_ALPHA_OPAQUE);
	stat_window = create_rect(15 + 64 * 24, 10,
			vs->wight - 20 - 64 * 24, 5 + 64 * 15);
	SDL_RenderFillRect(vs->render, &stat_window);
	carriages = vs->vc_list->carriage;
	while (carriages != NULL && ((ind < 0) ? i < 15 : i < 6))
	{
		color = (carriages->reg[0] < 0 && carriages->reg[0] > -5) ?
		        vs->text_color[-(carriages->reg[0]) - 1] : vs->text_color[4];
		if (ind < 0 || (ind >= 0 && carriages->op_pos == &(crrw->arena[ind])))
		{
			draw_frame(color, i, (ind < 0) ? 0 : 1);
			fill_frame(i++, carriages, (ind < 0) ? 0 : 1);
		}
		carriages = carriages->next;
	}
}
