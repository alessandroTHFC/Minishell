/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingUtils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org.au>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:28:26 by aboehm            #+#    #+#             */
/*   Updated: 2022/05/25 13:28:32 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	n_args(t_token *token)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = token;
	while (tmp && (tmp->type == T_COMMAND || tmp->type == T_SINGLE_QUOTES
			|| tmp->type == T_DOUBLE_QUOTES))
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

static void	make_pipe(t_cmd *cmd)
{
	int	new_pipe[2];

	pipe(new_pipe);
	cmd->pipe_in = new_pipe[0];
	(cmd - 1)->pipe_out = new_pipe[1];
}

static void	make_argv(t_token **tkn_lst, t_cmd *cmd)
{
	int	i;

	if (tkn_lst && (*tkn_lst)->type == T_PIPE)
	{
		if ((cmd - 1)->name)
			make_pipe(cmd);
		*tkn_lst = (*tkn_lst)->next;
	}
	if (!(cmd - 1)->name)
		cmd->pipe_in = STDIN_FILENO;
	if (!(cmd + 1)->name)
		cmd->pipe_out = STDOUT_FILENO;
	cmd->argc = n_args(*tkn_lst);
	cmd->argv = ft_calloc(cmd->argc + 1, sizeof (char *));
	i = 0;
	while (i < cmd->argc)
	{
		cmd->argv[i++] = ft_strdup((*tkn_lst)->value);
		*tkn_lst = (*tkn_lst)->next;
	}
}

void	make_cmd(t_token *tkn_lst_array, t_cmd *cmd)
{
	make_argv(&tkn_lst_array, cmd);
	cmd->name = cmd->argv[0];
	make_redirs(tkn_lst_array, cmd);
}
