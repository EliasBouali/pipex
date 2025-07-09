/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouali <ebouali@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:49:24 by ebouali           #+#    #+#             */
/*   Updated: 2025/07/09 14:49:26 by ebouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	launch_children(t_pipex *data, char **envp, pid_t *pid1,
		pid_t *pid2)
{
	*pid1 = fork();
	if (*pid1 == -1)
		pipe_and_process_error(data);
	if (*pid1 == 0)
		execute_cmd_one(data, envp);
	*pid2 = fork();
	if (*pid2 == -1)
		pipe_and_process_error(data);
	if (*pid2 == 0)
		execute_cmd_two(data, envp);
}

static void	close_and_wait(t_pipex *data, pid_t pid1, pid_t pid2)
{
	int	status;

	close(data->fd_in);
	close(data->fd_out);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	exit(0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
	{
		ft_printf("Usage: ./pipex file1 cmd1 cmd2 file2\n");
		return (1);
	}
	data.cmd1 = argv[2];
	data.cmd2 = argv[3];
	open_files(&data, argv);
	if (pipe(data.pipe_fd) == -1)
		pipe_and_process_error(&data);
	launch_children(&data, envp, &pid1, &pid2);
	close_and_wait(&data, pid1, pid2);
	return (0);
}
