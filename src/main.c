/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:24:20 by dpinto            #+#    #+#             */
/*   Updated: 2025/02/08 10:12:22 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exe.h"

int		g_exit_status;

void	is_args(int ac, char **av)
{
	if (ac > 1)
	{
		ft_printf("%s: no argument accepted, received %d\n", &av[0][2], ac - 1);
		exit(1);
	}
}

void	init_main_values(t_main *m, char *env[], char **argv)
{
	m->final = NULL;
	m->src = NULL;
	m->info = NULL;
	m->root = NULL;
	m->ast = NULL;
	m->final_env = NULL;
	m->mini_env = copy_env(env, argv);
	m->pwd = NULL;
}

void	ft_checker_bis(t_main *m)
{
	supp_quotes(m->root);
	m->ast = create_ast_command_redir(m->root);
	m->final = create_final_ast(m->ast);
	ft_free_before_final_ast(&m->ast);
	if (!check_if_one_cmd(m->root->first_child))
		update_cmd(&m->mini_env, m->root->first_child);
	m->final_env = transform_env_in_double_tab(m->mini_env);
	free_env(&m->mini_env);
	ft_free(NULL, &m->root, &m->src, &m->info);
	executor(m->final, m->final_env, m);
	m->mini_env = copy_env(m->final_env, NULL);
	free_final_env(&m->final_env);
	ft_free_final_ast(&m->final);
}

void	ft_checker(t_main *m)
{
	m->root = parse_simple_command(m->input, &m->src, &m->info);
	expand_env(m->mini_env, m->root);
	if (error_pars(m->root) == 1 && is_env_var(m->mini_env, m->root, m) == 1
		&& !is_unset(&m->mini_env, m->root, m))
		ft_checker_bis(m);
	else
		ft_free(NULL, &m->root, &m->src, &m->info);
}

int	main(int argc, char *argv[], char *env[])
{
	t_main	*m;

	is_args(argc, argv);
	ft_signal(1);
	m = (t_main *)malloc(sizeof(t_main));
	if (!m)
		return (1);
	init_main_values(m, env, argv);
	while (1)
	{
		m->prompt_name = get_prompt_name(m->mini_env, m);
		m->input = readline(m->prompt_name);
		free(m->prompt_name);
		if (!m->input)
			ft_exit_d(&m->mini_env, &m);
		if (*m->input != ' ' && is_printable(m->input))
			add_history(m->input);
		if (single_enter(m->input) == 0 && does_quotes_closed(m->input) == 1
			&& check_space_append_heredoc(m->input) == 1)
			ft_checker(m);
		else
			(free(m->input));
	}
}
