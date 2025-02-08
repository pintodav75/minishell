/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:33:58 by wacista           #+#    #+#             */
/*   Updated: 2024/12/16 20:33:59 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

void	free_tab(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_pipex(t_pipex *p)
{
	int	i;

	i = 0;
	free_tab(p->path);
	if (p->cmd_path)
		free(p->cmd_path);
	if (p->fd)
	{
		while (i < p->nb_cmds - 1)
		{
			if (p->fd[i] != NULL)
				free(p->fd[i]);
			else
				break ;
			i++;
		}
		free(p->fd);
		p->fd = NULL;
	}
	if (p->child != NULL)
	{
		free(p->child);
		p->child = NULL;
	}
	free(p);
}

bool	pipe_error(t_pipex *p, int i)
{
	int	tmp;

	tmp = i + 1;
	while (i >= 0)
	{
		close(p->fd[i][0]);
		close(p->fd[i][1]);
		i--;
	}
	i = 0;
	while (i <= tmp)
	{
		free(p->fd[i]);
		i++;
	}
	free(p->fd);
	p->fd = NULL;
	print_perror("start_pipeline: pgrp pipe");
	free_pipex(p);
	g_exit_status = 24;
	return (false);
}

bool	fork_error(t_pipex *p)
{
	int	i;

	i = 0;
	ft_signal(1);
	while (i < p->nb_cmds - 1)
	{
		close(p->fd[i][0]);
		close(p->fd[i][1]);
		i++;
	}
	print_perror("fork: retry");
	free_pipex(p);
	g_exit_status = 11;
	return (false);
}
