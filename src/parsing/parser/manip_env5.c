/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_env5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:30:53 by dpinto            #+#    #+#             */
/*   Updated: 2025/02/08 13:00:36 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_job(t_env *head, t_node *ptr)
{
	int		i;
	char	*save_var;
	char	*b_do;
	char	*a_do;
	char	*str;

	i = 0;
	while (ptr->txt && ptr->txt[i])
	{
		if (ptr->txt[i] == '$' && expand_guillemets(ptr->txt, i) == 1)
		{
			b_do = before_dollar(ptr->txt);
			save_var = catch_var(ptr->txt + (i + 1));
			a_do = ft_strdup(find_end_of_var(ptr->txt + (i + 1)));
			str = join_cmd(b_do, return_matching_value(head, save_var));
			final_txt(a_do, str, ptr, save_var);
			a_do = NULL;
			free(b_do);
			b_do = NULL;
			i = 0;
		}
		else
			i++;
	}
}
