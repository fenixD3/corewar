
#ifndef ASM_DASHA_H
#define ASM_DASHA_H
#include "file_to_list.h"
#include <stdlib.h>
#include <fcntl.h>

#include <stdio.h>
#include "libft.h"
#include <options.h>
#include "errors.h"

#include "asm.h"


#define ML_CHECK_LST 3

typedef struct		s_token_sec
{
	_Bool			name;
	_Bool			comment;
	_Bool			comment_prog;
	_Bool			str_name;
	_Bool			str_comment;
	_Bool			command;
	_Bool			label;
	_Bool			arg;
	_Bool			separator;
	_Bool			new_line;
	_Bool			new_line_name;
	_Bool			new_line_comment;
	char			*chmp_name;
	char 			*chmp_comment;
}					t_token_sec;

int					token_exit(char *error, t_token *token);
_Bool				token_sequence(t_token *token);

u_int32_t			calc_command_weight(t_token *token);

void				print_header(int fd, header_t *header);

#endif