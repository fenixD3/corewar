
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
# define ML_HEADER 4
# define ML_CMD_NUM 7

#define MAX_FILE_LENGTH (CHAMP_MAX_SIZE + PROG_NAME_LENGTH + COMMENT_LENGTH + 16)

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
_Bool				token_sequence(t_token *token, t_token_sec	**check_list);

u_int32_t			command_length(t_token *token);
void			    print_commands(int fd, t_token *token, t_label *label);

void				label_substitution(t_label *head);

void				print_header(int fd, header_t *header);
void				if_label(t_token *token, t_token_sec **check_list);
void				if_arg(t_token *token, t_token_sec **check_list);
void				if_name(t_token *token, t_token_sec **check_list);
void				if_nl(t_token *token, t_token_sec **check_list);
void				if_comment_prog(t_token *token, t_token_sec **check_list);
void				command_check(t_token *token);
void				init_headers(header_t **header, t_token *token, t_token_sec *info);

#endif