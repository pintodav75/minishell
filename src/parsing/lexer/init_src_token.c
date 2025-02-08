/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_src_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:20:52 by dpinto            #+#    #+#             */
/*   Updated: 2024/12/16 20:20:53 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_source	**init_src(t_source **src, char *input)
{
	t_source	*src_ft;

	*(src) = malloc(sizeof(t_source));
	src_ft = *src;
	src_ft->buffer = input;
	src_ft->bufsize = ft_strlen(input);
	src_ft->curpos = 0;
	src_ft->end_input = 0;
	src_ft->exit = 0;
	return (src);
}

t_info_tok	**init_global_info_token(t_info_tok **info)
{
	t_info_tok	*info_ft;

	*(info) = malloc(sizeof(t_info_tok));
	info_ft = *(info);
	info_ft->tok_buf = NULL;
	info_ft->tok_bufsize = 0;
	info_ft->tok_bufindex = -1;
	return (info);
}
