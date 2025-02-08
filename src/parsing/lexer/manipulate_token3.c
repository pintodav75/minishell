/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_token3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:26:46 by dpinto            #+#    #+#             */
/*   Updated: 2025/02/08 11:46:21 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize_while(t_source *src, t_info_tok *info, char c)
{
	if (tokenize_quotes(src, info, c) == 1)
		return (1);
	if ((c == ' ' || c == '\t' || c == '\n')
		&& (does_str_has_quotes(info->tok_buf)) == 0)
	{
		if (tokenize_space(c, src, info) == 1)
			return (1);
	}
	else if (c == '|' && (does_str_has_quotes(info->tok_buf)) == 0)
	{
		if (tokenize_pipe(c, src, info) == 1)
			return (1);
	}
	else if ((c == '<' || c == '>')
		&& (does_str_has_quotes(info->tok_buf)) == 0)
	{
		if (tokenize_in_out(c, src, info) == 1)
			return (1);
	}
	else if (c != '"' && c != '\'')
	{
		info->tok_bufindex++;
		add_to_buf(c, info);
	}
	return (0);
}

void	init_buf_size(t_info_tok *info, long bufsize)
{
	info->tok_bufsize = (int)bufsize + 1024;
	info->tok_buf = ft_calloc(info->tok_bufsize, sizeof(char));
}

int	does_str_has_quotes(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (2);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int	is_just_tok_quotes(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		if (str[i] != '"' && str[i] != '\'')
			return (1);
	}
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '"' && str[i] != '\'')
				i++;
			if (str[i] == '\'' || str[i] == '"')
				return (1);
		}
		i++;
	}
	return (0);
}

int	is_double_quotes_str_closed(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (1);
	return (0);
}
