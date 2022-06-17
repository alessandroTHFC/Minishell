/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org.au>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:22:26 by aboehm            #+#    #+#             */
/*   Updated: 2022/05/25 13:22:27 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	define_value(char **value, char *key, t_env *local_vars)
{
	char	*env_data;

	(void)local_vars;
	env_data = search(key).data;
	if (env_data)
		*value = env_data;
	if (!*value)
		*value = "";
}

static bool	check_double_quotes(char **temp, char **key)
{
	if (ft_strchr(*temp, '"'))
	{
		*key = ft_strtrim(*temp, "\"");
		return (true);
	}
	*key = ft_strdup(*temp);
	return (false);
}

static void	restore_quote(char **value, char **temp)
{
	*temp = ft_strjoin(*value, "\"");
	free(*value);
	*value = ft_strdup(*temp);
	free(*temp);
}

void	expand(char **variable, bool dollar)
{
	t_env	local_vars[256];
	char	*value;
	char	*key;
	char	*temp;
	bool	has_quote;

	value = NULL;
	has_quote = false;
	temp = *variable;
	has_quote = check_double_quotes(&temp, &key);
	if (dollar)
		temp++;
	define_value(&value, temp, local_vars);
	free(*variable);
	free(key);
	if (has_quote)
		restore_quote(&value, &temp);
	*variable = value;
}

void	expandlst(t_token *lst)
{
	while (lst)
	{
		if (lst->type == T_SINGLE_QUOTES)
		{
			lst = lst->next;
			while (lst && lst->type != T_SINGLE_QUOTES)
				lst = lst->next;
		}
		else if ((lst->type == T_COMMAND || lst->type == T_DOUBLE_QUOTES)
			&& lst->value[1] != '\0')
		{
			expand_variables(&lst->value);
		}
		if (lst)
			lst = lst->next;
	}
}
