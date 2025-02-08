/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_name_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:38:06 by wacista           #+#    #+#             */
/*   Updated: 2025/02/01 21:41:08 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_env	*env, char *var)
{
	while (env)
	{
		if (!ft_strcmp(env->var_name, var))
			return (env->var_value);
		env = env->next;
	}
	return (NULL);
}

char	*get_pwd_format(t_env *env, t_prompt *p, char	*pwd)
{
	char	*home;

	home = get_env(env, "HOME");
	if (!home)
		return (p->len += ft_strlen(pwd), p->pwd = ft_strdup(pwd));
	if (!ft_strncmp(pwd, home, ft_strlen(home)) && \
	((pwd[ft_strlen(home)] == '/') || (pwd[ft_strlen(home)]) == '\0'))
	{
		p->pwd = ft_strjoin("~", pwd + ft_strlen(home));
		if (!p->pwd)
			return (p->len += ft_strlen(pwd), p->pwd = ft_strdup(pwd));
		return (p->len += ft_strlen(p->pwd), p->pwd);
	}
	return (p->len += ft_strlen(pwd), p->pwd = ft_strdup(pwd));
}

void	free_prompt(t_prompt *p)
{
	if (p->user)
		free(p->user);
	if (p->name)
		free(p->name);
	if (p->pwd)
		free(p->pwd);
	free(p);
}

void	init_to_null(t_prompt *p)
{
	p->len = 0;
	p->i = 0;
	p->j = 0;
	p->status = 0;
	p->name = NULL;
	p->user = NULL;
	p->pwd = NULL;
}
