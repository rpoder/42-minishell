/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_prototypes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:07:16 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/25 23:20:27 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cancel_sigquit(void)
{
	signal(SIGQUIT, SIG_IGN);
}

void	ignore_all_sigs(void)
{
	signal(SIGINT, SIG_IGN);
}

void	default_all_sigs(void)
{
	signal(SIGINT, SIG_DFL);
}

void	custom_all_sigs(void)
{
	signal(SIGINT, handle_custom_sigint);
}

void	custom_heredoc_all_sigs(void)
{
	signal(SIGINT, handle_heredoc_sigs);
}
