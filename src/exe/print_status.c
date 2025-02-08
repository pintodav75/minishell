/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:34:47 by wacista           #+#    #+#             */
/*   Updated: 2025/01/31 14:42:29 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

void	print_perror(char *s)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ", 2);
	perror("");
}

void	print_perror_cd(char *s, bool n, t_pipex *p, t_cd *cd)
{
	p->exit_status = 1;
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(s, 2);
	if (n)
	{
		ft_putstr_fd(": ", 2);
		perror("");
	}
	else
		ft_putstr_fd("\n", 2);
	if (cd->path)
		free(cd->path);
	if (cd->cwd)
		free(cd->cwd);
	if (cd->pwd)
		free(cd->pwd);
	free(cd);
}

void	print_exit(t_final *cmds, t_pipex *p, char *s, bool n)
{
	ft_putstr_fd("exit\n", 1);
	if (n)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		p->exit_status = 1;
	}
	else
	{
		if (p->nb_cmds == 1)
			remove_heredoc(cmds);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		p->exit_status = 2;
	}
}
