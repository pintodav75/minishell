/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_exec_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 04:25:26 by wacista           #+#    #+#             */
/*   Updated: 2025/01/30 05:54:16 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

void	permission_denied(char *err_msg, int *exit_status)
{
	err_msg = ft_strjoin_free(err_msg, ": Permission denied\n");
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	*exit_status = 126;
	free(err_msg);
}

void	command_not_found(char *err_msg, int *exit_status)
{
	char	*msg;

	msg = ft_strjoin(&err_msg[11], ": command not found\n");
	free(err_msg);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	free(msg);
	*exit_status = 127;
}

void	is_a_directory(char *err_msg, int *exit_status)
{
	err_msg = ft_strjoin_free(err_msg, ": Is a directory\n");
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	*exit_status = 126;
	free(err_msg);
}

void	not_a_directory(char *err_msg, int *exit_status)
{
	err_msg = ft_strjoin_free(err_msg, ": Not a directory\n");
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	*exit_status = 126;
	free(err_msg);
}

void	no_such_file_or_directory(char *err_msg, int *exit_status)
{
	err_msg = ft_strjoin_free(err_msg, ": No such file or directory\n");
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	*exit_status = 127;
	free(err_msg);
}
