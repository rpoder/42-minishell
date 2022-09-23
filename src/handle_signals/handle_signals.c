/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:07:16 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/23 17:40:38 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	ignore_all_sigs(void)
{
	signal(SIGINT, SIG_IGN);
}

/* void	handle_default_sigint(int signum)
{
	set_expand(g_data, "?", "130");
	global_free(g_data, NO_ERR);
} */

void	default_all_sigs(void)
{
	signal(SIGINT, SIG_DFL);
}

void	handle_custom_sigint(int signum)
{
	// set_expand(g_data, "?", "130");

	// free_line_datas(g_data);
	ioctl(0, TIOCSTI, "\n");
	// ft_putstr_fd("\b\n\n", 0);
	g_close_heredoc = true;
	rl_redisplay();
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	custom_all_sigs(void)
{
	signal(SIGINT, handle_custom_sigint);
}

/////////////////////////herddoc sig
/*
void	handle_heredoc_sigint(int signum)
{
	g_close_heredoc = true;
	write(2, "\n", 1);
	// ft_putstr_fd("\b", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
 	rl_redisplay();
}

void	init_heredoc_sig(void)
{
	signal(SIGINT, handle_heredoc_sigint);
} */


/*
void	create_parent_signals(void)
{
	// ft_printf_fd("///////////////CREATE CHILD SIGNALS///// %d\n", 2, getpid());
	signal(SIGINT, handle_parent_sigint);
	signal(SIGQUIT, SIG_IGN);
	// signal(SIGQUIT, block_parent_sigquit);
}

void	handle_parent_sigint(int signum)
{
	signal(SIGINT, handle_child_sigint);
}

	set_expand(g_data, "?", "130");

	free_line_datas(g_data);
	ft_putstr_fd("\n\b", 1);
	rl_on_new_line();
	rl_redisplay();
	rl_replace_line("", 0);
}

void	cancel_parent_signals(void)
{
	ft_printf_fd("cancel parent sig pid %d\n", 2, getpid());
	signal(SIGINT, SIG_IGN);
}



void	handle_child_sigint(int signum)
{
	ft_printf_fd("[enfant %d]\n", 2, getpid());
	set_expand(g_data, "?", "130");
	exit(56);
	// global_free(g_data, NO_ERR);
}

void	create_child_signals(void)
{
	ft_printf_fd("////////CREATE CHILD SIGNALS///// %d\n", 2, getpid());
	signal(SIGINT, handle_child_sigint);
}


 */

