/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:31:32 by wacista           #+#    #+#             */
/*   Updated: 2025/02/08 04:13:56 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

static t_final	*get_right_cmd(t_final *cmds, int i)
{
	int	j;

	j = 0;
	while (cmds)
	{
		if (j == i)
			return (cmds);
		cmds = cmds->next;
		j++;
	}
	return (cmds);
}

static bool	isprintable(char *s)
{
	if (!s)
		return (false);
	while (*s)
	{
		if (ft_isprint(*s++))
			return (true);
	}
	return (false);
}

static char	*get_last_cmd(t_pipex *p, t_final *cmd)
{
	int		i;
	char	*dest;

	i = 1;
	if (p->cmd_path)
		dest = p->cmd_path;
	else
		i = 0;
	while (cmd->cmds[i])
	{
		dest = cmd->cmds[i];
		i++;
	}
	return (dest);
}

void	update_cmd_exe(t_pipex *p, t_final *cmd, char *env[])
{
	char	*txt;

	txt = get_last_cmd(p, cmd);
	if (!txt)
		return ;
	while (*env)
	{
		if (!ft_strncmp(*env, "_", 1) && (*env)[1] == '=')
		{
			free(*env);
			*env = ft_strjoin("_=", txt);
			return ;
		}
		env++;
	}
}

void	child_processs(t_final *cmds, char *env[], t_pipex *p, t_main *m)
{
	t_final	*tmp_cmds;
	t_redir	*tmp_redir;

	close_unused_pipes(p);
	tmp_cmds = get_right_cmd(cmds, p->i);
	tmp_redir = tmp_cmds->redir;
	if (p->i != 0)
		dup2(p->fd[p->i - 1][0], STDIN_FILENO);
	if (p->i != p->nb_cmds - 1)
		dup2(p->fd[p->i][1], STDOUT_FILENO);
	if (isprintable(tmp_cmds->cmds[0]))
		is_access(p, tmp_cmds, env);
	if (!init_redir(tmp_redir, p))
		exit_exe(cmds, env, p, m);
	if (!builtin(tmp_cmds, env, p, m))
	{
		if (isprintable(tmp_cmds->cmds[0]))
		{
			if (!p->cmd_path || execve(p->cmd_path, tmp_cmds->cmds, env) == -1)
				print_exec(tmp_cmds->cmds[0], p);
		}
	}
	exit_exe(cmds, env, p, m);
}
