/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org.au>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:24:04 by aboehm            #+#    #+#             */
/*   Updated: 2022/05/25 13:32:26 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	n_pipes(t_token **token)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = *token;
	while (tmp)
	{
		if (tmp->type == T_PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

static bool	check_filename_after_redir(t_token *token)
{
	t_token	*next;

	while (token)
	{
		next = token->next;
		if (token->type == T_REDIR_TO_F || token->type == T_REDIR_FROM_F
			|| token->type == T_REDIR_FROM_H)
			if (!next || !(next->type == T_COMMAND || next->type
					== T_DOUBLE_QUOTES || next->type == T_SINGLE_QUOTES))
				return (false);
		token = next;
	}
	return (true);
}

//splits the token list into an array of token lists
static t_token	**split_tkn_lsts(t_token **lst)
{
	t_token	**tkn_lst_array;
	t_token	*tmp;
	int		i;
	int		numcmds;

	numcmds = n_pipes(lst) + 1;
	tkn_lst_array = malloc(sizeof(char *) * (numcmds + 1));
	tkn_lst_array[numcmds] = NULL;
	i = 0;
	tkn_lst_array[i] = *lst;
	tmp = *lst;
	while (tmp)
	{
		if (tmp->type == T_PIPE)
		{
			(*lst)->next = NULL;
			*lst = tmp;
			tkn_lst_array[++i] = *lst;
		}
		*lst = tmp;
		tmp = (*lst)->next;
	}
	return (tkn_lst_array);
}

//generate the token list for each T_COMMAND
//cmds[i + 1] because the first command is null so
// that the cmdlist can be reverse iterated through
static t_cmd	*make_cmd_lst(t_token **tkn_lst_array)
{
	int		numcmds;
	int		i;
	t_cmd	*cmds;

	numcmds = 0;
	while (tkn_lst_array[++numcmds])
		;
	cmds = ft_calloc(numcmds + 2, sizeof(t_cmd));
	cmds[0].argv = NULL;
	cmds[0].name = NULL;
	i = -1;
	while (++i < numcmds)
		make_cmd(tkn_lst_array[i], &cmds[i + 1]);
	cmds[i + 1].argv = NULL;
	cmds[i + 1].name = NULL;
	return (cmds);
}

t_cmd	*parse(t_token **lst)
{
	t_cmd	*cmds;
	t_token	**tkn_lst_array;

	if (!check_filename_after_redir(*lst))
	{
		printf("Nowhere to redirect to");
		return (NULL);
	}
	expandlst(*lst);
	tkn_lst_array = split_tkn_lsts(lst);
	cmds = make_cmd_lst(tkn_lst_array);
	free_tkn_lst_array(tkn_lst_array);
	return (cmds);
}
