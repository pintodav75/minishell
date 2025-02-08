/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:30:54 by wacista           #+#    #+#             */
/*   Updated: 2025/02/04 02:28:13 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

void	ft_exit_d(t_env **env, t_main **m)
{
	free_env(env);
	if ((*m)->pwd)
		free((*m)->pwd);
	free(*m);
	ft_putstr_fd("exit\n", 1);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit (g_exit_status);
}

static bool	exit_return(t_final *cmds, char *env[], t_pipex *p, t_main *m)
{
	if (p->nb_cmds == 1)
		remove_heredoc(cmds);
	ft_putstr_fd("exit\n", 1);
	exit_exe(cmds, env, p, m);
	return (true);
}

static void	builtin_exit_bis(t_final *cmds, t_pipex *p)
{
	long long	tmp;

	if (cmds->cmds[1][0] == '-')
	{
		if (ft_strlen(cmds->cmds[1]) > 20)
			return (print_exit(cmds, p, cmds->cmds[1], false));
		tmp = ft_atol_minus(cmds->cmds[1]);
		if (tmp > 0)
			return (print_exit(cmds, p, cmds->cmds[1], false));
	}
	else
	{
		if (ft_strlen(cmds->cmds[1]) > 19)
			return (print_exit(cmds, p, cmds->cmds[1], false));
		tmp = ft_atol_plus(cmds->cmds[1]);
		if (tmp < 0)
			return (print_exit(cmds, p, cmds->cmds[1], false));
	}
	p->exit_status = (int)tmp;
	if (p->nb_cmds == 1)
		remove_heredoc(cmds);
	ft_putstr_fd("exit\n", 1);
}

bool	builtin_exit(t_final *cmds, char *env[], t_pipex *p, t_main *m)
{
	int				i;
	int				j;

	if (!cmds->cmds[1])
		return (exit_return(cmds, env, p, m));
	i = 1;
	while (cmds->cmds[i])
	{
		j = 0;
		if (i > 1)
			return (print_exit(cmds, p, NULL, true), true);
		if ((cmds->cmds[i][j] == '-' || cmds->cmds[i][j] == '+') \
		&& cmds->cmds[i][j + 1])
			j++;
		while (cmds->cmds[i][j])
		{
			if (!ft_isdigit(cmds->cmds[i][j]))
				return (print_exit(cmds, p, cmds->cmds[i], false), \
				exit_exe(cmds, env, p, m), true);
			j++;
		}
		i++;
	}
	builtin_exit_bis(cmds, p);
	return (exit_exe(cmds, env, p, m), true);
}
