/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_minishell_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 17:11:26 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/10 20:11:50 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup_gnl(char *str, int start, int len, int *ret)
{
	char	*dst;
	int		i;
	int		len_to_save;

	len_to_save = len - start;
	dst = (char *)malloc((len_to_save + 1) * sizeof(char));
	if (dst == NULL)
	{
		*ret = MALLOC_ERR;
		return (NULL);
	}
	i = 0;
	while (i < len_to_save)
	{
		dst[i] = str[start];
		i++;
		start++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_fill_dst(char *s1, char *s2, char *dst)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s1 != NULL)
	{
		while (s1[i])
		{
			dst[j] = s1[i];
			i++;
			j++;
		}
		i = 0;
	}
	while (s2[i])
	{
		dst[j] = s2[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (dst);
}

char	*ft_strjoin_gnl(char *s1, char *s2, int *ret)
{
	char	*dst;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	dst = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (dst == NULL)
	{	
		*ret = MALLOC_ERR;
		return (NULL);
	}
	dst = ft_fill_dst(s1, s2, dst);
	return (dst);
}
