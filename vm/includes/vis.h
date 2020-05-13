

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

#define ML_VS 8

# define DESTROY_TXTR(X) if (X) SDL_DestroyTexture(X);


int		g_mode;
bool	g_contnue;


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
	SDL_Color		text_color[6];
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

bool 				init();

void 				visualise_arena(t_corewar *corewar, bool *quit);

void				create_vs(void);

void				print_arena(char **arena);

void				draw_frame(t_vc *vc, int *i, int extndd, t_corewar *crwr);

void				higlight_cells(int cariages, t_vc *vc, t_corewar *crwr, int ind);

/*
 * Support_func.c
 */
void				free_mem_font(void);

void				ft_free_strsplit(char **str_array);

int					track_events(int *indx, SDL_Event *e, bool *quit, t_corewar *corewar);


SDL_Rect			create_rect(int x, int y, int text_w, int text_h);

void				create_string(char str[100], int input,
													char *str_inp, char *f);

void				disasm(t_carriages *champ, char str[100], unsigned char *arena);

//void    			disasm(char str[100], unsigned char *champ, unsigned char arena[MEM_SIZE]);

//void				disasm(char *str, unsigned char champ[100], unsigned char arena[MEM_SIZE]);

void				display_game_data(t_corewar *corewar);

int					display_side_menu(t_corewar *crwr, int ind, t_vc *vc);


void				display_carriages(t_corewar *corewar);

void				add_new_vc(t_vc **head, t_carriages *new);
void    			insert_vc(t_vc **head, t_vc *prev, t_vc *insert);
t_vc    			*cut_vc(t_vc **prev);
t_vc				*find_prev_to_insert(t_vc *head, t_vc *insert);
t_vc 				*find_and_cut_unsorted_elem(t_vc **head);
void				sort_vc(t_vc **head);
void				delete_vc_by_deletion_carriage(t_carriages *del);

#endif
