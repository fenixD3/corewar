/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 13:38:40 by mdeanne           #+#    #+#             */
/*   Updated: 2020/05/12 00:29:49 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include <stdlib.h>
# include <stdint.h>
# include <fcntl.h>

# include "op.h"
# include "ft_ptintf.h"
# include "libft.h"
# include "options.h"
# include "errors.h"

# define ML_GNL_LINE	10
# define ML_TOKEN	20
# define ML_ARGUMENT	30
# define ML_CMD_NAME 40
# define ML_L_NAME	50
# define ML_S_CONTENT 60
# define ML_LABEL	70
# define ML_CMD_NUM	80
# define ML_CHECK    150

# define TKNZE_BREAK	1
# define TKNZE_CONT	2
# define ENDFILE		3
# define ENDLINE		4
# define NOTENDSTR	5

typedef enum	e_token_type
{
	NAME = 1,
	COMMENT_PROG,
	COMMAND,
	STRING,
	COMMENT,
	LABEL,
	ARGUMENT,
	ARGUMENT_LABEL,
	SEPARATOR,
	NEW_LINE,
	END
}				t_token_type;

typedef struct	s_token
{
	t_token_type	type;
	u_int32_t		row;
	u_int16_t		column;
	void			*content;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct	s_label
{
	char			*name;
	t_token			*token;
	struct s_label	*prev;
	struct s_label	*next;
}				t_label;

typedef struct	s_argument
{
	u_int8_t		type;
	void			*content;
	int				num;
}				t_arg;

typedef struct	s_parser_carriage
{
	u_int32_t		row;
	u_int16_t		column;
	char			*line;
}				t_pc;

typedef struct	s_token_sec
{
	_Bool	name;
	_Bool	comment;
	_Bool	comment_prog;
	_Bool	str_name;
	_Bool	str_comment;
	_Bool	command;
	_Bool	arg;
	_Bool	separator;
	_Bool	new_line;
}				t_token_sec;

t_token			*add_token(t_pc *pc, t_token **token_tail, t_label **label_tail,
																u_int8_t flag);
void			add_label(char *str, t_token *token, t_label **tail,
														t_arg_type arg_type);
t_arg			*add_arg(char *str, t_arg_type type);
char			*add_string(char *str, t_token *token);

void			token_fill(char *str, t_token *token, t_label **tail,
																u_int8_t flag);
u_int8_t		token_rewind(t_pc *pc, t_token *token);
void			rewind_n(t_pc *pc, u_int16_t n);
void			tokenize(int fd, t_token **token, t_label **label);
u_int8_t		check_prev_str(t_token *token, u_int8_t flag);

u_int32_t		command_length(t_token *token);

void			label_substitution(t_label *head);

char			*tkn_str_cat(char *dst, t_token *token, u_int32_t max_len);
t_token			*find_token(t_token *head, t_token_type type);

void			token_exception(char *error, t_token *token, _Bool warning);

_Bool			is_special_char(char c, char *specials);

_Bool			skip_delims(char **line, char *delims, char *comments);

_Bool			find_label(t_label **head, t_label *label_arg);

void			token_sequence(t_token *token, t_token_sec	*check_list);

void			print_commands(int fd, t_token *token);

void			print_header(int fd, t_header *header);
void			if_label(t_token *token, t_token_sec *check_list);
void			if_arg(t_token *token, t_token_sec *check_list);
void			if_name(t_token *token, t_token_sec *check_list);
void			if_nl_or_comment(t_token *token, t_token_sec *check_list);
void			if_comment_prog(t_token *token, t_token_sec *check_list);
void			command_check(t_token *token);
void			init_headers(t_header *header, t_token *token);

static char	*g_type[] =
{
	"NAME",
	"COMMENT_PROG",
	"COMMAND",
	"STRING",
	"COMMENT",
	"LABEL",
	"ARGUMENT",
	"ARGUMENT_LABEL",
	"SEPARATOR",
	"NEW_LINE",
	"END",
};

#endif
