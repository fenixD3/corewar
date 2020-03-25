
#include "vis.h"
#include "vis_errors.h"

t_vis_tools		*create_vs(void)
{
	t_vis_tools	*vs;

	if (!(vs = (t_vis_tools*)ml_malloc(sizeof(t_vis_tools), ML_VS)))
		go_exit(ERR_CREATE_VS);
	vs->window = NULL;
	vs->render = NULL;
	vs->font = NULL;
	vs->text_color.r = 199;
	vs->text_color.g = 196;
	vs->text_color.b = 163;
	vs->text_color.a = 0;
	vs->speed = 5000;
	return (vs);
}