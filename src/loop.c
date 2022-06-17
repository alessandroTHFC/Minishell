/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org.au>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:25:24 by aboehm            #+#    #+#             */
/*   Updated: 2022/05/25 15:25:29 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	freecmd(t_cmd cmd)
{
	if (cmd.pipe_in != STDIN_FILENO)
		close(cmd.pipe_in);
	if (cmd.pipe_out != STDOUT_FILENO)
		close(cmd.pipe_out);
	if (cmd.redir_in != STDIN_FILENO)
		close(cmd.redir_in);
	if (cmd.redir_out != STDOUT_FILENO)
		close(cmd.redir_out);
	free2d_array((void **)cmd.argv);
}

/* Read a string, and return a pointer to it.  Returns NULL on EOF. */
static char	*rl_get(void)
{
	static char const	*line_read;

	line_read = NULL;
	if (line_read)
	{
		free((char *)line_read);
		line_read = (char *) NULL;
	}
	line_read = readline(">>>");
	if (line_read == NULL)
		safe_exit(0);
	if (*line_read)
		add_history(line_read);
	return ((char *)line_read);
}

//	if (!ft_strncmp(cmds[(*i)].name, "cat", 3))
//		write(1, "\n", 1);
static void	get_exit_and_free(const t_cmd *cmds, int *i, int *status)
{
	waitpid(cmds[(*i)].pid, status, 0);
	if (!WIFEXITED((*status)) && WEXITSTATUS(*status))
		printf(" cmd %i returned: %i\n", *i, WEXITSTATUS(*status));
	freecmd(cmds[(*i)++]);
}

static int	iterate_cmds(t_cmd *cmds, bool *exit)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (cmds[i].name)
	{
		*exit = !ft_strncmp("exit", cmds[i].name, 5);
		if (*exit)
			return (i);
		executor(&cmds[i++]);
	}
	i = 1;
	while (cmds[i].name)
		get_exit_and_free(cmds, &i, &status);
	insert(ft_strdup("?"), ft_itoa(WEXITSTATUS(status)));
	free(cmds);
	cmds = NULL;
	return (0);
}

void	loop_shell(void)
{
	t_cmd	*cmds;
	t_token	*token_lst;
	bool	exit;
	int		i;

	i = 0;
	exit = false;
	define_input_signals();
	while (!exit)
	{
		token_lst = lex(rl_get());
		if (!token_lst)
			continue ;
		cmds = parse(&token_lst);
		if (cmds && cmds[1].name)
			i = iterate_cmds(cmds, &exit);
	}
	while (cmds && cmds[i].argv)
		freecmd(cmds[i++]);
	free(cmds);
}
