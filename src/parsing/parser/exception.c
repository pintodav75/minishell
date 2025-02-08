/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:29:33 by dpinto            #+#    #+#             */
/*   Updated: 2025/02/08 10:11:14 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_enter(char *input)
{
	if (!input)
		return (1);
	if (input[0] == '\0')
		return (1);
	if (ft_strlen(input) <= 0)
		return (1);
	if (ft_strlen(input) >= 131072)
	{
		ft_printf("minishell: command-not-found: Argument list too long\n");
		return (1);
	}
	if (input[0] == '\n')
		return (1);
	if (only_space(input) == 1)
		return (1);
	return (0);
}

int	only_space(char *str)
{
	int	i;
	int	letter;

	i = 0;
	letter = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			letter++;
		i++;
	}
	if (letter == 0)
		return (1);
	return (0);
}
