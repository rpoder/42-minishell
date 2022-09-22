/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:07:16 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/22 22:09:52 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	ignore_all_sigs(void)
{
	signal(SIGINT, SIG_IGN);
}

void	handle_default_sigint(int signum)
{
	ft_printf_fd("SIG INT IN CHILD CALLED\n", 2);
	set_expand(g_data, "?", "130");
	global_free(g_data, NO_ERR);
}

void	default_all_sigs(void)
{
	signal(SIGINT, handle_default_sigint);
}

void	handle_custom_sigint(int signum)
{
	set_expand(g_data, "?", "130");

	free_line_datas(g_data);
	ft_putstr_fd("\n\b", 1);
	rl_on_new_line();
	rl_redisplay();
	rl_replace_line("", 0);
}

void	custom_all_sigs(void)
{
	signal(SIGINT, handle_custom_sigint);

}


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

