/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:32:10 by wacista           #+#    #+#             */
/*   Updated: 2025/01/16 03:40:25 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

void	free_exe(t_final **cmds, char ***env, t_main **m)
{
	t_final	*tmp_cmds;
	t_redir	*tmp_redir;
	t_redir	*redir_free;
	int		i;

	while (*cmds)
	{
		i = 0;
		tmp_cmds = (*cmds)->next;
		tmp_redir = (*cmds)->redir;
		while (tmp_redir)
		{
			redir_free = tmp_redir;
			tmp_redir = tmp_redir->next;
			ft_free_str(&redir_free->txt);
			free(redir_free);
		}
		while ((*cmds)->cmds[i])
			free((*cmds)->cmds[i++]);
		free((*cmds)->cmds);
		free(*cmds);
		*cmds = tmp_cmds;
	}
	free_final_env(env);
	free(*m);
}

void	exit_exe(t_final *cmds, char *env[], t_pipex *p, t_main *m)
{
	if (p->i != p->nb_cmds - 1)
		close(p->fd[p->i][1]);
	if (p->i != 0)
		close(p->fd[p->i - 1][0]);
	g_exit_status = p->exit_status;
	free_pipex(p);
	if (m->pwd)
		free(m->pwd);
	free_exe(&cmds, &env, &m);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	ft_signal(5);
	exit(g_exit_status);
}
