
#include "vis.h"
#include "vis_errors.h"

t_vis_tools		*create_vs(void)
{
	t_vis_tools	*vs;

	if (!(vs = (t_vis_tools*)ml_malloc(sizeof(t_vis_tools), ML_VS)))
		go_exit(ERR_CREATE_VS);
	vs->wight = 1769;
	vs->height = 1035;
	vs->window = NULL;
	vs->render = NULL;
	vs->font = NULL;
	vs->text_color[0] = init_color(225, 0, 0, 0);
	vs->text_color[1] = init_color(0, 127, 225, 0);
	vs->text_color[2] = init_color(	0, 128, 0, 0);
	vs->text_color[3] = init_color(225, 225, 0, 0);
	vs->text_color[4] = init_color(128, 128, 128, 0);
//	vs->text_color[0] = init_color(166, 130, 186, 0);
//	vs->text_color[1] = init_color(136, 198, 227, 0);
//	vs->text_color[2] = init_color(	172, 176, 65, 0);
//	vs->text_color[3] = init_color(195, 126, 102, 0);
//	vs->text_color[4] = init_color(222, 216, 223, 0);
//	vs->text_color[0] = init_color(109, 80, 124, 0);
//	vs->text_color[1] = init_color(188, 182, 106, 0);
//	vs->text_color[2] = init_color(222, 150, 65, 0);
//	vs->text_color[3] = init_color(132, 192, 255, 0);
//	vs->text_color[4] = init_color(244, 238, 240, 0);

//	vs->text_color[0] = init_color(214, 120, 86, 0);
//	vs->text_color[1] = init_color(186, 136, 61, 0);
//	vs->text_color[2] = init_color(147, 150, 60, 0);
//	vs->text_color[3] = init_color(78, 68, 35, 0);
//	vs->text_color[4] = init_color(199, 196, 163, 0);
	vs->speed = 1;
	return (vs);
}