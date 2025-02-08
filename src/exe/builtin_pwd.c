/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:31:19 by wacista           #+#    #+#             */
/*   Updated: 2025/01/19 06:33:50 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

char	*get_pwd(char *env[])
{
	if (!env)
		return (NULL);
	while (*env)
	{
		if (!ft_strncmp(*env, "PWD", 3) && (*env)[3] == '=')
			return (&(*env)[4]);
		env++;
	}
	return (NULL);
}

bool	builtin_pwd(t_pipex *p, t_main *m, char *env[])
{
	p->exit_status = 0;
	if (m->pwd)
		return (printf("%s\n", m->pwd), true);
	else
		return (printf("%s\n", get_pwd(env)), true);
	return (true);
}
