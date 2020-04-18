
#include "vis.h"
#include "vis_errors.h"

t_vis_tools *vs;

void		create_vs(void)
{
	if (!(vs = (t_vis_tools*)ml_malloc(sizeof(t_vis_tools), ML_VS)))
		go_exit(ERR_CREATE_VS);
	vs->wight = 1780;
	vs->height = 1035;
	vs->window = NULL;
	vs->render = NULL;
	vs->font = NULL;
	vs->text_color[0] = init_color(225, 0, 0, 0);
	vs->text_color[1] = init_color(0, 127, 225, 0);
	vs->text_color[2] = init_color(	0, 128, 0, 0);
	vs->text_color[3] = init_color(225, 225, 0, 0);
	vs->text_color[4] = init_color(128, 128, 128, 0);
	vs->vc_list = NULL;
	vs->speed = 1;
}
