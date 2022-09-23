/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpourrey <mpourrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:24:00 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/23 21:16:00 by mpourrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	g_close_heredoc = false;

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
		free_line_datas(data);
	}
	global_free(data, END);
	rl_clear_history();
}
