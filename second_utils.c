/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouali <ebouali@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:50:14 by ebouali           #+#    #+#             */
/*   Updated: 2025/07/09 14:50:15 by ebouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*search_cmd_path(char **path_split, char *cmd)
{
	int		i;
	char	*tmp;
	char	*full_path;

	i = 0;
	while (path_split[i])
	{
		tmp = ft_strjoin(path_split[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full_path)
			return (full_path_error(path_split));
		if (access(full_path, X_OK) == 0)
		{
			free_split(path_split);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_split(path_split);
	return (NULL);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && i < (n - 1) && s1[i] == s2[i])
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
