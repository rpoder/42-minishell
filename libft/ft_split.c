/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 19:50:28 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/08 20:11:43 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free_tab_split(char **ptr, int k)
{
	while (k >= 0)
	{
		free(ptr[k]);
		k--;
	}
	free(ptr);
	return (NULL);
}

static int	ft_count_char(char const *s, char c, int i)
{
	int	j;

	j = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && s[i] != c)
	{
		i++;
		j++;
	}	
	return (j);
}

static int	ft_count_str(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			j++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (j);
}

static char	**ft_fill_str(char **ptr, char const *s, char c)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (s[i] && k < (ft_count_str(s, c)))
	{
		while (s[i] == c)
			i++;
		ptr[k] = (char *)malloc((ft_count_char(s, c, i) + 1) * sizeof (char));
		if (ptr[k] == NULL)
			return (ft_free_tab_split(ptr, k));
		j = 0;
		while (s[i] && s[i] != c)
		{
			ptr[k][j] = s[i];
			i++;
			j++;
		}
		ptr[k][j] = '\0';
		k++;
	}
	ptr[k] = NULL;
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;

	if (s == NULL)
		return (NULL);
	ptr = (char **) malloc((ft_count_str(s, c) + 1) * sizeof (char *));
	if (ptr == NULL)
		return (NULL);
	ptr = ft_fill_str(ptr, s, c);
	return (ptr);
}
