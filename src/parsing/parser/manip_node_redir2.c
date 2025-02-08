/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_node_redir2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:31:44 by dpinto            #+#    #+#             */
/*   Updated: 2024/12/12 18:31:45 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_redir_if(t_redir *ptr, t_node *node)
{
	ptr->heredoc = 0;
	ptr->in_file = 0;
	ptr->out_file = 0;
	ptr->append = 0;
	ptr->file = 0;
	ptr->txt = malloc(sizeof(char) * ((ft_strlen(node->txt) + 1)));
	ft_strlcpy(ptr->txt, node->txt, ft_strlen(node->txt) + 1);
	ptr->next = NULL;
}

void	init_redir_else(t_redir *ptr)
{
	ptr->heredoc = 0;
	ptr->in_file = 0;
	ptr->out_file = 0;
	ptr->append = 0;
	ptr->file = 0;
}

void	ft_heredoc_redir(t_redir *ptr)
{
	ptr->heredoc = 1;
	free(ptr->txt);
	ptr->txt = malloc(sizeof(char) * 3);
	ft_strlcpy(ptr->txt, "<<", 3);
}

void	ft_file(t_redir *ptr)
{
	ptr->in_file = 1;
}

void	ft_append(t_redir *ptr)
{
	ptr->append = 1;
	free(ptr->txt);
	ptr->txt = malloc(sizeof(char) * 3);
	ft_strlcpy(ptr->txt, ">>", 3);
}
