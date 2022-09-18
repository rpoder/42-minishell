/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:42:27 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/18 18:17:22 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_and_skip_cmd_node(char **words, t_cmd_node *cmd, int *i, char *amb_redir)
{
	int	ret;

	ret = check_and_set_redirection(words, *i, cmd, amb_redir);
	if (ret != NO_ERR && ret != OPEN_ERR)
		return (ret);
	ret = set_cmd_tab(words, *i, cmd);
	if (ret != NO_ERR)
		return (ret);
	while (words[*i] && words[*i][0] != '|')
		(*i)++;
	return (NO_ERR);
}
