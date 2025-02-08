/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exe.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:39:04 by wacista           #+#    #+#             */
/*   Updated: 2025/02/08 04:31:16 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXE_H
# define MINISHELL_EXE_H

# include "minishell.h"

typedef struct s_pipex
{
	pid_t	*child;
	int		**fd;
	int		nb_cmds;
	int		i;
	int		exit_status;
	char	**path;
	char	*cmd_path;
}	t_pipex;

typedef struct s_heredoc
{
	int		len;
	int		i;
	int		i_save;
	int		j;
	int		i_env;
	int		j_env;
	int		k;
	int		dollar;
	char	*tmp;
	char	*dest;
	char	*file_name;
	char	*input;
	int		reader;
	int		fd;
}	t_heredoc;

typedef struct s_cd
{
	char	*pwd;
	char	*path;
	char	*cwd;
}	t_cd;

typedef struct s_export
{
	int		i;
	int		j;
	int		min_idx;
	int		len;
}	t_export;

//pipex.c
void	pipex(t_final *cmds, char *env[], t_main *m);
void	close_unused_pipes(t_pipex *p);

//pipex_init.c
bool	init_pipes(t_pipex *p);
bool	init_forks(t_final *cmds, char *env[], t_pipex *p, t_main *m);

//pipex_lonely.c
void	lonely_builtin(t_final *cmds, char *env[], t_pipex *p, t_main *m);

//pipex_errors.c
void	free_pipex(t_pipex *p);
bool	pipe_error(t_pipex *p, int i);
bool	fork_error(t_pipex *p);

//heredoc.c - heredoc_expand.c - heredoc_utils.c
bool	is_heredoc(t_final *cmds);
bool	ft_heredoc(t_final *cmds, char *env[], t_main *m);
void	remove_heredoc(t_final *cmds);
char	*heredoc_file_name(int i, int j);
char	*heredoc_expand(t_heredoc *h, char *env[], bool n);
void	heredoc_exit(t_final *cmds, char *env[], bool n, t_main *m);
bool	init_values(t_heredoc *h, bool n);
int		env_var_len(char *env);
bool	infinite_loop(char *env[], t_redir *redir, t_heredoc *h);
bool	free_heredoc(t_heredoc *h, bool n);

//childs.c
void	child_processs(t_final *cmds, char *env[], t_pipex *p, t_main *m);

//cmd_access.c
void	is_access(t_pipex *p, t_final *cmds, char *env[]);
void	update_cmd_exe(t_pipex *p, t_final *cmd, char *env[]);

//redir.c
bool	init_redir(t_redir *redir, t_pipex *p);

//redir_utils.c
bool	redir_infile(t_redir *redir, t_pipex *p);
bool	redir_heredoc(t_redir *redir, t_pipex *p, int j);
bool	redir_outfile(t_redir *redir, t_pipex *p);
bool	redir_append(t_redir *redir, t_pipex *p);

//free_exe.c
void	free_exe(t_final **cmds, char ***env, t_main **m);
void	exit_exe(t_final *cmds, char *env[], t_pipex *p, t_main *m);

//print_status.c
void	print_perror(char *s);
void	print_exit(t_final *cmds, t_pipex *p, char *s, bool n);
void	print_perror_cd(char *s, bool n, t_pipex *p, t_cd *cd);

//print_exec.c
void	print_exec(char *s, t_pipex *p);

//print_exec_utils.c
void	permission_denied(char *err_msg, int *exit_status);
void	command_not_found(char *err_msg, int *exit_status);
void	is_a_directory(char *err_msg, int *exit_status);
void	not_a_directory(char *err_msg, int *exit_status);
void	no_such_file_or_directory(char *err_msg, int *exit_status);

//builtin.c
bool	isbuiltin(t_final *cmds);
bool	builtin(t_final *cmds, char *env[], t_pipex *p, t_main *m);

//builtin_cd.c - builtin_cd_utils.c
void	free_cd(t_cd *cd);
size_t	env_finder(char *name, char **env);
char	**export_env(char *variable, char *val, char *env[], t_main *m);
char	*get_env_input(char *variable, int j, char *env[]);
bool	builtin_cd(t_final *cmds, char *env[], t_pipex *p, t_main *m);

//builtin_echo.c
bool	builtin_echo(t_final *cmds, t_pipex *p);

//builtin_env.c
bool	builtin_env(char *env[], t_pipex *p);

//builtin_exit.c
bool	builtin_exit(t_final *cmds, char *env[], t_pipex *p, t_main *m);

//builtin_export.c
bool	builtin_export(char *env[], t_pipex *p);

//builtin_export=.c
void	builtin_exp_equl(t_final *cmds);

//builtin_pwd.c
bool	builtin_pwd(t_pipex *p, t_main *m, char *env[]);

//utils
int		lenlist(t_final *L);
void	ft_swap(char **a, char **b);
void	ft_free_str(char **str);
char	*ft_strjoin_env(char *s1, char *s2);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_strjoin_s2(char *s1, char *s2);
size_t	ft_tablen(char **t);
int		ft_strcmp_e(char *s1, char *s2);

#endif