/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:32:57 by dpinto            #+#    #+#             */
/*   Updated: 2024/12/12 18:32:58 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	ft_sigint(int sigint)
{
	g_exit_status = sigint;
	g_exit_status = 130;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_sigint_heredoc(int sigint)
{
	g_exit_status += sigint;
	signal(SIGINT, SIG_IGN);
	ft_putstr_fd("\n", 1);
	close(STDIN_FILENO);
	g_exit_status = 930;
}

void	ft_sig_child(int sigint)
{
	g_exit_status += sigint;
	g_exit_status = 130;
	ft_putstr_fd("\n", 1);
	close(0);
}

void	ft_sig_quit(int sigint)
{
	g_exit_status += sigint;
	ft_putstr_fd("Quit (core dumped)\n", 1);
	close(STDIN_FILENO);
	g_exit_status = 131;
}

void	ft_signal(int i)
{
	if (i == 1)
	{
		signal(SIGINT, ft_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	if (i == 2)
	{
		signal(SIGINT, ft_sig_child);
		signal(SIGQUIT, ft_sig_quit);
	}
	if (i == 3)
	{
		signal(SIGINT, ft_sigint_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
	if (i == 4)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	if (i == 5)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}
