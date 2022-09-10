/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:25:35 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/10 19:35:55 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef struct s_quotes {
	bool		sgl_quote;
	bool		dbl_quote;
}	t_quotes;

typedef struct s_split_tool
{
	int			i;
	int			nb_of_words;
	int			word_start;
}	t_split_tool;

typedef struct s_mute_tool
{
	int			i;
	int			len;
	char		quote;
}	t_mute_tool;

typedef struct s_expand_tool
{
	int			i;
	int			len;
	t_quotes	*quotes;
}	t_expand_tool;

typedef struct s_heredoc_tool
{
	char		*lim;
	char		*str;
	char		*heredoc_path;
	int			*ret;
}	t_heredoc_tool;

#endif