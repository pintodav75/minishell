/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:30:25 by wacista           #+#    #+#             */
/*   Updated: 2025/01/31 15:38:23 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

void	free_cd(t_cd *cd)
{
	if (cd->pwd)
		free(cd->pwd);
	if (cd->path)
		free(cd->path);
	if (cd->cwd)
		free(cd->cwd);
	free(cd);
}

size_t	env_finder(char *name, char **env)
{
	size_t	i;

	i = 0;
	while (env[i] && ft_strncmp(name, env[i], ft_strlen(name)))
		i++;
	return (i);
}

char	*get_env_input(char *variable, int j, char *env[])
{
	size_t	i;
	char	*dest;

	i = env_finder(variable, env);
	if (i == ft_tablen(env))
		return (NULL);
	dest = ft_strdup(&env[i][j]);
	return (dest);
}

bool	find_env(char **env, char *var, char *val)
{
	while (*env)
	{
		if (!ft_strncmp(*env, var, ft_strlen(var)))
		{
			free(*env);
			*env = ft_strjoin_env(var, val);
			return (true);
		}
		env++;
	}
	return (false);
}

char	**export_env(char *variable, char *val, char *env[], t_main *m)
{
	int		i;
	char	**new_env;

	if (m->pwd)
	{
		free(m->pwd);
		m->pwd = NULL;
	}
	if (find_env(env, variable, val))
		return (env);
	new_env = (char **)malloc(sizeof(char *) * (ft_tablen(env) + 2));
	if (!new_env)
		return (perror("malloc"), env);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = ft_strjoin_env(variable, val);
	i++;
	new_env[i] = NULL;
	free_final_env(&env);
	return (new_env);
}
