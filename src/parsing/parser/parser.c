/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:31:55 by dpinto            #+#    #+#             */
/*   Updated: 2024/12/16 21:08:18 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*new_node(t_token *tok)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->txt = NULL;
	node->after_here_doc = 0;
	node->quotes = 0;
	node->heredoc = 0;
	if (tok)
		node->txt = ft_strdup((tok->text));
	node->children = 0;
	node->first_child = NULL;
	node->next = NULL;
	node->prev_sibling = NULL;
	return (node);
}

t_node	*add_node_to_ast(t_node *root, t_node *node)
{
	t_node	*ptr;
	t_node	*prev;

	if (root->first_child == NULL)
		root->first_child = node;
	else
	{
		ptr = root->first_child;
		while (ptr != NULL)
		{
			prev = ptr;
			ptr = ptr->next;
		}
		prev->next = node;
		node->prev_sibling = prev;
	}
	return (root);
}

t_node	*parse_simple_command(char *input, t_source **src, t_info_tok **info)
{
	t_node		*root;
	t_token		*tok;
	t_source	*src_ft;
	t_info_tok	*info_ft;

	if (!input)
		return (NULL);
	src = init_src(src, input);
	info = init_global_info_token(info);
	root = new_node(NULL);
	src_ft = *src;
	info_ft = *info;
	if (!root)
		return (NULL);
	if (src_ft->end_input != 1)
		tok = tokenize(src_ft, info_ft);
	while (src_ft->exit != 1 || tok != NULL)
	{
		if (!(if_tok_exist(tok, root, info)))
			return (NULL);
		info = init_global_info_token(info);
		info_ft = *(info);
		tok = tokenize(src_ft, info_ft);
	}
	return (free_tok(&tok), root);
}

t_node	*if_tok_exist(t_token *tok, t_node *root, t_info_tok **info)
{
	t_node	*node;

	if (tok)
	{
		node = new_node(tok);
		if (!node)
			return (NULL);
		add_node_to_ast(root, node);
		free_tok(&tok);
	}
	free_info(info);
	info = NULL;
	return (root);
}
