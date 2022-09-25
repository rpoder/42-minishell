/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:24:00 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/25 16:01:06 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	g_close_heredoc = false;

static void	execute_line(t_data *data, char *line)
{
	add_history(line);
	data->prompt_line = line;
	if (!data->prompt_line)
		global_free(data, malloc_err);
	if (quote_syntax_checker(line) == 0)
	{
		mute_in_quotes(data);
		expander(data);
		lexer(data);
		if (data->words && data->words[0])
			redirection_syntax_printer(data->words);
		if (parser(data) == 0)
			executer(data);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_data	*data;

	cancel_sigquit();
	data = init_data(env);
	while (1)
	{
		custom_all_sigs();
		line = readline("minilsshell> ");
		if (!line)
		{
			set_expand(data, "?", "0");
			rl_clear_history();
			global_free(data, end);
		}
		if (ft_strlen(line) >= 1)
			execute_line(data, line);
		free_line_datas(data);
	}
	global_free(data, end);
	rl_clear_history();
}
