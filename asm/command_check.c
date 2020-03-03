
#include <stdbool.h>
#include <stdio.h>
#include "libft.h"
#include "asm.h"
#include "asm_dasha.h"

void	check_live(t_token *token)
{
	t_arg	*arg;

	arg = (t_arg*)token->content;
	if (!((arg->type & T_DIR) && (token->next->type == NEW_LINE)))
		token_exit("ERROR: Command 'live'/'zjmp'/'fork'/'lfork'"
						" should be followed exactly by one argument"
						" of type T_DIR", token->row, token->column);

}

void	check_aff(t_token *token)
{
	t_arg	*arg;

	arg = (t_arg*)token->content;
	if (!((arg->type & T_REG) && (token->next->type == NEW_LINE)))
		token_exit("ERROR: Command 'aff'"
		           " should be followed exactly by one argument"
		           " of type T_REG", token->row, token->column);
}

void    check_ld(t_token *token)
{
	t_arg	*arg;
	int 	i;
	char    *error;
	t_token	*tok_cp;

	i = 0;
	error = "ERROR: Command 'ld'/'lld' should be followed exactly"
			" by two arguments of types T_DIR/T_IND, T_REG";
	tok_cp = token;
	while (token->next != NULL && token->type != NEW_LINE)
	{
		if (token->type == ARGUMENT)
		{
			arg = (t_arg*)token->content;
			if (i == 0 && !(arg->type & T_DIR || arg->type & T_IND))
				token_exit(error, token->row, token->column);
			if (i == 2 && !(arg->type & T_REG))
				token_exit(error, token->row, token->column);
			if (i++ == 4 && (arg->type))
				token_exit(error, token->row, token->column);
		}
		token = token->next;
	}
	token = tok_cp;
}

void    check_st(t_token *token)
{
	t_arg	*arg;
	int 	i;
	char    *error;
	t_token	*tok_cp;

	i = 0;
	error = "ERROR: Command 'st' should be followed exactly"
			" by two arguments of types T_REG, T_REG/T_IND";
	tok_cp = token;
	while (token->next != NULL && token->type != NEW_LINE)
	{
		if (token->type == ARGUMENT)
		{
			arg = (t_arg*)token->content;
			if (i == 0 && !(arg->type & T_REG))
				token_exit(error, token->row, token->column);
			if (i == 2 && !(arg->type & T_REG || arg->type & T_IND))
				token_exit(error, token->row, token->column);
			if (i++ == 4 && (arg->type))
				token_exit(error, token->row, token->column);
		}
		token = token->next;
	}
	token = tok_cp;
}

void    check_add(t_token *token)
{
	t_arg	*arg;
	int 	i;
	char    *error;
	t_token	*tok_cp;

	i = 0;
	error = "ERROR: Command 'add'/'sub' should be followed exactly"
			" by tree arguments each of type T_REG";
	tok_cp = token;
	while (token->next != NULL && token->type != NEW_LINE)
	{
		if (token->type == ARGUMENT)
		{
			arg = (t_arg*)token->content;
			if (i == 0 && !(arg->type & T_REG))
				token_exit(error, token->row, token->column);
			if (i == 2 && !(arg->type & T_REG))
				token_exit(error, token->row, token->column);
			if (i++ == 4 && !(arg->type & T_REG))
				token_exit(error, token->row, token->column);
		}
		token = token->next;
	}
	token = tok_cp;
}

void    check_and(t_token *token)
{
	t_arg	*arg;
	int 	i;
	char    *error;
	t_token	*tok_cp;

	i = 0;
	error = "ERROR: Command 'and'/'or'/'xor' should be followed by 3 arguments,"
			" of types T_REG/T_DIR/T_IND, T_REG/T_DIR/T_IND and T_REG";
	tok_cp = token;
	while (token->next != NULL && token->type != NEW_LINE)
	{
		if (token->type == ARGUMENT)
		{
			arg = (t_arg*)token->content;
			if (i == 0 && !(arg->type & T_REG || arg->type & T_DIR
				|| arg->type & T_IND))
				token_exit(error, token->row, token->column);
			if (i == 2 && !(arg->type & T_REG || arg->type & T_DIR
				|| arg->type & T_IND))
				token_exit(error, token->row, token->column);
			if (i++ == 4 && !(arg->type & T_REG))
				token_exit(error, token->row, token->column);
		}
		token = token->next;
	}
	token = tok_cp;
}

void    check_ldi(t_token *token)
{
	t_arg	*arg;
	int 	i;
	char    *error;
	t_token	*tok_cp;

	i = 0;
	error = "ERROR: Command 'ldi'/'lldi' should be followed exactly "
			"by tree arguments, of types T_REG/T_DIR/T_IND, T_REG/T_DIR and T_REG";
	tok_cp = token;
	while (token->next != NULL && token->type != NEW_LINE)
	{
		if (token->type == ARGUMENT)
		{
			arg = (t_arg*)token->content;
			if (i == 0 && !(arg->type & T_REG || arg->type & T_DIR
				|| arg->type & T_IND))
				token_exit(error, token->row, token->column);
			if (i == 2 && !(arg->type & T_REG || arg->type & T_DIR))
				token_exit(error, token->row, token->column);
			if (i++ == 4 && !(arg->type & T_REG))
				token_exit(error, token->row, token->column);
		}
		token = token->next;
	}
	token = tok_cp;
}

void    check_sti(t_token *token)
{
	t_arg	*arg;
	int 	i;
	char    *error;
	t_token	*tok_cp;

	i = 0;
	error = "ERROR: Command 'sti' should be followed exactly "
			"by tree arguments, of types T_REG, T_REG/T_DIR/T_IND and T_REG/T_DIR";
	tok_cp = token;
	while (token->next != NULL && token->type != NEW_LINE)
	{
		if (token->type == ARGUMENT)
		{
			arg = (t_arg*)token->content;
			if (i == 0 && !(arg->type & T_REG))
				token_exit(error, token->row, token->column);
			if (i == 2 && !(arg->type & T_REG || arg->type & T_DIR
				|| arg->type & T_IND))
				token_exit(error, token->row, token->column);
			if (i++ == 4 && !(arg->type & T_REG || arg->type & T_DIR))
				token_exit(error, token->row, token->column);
		}
		token = token->next;
	}
	token = tok_cp;
}

void    check_rest(t_token *token)
{
	if (!ft_strcmp("ldi", token->content))
		check_ldi(token);
	else if (!ft_strcmp("sti", token->content))
		check_sti(token);
	else if (!ft_strcmp("fork", token->content))
		check_live(token);
	else if (!ft_strcmp("lld", token->content))
		check_ld(token);
	else if (!ft_strcmp("lldi", token->content))
		check_ldi(token);
	else if (!ft_strcmp("aff", token->content))
		check_aff(token);
}

void	command_check(t_token *token)
{
	if (!(token->type == COMMAND))
		return ;
	else
	{
		if (!ft_strcmp("live", token->content))
			check_live(token);
		else if (!ft_strcmp("ld", token->content))
			check_ld(token);
		else if (!ft_strcmp("st", token->content))
			check_st(token);
		else if (!ft_strcmp("add", token->content))
			check_add(token);
		else if (!ft_strcmp("sub", token->content))
			check_add(token);
		else if (!ft_strcmp("and", token->content))
			check_and(token);
		else if (!ft_strcmp("or", token->content))
			check_and(token);
		else if (!ft_strcmp("xor", token->content))
			check_and(token);
		else if (!ft_strcmp("zjmp", token->content))
			check_live(token);
		else
			check_rest(token);
	}
}
