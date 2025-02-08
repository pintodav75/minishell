/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export=.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:31:08 by wacista           #+#    #+#             */
/*   Updated: 2025/02/08 04:31:11 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

static bool	is_export_or_unset_all(char **s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (!ft_strncmp(s[i], "export=", 7) || !(ft_strncmp(s[i], "unset=", 6)))
			count++;
		i++;
	}
	if (count == i)
		return (true);
	return (false);
}

void	builtin_exp_equl(t_final *cmds)
{
	int	i;
	int	j;

	if (is_export_or_unset_all(cmds->cmds))
		return ;
	i = 0;
	j = 0;
	while (cmds->cmds[i])
	{
		if (!ft_strncmp(cmds->cmds[i], "export=\
", 7) || !ft_strncmp(cmds->cmds[i], "unset=", 6))
			free(cmds->cmds[i]);
		else
		{
			while (cmds->cmds[i])
			{
				cmds->cmds[j] = cmds->cmds[i];
				i++;
				j++;
			}
			break ;
		}
		i++;
	}
	cmds->cmds[j] = NULL;
}
