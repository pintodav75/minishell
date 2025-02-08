/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 04:25:33 by wacista           #+#    #+#             */
/*   Updated: 2025/01/27 06:26:37 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

static bool	slash_check(char *s)
{
	if (!s)
		return (false);
	while (*s)
		if (*s++ == '/')
			return (true);
	return (false);
}

void	print_exec(char *s, t_pipex *p)
{
	char		*err_msg;
	struct stat	sb;

	err_msg = ft_strjoin("minishell: ", s);
	if (stat(s, &sb) == 0)
	{
		if (S_ISREG(sb.st_mode))
		{
			if (slash_check(s))
				return (permission_denied(err_msg, &p->exit_status));
			return (command_not_found(err_msg, &p->exit_status));
		}
		if (S_ISDIR(sb.st_mode))
		{
			if (slash_check(s))
				return (is_a_directory(err_msg, &p->exit_status));
			return (command_not_found(err_msg, &p->exit_status));
		}
	}
	if (!ft_strcmp(strerror(errno), "Not a directory"))
		return (not_a_directory(err_msg, &p->exit_status));
	if (slash_check(s))
		return (no_such_file_or_directory(err_msg, &p->exit_status));
	command_not_found(err_msg, &p->exit_status);
}
