/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:35:52 by wacista           #+#    #+#             */
/*   Updated: 2025/02/08 12:58:14 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_info(t_info_tok **info)
{
	t_info_tok	*ptr;

	if (info)
	{
		ptr = *info;
		if (ptr)
		{
			if (ptr -> tok_buf)
			{
				free(ptr -> tok_buf);
				ptr -> tok_buf = NULL;
			}
			free(ptr);
			ptr = NULL;
		}
		else
			free(ptr);
		info = NULL;
	}
}

void	free_src(t_source **src)
{
	t_source	*ptr;

	if (src)
	{
		ptr = *src;
		if (ptr)
		{
			if (ptr -> buffer)
			{
				free (ptr -> buffer);
				ptr -> buffer = NULL;
			}
			free(ptr);
		}
		src = NULL;
	}
}

void	free_tok(t_token **tok)
{
	t_token	*ptr;

	if (tok)
	{
		ptr = *tok;
		if (ptr)
		{
			if (ptr -> text)
			{
				if (ptr -> text)
				{
					free(ptr-> text);
					ptr -> text = NULL;
				}
				ptr -> text = NULL;
			}
			free(ptr);
		}
		tok = NULL;
	}
}

void	free_info_buf(t_info_tok *info)
{
	t_info_tok	*ptr;

	if (info)
	{
		ptr = info;
		if (ptr)
		{
			if (ptr -> tok_buf)
			{
				free(ptr -> tok_buf);
				ptr -> tok_buf = NULL;
			}
			ptr -> tok_buf = NULL;
		}
	}
}
