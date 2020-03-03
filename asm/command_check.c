
#include <stdbool.h>
#include <stdio.h>
#include "libft.h"
#include "asm.h"
#include "asm_dasha.h"
#include "../options.h"

//void	check_live(t_token *token)
//{
//	t_arg	*arg;
//
//	arg = (t_arg*)token->content;
//	if (!((arg->type & T_DIR) && (token->next->type == NEW_LINE)))
//		token_exit(, token->row, token->column);
//
//}
//
//void	check_aff(t_token *token)
//{
//	t_arg	*arg;
//
//	arg = (t_arg*)token->content;
//	if (!((arg->type & T_REG) && (token->next->type == NEW_LINE)))
//		token_exit(ASM_AFF_ERR, token->row, token->column);
//}
//
//void    check_ld(t_token *token)
//{
//	t_arg	*arg;
//	int 	i;
//	t_token	*tok_cp;
//
//	i = 0;
//	tok_cp = token;
//	while (token->next != NULL && token->type != NEW_LINE)
//	{
//		if (token->type == ARGUMENT)
//		{
//			arg = (t_arg*)token->content;
//			if (i == 0 && !(arg->type & T_DIR || arg->type & T_IND))
//				token_exit(ASM_LD_ERR, token->row, token->column);
//			if (i == 2 && !(arg->type & T_REG))
//				token_exit(ASM_LD_ERR, token->row, token->column);
//			if (i++ == 4 && (arg->type))
//				token_exit(ASM_LD_ERR, token->row, token->column);
//		}
//		token = token->next;
//	}
//	token = tok_cp;
//}
//
//void    check_st(t_token *token)
//{
//	t_arg	*arg;
//	int 	i;
//	t_token	*tok_cp;
//
//	i = 0;
//	tok_cp = token;
//	while (token->next != NULL && token->type != NEW_LINE)
//	{
//		if (token->type == ARGUMENT)
//		{
//			arg = (t_arg*)token->content;
//			if (i == 0 && !(arg->type & T_REG))
//				token_exit(ASM_ST_ERR, token->row, token->column);
//			if (i == 2 && !(arg->type & T_REG || arg->type & T_IND))
//				token_exit(ASM_ST_ERR, token->row, token->column);
//			if (i++ == 4 && (arg->type))
//				token_exit(ASM_ST_ERR, token->row, token->column);
//		}
//		token = token->next;
//	}
//	token = tok_cp;
//}
//
//void    check_add(t_token *token)
//{
//	t_arg	*arg;
//	int 	i;
//	t_token	*tok_cp;
//
//	i = 0;
//	tok_cp = token;
//	while (token->next != NULL && token->type != NEW_LINE)
//	{
//		if (token->type == ARGUMENT)
//		{
//			arg = (t_arg*)token->content;
//			if (i == 0 && !(arg->type & T_REG))
//				token_exit(ASM_ADD_ERR, token->row, token->column);
//			if (i == 2 && !(arg->type & T_REG))
//				token_exit(ASM_ADD_ERR, token->row, token->column);
//			if (i++ == 4 && !(arg->type & T_REG))
//				token_exit(ASM_ADD_ERR, token->row, token->column);
//		}
//		token = token->next;
//	}
//	token = tok_cp;
//}
//
//void    check_and(t_token *token)
//{
//	t_arg	*arg;
//	int 	i;
//	t_token	*tok_cp;
//
//	i = 0;
//	tok_cp = token;
//	while (token->next != NULL && token->type != NEW_LINE)
//	{
//		if (token->type == ARGUMENT)
//		{
//			arg = (t_arg*)token->content;
//			if (i == 0 && !(arg->type & T_REG || arg->type & T_DIR
//				|| arg->type & T_IND))
//				token_exit(ASM_AND_ERR, token->row, token->column);
//			if (i == 2 && !(arg->type & T_REG || arg->type & T_DIR
//				|| arg->type & T_IND))
//				token_exit(ASM_AND_ERR, token->row, token->column);
//			if (i++ == 4 && !(arg->type & T_REG))
//				token_exit(ASM_AND_ERR, token->row, token->column);
//		}
//		token = token->next;
//	}
//	token = tok_cp;
//}
//
//void    check_ldi(t_token *token)
//{
//	t_arg	*arg;
//	int 	i;
//	t_token	*tok_cp;
//
//	i = 0;
//	tok_cp = token;
//	while (token->next != NULL && token->type != NEW_LINE)
//	{
//		if (token->type == ARGUMENT)
//		{
//			arg = (t_arg*)token->content;
//			if (i == 0 && !(arg->type & T_REG || arg->type & T_DIR
//				|| arg->type & T_IND))
//				token_exit(ASM_LDI_ERR, token->row, token->column);
//			if (i == 2 && !(arg->type & T_REG || arg->type & T_DIR))
//				token_exit(ASM_LDI_ERR, token->row, token->column);
//			if (i++ == 4 && !(arg->type & T_REG))
//				token_exit(ASM_LDI_ERR, token->row, token->column);
//		}
//		token = token->next;
//	}
//	token = tok_cp;
//}
//
//void    check_sti(t_token *token)
//{
//	t_arg	*arg;
//	int 	i;
//	t_token	*tok_cp;
//
//	i = 0;
//	tok_cp = token;
//	while (token->next != NULL && token->type != NEW_LINE)
//	{
//		if (token->type == ARGUMENT)
//		{
//			arg = (t_arg*)token->content;
//			if (i == 0 && !(arg->type & T_REG))
//				token_exit(ASM_STI_ERR, token->row, token->column);
//			if (i == 2 && !(arg->type & T_REG || arg->type & T_DIR
//				|| arg->type & T_IND))
//				token_exit(ASM_STI_ERR, token->row, token->column);
//			if (i++ == 4 && !(arg->type & T_REG || arg->type & T_DIR))
//				token_exit(ASM_STI_ERR, token->row, token->column);
//		}
//		token = token->next;
//	}
//	token = tok_cp;
//}
//
//void    check_rest(t_token *token)
//{
//	if (!ft_strcmp("ldi", token->content))
//		check_ldi(token);
//	else if (!ft_strcmp("sti", token->content))
//		check_sti(token);
//	else if (!ft_strcmp("fork", token->content))
//		check_live(token);
//	else if (!ft_strcmp("lld", token->content))
//		check_ld(token);
//	else if (!ft_strcmp("lldi", token->content))
//		check_ldi(token);
//	else if (!ft_strcmp("aff", token->content))
//		check_aff(token);
//}

//void	command_check(t_token *token)
//{
//	if (!(token->type == COMMAND))
//		return ;
//	else
//	{
//		if (*((int*)token->content) == 1)
//			check_live(token);
//		else if (!ft_strcmp("ld", token->content))
//			check_ld(token);
//		else if (!ft_strcmp("st", token->content))
//			check_st(token);
//		else if (!ft_strcmp("add", token->content))
//			check_add(token);
//		else if (!ft_strcmp("sub", token->content))
//			check_add(token);
//		else if (!ft_strcmp("and", token->content))
//			check_and(token);
//		else if (!ft_strcmp("or", token->content))
//			check_and(token);
//		else if (!ft_strcmp("xor", token->content))
//			check_and(token);
//		else if (!ft_strcmp("zjmp", token->content))
//			check_live(token);
//		else
//			check_rest(token);
//	}
//}

void	check_args(t_token *token, int *i, t_op g_op)
{
	t_token	*cp_tok;
	t_arg	arg;

	cp_tok = token;
	while (token->next != NULL && token->type != NEW_LINE)
	{
		if (token->next->type == ARGUMENT)
		{
			arg = (t_arg*)token->content;
			if (!(arg.type & ((g_op[com_code])->(args_type[*i]))))
				token_exit(ASM_ERR_ARGS, token);
			(*i)++;
		}
		token = token->next;
	}
	token = cp_tok;
}

void	command_check(t_token *token)
{
	int		i;
	t_op	g_op;
	int		com_code;

	com_code = 0;
	i = 0;
	if (!(token->type == COMMAND))
		return ;
	else
	{
		com_code = *((int *)token->content) - 1;
		check_args(token, &i, g_op);
		if ((i < 2 && ((g_op[com_code])->(args_type[1]) != 0))
			|| (i < 3 && ((g_op[com_code])->(args_type[2]) != 0)))
			token_exit(ASM_ERR_ARGS, token);
	}
}
