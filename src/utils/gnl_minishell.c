/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 18:01:48 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/10 20:11:30 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_to_save(char *line, int stop, int *ret)
{
	char	*to_save;
	int		i;
	int		len;

	i = 0;
	if (line != NULL && stop > 0)
	{
		while (line[i] != '\n')
			i++;
		len = i;
		while (line[len] != '\0')
			len++;
		if (len == i + 1)
		{
			free(line);
			return (NULL);
		}
		to_save = ft_strndup_gnl(line, i + 1, len, ret);
		free (line);
		return (to_save);
	}
	if (stop <= 0)
		free(line);
	return (NULL);
}

static char	*ft_to_return(char *line, int *ret)
{
	char	*to_return;
	int		len;
	int		i;

	len = 0;
	while (line[len] != '\n' && line[len] != '\0')
		len++;
	if (line[len] == '\n')
		len++;
	to_return = (char *)malloc(len + 1 * sizeof(char));
	if (to_return == NULL)
	{
		*ret = MALLOC_ERR;
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		to_return[i] = line[i];
		i++;
	}
	to_return[i] = '\0';
	return (to_return);
}

static char	*ft_make_line(char *line, char *buf, int *ret)
{
	char	*new_line;

	new_line = ft_strjoin_gnl(line, buf, ret);
	if (line != NULL)
		free(line);
	return (new_line);
}

static char	*ft_read(int fd, int *ret)
{
	char		*buf;
	static char	*line = NULL;
	char		*to_return;
	int			nb_lus;

	nb_lus = 1;
	while (nb_lus > 0 && ft_strchr(line, '\n') == 0)
	{
		buf = (char *)malloc(BUFFER_SIZE_GNL + 1 * sizeof(char));
		if (buf == NULL)
		{
			*ret = MALLOC_ERR;
			return (NULL);
		}
		nb_lus = read(fd, buf, BUFFER_SIZE_GNL);
		if (nb_lus <= 0 && line == NULL)
		{
			free(buf);
			return (NULL);
		}
		buf[nb_lus] = '\0';
		line = ft_make_line(line, buf, ret);
		free(buf);
		if (*ret != NO_ERR)
			return (NULL);
	}
	to_return = ft_to_return(line, ret);
	line = ft_to_save(line, nb_lus, ret);
	if (to_return != NULL && *ret != NO_ERR)
		free(to_return);
	return (to_return);
}

char	*gnl_minishell(int fd, int *ret)
{
	char	*to_return;

	if (fd < 0 || BUFFER_SIZE_GNL < 1)
	{
		*ret = ERR_NOT_DEFINED;
		return (NULL);
	}
	to_return = ft_read(fd, ret);
	if (*ret != NO_ERR)
		return (NULL);
	return (to_return);
}
