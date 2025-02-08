/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:34:37 by wacista           #+#    #+#             */
/*   Updated: 2024/12/16 20:34:38 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

void	close_unused_pipes(t_pipex *p)
{
	int	j;
	int	fd_to_keep[1024];

	j = 0;
	ft_memset(fd_to_keep, 0, sizeof(fd_to_keep));
	while (j < p->nb_cmds - 1)
	{
		if (j != p->i)
			close(p->fd[j][1]);
		else
			fd_to_keep[p->fd[j][1]] = 1;
		if (j + 1 != p->i)
			close(p->fd[j][0]);
		else
			fd_to_keep[p->fd[j][0]] = 1;
		j++;
	}
	j = 3;
	while (j < 1024)
	{
		if (!fd_to_keep[j])
			close(j);
		j++;
	}
}

static void	close_pipes_main(t_pipex *p)
{
	int	i;

	i = 0;
	while (i < p->nb_cmds - 1)
	{
		close(p->fd[i][0]);
		close(p->fd[i][1]);
		i++;
	}
}

static void	wait_childs(t_pipex *p)
{
	int	i;

	i = 0;
	while (i < p->nb_cmds)
	{
		waitpid(p->child[i], &g_exit_status, 0);
		if (WIFEXITED(g_exit_status))
			g_exit_status = (WEXITSTATUS(g_exit_status));
		else if (WIFSIGNALED(g_exit_status))
			g_exit_status = 128 + WTERMSIG(g_exit_status);
		i++;
	}
	ft_signal(1);
}

void	init_pipex(t_pipex *p, t_final *cmds)
{
	if (!p)
		return ;
	p->i = 0;
	p->fd = NULL;
	p->path = NULL;
	p->child = NULL;
	p->cmd_path = NULL;
	p->nb_cmds = lenlist(cmds);
	p->exit_status = cmds->exit_tmp;
}

void	pipex(t_final *cmds, char *env[], t_main *m)
{
	t_pipex	*p;

	p = (t_pipex *)malloc(sizeof(t_pipex));
	if (!p)
		return (print_perror("malloc"));
	init_pipex(p, cmds);
	if (p->nb_cmds == 1 && isbuiltin(cmds))
		return (lonely_builtin(cmds, env, p, m));
	if (!init_pipes(p))
		return ;
	if (!init_forks(cmds, env, p, m))
		return ;
	close_pipes_main(p);
	wait_childs(p);
	free_pipex(p);
}
