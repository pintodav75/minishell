/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:30:32 by wacista           #+#    #+#             */
/*   Updated: 2025/01/31 16:14:29 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

static bool	first_check(t_final *cmds, t_pipex *p, t_cd *cd, t_main *m)
{
	if (!cmds->cmds[1] || (cmds->cmds[1][0] == '~' \
	&& !cmds->cmds[1][1] && !cmds->cmds[2]))
	{
		cd->path = get_env_input("HOME=", 5, m->final_env);
		if (!cd->path)
			return (print_perror_cd("HOME not set", false, p, cd), false);
		if (chdir(cd->path))
			return (print_perror_cd(cd->path, true, p, cd), false);
		if (m->pwd)
			cd->pwd = ft_strdup(m->pwd);
		else
			cd->pwd = get_env_input("PWD=", 4, m->final_env);
		cd->cwd = getcwd(NULL, 0);
		m->final_env = export_env("OLDPWD=", cd->pwd, m->final_env, m);
		m->final_env = export_env("PWD=", cd->cwd, m->final_env, m);
		p->exit_status = 0;
		return (free_cd(cd), false);
	}
	if (ft_tablen(cmds->cmds) > 2)
		return (print_perror_cd("too many arguments", false, p, cd), false);
	return (true);
}

static bool	isdotdot(char *s)
{
	int	c;

	if (!s)
		return (false);
	while (*s)
	{
		c = 0;
		if (*s != '/' && *s != '.')
			return (false);
		if (*s == '.')
		{
			while (*s && *s == '.')
			{
				c++;
				s++;
				if (c > 2)
					return (false);
			}
		}
		if (*s)
			s++;
	}
	return (true);
}

static bool	cd_relative(t_final *cmds, t_pipex *p, t_cd *cd, t_main *m)
{
	cd->path = ft_strjoin(cd->pwd, "/");
	cd->path = ft_strjoin_free(cd->path, cmds->cmds[1]);
	if (chdir(cd->path))
	{
		if (!isdotdot(cmds->cmds[1]))
			return (print_perror_cd(cmds->cmds[1], true, p, cd), false);
		chdir(cmds->cmds[1]);
		cd->cwd = getcwd(NULL, 0);
		if (cd->cwd)
			m->final_env = export_env("PWD=", cd->cwd, m->final_env, m);
		else
		{
			perror("cd: error retrieving current directory: \
getcwd: cannot access parent directories");
			m->final_env = export_env("PWD=", cd->path, m->final_env, m);
		}
	}
	else
	{
		cd->cwd = getcwd(NULL, 0);
		m->final_env = export_env("PWD=", cd->cwd, m->final_env, m);
	}
	return (true);
}

static bool	cd_builtin(t_final *cmds, t_pipex *p, t_cd *cd, t_main *m)
{
	if (cmds->cmds[1][0] != '/')
	{
		if (!cd_relative(cmds, p, cd, m))
			return (false);
	}
	else if (chdir(cmds->cmds[1]))
		return (print_perror_cd(cmds->cmds[1], true, p, cd), false);
	else
	{
		cd->cwd = getcwd(NULL, 0);
		m->final_env = export_env("PWD=", cd->cwd, m->final_env, m);
	}
	m->final_env = export_env("OLDPWD=", cd->pwd, m->final_env, m);
	return (true);
}

bool	builtin_cd(t_final *cmds, char *env[], t_pipex *p, t_main *m)
{
	t_cd	*cd;

	cd = (t_cd *)malloc(sizeof(t_cd));
	if (!cd)
		return (true);
	cd->path = NULL;
	cd->cwd = NULL;
	cd->pwd = NULL;
	if (!first_check(cmds, p, cd, m))
		return (true);
	if (m->pwd)
		cd->pwd = ft_strdup(m->pwd);
	else
		cd->pwd = get_env_input("PWD=", 4, env);
	if (!cd_builtin(cmds, p, cd, m))
		return (true);
	return (p->exit_status = 0, free_cd(cd), true);
}
