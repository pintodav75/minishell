/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:32:38 by wacista           #+#    #+#             */
/*   Updated: 2024/12/16 20:32:39 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

static void	init_final(t_heredoc *h, char *env[], bool n)
{
	h->j_env = ft_strlen(h->tmp) + 1;
	while (env[h->i_env][h->j_env])
	{
		if (n)
			h->dest[h->k++] = env[h->i_env][h->j_env++];
		else
		{
			h->j_env++;
			h->len++;
		}
	}
}

static void	get_from_env(t_heredoc *h, char *env[], bool n)
{
	h->i_env = 0;
	h->j_env = 0;
	while (env[h->i_env])
	{
		if ((int)ft_strlen(h->tmp) == env_var_len(env[h->i_env]))
		{
			if (!ft_strncmp(env[h->i_env], h->tmp, env_var_len(env[h->i_env])))
			{
				init_final(h, env, n);
				break ;
			}
		}
		h->i_env++;
	}
	if (h->input[h->i] == '$')
		h->dollar = true;
	free(h->tmp);
}

static void	init_tmp(t_heredoc *h, char *env[], bool n)
{
	int	k;

	h->tmp = (char *)malloc(sizeof(char) * h->j + 1);
	if (!h->tmp)
	{
		if (n)
			free(h->dest);
		return (print_perror("malloc"));
	}
	k = 0;
	while (k < h->j)
	{
		h->tmp[k] = h->input[h->i_save];
		h->i_save++;
		k++;
	}
	h->tmp[k] = '\0';
	get_from_env(h, env, n);
}

static void	expand_process(t_heredoc *h, char *env[], bool n)
{
	h->i++;
	h->i_save = h->i;
	if (ft_isalpha(h->input[h->i]) || h->input[h->i] == '_')
	{
		while (h->input[h->i] && h->input[h->i] != '$' \
		&& (ft_isalnum(h->input[h->i]) || h->input[h->i] == '_'))
		{
			h->i++;
			h->j++;
		}
		init_tmp(h, env, n);
	}
	else if (h->input[h->i] == '?')
	{
		h->i++;
		h->j++;
		init_tmp(h, env, n);
	}
	else
		h->i++;
}

char	*heredoc_expand(t_heredoc *h, char *env[], bool n)
{
	if (!init_values(h, n))
		return (NULL);
	while (h->input[h->i])
	{
		h->j = 0;
		if (h->input[h->i] == '$' && h->input[h->i + 1] && h->input[h->i + 1] \
		!= '$' && (ft_isalnum(h->input[h->i + 1]) || h->input[h->i + 1] == '?' \
		|| h->input[h->i + 1] == '_'))
			expand_process(h, env, n);
		else if (h->dollar == true)
			h->dollar = false;
		else if (n)
			h->dest[h->k++] = h->input[h->i++];
		else
		{
			h->len++;
			h->i++;
		}
	}
	if (!n)
		return (heredoc_expand(h, env, true));
	h->dest[h->k] = '\0';
	free(h->input);
	return (h->dest);
}
