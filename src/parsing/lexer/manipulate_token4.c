/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_token4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:26:56 by dpinto            #+#    #+#             */
/*   Updated: 2024/12/12 18:40:47 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	avance_curpos(t_source *src, char c)
{
	if (c != '"' && c != '\'')
		src->curpos++;
}

int	tokenize_double_quote(char c, t_source *src, t_info_tok *info)
{
	if (info->tok_bufindex != -1
		&& (does_str_has_double_quotes(info->tok_buf) == 1)
		&& (is_single_quotes_str_closed(info->tok_buf) == 1)
		&& (next_src_is_legit(src) == 0))
	{
		info->tok_bufindex++;
		add_to_buf(c, info);
		info->tok_bufindex++;
		info->tok_buf[info->tok_bufindex] = '\0';
		src->curpos++;
		return (1);
	}
	else
	{
		info->tok_bufindex++;
		add_to_buf(c, info);
		src->curpos++;
		return (0);
	}
	return (0);
}

int	next_src_is_legit(t_source *src)
{
	if (!src)
		return (0);
	if (!(src->buffer[src->curpos + 1]))
		return (0);
	if (src->buffer[src->curpos + 1])
	{
		if (src->buffer[src->curpos + 1] != ' '
			&& src->buffer[src->curpos + 1] != '\t')
			return (1);
	}
	return (0);
}

int	does_str_has_single_quotes(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (2);
	while (str[i])
	{
		if (str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int	does_str_has_double_quotes(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (2);
	while (str[i])
	{
		if (str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}
