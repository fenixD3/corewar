#include "vis.h"

void			draw_frame(t_vis_tools *vs, SDL_Color color, int i, int extndd)
{
	SDL_Rect	rectangle;
	int			rec_h;

	rec_h = extndd ? 158 : 63;
	SDL_SetRenderDrawColor(vs->render, color.r, color.g, color.b,
	                       SDL_ALPHA_OPAQUE);
	rectangle = create_rect(20 + 64 * 24, 15 + rec_h * i,
	                        vs->wight - 30 - 64 * 24, rec_h);
	SDL_RenderFillRect(vs->render, &rectangle);
}

int				display_text(char *text, t_vis_tools *vs, int y)
{
	int			text_width;
	int			text_height;
	SDL_Rect	dstrect;

	vs->txt_srfc = TTF_RenderText_Solid(vs->text_font, text,
												vs->text_color[4]);
	vs->text = SDL_CreateTextureFromSurface(vs->render, vs->txt_srfc);
	text_width = vs->txt_srfc->w;
	text_height = vs->txt_srfc->h;
	dstrect = create_rect(30 + 64 * 24, y, text_width, text_height);
	SDL_RenderCopy(vs->render, vs->text, NULL, &dstrect);
	free_mem_font(vs);
	free(text);
	return (text_height);
}

void			registers(t_vis_tools *vs, int i, t_carriages *carriages, int extndd)
{

}

void			fill_frame(t_vis_tools *vs, int i, t_carriages *carriages, int extndd)
{
	SDL_Rect	rectangle;
	char		*text;
	int			text_height;
	int			j;

	j = 0;
	SDL_SetRenderDrawColor(vs->render, 0, 0, 0, SDL_ALPHA_OPAQUE);
	rectangle = create_rect(26 + 64 * 24, 21 + (extndd ? 158 : 63) * i,
	       vs->wight - 42 - 64 * 24, (extndd ? 146: 51));
	SDL_RenderFillRect(vs->render, &rectangle);
	text = ft_strjoin("cycles before execution : ",
			ft_itoa(carriages->cycle_op));
	text_height = display_text(text, vs, 24 + (extndd ? 158 : 63) * i);
	text = ft_strjoin("operation code : ", ft_itoa(carriages->op_code));
	display_text(text, vs, 24 + text_height + 3 + (extndd ? 158 : 63) * i);
	text = ft_strjoin("previous live execution : ",
			ft_itoa(carriages->cycle_when_live));
	display_text(text, vs, 30 + text_height * 2 + (extndd ? 158 : 63) * i);
	if (extndd)
	{
		while (j < 8)
		{
			text = ft_strjoin("1: ", ft_itoa(carriages->reg[j]));
			display_text(text, vs, 30 + 3 * (j + 1) + text_height * (j + 3) + 126 * i);
			j++;
		}
//		while ((j = 0) < 8)
//		{
//			text = ft_strjoin("1: ", ft_itoa(carriages->reg[8 + j]));
//			display_text(text, vs, 30 + text_height * 3 + 126 * i);
//			j++;
//		}
	}
}

void			display_side_menu(t_corewar *crrw, int inxd, t_vis_tools *vs, t_carriages *carriages)
{
	SDL_Color	color;
	int			i;
	SDL_Rect	stat_window;

	i = 0;
	SDL_SetRenderDrawColor(vs->render, 0, 0, 0, SDL_ALPHA_OPAQUE);
	stat_window = create_rect(15 + 64 * 24, 10,
			vs->wight - 20 - 64 * 24, 5 + 64 * 15);
	SDL_RenderFillRect(vs->render, &stat_window);
	while (carriages != NULL && ((inxd < 0) ? i < 15 : i < 6))
	{
		color = (carriages->reg[0] < 0 && carriages->reg[0] > -5) ?
		        vs->text_color[-(carriages->reg[0]) - 1] : vs->text_color[4];
		if (inxd < 0)
		{
			draw_frame(vs, color, i, (inxd < 0) ? 0 : 1);
			fill_frame(vs, i++, carriages, (inxd < 0) ? 0 : 1);
		}
		else if (inxd >= 0 && carriages->op_pos == &(crrw->arena[inxd]))
		{
			draw_frame(vs, color, i, 1);
			fill_frame(vs, i++, carriages, 1);
		}
		carriages = carriages->next;
	}
}
