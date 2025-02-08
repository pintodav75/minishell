/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:37:57 by wacista           #+#    #+#             */
/*   Updated: 2024/12/16 20:37:58 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	print_error_next(t_node *ptr)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(ptr->next->next->txt, 2);
	ft_putstr_fd("'\n", 2);
	g_exit_status = 2;
}

void	print_error_second_check(t_node *ptr)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `\n", 2);
	ft_putstr_fd(ptr->next->txt, 2);
	ft_putstr_fd("'\n", 2);
	g_exit_status = 2;
}

void	print_error_export(char *s)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_exit_status = 1;
}

void	print_error_syntax(char *s)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("'\n", 2);
	g_exit_status = 2;
}

void	print_error_quotes(char *s)
{
	ft_putstr_fd("minishell: error: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(" are not closed\n", 2);
	g_exit_status = 2;
}
