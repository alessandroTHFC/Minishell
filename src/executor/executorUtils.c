/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executorUtils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org.au>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:21:28 by aboehm            #+#    #+#             */
/*   Updated: 2022/05/25 13:21:30 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//string join a directory in path[] to the T_COMMAND name
char	*getfile(char *dir, char *name)
{
	char	*file;
	char	*subfile;

	subfile = ft_strjoin("/", name);
	file = ft_strjoin(dir, subfile);
	free(subfile);
	subfile = NULL;
	return (file);
}

void	setup_fds(t_cmd *cmd)
{
	if (cmd->pipe_in != STDIN_FILENO)
	{
		dup2(cmd->pipe_in, STDIN_FILENO);
		close((cmd - 1)->pipe_out);
		close(cmd->pipe_in);
	}
	if (cmd->pipe_out != STDOUT_FILENO)
	{
		dup2(cmd->pipe_out, STDOUT_FILENO);
		close((cmd + 1)->pipe_in);
		close(cmd->pipe_out);
	}
	if (cmd->redir_in != STDIN_FILENO)
	{
		if ((cmd - 1)->name)
			close(cmd->pipe_in);
		dup2(cmd->redir_in, STDIN_FILENO);
	}
	if (cmd->redir_out != STDOUT_FILENO)
	{
		if ((cmd + 1)->name)
			close(cmd->pipe_out);
		dup2(cmd->redir_out, STDOUT_FILENO);
	}
}

void	exec_builtin(void (function)(), t_cmd *cmd)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		setup_fds(cmd);
		(*function)(cmd);
		exit(0);
	}
}

//runs all builtins in a new command except cd which
bool	builtin(t_cmd *cmd)
{
	if (!strcmp(cmd->name, "pwd"))
		exec_builtin(pwd, cmd);
	else if (!strcmp(cmd->name, "cd"))
		cd(cmd);
	else if (!strcmp(cmd->name, "env"))
		exec_builtin(display, cmd);
	else if (!strcmp(cmd->name, "export"))
		ft_export(cmd);
	else if (!strcmp(cmd->name, "unset"))
		unset(cmd);
	else if (!strcmp(cmd->name, "echo"))
		exec_builtin(echo, cmd);
	else
		return (false);
	return (true);
}
