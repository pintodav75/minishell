/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:36:00 by wacista           #+#    #+#             */
/*   Updated: 2024/12/16 20:36:01 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_ast_loop(t_final *ast, t_final *save_ast, \
t_redir *save_redir, int i)
{
	while (ast)
	{
		save_ast = ast -> next;
		while (ast -> cmds[i])
		{
			free(ast -> cmds[i]);
			ast -> cmds[i] = NULL;
			i++;
		}
		free(ast -> cmds);
		while (ast -> redir)
		{
			save_redir = ast -> redir -> next;
			if (ast -> redir -> txt)
				free(ast -> redir -> txt);
			ast -> redir -> txt = NULL;
			if (ast -> redir)
				free(ast -> redir);
			ast -> redir = NULL;
			ast -> redir = save_redir;
		}
		i = 0;
		free(ast);
		ast = save_ast;
	}
}

void	ft_free_final_ast(t_final **ast_before)
{
	t_final	*ast;
	t_final	*save_ast;
	t_redir	*save_redir;
	int		i;

	if (!ast_before)
		return ;
	ast = *ast_before;
	if (!ast)
		return ;
	i = 0;
	save_ast = NULL;
	save_redir = NULL;
	ft_free_ast_loop(ast, save_ast, save_redir, i);
	ast_before = NULL;
}

void	ft_free_before_ast_loop(t_com **ast, t_com *ptr, t_com *save_ptr)
{
	int	i;

	i = 0;
	while (ast[i])
	{
		ptr = ast[i];
		while (ptr)
		{
			save_ptr = ptr -> next;
			if (ptr -> txt)
			{
				free(ptr -> txt);
				ptr -> txt = NULL;
			}
			free(ptr);
			ptr = save_ptr;
		}
		ast[i] = NULL;
		i++;
	}
}

void	ft_free_before_final_ast(t_com ***ast_before)
{
	t_com	**ast;
	t_com	*ptr;
	t_com	*save_ptr;

	if (!ast_before)
		return ;
	ast = *ast_before;
	if (!ast)
		return ;
	ptr = NULL;
	save_ptr = NULL;
	ft_free_before_ast_loop(ast, ptr, save_ptr);
	free(ast);
	ast_before = NULL;
}

void	free_in_insert_input_env(char *env, char *var_name, char *var_value)
{
	if (env)
		free(env);
	if (var_name)
		free(var_name);
	if (var_value)
		free(var_value);
}
