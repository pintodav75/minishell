/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:30:30 by dpinto            #+#    #+#             */
/*   Updated: 2024/12/12 18:30:30 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	how_many_back_slash(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == '\\')
		i++;
	return (i);
}

void	back_slash(char *s, char *ptr, int *i, int *j)
{
	int	sl;

	sl = how_many_back_slash(s);
	*i += sl;
	sl = sl / 2;
	while (sl)
	{
		ptr[(*j)++] = '\\';
		sl--;
	}
}

char	*ft_strcpy_env(char *str)
{
	int		i;
	int		j;
	char	*ptr;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	ptr = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i] != '\0')
	{
		if_double_env(ptr, &i, &j, str);
		if (!str[i])
			break ;
		if_simple_env(ptr, &i, &j, str);
		if (!str[i])
			break ;
		if (str[i] == '\\')
			back_slash(str + i, ptr, &i, &j);
		else if (str[i] != '\'' && str[i] != '"')
			ptr[j++] = str[i++];
	}
	return (ptr[j] = '\0', ptr);
}

t_env	*new_node_env(void)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->next = NULL;
	node->txt = NULL;
	node->var_name = NULL;
	node->var_value = NULL;
	return (node);
}

t_env	*add_node_env(t_env *head)
{
	t_env	*ptr;

	if (!head)
		return (NULL);
	ptr = head;
	if (head->next == NULL)
	{
		head->next = new_node_env();
		return (head);
	}
	else
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new_node_env();
	}
	return (head);
}
