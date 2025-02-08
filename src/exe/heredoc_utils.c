/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:33:04 by wacista           #+#    #+#             */
/*   Updated: 2024/12/16 20:33:05 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

int	env_var_len(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

bool	init_values(t_heredoc *h, bool n)
{
	h->i = 0;
	if (!n)
		h->len = 0;
	h->tmp = NULL;
	h->k = 0;
	h->dollar = false;
	if (n)
	{
		h->dest = (char *)malloc(sizeof(char) * h->len + 1);
		if (!h->dest)
			return (print_perror("malloc"), false);
	}
	return (true);
}

void	heredoc_exit(t_final *cmds, char *env[], bool n, t_main *m)
{
	free_exe(&cmds, &env, &m);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	ft_signal(5);
	if (n)
	{
		g_exit_status = 0;
		exit(g_exit_status);
	}
	else if (g_exit_status == 930)
		g_exit_status = 130;
	else if (g_exit_status == 940)
		g_exit_status = 0;
	else
		g_exit_status = 1;
	exit(g_exit_status);
}

void	remove_heredoc(t_final *cmds)
{
	int		i;
	int		j;
	char	*file_name;
	t_redir	*redir;

	i = 0;
	while (cmds)
	{
		j = 0;
		redir = cmds->redir;
		while (redir)
		{
			if (redir->heredoc == 1)
			{
				file_name = heredoc_file_name(i, j);
				unlink(file_name);
				free(file_name);
			}
			j++;
			redir = redir->next;
		}
		i++;
		cmds = cmds->next;
	}
}

bool	is_heredoc(t_final *cmds)
{
	t_final	*tmp_cmds;
	t_redir	*tmp_redir;

	tmp_cmds = cmds;
	while (tmp_cmds)
	{
		tmp_redir = tmp_cmds->redir;
		while (tmp_redir)
		{
			if (tmp_redir->heredoc == 1)
				return (true);
			tmp_redir = tmp_redir->next;
		}
		tmp_cmds = tmp_cmds->next;
	}
	return (false);
}
