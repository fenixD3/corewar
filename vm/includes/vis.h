
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
#define ML_CELL 10
#define ML_SUPPORT 9

# define DESTROY_TXTR(X)	if (X) SDL_DestroyTexture(X);



typedef struct		s_vis_tools
{
	int				wight;
	int				height;
	int				speed;
	SDL_Color		text_color[5];
	SDL_Window		*window;
	SDL_Renderer	*render;
	SDL_Surface		*backgrnd;
	SDL_Surface		*txt_srfc;
	SDL_Texture		*text;
	SDL_Texture		*backgrnd_txtr;
	TTF_Font		*font;
}					t_vis_tools;

typedef struct		s_cells
{
	char			*code;
	t_carriages		*carriages;
	SDL_Color		color;
	int				font;//bold or not?
	struct s_cells	*next;
}					t_cells;

typedef struct		s_arena
{
//	t_cells			*cell;
	int				chmp_num;
	unsigned int	prog_size[4];//aaa in corewar?!
	int				step;//aaa in corewar?!
}					t_arena;

bool				init(t_vis_tools *vs);

void				visualise_arena(t_corewar *corewar, t_vis_tools *vs, bool *quit);

t_vis_tools			*create_vs(void);

t_cells				*add_cell(int i, t_corewar *corewar);

void				save_cell(t_cells **celllst, t_cells *new_cell);

void				print_arena(t_vis_tools *vs, char **arena);

/*
 * Support_func.c
 */
void				free_mem_font(t_vis_tools *vs);

void				track_events(t_vis_tools *vs, SDL_Event *e, bool *quit);

SDL_Rect			create_rect(int x, int y, int text_w, int text_h);

SDL_Color			init_color(int r, int g, int b, int a);

#endif
