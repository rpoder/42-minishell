/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:17:07 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/13 19:39:24 by ronanpoder       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*init_pipe(t_data *data)
{
	int	*pipe_fd;

	pipe_fd = malloc(sizeof(int) * 2);
	if (!pipe_fd)
		global_free(data, MALLOC_ERR);
	if (pipe(pipe_fd) != 0)
	{
		free(pipe_fd);
		global_free(data, PIPE_ERR);
	}
	return(pipe_fd);
}

void	execute_cmds(t_data *data, t_list *cmd)
{
	int		*pipe_fd;
	char	**execve_tab;
	int		fd_stdin;
	pid_t	fork_ret[2];
	char	**env_tab;
	int		i;
	int		j;

	i = 0;
	fd_stdin = dup(0);
	while(cmd)
	{
		printf("cmd tab %s\n", ((t_cmd_node *)cmd->content)->cmd_tab[0]);
		pipe_fd = init_pipe(data);
		pipe(pipe_fd);
		fork_ret[i] = fork();

		if (fork_ret[i] == 0)
		{
			if (!is_last_cmd(cmd))
			{
				printf("dup sortie dans pipe %s\n", ((t_cmd_node *)cmd->content)->cmd_tab[0]);
				dup2(pipe_fd[1], 1);
			}
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			// rediriger chevrons

			env_tab = get_env_tab(data);
			if (!env_tab)
				global_free(data, MALLOC_ERR);

			if (execve(((t_cmd_node *)cmd->content)->path, ((t_cmd_node *)cmd->content)->cmd_tab, env_tab) != 0)
			{
				// global free si execve echoue
				global_free(data, ERR_NOT_DEFINED);
			}
		}
		else {
			dup2(pipe_fd[0], 0);

			close(pipe_fd[0]);
			close(pipe_fd[1]);

			cmd = cmd->next;
			i++;
		}
	}
	j = 2;
	while (j < 2)
	{
		waitpid(fork_ret[j], NULL, 0);
		j++;
	}
	// recuperer err de l'enfant

	dup2(fd_stdin, 0);
	close(fd_stdin);
}

void	executer(t_data *data)
{
	execute_cmds(data, data->cmds);
}

