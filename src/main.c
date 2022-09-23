/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:24:00 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/23 21:45:46 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	g_close_heredoc = false;

static void	execute_line(t_data *data, char *line)
{
	add_history(line);
	data->prompt_line = line;
	if (!data->prompt_line)
		global_free(data, MALLOC_ERR);
	if (quote_syntax_checker(line) == 0)
	{
		mute_in_quotes(data);
		expander(data);
		lexer(data);
		redirection_syntax_printer(data->words);
		if (parser(data) == 0)
			executer(data);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_data	*data;

	data = init_data(env);
	while (1)
	{
		custom_all_sigs();
		line = readline("minilsshell> ");
		if (!line)
		{
			rl_clear_history();
			global_free(data, END);
		}
		if (ft_strlen(line) >= 1)
			execute_line(data, line);
		free_line_datas(data);
	}
	global_free(data, END);
	rl_clear_history();
}
