
#include "vis.h"
#include "op.h"

t_vis_tools *vs;


void print_arena(char **arena)
{
	int			text_width;
	int			text_height;
	SDL_Rect	dstrect;
	int			i;

	i = 0;
	while (i < 64)
	{
		vs->txt_srfc = TTF_RenderText_Solid(vs->font,
											arena[i], vs->text_color[4]);
		vs->text = SDL_CreateTextureFromSurface(vs->render,
												vs->txt_srfc);
		text_width = vs->txt_srfc->w;
		text_height = vs->txt_srfc->h;
		dstrect = create_rect(10,
			15 + i * (text_height + 6), text_width, text_height);
		SDL_RenderCopy(vs->render, vs->text, NULL, &dstrect);
		free_mem_font();
		i++;
	}
}

//void			print_arena(char **arena)
//{
//	int			text_width;
//	int			text_height;
//	SDL_Rect	dstrect;
//	int			i;
//	int			j;
//
//	i = 0;
//	while (i < MEM_SIZE)
//	{
//		j = 0;
//		while (j < 64)
//		{
//			vs->txt_srfc = TTF_RenderText_Solid(vs->font,
//										arena[i], vs->text_color[4]);
//			vs->text = SDL_CreateTextureFromSurface(vs->render,
//					vs->txt_srfc);
//			text_width = vs->txt_srfc->w;
//			text_height = vs->txt_srfc->h;
//			dstrect = create_rect(10 + j++ * 24,
//				15 + (i++ / 64) * (text_height + 5), text_width, text_height);
//			SDL_RenderCopy(vs->render, vs->text, NULL, &dstrect);
//			free_mem_font();
//		}
//	}
//}
