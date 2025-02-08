/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:33:49 by wacista           #+#    #+#             */
/*   Updated: 2024/12/16 20:33:50 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

bool	free_heredoc(t_heredoc *h, bool n)
{
	if (access(h->file_name, W_OK) == -1)
	{
		n = false;
		perror(h->file_name);
	}
	if (h->fd)
		close(h->fd);
	if (h->file_name)
		free(h->file_name);
	if (h->input)
		free(h->input);
	if (h)
		free(h);
	return (n);
}

char	*heredoc_file_name(int i, int j)
{
	char	*k;
	char	*l;
	char	*file_name;

	k = ft_itoa(i);
	l = ft_itoa(j / 2);
	file_name = ft_strjoin_free("", ".data_heredoc_");
	file_name = ft_strjoin_free(file_name, k);
	file_name = ft_strjoin_free(file_name, "_");
	file_name = ft_strjoin_free(file_name, l);
	file_name = ft_strjoin_s2("/tmp/", file_name);
	free(k);
	free(l);
	return (file_name);
}

static bool	init_heredoc(char *env[], t_redir *redir, int i, int j)
{
	t_heredoc	*h;

	h = (t_heredoc *)malloc(sizeof(t_heredoc));
	if (!h)
		return (false);
	h->file_name = heredoc_file_name(i, j);
	h->fd = open(h->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (h->fd == -1)
		return (free_heredoc(h, false));
	redir = redir->next;
	if (!infinite_loop(env, redir, h))
		return (false);
	return (free_heredoc(h, true));
}

static void	define_heredoc(t_final *cmds, char *env[], t_main *m)
{
	int		i;
	int		j;
	t_final	*tmp_cmds;
	t_redir	*tmp_redir;

	i = 0;
	tmp_cmds = cmds;
	while (tmp_cmds)
	{
		j = 0;
		tmp_redir = tmp_cmds->redir;
		while (tmp_redir)
		{
			if (tmp_redir->heredoc == 1)
			{
				if (!init_heredoc(env, tmp_redir, i, j))
					return (heredoc_exit(cmds, env, false, m));
			}
			tmp_redir = tmp_redir->next;
			j++;
		}
		i++;
		tmp_cmds = tmp_cmds->next;
	}
	return (heredoc_exit(cmds, env, true, m));
}

bool	ft_heredoc(t_final *cmds, char *env[], t_main *m)
{
	pid_t	pid;

	if (!is_heredoc(cmds))
		return (true);
	ft_signal(4);
	pid = fork();
	if (pid == -1)
		return (print_perror("fork"), false);
	if (pid == 0)
	{
		ft_signal(3);
		define_heredoc(cmds, env, m);
	}
	waitpid(pid, &g_exit_status, 0);
	ft_signal(1);
	if (WIFEXITED(g_exit_status))
	{
		g_exit_status = (WEXITSTATUS(g_exit_status));
		if (g_exit_status != 0)
			return (false);
	}
	return (true);
}
