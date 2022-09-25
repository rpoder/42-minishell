/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_prototypes2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 01:07:39 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/26 01:07:55 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
