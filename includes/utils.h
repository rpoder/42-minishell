/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margot <margot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:25:35 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/27 14:52:12 by margot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef struct s_quotes {
	bool	sgl_quote;
	bool	dbl_quote;
}	t_quotes;

typedef struct	s_split_data
{
	int	i;
	int	nb_of_tokens;
	int	token_start;
}	t_split_data;

typedef struct	s_mute_data
{
	int		i;
	int		len;
	char	quote;
}	t_mute_data;

typedef struct s_expand_data
{
	int			i;
	int			len;
	t_quotes	*quotes;
}	t_expand_data;

#endif