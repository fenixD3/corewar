
#ifndef ASM_DASHA_H
#define ASM_DASHA_H
#include "op.h"
#include "file_to_list.h"
#include <stdlib.h>

#define ML_CHECK_LST 3

typedef struct		s_token_sec
{
	_Bool	name;
	_Bool	comment;
	_Bool	comment_prog;
	_Bool	str_name;
	_Bool	str_comment;
	_Bool	command;
	_Bool	label;
	_Bool	arg;
	_Bool	separator;
	_Bool	new_line;
	_Bool	new_line_name;
	_Bool	new_line_comment;
}					t_token_sec;

#endif