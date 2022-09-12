/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ronanpoder <ronanpoder@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:17:07 by ronanpoder        #+#    #+#             */
/*   Updated: 2022/09/12 15:15:47 by ronanpoder       ###   ########.fr       */
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
	pid_t	fork_ret;
	char	**env_tab;

	fd_stdin = dup(0);
	while(cmd)
	{
		pipe_fd = init_pipe(data);
		fork_ret = fork();
		if (fork_ret == 0)
		{
			if (!is_last_cmd(cmd))
				dup2(1, pipe_fd[1]);
			// rediriger chevrons

			env_tab = get_env_tab(data);
			if (!env_tab)
				global_free(data, MALLOC_ERR);
			execve(((t_cmd_node *)cmd->content)->path, ((t_cmd_node *)cmd->content)->cmd_tab, env_tab);
		}
		if (!is_last_cmd(cmd))
			dup2(0, pipe_fd[0]);
		cmd = cmd->next;
	}
	// recuperer err de l'enfant
	// remettre stdin dans fd0
}

void	executer(t_data *data)
{

	execute_cmds(data, data->cmds);
}

