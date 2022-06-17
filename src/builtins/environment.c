/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org.au>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 21:56:23 by aboehm            #+#    #+#             */
/*   Updated: 2022/04/13 21:57:06 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//printf("%s\n", search("PWD").data);
void	pwd(t_cmd *cmd)
{
	char	*wd;

	(void)cmd;
	wd = getcwd(NULL, 50);
	printf("%s\n", wd);
	free(wd);
}

void	ft_export(t_cmd *cmd)
{
	char	**vec;

	if (!cmd->argv[1])
		return ;
	vec = ft_split(cmd->argv[1], '=');
	insert(vec[0], vec[1]);
}

void	unset(t_cmd *cmd)
{
	t_env	*var;

	if (cmd->argv[1])
	{
		var = &g_env_table[hash(cmd->argv[1], ENV_SIZE)];
		free(var->key);
		free(var->data);
		var->key = NULL;
		var->data = NULL;
	}
}
