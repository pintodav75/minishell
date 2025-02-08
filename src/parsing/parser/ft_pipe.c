/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:30:06 by dpinto            #+#    #+#             */
/*   Updated: 2024/12/12 18:30:06 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

int	ft_pipe_first_check(t_node *ptr)
{
	if (!ptr)
		return (1);
	if (ptr->prev_sibling == NULL)
		return (print_error_syntax("|"), 0);
	if (ptr->next == NULL)
		return (print_error_syntax("newline"), 0);
	if (ptr->next)
		if (ft_stcmp(ptr->next->txt, "|") == 1)
			return (print_error_syntax("|"), 0);
	return (1);
}

int	ft_pipe_check(t_node *head)
{
	t_node	*ptr;

	ptr = head;
	if (!ptr)
		return (2);
	if (ptr->first_child)
		ptr = ptr->first_child;
	while (ptr != NULL)
	{
		if (ft_stcmp(ptr->txt, "|") == 1)
		{
			if (ft_pipe_first_check(ptr) == 0)
				return (0);
			while (ptr && (ft_stcmp(ptr->txt, "|") == 1))
				ptr = ptr->next;
		}
		if (ptr && ft_stcmp(ptr->txt, "|") != 1)
			ptr = ptr->next;
	}
	return (1);
}

int	how_much_pipe(t_node *root)
{
	t_node	*ptr;
	int		count;

	count = 0;
	if (!root)
		return (0);
	ptr = root->first_child;
	while (ptr)
	{
		if (ft_stcmp(ptr->txt, "|") == 1)
			count++;
		ptr = ptr->next;
	}
	return (count);
}
