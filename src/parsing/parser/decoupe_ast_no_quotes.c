/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoupe_ast_no_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:29:10 by dpinto            #+#    #+#             */
/*   Updated: 2024/12/16 21:05:01 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_com	**create_ast_command_redir(t_node *root)
{
	t_com	**ast;
	t_ast	*save_ast;
	t_node	*ptr;
	int		nbr_pipe;

	save_ast = NULL;
	ast = NULL;
	ptr = NULL;
	nbr_pipe = 0;
	if (!root)
		return (NULL);
	ptr = root->first_child;
	nbr_pipe = how_much_pipe(root);
	ast = malloc_ast(ast, nbr_pipe);
	ast = create_while(ast, save_ast, ptr, nbr_pipe);
	return (ast);
}

t_ast	*isolate_command_redir(t_node *pt)
{
	t_redir	*redir;
	t_com	*com;

	if (!pt)
		return (NULL);
	com = NULL;
	redir = NULL;
	if (pt)
	{
		while (pt && ft_stcmp(pt->txt, "|") != 1)
		{
			while (pt && ft_stcmp(pt->txt, "|") != 1 && ft_stcmp(pt->txt,
					"<") != 1 && ft_stcmp(pt->txt, ">") != 1)
			{
				com = create_com_node(com, pt);
				pt = pt->next;
			}
			if (pt)
			{
				if (ft_stcmp(pt->txt, "<") == 1 || ft_stcmp(pt->txt, ">") == 1)
					pt = return_ptr(&redir, pt);
			}
		}
	}
	return (return_save_ast(pt, com, redir));
}
