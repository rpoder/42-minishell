/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 21:23:22 by mpourrey          #+#    #+#             */
/*   Updated: 2022/06/30 19:30:43 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_to_save(char *line, int stop)
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
		to_save = ft_strndup_gnl(line, i + 1, len);
		free (line);
		return (to_save);
	}
	if (stop <= 0)
		free(line);
	return (NULL);
}

char	*ft_to_return(char *line)
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
		return (NULL);
	i = 0;
	while (i < len)
	{
		to_return[i] = line[i];
		i++;
	}
	to_return[i] = '\0';
	return (to_return);
}

char	*ft_make_line(char *line, char *buf)
{
	char	*new_line;

	new_line = ft_strjoin_gnl(line, buf);
	if (line != NULL)
		free(line);
	return (new_line);
}

char	*ft_read(int fd)
{
	char		*buf;
	static char	*line = NULL;
	char		*to_return;
	int			nb_lus;

	nb_lus = 1;
	while (nb_lus > 0 && ft_strchr(line, '\n') == 0)
	{
		buf = (char *)malloc(BUFFER_SIZE + 1 * sizeof(char));
		if (buf == NULL)
			return (NULL);
		nb_lus = read(fd, buf, BUFFER_SIZE);
		if (nb_lus <= 0 && line == NULL)
		{
			free(buf);
			return (NULL);
		}
		buf[nb_lus] = '\0';
		line = ft_make_line(line, buf);
		free(buf);
	}
	to_return = ft_to_return(line);
	line = ft_to_save(line, nb_lus);
	return (to_return);
}

char	*get_next_line(int fd)
{
	char	*to_return;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	to_return = ft_read(fd);
	return (to_return);
}
