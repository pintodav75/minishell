/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:42:34 by wacista           #+#    #+#             */
/*   Updated: 2025/02/08 12:40:34 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*last_env_node(t_env *head)
{
	t_env	*ptr;

	ptr = head;
	if (!ptr)
		return (NULL);
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

static char	*get_child(t_node *child)
{
	char	*dest;

	dest = NULL;
	while (child)
	{
		if (child->txt && *child->txt)
		{
			if (!ft_strcmp(child->txt, ">") || !ft_strcmp(child->txt, "<"))
			{
				child = child->next;
				if (!ft_strcmp(child->txt, ">") || !ft_strcmp(child->txt, "<"))
					child = child->next;
				child = child->next;
			}
			else
			{
				dest = child->txt;
				if (child)
					child = child->next;
			}
		}
		else
			child = child->next;
	}
	return (dest);
}

char	*join_cmd(char const *s1, char const *s2)
{
	int		i;
	char	*dest;

	if (!s1 && !s2)
		return (NULL);
	dest = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	if (s1)
	{
		while (*s1)
			dest[i++] = *s1++;
	}
	if (s2)
	{
		while (*s2)
			dest[i++] = *s2++;
	}
	dest[i] = '\0';
	return (dest);
}

static void	cmd_exist(t_env **head, t_env *ptr, char *txt, char *full)
{
	t_env	*last_node;

	if (check_if_exist(*head, ptr->var_name) == 1)
	{
		free(ptr->txt);
		ptr->txt = ft_strdup(full);
		if (txt)
		{
			free(ptr->var_value);
			ptr->var_value = ft_strdup(txt);
		}
		else
		{
			free(ptr->var_value);
			ptr->var_value = ft_strdup("");
		}
		return ;
	}
	if (txt)
	{
		if ((*head)->next == NULL)
			*head = add_node_env(*head);
		last_node = last_env_node(*head);
		return (fill_last_node(last_node, "_", txt, full));
	}
}

void	update_cmd(t_env **mini_env, t_node *child)
{
	t_env	**head;
	t_env	*ptr;
	char	*full;
	char	*txt;

	head = mini_env;
	ptr = *mini_env;
	txt = get_child(child);
	full = join_cmd("_=", txt);
	while (ptr)
	{
		if (!ft_strcmp(ptr->var_name, "_"))
			return (cmd_exist(head, ptr, txt, full), free(full));
		ptr = ptr->next;
	}
	ptr = add_node_env(*head);
	ptr = last_env_node(ptr);
	ptr->var_name = ft_strdup("_");
	if (txt)
		ptr->var_value = ft_strdup(txt);
	else
		ptr->var_value = ft_strdup("");
	ptr->txt = ft_strdup(full);
	return (free(full));
}
