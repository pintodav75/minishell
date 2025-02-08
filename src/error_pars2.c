/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pars2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:33:14 by dpinto            #+#    #+#             */
/*   Updated: 2025/02/01 21:39:22 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

int	end_comm(char *str, int i, int single, int double_q)
{
	if (str[i] == '|')
	{
		if (single % 2 != 0 || double_q % 2 != 0)
			return (print_error_quotes("quotes"), 0);
	}
	return (1);
}

static int	ft_is_print(int c)
{
	if (c == '\t')
		return (1);
	if (c > 32 && c <= 126)
		return (1);
	return (0);
}

bool	is_printable(char *s)
{
	if (!s)
		return (false);
	while (*s)
	{
		if (ft_is_print(*s++))
			return (true);
	}
	return (false);
}
