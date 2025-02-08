/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supp_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:32:09 by dpinto            #+#    #+#             */
/*   Updated: 2024/12/12 18:32:10 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	supp_quotes(t_node *root)
{
	t_node	*ptr;

	if (!root)
		return ;
	ptr = root->first_child;
	while (ptr)
	{
		if (does_str_has_quotes(ptr->txt) == 1)
			str_without_quotes(ptr);
		ptr = ptr->next;
	}
}

void	str_without_quotes(t_node *ptr)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(ptr->txt) + 1));
	while (ptr->txt[i] != '\0')
	{
		if_double(new_str, &i, &j, ptr);
		if (!ptr)
			break ;
		if_simple(new_str, &i, &j, ptr);
		if (!ptr)
			break ;
		if (ptr->txt[i] != '\'' && ptr->txt[i] != '"')
			new_str[j++] = ptr->txt[i];
		if (ptr->txt[i])
			i++;
	}
	new_str[j] = '\0';
	free(ptr->txt);
	ptr->txt = new_str;
}

void	if_double(char *new_str, int *i, int *j, t_node *ptr)
{
	if (ptr->txt[*(i)] == '"')
	{
		*(i) = *(i) + 1;
		if (!ptr)
			return ;
		while (ptr->txt[*(i)])
		{
			if (ptr->txt[*(i)] == '"')
			{
				*(i) = *(i) + 1;
				break ;
			}
			new_str[*(j)] = ptr->txt[*(i)];
			*(j) = *(j) + 1;
			*(i) = *(i) + 1;
		}
	}
}

void	if_simple(char *new_str, int *i, int *j, t_node *ptr)
{
	if (ptr->txt[*(i)] == '\'')
	{
		*(i) = *(i) + 1;
		if (!ptr)
			return ;
		while (ptr->txt[*(i)])
		{
			if (ptr->txt[*(i)] == '\'')
			{
				*(i) = *(i) + 1;
				break ;
			}
			new_str[*(j)] = ptr->txt[*(i)];
			*(j) = *(j) + 1;
			*(i) = *(i) + 1;
		}
	}
}
