/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:31:59 by dpinto            #+#    #+#             */
/*   Updated: 2024/12/12 18:31:59 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

int	single_quote_closed(t_node *head)
{
	t_node	*ptr;
	int		count;

	count = 0;
	if (!head)
		return (2);
	ptr = head->first_child;
	while (ptr)
	{
		if (ft_stcmp(ptr->txt, "'") == 1)
			count++;
		ptr = ptr->next;
	}
	if (count % 2 != 0)
		return (print_error_quotes("single quotes"), 0);
	return (1);
}

int	double_quote_closed(t_node *head)
{
	t_node	*ptr;
	int		count;

	count = 0;
	if (!head)
		return (2);
	ptr = head->first_child;
	while (ptr)
	{
		if (ft_stcmp(ptr->txt, "\"") == 1)
			count++;
		ptr = ptr->next;
	}
	if (count % 2 != 0)
		return (print_error_quotes("double quotes"), 0);
	return (1);
}

int	quote_closed(t_node *head)
{
	if (single_quote_closed(head) == 0)
		return (0);
	if (double_quote_closed(head) == 0)
		return (0);
	return (1);
}
