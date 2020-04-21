/*
#include "vis.h"

void			draw_frame(t_vis_tools *vs, SDL_Color color, int i, int extndd)
{
	SDL_Rect	rectangle;
	int			rec_h;

	rec_h = extndd ? 126 : 63;
	SDL_SetRenderDrawColor(vs->render, color.r, color.g, color.b,
	                       SDL_ALPHA_OPAQUE);
	rectangle = create_rect(20 + 64 * 24, 15 + rec_h * i,
	                        vs->wight - 30 - 64 * 24, rec_h);
	SDL_RenderFillRect(vs->render, &rectangle);
}

void			fill_frame(t_vis_tools *vs, int i, t_carriages *carriages, int extndd)
{
	SDL_Rect	rectangle;
	char		*text;
	int			text_width;
	int			text_height;
	SDL_Rect	dstrect[3];

	SDL_SetRenderDrawColor(vs->render, 0, 0, 0,
	                       SDL_ALPHA_OPAQUE);
	rectangle = create_rect(26 + 64 * 24, 21 + (extndd ? 126 : 63) * i,
	                        vs->wight - 42 - 64 * 24, (extndd ? 114 : 51));
	SDL_RenderFillRect(vs->render, &rectangle);

	text = ft_strjoin("cycles before execution : ", ft_itoa(carriages->cycle_op));
	vs->txt_srfc = TTF_RenderText_Solid(vs->text_font, text, vs->text_color[4]);
	vs->text = SDL_CreateTextureFromSurface(vs->render, vs->txt_srfc);
	text_width = vs->txt_srfc->w;
	text_height = vs->txt_srfc->h;
	dstrect[0] = create_rect(30 + 64 * 24, 24 + (extndd ? 126 : 63) * i, text_width, text_height);
	SDL_RenderCopy(vs->render, vs->text, NULL, &dstrect[0]);
	free_mem_font(vs);
	free(text);
	text = ft_strjoin("operation code : ", ft_itoa(carriages->op_code));
	vs->txt_srfc = TTF_RenderText_Solid(vs->text_font, text, vs->text_color[4]);
	vs->text = SDL_CreateTextureFromSurface(vs->render, vs->txt_srfc);
	text_width = vs->txt_srfc->w;
	text_height = vs->txt_srfc->h;
	dstrect[1] = create_rect(30 + 64 * 24, 24 + text_height + 3 + (extndd ? 126 : 63) * i,
							text_width, text_height);
	SDL_RenderCopy(vs->render, vs->text, NULL, &dstrect[1]);
	free_mem_font(vs);

	text = ft_strjoin("previous live execution : ", ft_itoa(carriages->cycle_when_live));
	vs->txt_srfc = TTF_RenderText_Solid(vs->text_font, text, vs->text_color[4]);
	vs->text = SDL_CreateTextureFromSurface(vs->render, vs->txt_srfc);
	text_width = vs->txt_srfc->w;
	text_height = vs->txt_srfc->h;
	dstrect[2] = create_rect(30 + 64 * 24, 30 + text_height * 2 + (extndd ? 126 : 63) * i,
	                      text_width, text_height);
	SDL_RenderCopy(vs->render, vs->text, NULL, &dstrect[2]);
	free_mem_font(vs);
}

void			display_side_menu(t_corewar *crrw, int inxd, t_vis_tools *vs)
{
	SDL_Color	color;
	int			i;
	t_carriages	*carriages;
	SDL_Rect stat_window;

	i = 0;
	SDL_SetRenderDrawColor(vs->render, 0, 0, 0, SDL_ALPHA_OPAQUE);
	stat_window = create_rect(15 + 64 * 24, 10,
			vs->wight - 20 - 64 * 24, 5 + 64 * 15);
	SDL_RenderFillRect(vs->render, &stat_window);
	carriages = crrw->carriages;
	while (carriages != NULL)
	{
		color = (carriages->reg[0] < 0 && carriages->reg[0] > -5) ?
		        vs->text_color[-(carriages->reg[0]) - 1] : vs->text_color[4];
		draw_frame(vs, color, i, (inxd < 0) ? 0 : 1);
		fill_frame(vs, i, carriages, (inxd < 0) ? 0 : 1);
		carriages = carriages->next;
		i++;
	}
}
*/
