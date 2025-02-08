/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:34:11 by wacista           #+#    #+#             */
/*   Updated: 2024/12/16 20:34:11 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

bool	init_forks(t_final *cmds, char *env[], t_pipex *p, t_main *m)
{
	p->i = 0;
	p->child = (pid_t *)malloc(sizeof(pid_t) * p->nb_cmds);
	if (!p->child)
		return (print_perror("malloc"), free_pipex(p), false);
	ft_signal(4);
	while (p->i < p->nb_cmds)
	{
		p->child[p->i] = fork();
		if (p->child[p->i] == -1)
			return (fork_error(p));
		if (p->child[p->i] == 0)
		{
			ft_signal(2);
			child_processs(cmds, env, p, m);
		}
		p->i++;
	}
	return (true);
}

void	set_fd_null(t_pipex *p)
{
	int	i;

	i = 0;
	while (i < p->nb_cmds - 1)
		p->fd[i++] = NULL;
}

bool	init_pipes(t_pipex *p)
{
	int	i;

	i = 0;
	p->fd = (int **)malloc(sizeof(int *) * (p->nb_cmds - 1));
	if (!p->fd)
		return (print_perror("malloc"), free(p), false);
	set_fd_null(p);
	while (i < p->nb_cmds - 1)
	{
		p->fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!p->fd[i])
			return (print_perror("malloc"), free_pipex(p), false);
		if (pipe(p->fd[i]) == -1)
			return (pipe_error(p, i - 1));
		i++;
	}
	return (true);
}
