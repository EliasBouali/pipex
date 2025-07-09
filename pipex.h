#ifndef PIPEX_H
#define PIPEX_H

# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdarg.h>


typedef struct s_pipex
{
  int fd_in;
  int fd_out;
  int pipe_fd[2];
  int fork_fd;
  char *cmd1;
  char *cmd2;
}     t_pipex;



// fonction dans le fichier utils.c :
void file_error(t_pipex *data);
void pipe_and_process_error(t_pipex *data);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void	free_split(char **split);
void path_cmd_error(char **cmd_array);

// fonction dans le fichier second_utils.c:
char *get_envp(char **envp);
char *full_path_error(char **path_split);
char *search_cmd_path(char **path_split, char *cmd);

// fonction dans le fichier pipex.c :
void open_files(t_pipex *data, char *argv[]);
char *get_path_to_cmd(char *cmd, char **envp);
void execute_cmd_one(t_pipex *data,char **envp);
void execute_cmd_two(t_pipex *data, char **envp);

// fonction du fichier ft_split.c :
char	**ft_split(char const *s, char c);

// fonction dans le fichier ft_strjoin.c :
size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);

// fonctions dans le dossier ft_printf:
int	ft_print_ptr(void *ptr);
int	ft_count(const char *format, int i, va_list args);
int	ft_printf(const char *format, ...);
int	ft_put_unsigned(unsigned int n);
int	ft_putchar(char c);
int	ft_puthex(unsigned int n, int is_upper);
int	ft_putnbr(int n);
int	ft_putstr(char *s);

#endif
