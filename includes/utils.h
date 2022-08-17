/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:25:35 by mpourrey          #+#    #+#             */
/*   Updated: 2022/08/17 17:50:30 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef struct	s_vars
{
	int	count;
	int	token_start;
}	t_vars;

typedef struct s_quotes {
	bool	sgl_quote;
	bool	dbl_quote;
}	t_quotes;

#endif