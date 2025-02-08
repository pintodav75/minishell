/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:35:24 by wacista           #+#    #+#             */
/*   Updated: 2024/12/16 20:35:25 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"

extern int	g_exit_status;

char	*ft_strjoin_s2(char *s1, char *s2)
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
	ft_free_str(&s2);
	return (dest);
}
