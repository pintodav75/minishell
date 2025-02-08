/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_node_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:31:39 by dpinto            #+#    #+#             */
/*   Updated: 2024/12/12 18:31:40 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*create_redir_node(t_redir *redir, t_node *node)
{
	t_redir	*ptr;

	ptr = malloc(sizeof(t_redir));
	if (!node)
		return (NULL);
	if (!redir)
	{
		init_redir_if(ptr, node);
		redir = ptr;
		redir = create_redir_node_if(redir, node, ptr);
	}
	else
	{
		init_redir_else(ptr);
		add_new_redir_to_list(redir, ptr, node);
		redir = create_redir_node_else(redir, node, ptr);
	}
	return (redir);
}
