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

static void	handle_cases(const char *line, t_token *token, t_lex *lex_data)
{
	if (line[(*lex_data).i] == '"' || line[(*lex_data).i] == '\'')
		handle_quote(token, lex_data);
	else if (line[(*lex_data).i] == '|')
		smoke_pipes(token, lex_data);
	else if (line[(*lex_data).i] == '>')
		redir_r(token, lex_data);
	else if (line[(*lex_data).i] == '<')
		redir_l(token, lex_data);
	else
		handle_rest(token, lex_data);
}

t_token	*lex(char const *line)
{
	t_token	*token;
	t_token	*tkn_lst;
	t_lex	lex_data;

	if (!ft_strncmp("\n", line, 2))
		return (NULL);
	lex_data.line = line;
	lex_data.i = 0;
	tkn_lst = NULL;
	skip_whitespace(&lex_data);
	while (line[lex_data.i] && line[lex_data.i + 1])
	{
		skip_whitespace(&lex_data);
		token = new_token(&tkn_lst);
		handle_cases(line, token, &lex_data);
	}
	return (tkn_lst);
}
