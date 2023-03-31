/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:51:11 by hanmpark          #+#    #+#             */
/*   Updated: 2023/03/31 15:39:45 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus/pipex_bonus.h"
#include "bonus/errors_bonus.h"

/* Returns the PATH variable in envp as a string */
static char	*define_path(int fileout, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4) != 0)
			return (envp[i]);
		i++;
	}
	close(fileout);
	ft_error(ERR_PATH);
	return (0);
}

/* Looks for the command's path and returns it (if found) as a string */
char	*define_cmdpath(char *cmd, char *env_path)
{
	char	**cmd_paths;
	char	*right_path;
	char	*dir_path;
	int		i;

	cmd_paths = ft_split(env_path + 5, ':');
	i = 0;
	while (cmd_paths[i])
	{
		dir_path = ft_strjoin(cmd_paths[i], "/");
		right_path = ft_strjoin(dir_path, cmd);
		free(dir_path);
		if (access(right_path, F_OK) == 0)
		{
			ft_freestr_array(cmd_paths);
			return (right_path);
		}
		free(right_path);
		i++;
	}
	ft_freestr_array(cmd_paths);
	return (0);
}

/* Checks if the commands exist and stock its path data->cmd_path */
void	check_cmd(t_cmd *data, char **argv, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;
	int		i;

	data->env_path = define_path(data->fileout, envp);
	i = data->cmd_index;
	while (i < data->last_cmd + 1)
	{
		cmd_args = ft_split(argv[i], ' ');
		cmd_path = define_cmdpath(cmd_args[0], data->env_path);
		ft_freestr_array(cmd_args);
		if (cmd_path == NULL)
		{
			close(data->fileout);
			ft_error(ERR_CMDPATH);
		}
		free(cmd_path);
		i++;
	}
}

/* Defines the cmd_args */
char	**define_cmdargs(char *cmd, char *path)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split(cmd, ' ');
	cmd_path = define_cmdpath(cmd_args[0], path);
	free(cmd_args[0]);
	cmd_args[0] = cmd_path;
	return (cmd_args);
}

/* Opens the file and returns its file descriptor */
int	open_file(char *fileName, int mode)
{
	int	fd;

	fd = -1;
	if (mode == READ)
		fd = open(fileName, O_RDONLY);
	else if (mode == WRITE)
		fd = open(fileName, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else if (mode == APPEND)
		fd = open(fileName, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
		ft_error(ERR_OPEN);
	return (fd);
}