/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:07:16 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/21 17:14:00 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	create_signals(void)
{
	struct sigaction	sa;

	ft_printf_fd("create parent pid %d\n", 2, getpid());
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_parent_sigint;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

void	create_child_signals(void)
{
	ft_printf_fd("create enfant pid %d\n", 2, getpid());
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_child_sigint;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

void	handle_parent_sigint(int sig, siginfo_t *info, void *context)
{
	(void) context;
	(void) *info;

//	ft_printf_fd("parent\n", 2);

	free_line_datas(global_data);
	ft_putchar_fd('\n\b', 1);
	rl_on_new_line();
	// rl_replace_line();
	rl_redisplay();
}

void	handle_child_sigint(int sig, siginfo_t *info, void *context)
{
	(void) context;
	(void) *info;

	// global_free(global_data, NO_ERR);
	ft_printf_fd("enfant\n", 2);
	exit(0);
}
