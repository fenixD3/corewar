
#ifndef VIS_H
# define VIS_H

# include <SDL.h>
//# include <mach/machine.h>
//# include <SDL2/SDL_image.h>
# include <SDL_ttf.h>
# include "libft.h"
# include "vm.h"
# include <stdbool.h>

#define ML_ARENA 6
#define ML_VS 8

# define DESTROY_TXTR(X)	if (X) SDL_DestroyTexture(X);

typedef struct		s_vis_tools
{
	int				speed;
	SDL_Color		text_color;
	SDL_Window		*window;
	SDL_Renderer	*render;
	SDL_Surface		*backgrnd;

	SDL_Surface		*text_surface;
	SDL_Texture		*text;
	SDL_Texture		*backgrnd_txtr;
	TTF_Font		*font;
}					t_vis_tools;



bool				init(t_vis_tools *vs);

void				visualise_arena(t_corewar *corewar, t_vis_tools *vs, bool *quit);

t_vis_tools			*create_vs(void);

#endif
