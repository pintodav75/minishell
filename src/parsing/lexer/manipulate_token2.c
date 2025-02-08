/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_token2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:26:38 by dpinto            #+#    #+#             */
/*   Updated: 2024/12/12 18:26:40 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

int	tokenize_space(char c, t_source *src, t_info_tok *info)
{
	(void)c;
	if (info->tok_bufindex != -1)
	{
		info->tok_bufindex++;
		info->tok_buf[info->tok_bufindex] = '\0';
		src->curpos++;
		return (1);
	}
	return (0);
}

int	tokenize_pipe(char c, t_source *src, t_info_tok *info)
{
	(void)c;
	if (info->tok_bufindex != -1)
	{
		info->tok_bufindex++;
		info->tok_buf[info->tok_bufindex] = '\0';
		return (1);
	}
	else
	{
		info->tok_bufindex++;
		add_to_buf(c, info);
		src->curpos++;
		return (1);
	}
	return (0);
}

void	tokenize_end(char c, t_source *src, t_info_tok *info)
{
	(void)c;
	if (info->tok_bufindex != -1)
	{
		info->tok_bufindex++;
		info->tok_buf[info->tok_bufindex] = '\0';
	}
	src->end_input = 1;
}

int	tokenize_in_out(char c, t_source *src, t_info_tok *info)
{
	(void)c;
	if (info->tok_bufindex != -1)
	{
		info->tok_bufindex++;
		info->tok_buf[info->tok_bufindex] = '\0';
		return (1);
	}
	else
	{
		info->tok_bufindex++;
		add_to_buf(c, info);
		src->curpos++;
		return (1);
	}
	return (0);
}

int	tokenize_single_quote(char c, t_source *src, t_info_tok *info)
{
	if (info->tok_bufindex != -1
		&& (does_str_has_single_quotes(info->tok_buf) == 1)
		&& (is_double_quotes_str_closed(info->tok_buf) == 1)
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
