/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoupe_ast_no_quotes2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:29:21 by dpinto            #+#    #+#             */
/*   Updated: 2025/01/09 20:43:39 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_com	**malloc_ast(t_com **ast, int nbr_pipe)
{
	if (nbr_pipe > 0)
	{
		ast = malloc(sizeof(t_com *) * ((nbr_pipe + 1) + 1));
		ast[(nbr_pipe + 1)] = NULL;
	}
	else
	{
		ast = malloc(sizeof(t_com *) * 2);
		ast[1] = NULL;
		nbr_pipe = 0;
	}
	return (ast);
}

void	create_while_help(t_ast *save_ast, t_com **ast, t_node **tmp, int i)
{
	if (save_ast->command)
		ast[i] = save_ast->command;
	else
	{
		ast[i] = ft_calloc(1, sizeof(t_com));
		ast[i]->txt = NULL;
	}
	if (ast[i])
		ast[i]->redir = save_ast->redir;
	*tmp = save_ast->save_ptr;
	free(save_ast);
	save_ast = NULL;
}

t_com	**create_while(t_com **ast, t_ast *save_ast, t_node *ptr, int nbr_pipe)
{
	int		i;
	int		first;
	t_node	*tmp;

	first = 1;
	i = 0;
	while (nbr_pipe-- >= 0)
	{
		if (first == 0)
			save_ast = isolate_command_redir(tmp);
		else
		{
			first = 0;
			save_ast = isolate_command_redir(ptr);
		}
		if (save_ast)
		{
			create_while_help(save_ast, ast, &tmp, i);
			i++;
		}
	}
	return (ast);
}

t_node	*return_ptr(t_redir **redir, t_node *pt)
{
	if ((pt->next && ft_stcmp(pt->next->txt, "<") == 1) || (pt->next
			&& (ft_stcmp(pt->next->txt, ">") == 1)))
	{
		if (pt && ft_stcmp(pt->txt, "|") != 1)
			*redir = create_redir_node(*redir, pt);
		if (pt && ft_stcmp(pt->txt, "|") != 1)
			pt = pt->next;
		if (pt && ft_stcmp(pt->txt, "|") != 1)
			pt = pt->next;
		if (pt && ft_stcmp(pt->txt, "|") != 1)
			*redir = create_redir_node(*redir, pt);
	}
	else if (pt && ft_stcmp(pt->txt, "|") != 1)
	{
		if (pt && ft_stcmp(pt->txt, "|") != 1)
			*redir = create_redir_node(*redir, pt);
		if (pt)
			pt = pt->next;
		if (pt && ft_stcmp(pt->txt, "|") != 1)
			*redir = create_redir_node(*redir, pt);
	}
	if (pt && ft_stcmp(pt->txt, "|") != 1)
		pt = pt->next;
	return (pt);
}

t_ast	*return_save_ast(t_node *ptr, t_com *com, t_redir *redir)
{
	t_ast	*save_ast;

	if (ptr)
		ptr = ptr->next;
	save_ast = malloc(sizeof(t_ast));
	if (!save_ast)
		return (NULL);
	if (com)
		save_ast->command = com;
	else
		save_ast->command = NULL;
	if (redir)
		save_ast->redir = redir;
	else
		save_ast->redir = NULL;
	if (ptr)
		save_ast->save_ptr = ptr;
	return (save_ast);
}
