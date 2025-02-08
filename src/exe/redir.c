/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:35:08 by wacista           #+#    #+#             */
/*   Updated: 2024/12/16 20:35:09 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

static bool	redir_in_here(t_redir *redir, t_pipex *p, int j)
{
	if (redir->in_file == 1)
	{
		redir = redir->next;
		if (!redir_infile(redir, p))
			return (false);
	}
	if (redir->heredoc == 1)
	{
		redir = redir->next;
		if (!redir_heredoc(redir, p, j))
			return (false);
	}
	return (true);
}

static bool	redir_out_app(t_redir *redir, t_pipex *p)
{
	if (redir->out_file == 1)
	{
		redir = redir->next;
		if (!redir_outfile(redir, p))
			return (false);
	}
	if (redir->append == 1)
	{
		redir = redir->next;
		if (!redir_append(redir, p))
			return (false);
	}
	return (true);
}

bool	init_redir(t_redir *redir, t_pipex *p)
{
	int		j;
	t_redir	*tmp_redir;

	j = 0;
	tmp_redir = redir;
	if (!tmp_redir)
		return (true);
	while (tmp_redir)
	{
		if (tmp_redir->in_file == 1 || tmp_redir->heredoc == 1)
		{
			if (!redir_in_here(tmp_redir, p, j))
				return (false);
		}
		else if (tmp_redir->out_file == 1 || tmp_redir->append == 1)
		{
			if (!redir_out_app(tmp_redir, p))
				return (false);
		}
		j++;
		tmp_redir = tmp_redir->next;
	}
	return (true);
}
