/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:34:55 by wacista           #+#    #+#             */
/*   Updated: 2024/12/16 20:34:56 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

bool	redir_infile(t_redir *redir, t_pipex *p)
{
	if (!redir)
		return (false);
	redir->fd_in = open(redir->txt, O_RDONLY);
	if (redir->fd_in == -1)
	{
		p->exit_status = 1;
		return (print_perror(redir->txt), false);
	}
	dup2(redir->fd_in, STDIN_FILENO);
	close(redir->fd_in);
	return (true);
}

bool	redir_heredoc(t_redir *redir, t_pipex *p, int j)
{
	char	*file_name;

	if (!redir)
		return (false);
	file_name = heredoc_file_name(p->i, j);
	redir->fd_in = open(file_name, O_RDONLY);
	if (redir->fd_in == -1)
	{
		p->exit_status = 1;
		return (print_perror(file_name), free(file_name), false);
	}
	dup2(redir->fd_in, STDIN_FILENO);
	close(redir->fd_in);
	free(file_name);
	p->exit_status = 0;
	return (true);
}

bool	redir_outfile(t_redir *redir, t_pipex *p)
{
	if (!redir)
		return (false);
	redir->fd_out = open(redir->txt, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (redir->fd_out == -1)
	{
		p->exit_status = 1;
		return (print_perror(redir->txt), false);
	}
	dup2(redir->fd_out, STDOUT_FILENO);
	close(redir->fd_out);
	return (true);
}

bool	redir_append(t_redir *redir, t_pipex *p)
{
	redir->fd_out = open(redir->txt, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (redir->fd_out == -1)
	{
		p->exit_status = 1;
		return (print_perror(redir->txt), false);
	}
	if (access(redir->txt, W_OK) == -1)
	{
		p->exit_status = 1;
		close(redir->fd_out);
		return (print_perror(redir->txt), false);
	}
	dup2(redir->fd_out, STDOUT_FILENO);
	close(redir->fd_out);
	return (true);
}
