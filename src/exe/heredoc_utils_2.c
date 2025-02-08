/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:32:31 by wacista           #+#    #+#             */
/*   Updated: 2024/12/16 20:32:32 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

static void	print_eof(char *s)
{
	g_exit_status = 940;
	ft_putstr_fd("minishell: warning: here-document \
not delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("')\n", 2);
}

bool	infinite_loop(char *env[], t_redir *redir, t_heredoc *h)
{
	while (1)
	{
		h->input = readline("> ");
		if (!h->input && g_exit_status != 930)
			return (print_eof(redir->txt), free_heredoc(h, false));
		if (g_exit_status == 930)
			return (free_heredoc(h, false));
		if (!ft_strcmp(h->input, redir->txt))
			break ;
		if (!redir->quotes)
			h->input = heredoc_expand(h, env, false);
		h->reader = write(h->fd, h->input, ft_strlen(h->input));
		if (h->reader == -1)
			return (free_heredoc(h, false));
		h->reader = write(h->fd, "\n", 1);
		free(h->input);
		h->input = NULL;
	}
	return (true);
}
