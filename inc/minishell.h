/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:38:55 by wacista           #+#    #+#             */
/*   Updated: 2025/02/08 13:01:26 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
//walid
# include <fcntl.h>
# include <stddef.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>

typedef struct s_prompt
{
	char		*name;
	char		*user;
	char		*pwd;
	int			len;
	int			save_len;
	size_t		i;
	size_t		j;
	int			i_gcp;
	int			j_gcp;
	int			status;
}	t_prompt;

// structure de l'input de l'user
typedef struct source_s
{
	char	*buffer;
	long	bufsize;
	long	curpos;
	int		end_input;
	int		exit;
}	t_source;

// structure of a token
typedef struct token_s
{
	t_source	*src;
	int			text_len;
	char		*text;
}	t_token;

// structure d'information global pour créer un token
typedef struct info_tok_s
{
	char	*tok_buf;
	int		tok_bufsize;
	int		tok_bufindex;
}	t_info_tok;

/* structure of a node in first AST*/
typedef struct node_s
{
	char			*txt;
	int				children;
	int				after_here_doc;
	int				quotes;
	int				heredoc;
	struct node_s	*first_child;
	struct node_s	*next;
	struct node_s	*prev_sibling;
}	t_node;
/*node of a redirection*/
typedef struct redir_node
{
	char				*txt;
	int					heredoc;
	int					quotes;
	int					in_file;
	int					out_file;
	int					append;
	int					file;
	int					fd_in;
	int					fd_out;
	struct redir_node	*next;
}	t_redir;

/*node of a command*/
typedef struct com_node
{
	char			*txt;
	t_redir			*redir;
	struct com_node	*next;
}	t_com;

/*node de la structure final qui sera donne a l'executeur*/
typedef struct final
{
	char			**cmds;
	t_redir			*redir;
	int				exit_tmp;
	struct final	*next;
}	t_final;

/*node of a command*/
typedef struct ast
{
	t_com	*command;
	t_redir	*redir;
	t_node	*save_ptr;
}	t_ast;

/* structure of env linked list*/
typedef struct env_s
{
	char			*txt;
	char			*var_name;
	char			*var_value;
	struct env_s	*next;
}	t_env;

typedef struct s_main
{
	t_env		*mini_env;
	t_source	*src;
	t_info_tok	*info;
	t_node		*root;
	t_com		**ast;
	t_final		*final;
	t_env		*last_node;
	char		*input;
	char		**final_env;
	char		*exit_status;
	char		*prompt_name;
	char		*pwd;
	int			ex;
}	t_main;

/* manipulate the input*/
char		next_char(t_source *src);
void		unget_char(t_source *src);// recule de 1 car dans linput
char		peek_char(t_source *src);// return le next char sans update pos 
void		skip_white_spaces(t_source *src);
t_source	**init_src(t_source **src, char *input);// init input struct
bool		is_printable(char *s);

/* manipulate the token*/
t_info_tok	**init_global_info_token(t_info_tok **info);
t_token		*tokenize(t_source *src, t_info_tok *info);
int			tokenize_while(t_source *src, t_info_tok *info, char c);
void		init_buf_size(t_info_tok *info, long bufsize);
int			tokenize_space(char c, t_source *src, t_info_tok *info);
int			tokenize_pipe(char c, t_source *src, t_info_tok *info);
void		tokenize_end(char c, t_source *src, t_info_tok *info);
int			tokenize_in_out(char c, t_source *src, t_info_tok *info);
void		free_token(t_token *tok);
void		add_to_buf(char c, t_info_tok *info);
t_token		*create_token(char *str, t_source *src, t_info_tok *info);
int			does_str_has_quotes(char *str);
int			does_str_has_single_quotes(char *str);
int			does_str_has_double_quotes(char *str);
int			tokenize_single_quote(char c, t_source *src, t_info_tok *info);
int			tokenize_double_quote(char c, t_source *src, t_info_tok *info);
int			is_just_tok_quotes(char *str);
int			next_src_is_legit(t_source *src);
void		avance_curpos(t_source *src, char c);
int			tokenize_quotes(t_source *src, t_info_tok *info, char c);

/* parsing*/
t_node		*parse_simple_command(char *input, t_source **src, \
		t_info_tok **info);
t_node		*new_node(t_token *tok);
t_node		*if_tok_exist(t_token *tok, t_node *root, t_info_tok **info);
t_node		*add_node_to_ast(t_node *root, t_node *node);
int			single_enter(char *input);
int			check_space_append_heredoc(char *str);
int			only_space(char *str);

/*env*/
t_env		*copy_env(char *original[], char **argv);
t_env		*env_not_exist(char **argv);
void		create_var_name_and_value(t_env *ptr);
void		copy_original_to_mini(char *original[], int i, t_env *ptr);
int			env_checks_quit(t_env **head, t_node *node);
char		*return_after(char *str, int j, int save);
void		fill_last_node(t_env *last_node, \
		char *name, char *value, char *env);
void		free_in_insert_input_env(char *env, \
		char *var_name, char *var_value);
t_env		*add_node_env(t_env *head);
t_env		*new_node_env(void);
int			is_env_var(t_env *mini_env, t_node *root, t_main *m);
int			insert_input_env(t_env **head, t_node *root, t_main *m);
bool		isequ(char *s, int *status);
void		expand_env(t_env *head, t_node *root);
char		*ft_strcpy_env(char *str);
void		if_double_env(char *new_str, int *i, int *j, char *str);
void		if_simple_env(char *new_str, int *i, int *j, char *str);
void		create_var_name(t_env *node);
void		create_var_value(t_env *node);
int			ft_stcmp(char *str1, char *str2);
void		final_txt(char *a_dol, char *new_str, t_node *ptr, char *save_var);
char		*extract_name(char *str);
char		*extract_value(char *str);
t_env		*last_env_node(t_env *head);
t_node		*do_i_have_to_expand(t_node *root);
char		*return_matching_value(t_env *head, char *str);
void		cut_dollar_sign(char *str);
int			is_here_doc(t_node *node);
void		expand_job(t_env *head, t_node *ptr);
int			expand_guillemets(char *str, int index_dol);
void		expand_guillemets_first(char *s, int *i_dol, \
		int *nb_simp, int *i_simp);
char		*find_end_of_var(char *str);
char		*after_dollar(char *str);
char		*before_dollar(char *str);
char		*catch_var(char *str);
int			pars_name(char *str, char *env_input, int *status);
int			check_if_exist(t_env *head, char *str);
void		supp_env(t_env **head, char *str);
int			supp_env_first(t_env *ptr, t_env **head, char *str);
int			supp_env_last(t_env *ptr, char *str, t_env *before);
int			supp_env_milieu(t_env *ptr, t_env *before, char *str);
int			is_unset(t_env **head, t_node *root, t_main *m);
char		*getpwd(t_env *head);
int			ft_stcmp_unset(char *str1, char *str2);
t_node		*attribue_here_doc(t_node *root);
void		attribute_atfer_here_doc(t_node *node);
int			is_it_heredoc(t_node *node);
char		**transform_env_in_double_tab(t_env *node);
void		free_final_env(char ***tab_env);
int			count_nbr_env(t_env *node);
int			expand_legtimate_values(char c);
void		update_cmd(t_env **mini_env, t_node *child);
int			is_empty(t_node *root, int empty);
int			check_if_one_cmd(t_node *node);
char		*join_cmd(char const *s1, char const *s2);

/*signals*/
void		ft_sigint(int sigint);
void		ft_signal(int i);

/*builtin exit*/
void		ft_exit_d(t_env **env, t_main **m);

/*free*/
void		free_info_buf(t_info_tok *info);
void		free_src(t_source **src);
void		free_tok(t_token **tok);
void		free_info(t_info_tok **info);
void		free_ast(t_node **root);
void		free_env(t_env **mini_env);
void		ft_free(t_env **mini_env, t_node **root, \
		t_source **src, t_info_tok **info);
void		ft_free_before_final_ast(t_com ***ast);
void		ft_free_final_ast(t_final **ast);

/*in and out redirection*/
int			ft_in_file_first_check(t_node *ptr);
int			ft_in_file_first_check_wrong_arrow(t_node *ptr);
int			in_file_second_check(t_node *ptr);
int			in_file_second_check_alone(t_node *ptr);
int			in_file_second_check_something_after(t_node *ptr);
int			ft_in_file(t_node *head);
int			does_quotes_closed(char *str);
int			in_file_next(t_node *ptr);
void		print_error_next(t_node *ptr);
void		print_error_second_check(t_node *ptr);

/* supp quotes*/
void		supp_quotes(t_node *root);
void		str_without_quotes(t_node *ptr);
void		if_double(char *new_str, int *i, int *j, t_node *ptr);
void		if_simple(char *new_str, int *i, int *j, t_node *ptr);
/*pipe*/
int			ft_pipe_first_check(t_node *ptr);
int			ft_pipe_check(t_node *head);
int			how_much_pipe(t_node *root);
/*error*/
int			error_pars(t_node *head);
int			end_comm(char *str, int i, int single, int double_q);

/*guillemets*/
int			single_quote_closed(t_node *head);
int			quote_closed(t_node *head);
int			double_quote_closed(t_node *head);
int			is_there_quotes(t_node *root);
int			is_there_single_quotes(t_node *root);
int			is_there_double_quotes(t_node *root);
int			is_there_both(t_node *root);

/*ast et redir command*/
t_com		**create_ast_command_redir(t_node *root);
t_node		*return_ptr(t_redir **redir, t_node *ptr);
t_ast		*return_save_ast(t_node *ptr, t_com *com, t_redir *redir);
t_ast		*isolate_command_redir(t_node *root);
t_com		**malloc_ast(t_com **ast, int nbr_pipe);
t_com		**create_while(t_com **ast, t_ast *save_ast, \
		t_node *ptr, int nbr_pipe);
void		init_redir_if(t_redir *ptr, t_node *node);
void		init_redir_else(t_redir *ptr);
void		ft_heredoc_redir(t_redir *ptr);
void		add_new_redir_to_list(t_redir *redir, t_redir *ptr, t_node *node);
t_redir		*create_redir_node_if(t_redir *redir, t_node *node, t_redir *ptr);
t_redir		*create_redir_node_else(t_redir *redir, t_node *node, t_redir *ptr);
void		ft_file(t_redir *ptr);
void		ft_append(t_redir *ptr);
void		ft_outfile(t_redir *ptr);
/*manipulate node command*/
t_com		*create_com_node(t_com *com, t_node *node);
/*manipulate node redir*/
t_redir		*create_redir_node(t_redir *redir, t_node *node);

/*create final data structure */
t_final		*create_final_ast(t_com **ast);
t_final		*create_list_final_ast(t_final *final, t_com *ast);
char		**break_linked_list_in_double_tab(t_com *com);
int			ft_com_len(t_com *com);
int			is_double_quotes_str_closed(char *str);
int			is_single_quotes_str_closed(char *str);

/* print status */
void		print_error_export(char *s);
void		print_error_syntax(char *s);
void		print_error_quotes(char *s);

/*EXEC*/
void		remove_heredoc(t_final *cmds);
void		executor(t_final *cmds, char *env[], t_main *m);
long long	ft_atol_plus(char *str);
long long	ft_atol_minus(char *str);
char		*get_prompt_name(t_env *env, t_main *m);
char		*get_pwd_format(t_env *env, t_prompt *p, char	*pwd);
void		free_prompt(t_prompt *p);
void		init_to_null(t_prompt *p);
char		*get_env(t_env	*env, char *var);
void		edit_pwd(t_env *mini_env, char **argv);

#endif