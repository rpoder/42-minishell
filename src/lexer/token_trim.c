/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_trim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:08:24 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/29 15:43:25 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	token_trim_len(char *src)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while(is_space(src[i]))
		i++;
	while(src[i])
	{
		if (src[i] != '\'' && src[i] != '\"')
			len++;
		i++;
	}
	i--;
	while(is_space(src[i]))
	{
		i--;
		len--;
	}
	return (len);
}

char	*token_trim(char *src)
{
	char	*dst;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = token_trim_len(src);
	dst = malloc(sizeof(char) * (len + 10));
	if (!dst)
		return (NULL);
	while(is_space(src[i]))
		i++;
	while(src[i] && j < len)
	{
		if (src[i] != '\'' && src[i] != '\"')
		{
			dst[j] = src[i];
			j++;
		}
		i++;
	}
	dst[j] = '\0';
	return (dst);
}