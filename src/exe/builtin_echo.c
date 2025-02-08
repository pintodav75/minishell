/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:30:38 by wacista           #+#    #+#             */
/*   Updated: 2025/01/17 16:57:48 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

int	n_arg(t_final *cmds)
{
	int	i;
	int	j;

	i = 1;
	while (cmds->cmds[i])
	{
		j = 0;
		if (!j && cmds->cmds[i][j] == '-')
			j++;
		else
			return (i);
		if (!cmds->cmds[i][j])
			return (i);
		while (cmds->cmds[i][j])
		{
			if (cmds->cmds[i][j] != 'n')
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

bool	builtin_echo(t_final *cmds, t_pipex *p)
{
	int	i;
	int	n;

	if (!cmds->cmds[1])
		return (p->exit_status = 0, ft_putstr_fd("\n", 1), true);
	i = n_arg(cmds);
	n = i;
	while (cmds->cmds[i])
	{
		ft_putstr_fd(cmds->cmds[i], 1);
		if (cmds->cmds[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (n == 1)
		ft_putstr_fd("\n", 1);
	p->exit_status = 0;
	return (true);
}
