/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 13:38:40 by mdeanne           #+#    #+#             */
/*   Updated: 2020/02/28 13:38:44 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
#define ASM_H
#include "op.h"
#include "../../file_to_list.h"
#include <stdlib.h>

#define ML_GNL_LINE	10
#define ML_TOKEN	20
#define ML_ARGUMENT	30
#define ML_CMD_NAME 40
#define ML_L_NAME	50
#define ML_S_CONTENT 60
#define ML_LABEL	70
#define ML_CMD_NUM	80

#define ENDLINE		1
#define ENDSTR		2
#define NOTENDSTR	3
#define ENDFILE		4
#define NOTSTR		5

typedef enum	s_token_type
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
	t_token_type 	type;
	u_int32_t		row;
	u_int16_t		column;
	void 			*content;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct	s_label
{
	char			*name;
	t_token 		*token;
	struct s_label	*prev;
	struct s_label	*next;
}				t_label;

typedef struct	s_argument
{
	u_int8_t		type;
	void 			*content;
	int				num;
}				t_arg;

typedef struct	s_parser_carriage
{
	u_int32_t		row;
	u_int16_t		column;
	char			*line;
}				t_pc;

t_token			*add_token(t_pc *pc, t_token **token_tail, t_label **label_tail, u_int8_t flag);
void			add_label(char *str, t_token *token, t_label **tail, t_arg_type arg_type);
t_arg           *add_arg(char *str, t_arg_type type);
char			*add_string(char *str, t_token *token);

void			token_fill(char *str, t_token *token, t_label **tail, u_int8_t flag);
u_int8_t		token_rewind(t_pc *pc, t_token *token);
void			rewind_n(t_pc *pc, u_int16_t n);
void			tokenize(int fd, t_token **token, t_label **label);


u_int32_t		command_length(t_token *token);

void 			label_substitution(t_label *head);

///// not need

_Bool	is_special_char(char c, char *specials);

_Bool	skip_delims(char **line, char *delims, char *comments);
char	**fast_strsplit(char *line, char *delims, char *comments, void *alloc_func(size_t)); // may be replaced to libft

_Bool	find_label(t_label **head, t_label *label_arg);


///print
void print_tokens(t_token *token, u_int8_t setting);
void print_token(t_token *t, u_int8_t setting);
char *print_cmd_name(t_token *token, u_int8_t flag);
void print_labels(t_label *label);



static char		*g_type[] = {
		"NAME",//
		"COMMENT_PROG",//
		"COMMAND",//
		"STRING",//
		"COMMENT",//
		"LABEL",
		"ARGUMENT",//
		"ARGUMENT_LABEL",//
		"SEPARATOR",//
		"NEW_LINE",//
		"END",//
		"T_REG",
		"T_DIR",
		"T_IND"
};

#endif
