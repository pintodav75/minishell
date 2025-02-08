/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:26:31 by dpinto            #+#    #+#             */
/*   Updated: 2025/02/08 11:36:19 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_buf(char c, t_info_tok *info)
{
	char	*tmp;

	if (info->tok_bufindex >= info->tok_bufsize)
	{
		tmp = ft_calloc((info->tok_bufsize * 2), sizeof(char));
		if (!tmp)
			return ;
		ft_strlcpy(tmp, info->tok_buf, ft_strlen(info->tok_buf));
		free(info->tok_buf);
		info->tok_buf = tmp;
		info->tok_bufsize = info->tok_bufsize * 2;
	}
	info->tok_buf[info->tok_bufindex] = c;
}

void	free_token(t_token *tok)
{
	if (tok)
	{
		if (tok->text)
			free(tok->text);
		free(tok);
		tok = NULL;
	}
}

t_token	*tokenize(t_source *src, t_info_tok *info)
{
	t_token	*tok;
	char	c;

	if (src->end_input == 1)
		src->exit = 1;
	tok = NULL;
	if (!src || !src->buffer || !src->bufsize)
		return (NULL);
	if (!(info->tok_buf))
		init_buf_size(info, src->bufsize);
	info->tok_buf[0] = '\0';
	c = src->buffer[src->curpos];
	while (c)
	{
		if (tokenize_while(src, info, c) == 1)
			break ;
		avance_curpos(src, c);
		c = src->buffer[src->curpos];
	}
	if (c == '\0' || c == '\n')
		tokenize_end(c, src, info);
	if (is_just_tok_quotes(info->tok_buf) == 1)
		tok = create_token(info->tok_buf, src, info);
	info->tok_bufindex = -1;
	return (tok);
}

t_token	*create_token(char *str, t_source *src, t_info_tok *info)
{
	t_token	*tok;

	if (info->tok_bufindex == -1)
		return (NULL);
	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->text_len = ft_strlen(str);
	tok->src = src;
	tok->text = malloc(sizeof(char) * ((tok->text_len) + 1));
	ft_strlcpy(tok->text, info->tok_buf, tok->text_len + 1);
	return (tok);
}
