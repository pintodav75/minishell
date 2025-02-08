/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_node_commannd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:31:34 by dpinto            #+#    #+#             */
/*   Updated: 2024/12/12 18:31:35 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_com	*create_com_node(t_com *com, t_node *node)
{
	t_com	*ptr;
	t_com	*follow;

	ptr = malloc(sizeof(t_com));
	if (!node)
		return (NULL);
	if (!com)
	{
		ptr->txt = malloc(sizeof(char) * ((ft_strlen(node->txt) + 1)));
		ft_strlcpy(ptr->txt, node->txt, ft_strlen(node->txt) + 1);
		ptr->next = NULL;
		com = ptr;
	}
	else
	{
		follow = com;
		while (follow->next != NULL)
			follow = follow->next;
		follow->next = ptr;
		ptr->txt = malloc(sizeof(char) * ((ft_strlen(node->txt) + 1)));
		ft_strlcpy(ptr->txt, node->txt, ft_strlen(node->txt) + 1);
		ptr->next = NULL;
	}
	return (com);
}
