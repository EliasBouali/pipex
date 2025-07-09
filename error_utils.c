#include "pipex.h"

void file_error(t_pipex *data)
{
  if (data)
  {
    if (data->fd_in >= 0)
    {
      close(data->fd_in);
      perror("first file");
    }
    if (data->fd_out >= 0)
    {
      close(data->fd_out);
      perror("open infile");
    }
  }
  exit(EXIT_FAILURE);
}

void pipe_and_process_error(t_pipex *data)
{
  if (data)
  {
    if (data->pipe_fd[0] >= 0)
    {
      close(data->pipe_fd[0]);
      perror("first pipe");
    }
    if (data->pipe_fd[1] >=0)
    {
      close(data->pipe_fd[1]);
      perror("last pipe");
    }
    if (data->fork_fd == -1)
      perror("fork/process failed");
  }
  exit(EXIT_FAILURE);
}

char *full_path_error(char **path_split)
{
  free_split(path_split);
  perror("full_path_error");
  return (NULL);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}
void path_cmd_error(char **cmd_array)
{
  ft_printf("Command one not found: %s\n", cmd_array[0]);
  free_split(cmd_array);
  exit(EXIT_FAILURE);
}
