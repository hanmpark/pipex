/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:20:46 by hanmpark          #+#    #+#             */
/*   Updated: 2023/03/31 12:28:13 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <sys/wait.h>
# include "../../libft/inc/libft.h"
# include "../../libft/inc/get_next_line.h"

/* Pipe's ends */
# define READ_END 0
# define WRITE_END 1

/* Process id */
# define CHILD_PROCESS 0

/* Modes for openFile() */
# define READ 1
# define WRITE 2
# define APPEND 3

typedef struct s_cmd
{
	int		cmdIndex;
	int		lastCommand;
	int		fileOut;
	char	*envPath;
}	t_cmd;

void	treatStdin(t_cmd *data, int argc, char **argv);
void	checkCommand(t_cmd *data, char **argv, char **envp);
void	runCommand(t_cmd *data, char **argv, char **envp);

char	*defineCommandPath(char *cmd, char *envPath);
int		openFile(char *fileName, int mode);

# endif