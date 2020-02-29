

#include "libft.h"
#include "asm.h"

.name       ""

.comment    ""

loop:
		sti r1, %:live, %1
live:
		live %0
		ld %0, r2
		zjmp %:loop

typedef struct	s_token
{
	t_token_type 	type;
	u_int32_t		row;
	u_int16_t		column;
	void 			*content;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

void 	init_check_list(t_token_sec	*check_list)
{
	check_list->arg = false;
	check_list->command = false;
	check_list->comment = false;
	check_list->separator = false;
	check_list->str_comment = false;
	check_list->str_name = false;
	check_list->name = false;
	check_list->new_line_name = false;
	check_list->new_line_comment = false;
	check_list->label = false;
}

void	if_str_check(t_token *token, )
{
	if (token->type == STRING)
	{
		if (check_list->name)
		{
			check_list->str_name = true;
			check_list->name = false;
		}
		else if (check_list->comment)
		{
			check_list->str_comment = true;
			check_list->comment = false;
		}
		else
			go_exit("ERROR: Champion's file contains error");
	}
}

_Bool	token_sequence(t_token *token)
{
	t_token_sec	*check_list;

	init_check_list(&check_list);
	while (token != NULL)
	{
		if (token->type == NAME)
			check_list->name = true;
		if (token->type == NEW_LINE)
		{
			if (check_list->str_name && !check_list->comment)
				check_list->new_line_name = true;
			if (check_list->str_comment && !check_list->label)
				check_list->new_line_comment = true;
			else
				;
		}
		if_str_check(token, check_list);
		if (token->type == LABEL)
		{
			if (!check_list->new_line_comment)
				go_exit("ERROR: Champion should have name before comment");
			else
				check_list->label = true;
		}
		if (token->type == COMMAND)
		{
			if (!check_list->label)
				go_exit("ERROR: Command should only follow some label");
			else
				check_list->command = true;
		}
		if (token->type == COMMENT)
			if (!check_list->str_name)
				go_exit("ERROR: Champion should have name before comment");
		token = token->next;
	}
}