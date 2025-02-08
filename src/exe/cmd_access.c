/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_access.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:31:50 by wacista           #+#    #+#             */
/*   Updated: 2025/02/08 04:31:20 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

static void	get_path(t_pipex *p, char *env[])
{
	int		i;
	char	*path_line;

	path_line = NULL;
	while (*env)
	{
		if (ft_strnstr(*env, "PATH=", 5))
		{
			path_line = ft_substr(*env, 5, ft_strlen(*env));
			break ;
		}
		env++;
	}
	if (!path_line)
		return ;
	p->path = ft_split(path_line, ':');
	free(path_line);
	i = 0;
	while (p->path[i])
	{
		p->path[i] = ft_strjoin_free(p->path[i], "/");
		i++;
	}
}

static bool	raw_access(t_pipex *p, t_final *cmds)
{
	if (!access(cmds->cmds[0], F_OK | X_OK))
	{
		p->cmd_path = ft_strdup(cmds->cmds[0]);
		return (true);
	}
	return (false);
}

static void	init_access(t_pipex *p, t_final *cmds)
{
	int		i;

	if (!p->path)
		return ;
	i = 0;
	while (p->path[i])
	{
		p->cmd_path = ft_strjoin(p->path[i], cmds->cmds[0]);
		if (!access(p->cmd_path, F_OK | X_OK))
			return ;
		free(p->cmd_path);
		p->cmd_path = NULL;
		i++;
	}
}

void	is_access(t_pipex *p, t_final *cmds, char *env[])
{
	if (cmds->cmds[0] && (!ft_strncmp(cmds->cmds[0], "export=\
", 7) || !ft_strncmp(cmds->cmds[0], "unset=", 6)))
		builtin_exp_equl(cmds);
	if (!raw_access(p, cmds))
	{
		get_path(p, env);
		init_access(p, cmds);
	}
	update_cmd_exe(p, cmds, env);
}
