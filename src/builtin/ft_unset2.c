/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:30:08 by wacista           #+#    #+#             */
/*   Updated: 2024/12/16 20:30:09 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	supp_env_first(t_env *ptr, t_env **head, char *str)
{
	if (ft_stcmp_unset(str, ptr -> var_name) == 1)
	{
		free(ptr -> var_name);
		free(ptr -> var_value);
		free(ptr -> txt);
		*head = ptr -> next;
		free(ptr);
		return (1);
	}
	return (0);
}

int	supp_env_last(t_env *ptr, char *str, t_env *before)
{
	if (ft_stcmp_unset(str, ptr -> var_name) == 1)
	{
		free(ptr -> var_name);
		free(ptr -> var_value);
		free(ptr -> txt);
		before -> next = NULL;
		free(ptr);
		return (1);
	}
	return (0);
}

int	supp_env_milieu(t_env *ptr, t_env *before, char *str)
{
	if (ft_stcmp_unset(str, ptr -> var_name) == 1)
	{
		free(ptr -> var_name);
		free(ptr -> var_value);
		free(ptr -> txt);
		before -> next = ptr -> next;
		free (ptr);
		return (1);
	}
	return (0);
}
