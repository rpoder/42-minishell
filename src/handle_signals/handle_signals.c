/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:07:16 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/22 02:41:02 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


void	handle_parent_sigint(int signum)
{
	// ft_printf_fd("[parent %d]\n", 2, getpid());

	free_line_datas(g_data);
	ft_putstr_fd("\n\b", 1);
	rl_on_new_line();
	rl_redisplay();
	rl_replace_line("", 0);
}

void	handle_child_sigint(int signum)
{
	// ft_printf_fd("[enfant %d]\n", 2, getpid());
	global_free(g_data, NO_ERR);
}

///////////////////////////////////////////////////

void	create_parent_signals(void)
{
	// ft_printf_fd("create parent pid %d\n", 2, getpid());
	signal(SIGINT, handle_parent_sigint);
	signal(SIGQUIT, SIG_IGN);
	// signal(SIGQUIT, block_parent_sigquit);
}

void	create_child_signals(void)
{
	// ft_printf_fd("create enfant pid %d\n", 2, getpid());
	signal(SIGINT, handle_child_sigint);
}

void	cancel_parent_signals(void)
{
	// ft_printf_fd("cancel parent sig pid %d\n", 2, getpid());
	signal(SIGINT, SIG_IGN);
}

