/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoder <rpoder@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:24:00 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/20 15:18:23 by rpoder           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_ambiguous_redirection(t_list *expands)
{
	int i;

	i = 0;
	printf("\nSAVED_EXPANDS :\n");
	while (expands)
	{
		printf("[%d] = %s\n", i, (char *)expands->content);
		expands = expands->next;
		i++;
	}
}

void	test_parser(t_list *cmds)
{
	int	i;
	int	j;
	t_list	*heredoc;

	i = 0;
	while (cmds)
	{
		j = 0;
		printf("CMD %d\n", i);
		printf("path = %s\n", ((t_cmd_node *)cmds->content)->path);
		while (((t_cmd_node *)cmds->content)->cmd_tab[j])
		{
			printf("cmd_tab[%d] = %s\n", j, ((t_cmd_node *)cmds->content)->cmd_tab[j]);
			j++;
		}
		printf("fd_in = %d\n", ((t_cmd_node *)cmds->content)->fd_in);
		printf("fd_out = %d\n", ((t_cmd_node *)cmds->content)->fd_out);
		heredoc = ((t_cmd_node *)cmds->content)->heredocs;
		printf("heredocs = ");
		while (heredoc)
		{
			printf("%s ",((char *)heredoc->content));
			heredoc = heredoc->next;
		}
		printf("\n\n");
		i++;
		cmds = cmds->next;
	}
}

void	test_lexer(char **words)
{
	int	i;

	printf("\n");
	i = 0;
	while (words[i] != NULL)
	{
		printf("word[%d] = |%s|\n", i, words[i]);
		i++;
	}
}

void	test_ronan(t_data *data)
{

	// t_list	*tmp;
	// tmp = data->local_expands;
	// while (tmp)
	// {
	// 	printf("%s = %s\n", ((t_expand *)tmp->content)->key, ((t_expand *)tmp->content)->value);
	// 	tmp = tmp->next;
	// }

	add_expand(data, &data->local_expands, ft_alloc_and_fill("CDPATH"), ft_alloc_and_fill("/mnt/nfs/homes/rpoder/tmp"));

	// char **args;
	// args = malloc(sizeof(char *) * 2);
	// args[0] = ft_alloc_and_fill("pwd");
	// args[1] = NULL;

	// ft_pwd(data, args);

}

int	main(int argc, char **argv, char **env)
{
	char 	*line;
	t_data	*data;

	data = init_data(env);
	while (1)
	{
		line = readline("mi_nils_shell j'écoute ? > ");
		if (ft_strlen(line) >= 1)
		{
			add_history(line);
			data->prompt_line = ft_alloc_and_fill(line);
			if (!data->prompt_line)
				global_free(data, MALLOC_ERR);
	 		if (quote_syntax_checker(line) == 0)
			{
 				mute_in_quotes(data);
				expander(data);
				lexer(data);
	//			test_lexer(data->words);
				redirection_syntax_printer(data->words);
				parser(data);
				executer(data);
	//			test_parser(data->cmds);
			}
		}
		free_line_datas(data);
	}
	global_free(data, END);
}
