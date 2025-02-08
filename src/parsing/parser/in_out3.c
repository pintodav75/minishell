/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:30:23 by dpinto            #+#    #+#             */
/*   Updated: 2024/12/12 18:30:25 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

int	in_file_next(t_node *ptr)
{
	if (ptr->next->next)
	{
		if (ft_stcmp(ptr->next->next->txt, "<") == 1
			|| ft_stcmp(ptr->next->next->txt, ">") == 1)
			return (print_error_next(ptr), 0);
	}
	return (1);
}
