/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unmute_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:27:03 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/23 18:33:52 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	unmute_char(char c)
{
	if (c < 0)
		c = c * -1;
	return (c);
}

int	unmute_word_len(char *str)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] > 0 || str[i] * -1 != '*')
			len++;
		i++;
	}
	return (len);
}

char	*unmute_word(char *str)
{
	int		i;
	int		j;
	char	*dst;

	i = 0;
	j = 0;
	dst = malloc(sizeof(char) * unmute_word_len(str) + 1);
	if (dst == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] < 0 && str[i] * -1 == '*')
			i++;
		else
		{
			if (str[i] < 0)
				dst[j] = str[i] * -1;
			else
				dst[j] = str[i];
			i++;
			j++;
		}
	}
	dst[j] = '\0';
	return (dst);
}
