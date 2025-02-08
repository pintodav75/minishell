/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_env3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:30:42 by dpinto            #+#    #+#             */
/*   Updated: 2025/02/02 23:11:09 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

char	*extract_name(char *str)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\0' && str[i] != '=')
		i++;
	ptr = malloc((sizeof(char) * i) + 1);
	i = 0;
	while (str[i] && str[i] != '=')
		ptr[j++] = str[i++];
	return (ptr[j] = '\0', ptr);
}

char	*extract_value(char *str)
{
	int		i;
	char	*ptr;
	int		status;

	i = 0;
	status = 1;
	if (!str)
		return (NULL);
	if (!isequ(str, &status))
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	if (!str[++i])
		return (NULL);
	ptr = ft_strdup(str + i);
	return (ptr);
}

static void	del_env(t_env **head, char *var_name, t_main *m)
{
	if (!ft_strcmp(var_name, "PWD"))
	{
		if (!m->pwd)
			m->pwd = getpwd(*head);
	}
	supp_env(head, var_name);
}

void	get_val(char **env_input, char **var_name, char **var_value, char *txt)
{
	*env_input = ft_strcpy_env(txt);
	*var_name = extract_name(*env_input);
	*var_value = extract_value(*env_input);
}

int	insert_input_env(t_env **head, t_node *node, t_main *m)
{
	char	*var_name;
	char	*var_value;
	char	*env_input;
	t_env	*last_node;

	if (env_checks_quit(head, node))
		return (1);
	node = node->next;
	while (node)
	{
		get_val(&env_input, &var_name, &var_value, node->txt);
		if (!pars_name(var_name, env_input, &m->ex) && isequ(env_input, &m->ex))
		{
			if (check_if_exist(*head, var_name) == 1)
				del_env(head, var_name, m);
			add_node_env(*head);
			last_node = last_env_node(*head);
			fill_last_node(last_node, var_name, var_value, env_input);
			if (!m->ex)
				g_exit_status = 0;
		}
		free_in_insert_input_env(env_input, var_name, var_value);
		node = node->next;
	}
	return (0);
}
