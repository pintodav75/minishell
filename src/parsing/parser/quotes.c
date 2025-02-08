/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:32:04 by dpinto            #+#    #+#             */
/*   Updated: 2024/12/12 18:32:05 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_there_quotes(t_node *root)
{
	t_node	*ptr;

	if (!root)
		return (2);
	ptr = root->first_child;
	while (ptr)
	{
		if (ft_stcmp(ptr->txt, "\"") == 1 || ft_stcmp(ptr->txt, "'") == 1)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

int	is_there_single_quotes(t_node *root)
{
	t_node	*ptr;

	if (!root)
		return (2);
	ptr = root->first_child;
	while (ptr)
	{
		if (ft_stcmp(ptr->txt, "'") == 1)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

int	is_there_double_quotes(t_node *root)
{
	t_node	*ptr;

	if (!root)
		return (2);
	ptr = root->first_child;
	while (ptr)
	{
		if (ft_stcmp(ptr->txt, "\"") == 1)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

int	is_there_both(t_node *root)
{
	t_node	*ptr;
	int		simple;
	int		double_quotes;

	simple = 0;
	double_quotes = 0;
	if (!root)
		return (2);
	ptr = root->first_child;
	while (ptr)
	{
		if (ft_stcmp(ptr->txt, "\"") == 1)
			simple++;
		if (ft_stcmp(ptr->txt, "'") == 1)
			double_quotes++;
		ptr = ptr->next;
	}
	if (simple > 0 && double_quotes > 0)
		return (1);
	return (0);
}
