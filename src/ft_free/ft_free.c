/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:36:08 by wacista           #+#    #+#             */
/*   Updated: 2025/02/06 03:05:52 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ast_conditions(t_node *ptr_node, t_node *save)
{
	if (ptr_node)
	{
		if (ptr_node -> next != NULL)
		{
			while (ptr_node -> next != NULL)
			{
				save = ptr_node -> next;
				free(ptr_node -> txt);
				free(ptr_node);
				ptr_node = save;
			}
			free(ptr_node -> txt);
			free(ptr_node);
		}
		else
		{
			free(ptr_node -> txt);
			free(ptr_node);
		}
	}
}

void	free_ast(t_node **root)
{
	t_node	*ptr_root;
	t_node	*ptr_node;
	t_node	*save;

	if (!root)
		return ;
	ptr_root = *root;
	save = NULL;
	if (ptr_root)
	{
		ptr_node = ptr_root -> first_child;
		free_ast_conditions(ptr_node, save);
		free(ptr_root);
		root = NULL;
	}
	free(root);
	root = NULL;
}

void	free_env(t_env **mini_env)
{
	t_env	*ptr_env;
	t_env	*save_env;

	if (!mini_env)
		return ;
	ptr_env = *mini_env;
	if (ptr_env)
	{
		while (ptr_env)
		{
			save_env = ptr_env->next;
			free(ptr_env->txt);
			free(ptr_env->var_name);
			free(ptr_env->var_value);
			free(ptr_env);
			ptr_env = save_env;
		}
	}
}

void	free_final_env(char ***tab_env)
{
	int		i;
	char	**tab;

	i = 0;
	if (!tab_env)
		return ;
	tab = *tab_env;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab_env = NULL;
}

void	ft_free(t_env **mini_env, t_node **root, \
t_source **src, t_info_tok **info)
{
	if (root)
		free_ast(root);
	if (mini_env)
		free_env(mini_env);
	if (src)
		free_src(src);
	if (info)
		free_info(info);
}
