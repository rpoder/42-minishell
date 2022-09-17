/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_syntax_checker.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:49:59 by mpourrey          #+#    #+#             */
/*   Updated: 2022/09/17 19:34:51 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_pipe_error(char **words, int i)
{
	if (words[i][1] && words[i][1] == '|')
	{
		ft_printf_fd("syntax error near unexpected token `%c'\n",
			2, words[i][1]);
		return (1);
	}
	return (0);
}

static int	check_l_chev_error(char **words, int i)
{
	int	j;

	j = 0;
	while (words[i][j + 1] && words[i][j] == '<')
		j++;
	if (j > 1 || words[i][j] == '>' || words[i][j] == '|')
	{
		ft_printf_fd("syntax error near unexpected token `%c'\n",
			2, words[i][j]);
		return (1);
	}
	if (words[i + 1] && is_redirection_operator(words[i + 1][0]))
	{
		ft_printf_fd("syntax error near unexpected token `%c'\n",
			2, words[i + 1][0]);
		return (1);
	}
	return (0);
}

static int	check_r_chev_error(char **words, int i)
{
	int	j;

	j = 0;
	while (words[i][j + 1] && words[i][j] == '>')
		j++;
	if (j > 1 || words[i][j] == '<' || words[i][j] == '|')
	{
		ft_printf_fd("syntax error near unexpected token `%c'\n",
			2, words[i][j]);
		return (1);
	}
	if (words[i + 1] && is_redirection_operator(words[i + 1][0]))
	{
		ft_printf_fd("syntax error near unexpected token `%c'\n",
			2, words[i + 1][0]);
		return (1);
	}
	return (0);
}

int	check_redir_op_error(char **words)
{
	int	i;

	i = 0;
	while (words[i])
	{
		if (words[i][0] == '>')
		{	
			if (check_r_chev_error(words, i) == 1)
				return (1);
		}
		else if (words[i][0] == '<')
		{
			if (check_l_chev_error(words, i) == 1)
				return (1);
		}	
		else if (words[i][0] == '|')
		{
			if (check_pipe_error(words, i) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}		

void	redirection_syntax_printer(char **words)
{
	int	i;

	i = 0;
	if (words)
	{
		if (check_redir_op_error(words) != 0)
			return ;
		while (words[i + 1])
			i++;
		if (is_redirection_operator(words[i][0]))
			ft_printf_fd("syntax error near unexpected `newline'\n", 2);
	}
}
