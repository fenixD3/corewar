//
// Created by Mort Deanne on 04/03/2020.
//

#include <stdio.h>
#include <libft/libft.h>
#include <corewar/options.h>
#include "asm.h"


void print_command_with_args(t_token *token)
{
	int i = 0;
	t_op *op;
	t_arg *arg;

	if (!token)
		return ;
	while (token && token->type != COMMAND)
		token = token->prev;
	if (!token)
		return ;
	op = &g_op[*(u_int8_t*)token->content];
	printf ("CMD:%s  ", op->name);
	while (token->type != NEW_LINE)
	{
		token = token->next;
		while (token && token->type != ARGUMENT && token->type != NEW_LINE)
			token = token->next;
		if (!token || token->type == NEW_LINE)
			break;
		printf("ARG:");
		arg = (t_arg*)token->content;
		if (arg->type == T_REG)
			printf("r");
		else if (arg->type == T_DIR)
			printf("d");
		else if (arg->type == T_IND)
			printf("i");
		else if (arg->type & T_LAB)
			printf("LABEL NOT CLEANED");
		else
			printf("WTF??");
		printf("%d %s  ", arg->num, (char*)arg->content);
	}
	printf("\n");
}

char *print_cmd_name(t_token *token, u_int8_t flag)
{
	if (token->type != COMMAND)
		return (NULL);
	if (!flag)
		return ((char*)token->content);
	return (ft_itoa((int)*(u_int8_t*)token->content));
}

void print_labels(t_label *label)
{
	while (label)
	{
		printf("[LABEL:%s]->[TOKEN:%s] ",  label->name, g_type[label->token->type - 1]);
		if (label->token->type == ARGUMENT_LABEL)
			printf("->[ARG]->[LABEL:%s]", ((t_label*)((t_arg*)label->token->content)->content)->name);
		else
			printf("->[LABEL:%s]", ((t_label*)label->token->content)->name);
		printf("\n");
		label = label->next;
	}
	printf("----------------------------\n");
}

void print_token(t_token *t, u_int8_t setting)
{
	int flag = 0;
	printf("[%s", g_type[t->type - 1]);
	if (t->type == COMMAND || t->type == STRING)
	{
		if (setting == 0 || t->type == STRING)
			printf(":%s", (char*)t->content);
		else if (setting == 2)
			printf(":%s", g_op[*(u_int8_t*)t->content].name);
		else
			printf(":%02x", *(u_int8_t*)t->content);

	}
	else if (t->type == ARGUMENT || t->type == ARGUMENT_LABEL)
	{
		if (t->type == ARGUMENT_LABEL)
		{
			flag = 1;
			//((t_arg*)t->content)->type = ((t_arg*)t->content)->type & ~T_LAB;
			printf(":%s", g_type[((t_arg*)t->content)->type & ~T_LAB + 10]);
		}
		else
			printf(":%s", g_type[((t_arg*)t->content)->type + 10]);
		if (!flag)
			printf(":%d", ((t_arg*)t->content)->num);
		else
			printf(":%s", ((t_label*)((t_arg*)t->content)->content)->name);
	}
	else if (setting == 1 && t->type == LABEL)
		printf(":%s", ((t_label*)t->content)->name);
	printf("] ");
}

void print_tokens(t_token *token, u_int8_t setting)
{
	while (token->prev)
		token = token->prev;
	printf("-");
	while (token)
	{
		if (!setting)
			printf("[%s] ", g_type[token->type - 1]);
		else
			print_token(token, 0);
		if (token->type == NEW_LINE || token->type == END)
			printf("\n");
		token = token->next;
	}
}
