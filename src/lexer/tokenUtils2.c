/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apangraz <apangraz@42adel.org.au>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:22:45 by apangraz          #+#    #+#             */
/*   Updated: 2022/05/25 13:31:54 by apangraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	smoke_pipes(t_token *token, t_lex *lex_data)
{
	token->type = T_PIPE;
	token->value = "|";
	lex_data->i++;
}

void	redir_r(t_token *token, t_lex *lex_data)
{
	if (lex_data->line[lex_data->i] == '>'
		&& lex_data->line[lex_data->i + 1] == '>')
	{
		token->type = T_APPEND_RD;
		token->value = ">>";
		lex_data->i += 2;
	}
	else
	{
		token->type = T_REDIR_TO_F;
		token->value = ">";
		lex_data->i += 1;
	}
}

void	redir_l(t_token *token, t_lex *lex_data)
{
	if (lex_data->line[lex_data->i] == '<'
		&& lex_data->line[lex_data->i + 1] == '<')
	{
		token->type = T_REDIR_FROM_H;
		token->value = "<<";
		lex_data->i += 2;
		lex_data->dlim_flag = 1;
	}
	else
	{
		token->type = T_REDIR_FROM_F;
		token->value = "<";
		lex_data->i += 1;
	}
}

void	handle_rest(t_token *token, t_lex *lex_data)
{
	int	start;
	int	j;

	start = lex_data->i;
	token->type = T_COMMAND;
	j = start;
	while (lex_data->line[j] && !is_whitespace(lex_data->line[j]))
		j++;
	token->value = ft_substr(lex_data->line, start, j - start);
	lex_data->i = j;
}

void	free_tkn_lst_array(t_token **tkn_lst)
{
	void	*freeme;
	t_token	*tmp;

	tmp = *tkn_lst;
	freeme = tkn_lst;
	while (*tkn_lst)
	{
		while (*tkn_lst)
		{
			if ((*tkn_lst)->type < T_PIPE && *(*tkn_lst)->value != '\0')
				free((*tkn_lst)->value);
			(*tkn_lst)->value = NULL;
			tmp = *tkn_lst;
			*tkn_lst = (*tkn_lst)->next;
			free(tmp);
		}
		tkn_lst++;
	}
	free(freeme);
}
