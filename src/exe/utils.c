/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:35:39 by wacista           #+#    #+#             */
/*   Updated: 2025/01/31 16:25:48 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

void	ft_free_str(char **str)
{
	if (str != NULL && **str != '\0')
	{
		free(*str);
		*str = NULL;
	}
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	int		i;
	char	*dest;

	if (!s1 && !s2)
		return (NULL);
	dest = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2 && *s2)
		dest[i++] = *s2++;
	dest[i] = '\0';
	if (s1 && *s1)
		free(s1);
	return (dest);
}

char	*ft_strjoin_env(char *s1, char *s2)
{
	char	*dest;
	size_t	len;
	int		i;
	int		j;

	if ((!s1) && (!s2))
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	len = (i + j + 1);
	dest = (char *)malloc((len) * sizeof(char));
	if (!dest)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i])
		dest[j++] = s1[i];
	i = -1;
	while (s2[++i])
		dest[j++] = s2[i];
	dest[j] = '\0';
	return (dest);
}

int	lenlist(t_final *L)
{
	int	len;

	len = 0;
	while (L)
	{
		len++;
		L = L->next;
	}
	return (len);
}
