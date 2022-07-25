/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:01:07 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/07/22 15:42:26 by ronanpoder       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "stdbool.h"
# include "stdlib.h"
# include "unistd.h"
# include "stdio.h"
# include "libft.h"

char *metachar_interpreter(char *src);

#endif



