/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:30:18 by dpinto            #+#    #+#             */
/*   Updated: 2024/12/12 18:30:19 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

int	in_file_second_check_alone(t_node *ptr)
{
	if ((ptr->next) == NULL)
		return (print_error_syntax("newline"), 0);
	return (1);
}

int	in_file_second_check_something_after(t_node *ptr)
{
	if (ft_stcmp(ptr->txt, "<") == 1)
		if (ptr->next)
			if (ft_stcmp(ptr->next->txt, ">") == 1)
				return (print_error_second_check(ptr), 0);
	if (ft_stcmp(ptr->txt, ">") == 1)
		if (ptr->next)
			if (ft_stcmp(ptr->next->txt, "<") == 1)
				return (print_error_second_check(ptr), 0);
	return (1);
}

int	ft_in_file_first_check_wrong_arrow(t_node *ptr)
{
	if (ft_stcmp(ptr->txt, "<") == 1 && ft_stcmp(ptr->next->txt, ">") == 1)
		return (print_error_syntax(">"), 0);
	if (ft_stcmp(ptr->txt, ">") == 1 && ft_stcmp(ptr->next->txt, "<") == 1)
		return (print_error_syntax("<"), 0);
	return (1);
}
