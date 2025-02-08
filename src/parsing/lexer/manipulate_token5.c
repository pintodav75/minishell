/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_token5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:27:03 by dpinto            #+#    #+#             */
/*   Updated: 2024/12/12 18:28:50 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_single_quotes_str_closed(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (1);
	return (0);
}

int	tokenize_quotes(t_source *src, t_info_tok *info, char c)
{
	if (c == '"' || c == '\'')
	{
		if (c == '"')
		{
			if (tokenize_double_quote(c, src, info) == 1)
				return (1);
		}
		else
		{
			if (tokenize_single_quote(c, src, info) == 1)
				return (1);
		}
	}
	return (0);
}
