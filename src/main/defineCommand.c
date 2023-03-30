/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defineCommand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:25:57 by hanmpark          #+#    #+#             */
/*   Updated: 2023/03/30 18:13:01 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main/pipex.h"
#include "main/errors.h"

/* Look for the right path for the command and returns the path as a string */
static char	*defineCommandPath(char *cmd, char *envPath)
{
	char	**cmdPaths;
	char	*rightPath;
	char	*dirPath;
	int		i;

	cmdPaths = ft_split(envPath + 5, ':');
	i = 0;
	while (cmdPaths[i])
	{
		dirPath = ft_strjoin(cmdPaths[i], "/");
		rightPath = ft_strjoin(dirPath, cmd);
		free(dirPath);
		if (access(rightPath, F_OK) == 0)
		{
			ft_freestr_array(cmdPaths);
			return (rightPath);
		}
		free(rightPath);
		i++;
	}
	ft_freestr_array(cmdPaths);
	return (0);
}

/* Returns the PATH in envp */
static char	*definePath(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4) != NOT_FOUND)
			return (envp[i]);
		i++;
	}
	ft_error(ERR_PATH);
	return (0);
}

/* Checks if the commands exist and stock its path data->cmdPath */
void	defineCommand(t_cmd *data, char **argv, char **envp)
{
	int		i;
	char	**cmdv;

	data->envPath = definePath(envp);
	data->cmdPath = ft_calloc(data->nbrCommands, sizeof(char *));
	if (data->cmdPath == NULL)
		ft_error(ERR_MALLOC);
	i = 0;
	while (i < data->nbrCommands)
	{
		cmdv = ft_split(argv[2 + i], ' ');
		data->cmdPath[i] = defineCommandPath(cmdv[0], data->envPath);
		ft_freestr_array(cmdv);
		if (data->cmdPath[i] == NULL)
		{
			ft_freestr_array(data->cmdPath);
			ft_error(ERR_CMDPATH);
		}
		i++;
	}
}
