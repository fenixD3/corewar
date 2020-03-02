
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

_Bool	check_ld(t_token *token)
{
	t_arg	*arg;
	t_arg	*nxt_arg;

	arg = (t_arg*)token->content;
	nxt_arg = (t_arg*)(token->next->content);
	if ((arg->type & T_DIR || arg->type & T_IND) && (nxt_arg->type & T_REG))
		return (true);
	else
		token_exit("ERROR: Command 'ld'/'lld' should be followed exactly"
							" by two arguments of types T_DIR/T_IND, T_REG",
							token->row, token->column);
}

void	check_st(t_token *token)
{
	t_arg	*arg;
	t_arg	*nxt_arg;
	char    *error;

	error = "ERROR: Command 'st' should be followed exactly"
	        " by two arguments of types T_REG, T_REG/T_IND";
	arg = (t_arg*)token->content;
	if (token->next != NULL)
		nxt_arg = (t_arg *) (token->next->content);
	else
		token_exit(error, token->row, token->column);
	if ((nxt_arg->type & T_REG || nxt_arg->type & T_IND) && (arg->type & T_REG))
		;
	else
		token_exit(error, token->row, token->column);
}

_Bool	tree_reg(t_token *token)
{
	t_arg	*arg;
	t_arg	*nxt_arg;
	t_arg	*nxt_nxt_arg;

	arg = (t_arg*)token->content;
	if (token->next != NULL)
		nxt_arg = (t_arg *) (token->next->content);
	else
		return (false);
	if (token->next->next != NULL)
		nxt_nxt_arg = (t_arg *) (token->next->next->content);
	else
		return (false);
	if (nxt_arg->type & T_REG && arg->type & T_REG && nxt_nxt_arg->type & T_REG)
		return (true);
	else
		return (false);
}

void	check_add(t_token *token)
{
	if (!tree_reg(token))
		token_exit("ERROR: Command 'add'/'sub' should be followed exactly"
							" by tree arguments each of type T_REG",
							token->row, token->column);
}

void	check_and(t_token *token)
{
	t_arg	*arg;
	t_arg	*nxt_arg;
	t_arg	*nxt_nxt_arg;
	char    *error;

	error = "ERROR: Command 'and'/'or'/'xor' should be followed by 3 arguments,"
	        " of types T_REG/T_DIR/T_IND, T_REG/T_DIR/T_IND and T_REG";
	arg = (t_arg*)token->content;
	if (token->next != NULL)
		nxt_arg = (t_arg *) (token->next->content);
	else
		token_exit(error, token->row, token->column);
	if (token->next->next != NULL)
		nxt_nxt_arg = (t_arg *) (token->next->next->content);
	else
		token_exit(error, token->row, token->column);
	if (token->next->next->next->type != NEW_LINE)
		token_exit(error, token->row, token->column);
	if (!(nxt_nxt_arg->type & T_REG))
		token_exit(error, token->row, token->column);
	else
		if (!((arg->type & T_REG || arg->type & T_DIR || arg->type & T_IND) &&
		((nxt_arg->type & T_REG) || (nxt_arg->type & T_DIR) ||
		(nxt_arg->type & T_IND))))
			token_exit(error, token->row, token->column);
}

void    check_ldi(t_token *token)
{
	t_arg	*arg;
	t_arg	*nxt_arg;
	t_arg	*nxt_nxt_arg;
	char    *error;

	error = "ERROR: Command 'ldi'/'lldi' should be followed exactly "
	        "by tree arguments, of types T_REG/T_DIR/T_IND,"
	        "T_REG/T_DIR and T_REG";
	arg = (t_arg*)token->content;
	if (token->next != NULL)
		nxt_arg = (t_arg *) (token->next->content);
	else
		token_exit(error, token->row, token->column);
	if (token->next->next != NULL)
		nxt_nxt_arg = (t_arg *) (token->next->next->content);
	else
		token_exit(error, token->row, token->column);
	if (token->next->next->next->type != NEW_LINE)
		token_exit(error, token->row, token->column);
	if (!(nxt_nxt_arg->type & T_REG))
		token_exit(error, token->row, token->column);
	else
	if (!((arg->type & T_REG || arg->type & T_DIR || arg->type & T_IND) &&
	      ((nxt_arg->type & T_REG) || (nxt_arg->type & T_DIR))))
		token_exit(error, token->row, token->column);
}

void    check_sti(t_token *token)
{
	t_arg	*arg;
	t_arg	*nxt_arg;
	t_arg	*nxt_nxt_arg;
	char    *error;

	error = "ERROR: Command 'sti' should be followed exactly "
	        "by tree arguments, of types T_REG,"
	        "T_REG/T_DIR/T_IND and T_REG/T_DIR";
	arg = (t_arg*)token->content;
	if (token->next != NULL)
		nxt_arg = (t_arg *) (token->next->content);
	else
		token_exit(error, token->row, token->column);
	if (token->next->next != NULL)
		nxt_nxt_arg = (t_arg *) (token->next->next->content);
	else
		token_exit(error, token->row, token->column);
	if (token->next->next->next->type != NEW_LINE)
		token_exit(error, token->row, token->column);
	if (!(arg->type & T_REG))
		token_exit(error, token->row, token->column);
	else
		if (!((nxt_arg->type & T_REG || nxt_arg->type & T_DIR || nxt_arg->type & T_IND) &&
	      ((nxt_nxt_arg->type & T_REG) || (nxt_nxt_arg->type & T_DIR))))
			token_exit(error, token->row, token->column);
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
