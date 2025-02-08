/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_env9.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:31:15 by dpinto            #+#    #+#             */
/*   Updated: 2025/02/08 12:56:46 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_guillemets(char *str, int index_dol)
{
	int	i;
	int	save_index_dol;
	int	index_simple;
	int	nbr_double_q;
	int	nbr_simple;

	i = 0;
	nbr_simple = 0;
	nbr_double_q = 0;
	save_index_dol = index_dol;
	expand_guillemets_first(str, &index_dol, &nbr_simple, &index_simple);
	if (nbr_simple == 0)
		return (1);
	index_dol = save_index_dol;
	while (i <= index_simple)
	{
		if (str[i] == '"')
			nbr_double_q++;
		i++;
	}
	if (nbr_simple % 2 == 0)
		return (1);
	if (nbr_double_q > 0 && nbr_double_q % 2 != 0)
		return (1);
	return (0);
}

t_node	*attribue_here_doc(t_node *root)
{
	t_node	*ptr;

	if (!root)
		return (NULL);
	ptr = root->first_child;
	if (ptr)
		ptr->quotes = 0;
	while (ptr)
	{
		if (is_it_heredoc(ptr) == 1)
		{
			ptr->heredoc = 0;
			ptr->next->heredoc = 1;
			return (ptr->next);
		}
		else
		{
			ptr->heredoc = 0;
			ptr->after_here_doc = 0;
		}
		ptr = ptr->next;
	}
	return (NULL);
}

void	attribute_atfer_here_doc(t_node *node)
{
	t_node	*ptr;

	if (!node)
		return ;
	ptr = node->next;
	while (ptr)
	{
		if (does_str_has_quotes(ptr->txt) == 1)
			ptr->quotes = 1;
		else
			ptr->quotes = 0;
		ptr->after_here_doc = 1;
		ptr = ptr->next;
	}
}
