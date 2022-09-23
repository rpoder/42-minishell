/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:07:16 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/23 21:28:01 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ignore_all_sigs(void)
{
	signal(SIGINT, SIG_IGN);
}

void	default_all_sigs(void)
{
	signal(SIGINT, SIG_DFL);
}

void	handle_custom_sigint(int signum)
{
	ioctl(0, TIOCSTI, "\n");
	g_close_heredoc = true;
	rl_redisplay();
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	custom_all_sigs(void)
{
	signal(SIGINT, handle_custom_sigint);
}
