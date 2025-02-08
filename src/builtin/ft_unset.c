/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:29:58 by wacista           #+#    #+#             */
/*   Updated: 2025/02/05 07:03:30 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

int	ft_stcmp_unset(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1)
		return (0);
	if (!str2)
		return (0);
	if (str1[0] == '\0')
		return (0);
	if (ft_strlen(str1) != ft_strlen(str2))
		return (0);
	while (str1[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}

static void	unset_del(t_env **head, t_node *ptr, t_main *m)
{
	while (ptr)
	{
		if (check_if_exist(*head, ptr->txt) == 1)
		{
			if (!ft_strcmp(ptr->txt, "PWD"))
				if (!m->pwd)
					m->pwd = getpwd(*head);
			if (ft_strcmp(ptr->txt, "_"))
				supp_env(head, ptr->txt);
		}
		ptr = ptr->next;
	}
}

int	is_unset(t_env **head, t_node *root, t_main *m)
{
	t_node	*ptr;

	if (!root)
		return (1);
	if (how_much_pipe(root))
		return (0);
	ptr = root->first_child;
	if (ptr)
	{
		if (!ft_strcmp(ptr->txt, "unset"))
		{
			g_exit_status = 0;
			if (ptr->next && !is_empty(ptr, 1))
			{
				ptr = ptr->next;
				unset_del(head, ptr, m);
			}
			update_cmd(head, root->first_child);
			return (1);
		}
	}
	return (0);
}

int	check_if_exist(t_env *head, char *str)
{
	t_env	*ptr;

	if (!head)
		return (2);
	ptr = head;
	while (ptr != NULL)
	{
		if (ft_stcmp_unset(str, ptr -> var_name) == 1)
			return (1);
		ptr = ptr -> next;
	}
	return (0);
}

void	supp_env(t_env **head, char *str)
{
	t_env	*ptr;
	t_env	*before;

	if (!head)
		return ;
	ptr = *head;
	if (!ptr)
		return ;
	if (supp_env_first(ptr, head, str) == 1)
		return ;
	before = ptr;
	while (ptr -> next != NULL)
	{
		if (supp_env_milieu(ptr, before, str) == 1)
			return ;
		before = ptr;
		ptr = ptr -> next;
	}
	if (supp_env_last(ptr, str, before) == 1)
		return ;
}
