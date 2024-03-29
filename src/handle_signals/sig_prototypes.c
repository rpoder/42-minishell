/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_prototypes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:07:16 by rpoder            #+#    #+#             */
/*   Updated: 2022/09/26 01:07:58 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cancel_sigquit(void)
{
	signal(SIGQUIT, SIG_IGN);
}

void	custom_sigquit(void)
{
	signal(SIGQUIT, SIG_DFL);
}

void	ignore_all_sigs(void)
{
	signal(SIGINT, SIG_IGN);
}
