/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_env6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:30:58 by dpinto            #+#    #+#             */
/*   Updated: 2025/02/08 13:01:18 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_var_value(t_env *node)
{
	int	i;
	int	equal;

	if (!node)
		return ;
	if (node->txt == NULL)
		return ;
	equal = 0;
	while (node->txt[equal] != '=')
		equal++;
	i = equal;
	while (node->txt[i] != '\0')
		i++;
	node->var_value = malloc((sizeof(char) * (i - equal)) + 1);
	if (node->var_value == NULL)
		return ;
	i = 0;
	equal++;
	while (node->txt[equal] != '\0')
	{
		node->var_value[i] = node->txt[equal];
		i++;
		equal++;
	}
	node->var_value[i] = '\0';
}

t_node	*do_i_have_to_expand(t_node *node)
{
	t_node	*ptr;
	int		i;

	i = 0;
	if (!node)
		return (NULL);
	ptr = node;
	if (node->after_here_doc == 1)
		return (NULL);
	if (ptr != NULL)
	{
		while (ptr->txt[i] != '\0')
		{
			if (ptr->txt[i] == '$' && (ft_isalnum(ptr->txt[i + 1])
					|| ptr->txt[i + 1] == '?' || ptr->txt[i + 1] == '_'))
				return (ptr);
			i++;
		}
	}
	return (NULL);
}

void	expand_env(t_env *head, t_node *root)
{
	t_node	*ptr;
	t_node	*expand;

	if (!head || !root)
		return ;
	attribute_atfer_here_doc(attribue_here_doc(root));
	ptr = root->first_child;
	while (ptr)
	{
		expand = do_i_have_to_expand(ptr);
		if (expand)
			expand_job(head, ptr);
		ptr = ptr->next;
	}
}

int	is_it_heredoc(t_node *node)
{
	t_node	*ptr;

	if (!node)
		return (0);
	ptr = node;
	if (ptr->txt[0] == '<')
	{
		if (ptr->next)
		{
			if (ptr->next->txt[0] == '<')
				return (1);
		}
	}
	return (0);
}
