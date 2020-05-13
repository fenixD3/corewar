

#ifndef VIS_H
# define VIS_H

# include "vm.h"
# include <SDL.h>
//# include <mach/machine.h>
//# include <SDL2/SDL_image.h>
# include <SDL_ttf.h>
# include "libft.h"
# include <stdbool.h>


#define CARRIAGE_VISUAL 100

#define ML_ARENA 6
#define ML_VS 8
#define ML_CELL 10
#define ML_SUPPORT 9

# define DESTROY_TXTR(X) if (X) SDL_DestroyTexture(X);


int g_mode;

typedef struct  s_visual_carriages
{
	t_carriages                 *carriage;
	_Bool                       is_open;
	struct s_visual_carriages   *next;
}               t_vc;

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
	TTF_Font		*text_font;
	t_vc			*vc_list;
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

bool init();

void visualise_arena(t_corewar *corewar, bool *quit);

void				create_vs(void);

t_cells				*add_cell(int i, t_corewar *corewar);

void				save_cell(t_cells **celllst, t_cells *new_cell);

void				print_arena(char **arena);

/*
 * Support_func.c
 */
void				free_mem_font(void);

void				track_events(int *indx, SDL_Event *e, bool *quit, int *stop);

SDL_Rect			create_rect(int x, int y, int text_w, int text_h);

void				create_string(char str[100], int input, char *str_inp);



char    *disasm(unsigned char *champ);


void display_side_menu(t_corewar *crrw, int inxd);

void				display_carriages(t_corewar *corewar);

void			add_new_vc(t_vc **head, t_carriages *new);
void    		insert_vc(t_vc **head, t_vc *prev, t_vc *insert);
t_vc    		*cut_vc(t_vc **prev);
t_vc			*find_prev_to_insert(t_vc *head, t_vc *insert);
t_vc 			*find_and_cut_unsorted_elem(t_vc **head);
void			sort_vc(t_vc **head);
void			delete_vc_by_deletion_carriage(t_carriages *del);

#endif
