/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:31:25 by wacista           #+#    #+#             */
/*   Updated: 2025/02/08 12:16:09 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

static bool	builtin_export_unset(t_pipex *p)
{
	p->exit_status = 0;
	return (true);
}

static void	print_export(char *s, int *ex, int *p_status)
{
	char	*msg;

	msg = ft_strjoin("minishell: export: `", s);
	msg = ft_strjoin_free(msg, "': not a valid identifier\n");
	write(2, msg, ft_strlen(msg));
	free(msg);
	*ex = 1;
	*p_status = 1;
}

static	bool	builtin_export_exe(t_final *cmds, t_pipex *p, t_main *m)
{
	int	i;
	int	j;

	i = 1;
	m->ex = 0;
	while (cmds->cmds[i])
	{
		j = 0;
		if (!ft_isalpha(cmds->cmds[i][j]))
			print_export(cmds->cmds[i], &m->ex, &p->exit_status);
		else
		{
			while (cmds->cmds[i][j] && cmds->cmds[i][j] != '=')
			{
				if (!ft_isalnum(cmds->cmds[i][j]))
					print_export(cmds->cmds[i], &m->ex, &p->exit_status);
				j++;
			}
		}
		i++;
	}
	if (!m->ex)
		p->exit_status = 0;
	return (true);
}

bool	builtin(t_final *cmds, char *env[], t_pipex *p, t_main *m)
{
	if (!ft_strcmp(cmds->cmds[0], "exit"))
		return (builtin_exit(cmds, env, p, m));
	if (!ft_strcmp(cmds->cmds[0], "echo"))
		return (builtin_echo(cmds, p));
	if (!ft_strcmp(cmds->cmds[0], "unset"))
		return (builtin_export_unset(p));
	if (!ft_strcmp(cmds->cmds[0], "cd"))
		return (builtin_cd(cmds, env, p, m));
	if (!ft_strcmp(cmds->cmds[0], "pwd"))
		return (builtin_pwd(p, m, env));
	if (!ft_strcmp(cmds->cmds[0], "export\
") && (!cmds->cmds[1] || !*(cmds->cmds)[1]))
		return (builtin_export(env, p));
	if (!ft_strcmp(cmds->cmds[0], "export") && cmds->cmds[1])
		return (builtin_export_exe(cmds, p, m));
	if ((!ft_strcmp(cmds->cmds[0], "env")) && !cmds->cmds[1])
		return (builtin_env(env, p));
	if (cmds->cmds[0] && (!ft_strncmp(cmds->cmds[0], "export=\
", 7) || !ft_strncmp(cmds->cmds[0], "unset=", 6)))
		return (p->exit_status = 0, true);
	return (false);
}

bool	isbuiltin(t_final *cmds)
{
	if (!ft_strcmp(cmds->cmds[0], "exit"))
		return (true);
	if (!ft_strcmp(cmds->cmds[0], "echo"))
		return (true);
	if (!ft_strcmp(cmds->cmds[0], "cd"))
		return (true);
	if ((!ft_strcmp(cmds->cmds[0], "export")))
		return (true);
	if (!ft_strcmp(cmds->cmds[0], "pwd"))
		return (true);
	return (false);
}
