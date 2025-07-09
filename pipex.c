/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouali <ebouali@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:49:56 by ebouali           #+#    #+#             */
/*   Updated: 2025/07/09 14:49:58 by ebouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_files(t_pipex *data, char *argv[])
{
	data->fd_in = open(argv[1], O_RDONLY);
	if (data->fd_in < 0)
		file_error(data);
	data->fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd_out < 0)
	{
		perror("open outfile");
		file_error(data);
	}
}

char	*get_path_to_cmd(char *cmd, char **envp)
{
	char	*content;
	char	**path_split;

	content = get_envp(envp);
	if (!content)
		return (NULL);
	path_split = ft_split(content, ':');
	if (!path_split)
		return (NULL);
	return (search_cmd_path(path_split, cmd));
}

void	execute_cmd_one(t_pipex *data, char **envp)
{
	char	**cmd_array;
	char	*path_cmd;

	if (dup2(data->fd_in, STDIN_FILENO) == -1)
		pipe_and_process_error(data);
	if (dup2(data->pipe_fd[1], STDOUT_FILENO) == -1)
		pipe_and_process_error(data);
	close(data->fd_in);
	close(data->fd_out);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	cmd_array = ft_split(data->cmd1, ' ');
	if (!cmd_array)
		exit(EXIT_FAILURE);
	path_cmd = get_path_to_cmd(cmd_array[0], envp);
	if (!path_cmd)
		path_cmd_error(cmd_array);
	execve(path_cmd, cmd_array, envp);
	perror("execve");
	free(path_cmd);
	free_split(cmd_array);
	exit(EXIT_FAILURE);
}

void	execute_cmd_two(t_pipex *data, char **envp)
{
	char	**cmd_array;
	char	*path_cmd;

	if (dup2(data->pipe_fd[0], STDIN_FILENO) == -1)
		pipe_and_process_error(data);
	if (dup2(data->fd_out, STDOUT_FILENO) == -1)
		pipe_and_process_error(data);
	close(data->fd_in);
	close(data->fd_out);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	cmd_array = ft_split(data->cmd2, ' ');
	if (!cmd_array)
		exit(EXIT_FAILURE);
	path_cmd = get_path_to_cmd(cmd_array[0], envp);
	if (!path_cmd)
		path_cmd_error(cmd_array);
	execve(path_cmd, cmd_array, envp);
	perror("execve two");
	free(path_cmd);
	free_split(cmd_array);
	exit(EXIT_FAILURE);
}
