/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:19:15 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/25 23:19:39 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_custom_sigint(int signum)
{
	(void) signum;
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
	rl_replace_line("", 0);
}

void	handle_heredoc_sigs(int signum)
{
	(void) signum;
	close(0);
	printf("\n");
	rl_redisplay();
	rl_on_new_line();
	rl_replace_line("", 0);
}
