/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:26:18 by dpinto            #+#    #+#             */
/*   Updated: 2024/12/12 18:26:20 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	next_char(t_source *src)
{
	char	nc;

	nc = '\n';
	if (!src || !src->buffer)
	{
		return (nc);
	}
	if (src->buffer[src->curpos])
	{
		nc = src->buffer[src->curpos + 1];
		src->curpos++;
		return (nc);
	}
	return (nc);
}

void	unget_char(t_source *src)
{
	if (!src || !src->buffer)
		return ;
	if (src->curpos == 0)
		return ;
	else
		src->curpos--;
}

char	peek_char(t_source *src)
{
	char	nc;

	nc = '\n';
	if (!src || !src->buffer)
		return (nc);
	if (src->buffer[src->curpos])
	{
		nc = src->buffer[src->curpos + 1];
		return (nc);
	}
	return (nc);
}

void	skip_white_spaces(t_source *src)
{
	if (!src || !src->buffer)
		return ;
	while (src->buffer[src->curpos] && (src->buffer[src->curpos] == ' '
			|| src->buffer[src->curpos] == '\t'))
		src->curpos++;
}
